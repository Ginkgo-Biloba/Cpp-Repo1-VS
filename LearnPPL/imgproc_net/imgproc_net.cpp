// https://msdn.microsoft.com/zh-cn/library/ff398050.aspx

#include <Windows.h>
#include <gdiplus.h>
using Gdiplus::Bitmap;
#include <agents.h>
#include <ppl.h>
using namespace Concurrency;
#include <map>
#include <iostream>
using std::wstring;


/** 同步原语，当计数为 0 时接收到信号 */
class CountDownEvent
{
public:
	explicit CountDownEvent(unsigned count = 0u)
		: cur(static_cast<long>(count))
	{
		if (cur == 0l)
			event0.set();
	}


	void signal()
	{
		if (_InterlockedDecrement(&cur) == 0l)
			event0.set();
	}

	void addCount()
	{
		if (_InterlockedIncrement(&cur) == 1l)
			event0.reset();
	}

	void wait()
	{
		event0.wait();
	}

private:
	volatile long cur; // 当前数量
	event event0; // 当计数为 0 时事件被触发
	CountDownEvent(CountDownEvent const&) {}
	CountDownEvent& operator =(CountDownEvent const&) {}
};


inline void getRGB(DWORD color, BYTE& r, BYTE& g, BYTE& b)
{
	r = static_cast<BYTE>(0xffu & (color >> 16));
	g = static_cast<BYTE>(0xffu & (color >> 8));
	b = static_cast<BYTE>(0xffu & (color));
}


inline DWORD makeColor(BYTE r, BYTE g, BYTE b)
{
	return ((DWORD)(r) << 16) | ((DWORD)(g) << 8) | (DWORD)(b);
}


/** 调用指定的 std::function 对象，以转换 GDI+ 位图对象中每个像素的颜色值
 * 使用 concurrency::parallel_for 算法并行处理位图的每一行 */
void processImage(Bitmap* bmp, std::function<void(DWORD&)> const& func)
{
	int const width = bmp->GetWidth();
	int const height = bmp->GetHeight();

	// 锁住位图
	Gdiplus::BitmapData data;
	Gdiplus::Rect roi(0, 0, width, height);
	bmp->LockBits(&roi, Gdiplus::ImageLockModeWrite, PixelFormat32bppRGB, &data);
	DWORD* ptr = static_cast<DWORD*>(data.Scan0);

	// 调用处理函数
	parallel_for(0, height, [&func, ptr, width](int y) -> void
	{
		DWORD* cur = ptr + y * width;
		for (int x = 0; x < width; ++x)
			func(cur[x]);
	});

	// 解锁位图
	bmp->UnlockBits(&data);
}

/** 转换为灰度图 */
Bitmap* grayScale(Bitmap* bmp)
{
	processImage(bmp, [](DWORD& color)
	{
		BYTE r, g, b;
		getRGB(color, r, g, b);
		r = static_cast<BYTE>(r * 0.299 + g * 0.587 + b * 0.114 + 0.5);
		color = makeColor(r, r, r);
	});
	return bmp;
}


/** 对给定的图像应用棕色色调 */
Bitmap* sepiaTone(Bitmap* bmp)
{
	processImage(bmp, [](DWORD& color) -> void
	{
		BYTE r0, g0, b0;
		getRGB(color, r0, g0, b0);

		WORD r1 = static_cast<WORD>(r0 * 0.393 + g0 * 0.769 + b0 * 0.189);
		WORD g1 = static_cast<WORD>(r0 * 0.349 + g0 * 0.686 + b0 * 0.168);
		WORD b1 = static_cast<WORD>(r0 * 0.272 + g0 * 0.534 + b0 * 0.131);

		color = makeColor(min(0xffu, r1), min(0xffu, g1), min(0xffu, b1));
	});
	return bmp;
}


/** 应用给定的颜色遮罩到图像的每个像素 */
Bitmap* colorMask(Bitmap* bmp, DWORD mask)
{
	processImage(bmp, [mask](DWORD& color) -> void { color &= mask; });
	return bmp;
}


/** 讲给定的图片变暗 */
Bitmap* darken(Bitmap* bmp, float ratio)
{
	if (ratio < 0.f || ratio > 1.f)
	{
		std::wcerr << L"invalid argument: ratio = " << ratio << std::endl;
		abort();
	}

	processImage(bmp, [ratio](DWORD& color) -> void
	{
		BYTE r, g, b;
		getRGB(color, r, g, b);
		r = static_cast<BYTE>(r * ratio + 0.5f);
		g = static_cast<BYTE>(g * ratio + 0.5f);
		b = static_cast<BYTE>(b * ratio + 0.5f);
		color = makeColor(r, g, b);
	});
	return bmp;
}


/** 使用 concurrency::combinable 对象计算图像的主色 */
DWORD getMainColor(Bitmap* bmp)
{
	combinable<unsigned> red, green, blue;

	processImage(bmp, [&red, &green, &blue](DWORD& color) -> void
	{
		BYTE r, g, b;
		getRGB(color, r, g, b);
		if ((r > g) && (r > b))
			++(red.local());
		else if ((g > r) && (g > b))
			++(green.local());
		else
			++(blue.local());
	});

	unsigned const r = red.combine(std::plus<unsigned>());
	unsigned const g = green.combine(std::plus<unsigned>());
	unsigned const b = blue.combine(std::plus<unsigned>());
	if (r + r > g + b)
		return (0xffu << 16);
	else if (g + g > r + b)
		return (0xffu << 8);
	else
		return 0xffu;
}


/** 检索编码器的指定 MIME 类型的类标识符。 使用该函数检索位图的编码器 */
int getEncoderClsid(WCHAR const* format, CLSID* pclsid)
{
	using Gdiplus::ImageCodecInfo;
	UINT num = 0u; // 图像编码器的数量
	UINT size = 0u; // 图像编码器的尺寸，以字节为单位
	Gdiplus::GetImageEncodersSize(&num, &size);
	if (!size) return -1;

	ImageCodecInfo* codec = static_cast<ImageCodecInfo*>(malloc(size));
	if (!codec) return -2;

	GetImageEncoders(num, size, codec);
	for (UINT n = 0; n < num; ++n)
	{
		if (!wcscmp(codec[n].MimeType, format))
		{
			*pclsid = codec[n].Clsid;
			free(codec);
			return n;
		}
	}

	free(codec);
	return -3;
}


/** 创建对指定目录中每个 JPEG (.jpg) 图像执行图像处理的异步消息块网络
 * 此网络会执行以下图像处理操作：
 * 1. 将 Tom 创作的所有图像都转换为灰阶
 * 2. 对于以红色为主色的任何图像，删除绿色和蓝色组件，然后调暗图像
 * 3. 对其他所有图像应用棕褐色调
 * 此网络仅应用符合其中一个条件的第一个图像处理操作
 * 例如，如果图像由 Tom 创作而且以红色为主色，则只会将该图像转换为灰阶
 * 网络执行每个图像处理操作后，它会将图像作为位图 (.bmp) 文件保存到磁盘
 * 以下步骤演示如何创建该图像处理网络，并将该网络应用到指定目录中所有 JPEG 图像 */
void batchImage(wstring const& directory)
{
	// 记住正在处理的图像数量，并在处理结束后向主线程发信号
	CountDownEvent active(0);
	// 映射位图对象到他们的原始文件名
	std::map<Bitmap*, wstring> mapBmpName;

	/// 创建网络节点

	// 从磁盘读取位图
	transformer<wstring, Bitmap*> load( \
		[&mapBmpName](wstring const& fileName) -> Bitmap*
	{
		Bitmap* bmp = new Bitmap(fileName.c_str());
		if (bmp != nullptr)
			mapBmpName.emplace(bmp, fileName);
		return bmp;
	});

	// 保存位图对象
	unbounded_buffer<Bitmap*> bitmaps;

	// 转换由 Tom 创作的图像到灰度
	transformer<Bitmap*, Bitmap*> gray( \
		[](Bitmap* bmp) -> Bitmap* { return grayScale(bmp); },
		nullptr,
		[](Bitmap* bmp) -> bool
	{
		using Gdiplus::PropertyItem;
		if (!bmp) return false;

		// 检索艺术家名字
		UINT size = bmp->GetPropertyItemSize(PropertyTagArtist);
		if (!size) return false; // 没有艺术家属性

		PropertyItem* artist = static_cast<PropertyItem*>(malloc(size));
		bmp->GetPropertyItem(PropertyTagArtist, size, artist);
		char* ans = strstr(static_cast<char*>(artist->value), "Tom");
		free(artist);

		return ans != nullptr;
	});

	// 如果红色是主颜色，那么移除绿色和蓝色
	transformer<Bitmap*, Bitmap*> mask( \
		[](Bitmap* bmp) -> Bitmap* { return colorMask(bmp, 0xffu << 16); },
		nullptr,
		[](Bitmap* bmp) -> bool
	{
		if (bmp == nullptr) return false;
		return getMainColor(bmp) == (0xffu << 16);
	});

	// 变暗给定的图像
	transformer<Bitmap*, Bitmap*> dark( \
		[](Bitmap* bmp) -> Bitmap* { return darken(bmp, 0.4f); });

	// 应用棕色色调
	transformer<Bitmap*, Bitmap*> sepia( \
		[](Bitmap* bmp) -> Bitmap* { return sepiaTone(bmp); },
		nullptr,
		[](Bitmap* bmp) -> bool { return bmp != nullptr; });

	// 保存位图到磁盘
	transformer<Bitmap*, Bitmap*> save([&mapBmpName](Bitmap* bmp) -> Bitmap*
	{
		// 替换后缀名为 .bmp
		wstring name = mapBmpName[bmp];
		while (name.back() != '.') name.pop_back();
		name += L"bmp";

		CLSID clsid;
		getEncoderClsid(L"image/bmp", &clsid);
		bmp->Save(name.c_str(), &clsid);
		return bmp;
	});

	// 删除位图对象
	transformer<Bitmap*, Bitmap*> del( \
		[](Bitmap* bmp) -> Bitmap* { delete bmp; return nullptr; });

	// 减少事件计数
	call<Bitmap*> decrease([&active](Bitmap*) -> void { active.signal(); });

	/// 连接网络
	load.link_target(&bitmaps);

	bitmaps.link_target(&gray);
	bitmaps.link_target(&mask);
	mask.link_target(&dark);
	bitmaps.link_target(&sepia);
	bitmaps.link_target(&decrease);

	gray.link_target(&save);
	dark.link_target(&save);
	sepia.link_target(&save);

	save.link_target(&del);
	del.link_target(&decrease);

	/// 将目录中的每个文件发送到网络头

	wstring pattern = directory + L"\\*";
	WIN32_FIND_DATA fileFindData;
	HANDLE find = FindFirstFileW(pattern.c_str(), &fileFindData);
	if (find == INVALID_HANDLE_VALUE)
	{
		std::wcerr << L"INVALID_HANDLE_VALUE" << std::endl;
		return;
	}
	do
	{
		if (fileFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;

		wstring file = fileFindData.cFileName;
		// 只处理 jpg 文件
		if (file.rfind(L".jpg") == file.length() - 4u)
		{
			wstring fullpath = directory + L"\\";
			fullpath += file;
			active.addCount();
			send(load, fullpath);
		}
	} while (FindNextFileW(find, &fileFindData) != 0);

	FindClose(find);
	active.wait();
}


int wmain()
{
	using namespace Gdiplus;
	GdiplusStartupInput startIn;
	ULONG_PTR token;

	// 初始化 gdi+
	GdiplusStartup(&token, &startIn, nullptr);

	// 执行图像处理，更改这里的路径
	batchImage(L"..\\images");

	// 关闭 gdi+
	GdiplusShutdown(token);
}
