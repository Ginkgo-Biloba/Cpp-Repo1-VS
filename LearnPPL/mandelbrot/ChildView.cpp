
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "mandelbrot.h"
#include "ChildView.h"

// 在调试版本中，注释下面 3 行可阻止应用程序使用与 GDI+ 不兼容的 DEBUG_NEW 分配器
// #ifdef _DEBUG
// #  define new DEBUG_NEW
// #endif

inline unsigned getGray(unsigned i, unsigned k)
{
	// return (i >= k) ? 255u :
	return (unsigned)(sqrtf((float)(i & k) / k) * 255.f);
}

/////////////////// ScopeGuard ///////////////////
/** 实现 RAII 模式，当析构的时候执行指定函数 */
class ScopeGuard
{
public:
	explicit ScopeGuard(std::function<void()>&& func)
		: mFunc(std::forward<std::function<void()>>(func))
	{}

	/** 断开函数链接 */
	void dismiss()
	{
		mFunc = nullptr;
	}

	~ScopeGuard()
	{
		if (!mFunc) return;

		try { mFunc(); }
		catch (...) { std::terminate(); }
	}

private:
	std::function<void()> mFunc;

	// 删除复制和赋值函数
	ScopeGuard(ScopeGuard const&) {}
	ScopeGuard& operator =(ScopeGuard const&) {}
};


/////////////////// CChildView ////////////////////

CChildView::CChildView()
{
	// 初始化 GDI+
	Gdiplus::GdiplusStartupInput startInput;
	Gdiplus::GdiplusStartup(&mGdiplusToken, &startInput, NULL);
}

CChildView::~CChildView()
{
	// 关闭 GDI+
	Gdiplus::GdiplusShutdown(mGdiplusToken);
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
#ifdef CancelDraw
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_DESTROY()
#endif
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	// TODO: 在此处添加消息处理程序代码
	using Gdiplus::Bitmap;

#ifdef AsyncUI
	// 如果缓冲区包含图像，那么画图
	BitmapPtr pBitmap;
	if (Concurrency::try_receive(mMandelbortImages, pBitmap))
	{
		if (pBitmap) // 画图
		{
			Gdiplus::Graphics g(dc);
			g.DrawImage(pBitmap.get(), 0, 0);
		}
	}
	else
	{
		RECT rect;
		GetClientRect(&rect);
		mDrawTasks.run([rect, this]() -> void
		{ DrawMandelbrot(BitmapPtr(new Bitmap(rect.right, rect.bottom))); });
	}
#else
	// 得到客户端尺寸
	RECT rect;
	GetClientRect(&rect);

	// 创建相同尺寸的位图，并绘图
	BitmapPtr pBitmap(new Bitmap(rect.right, rect.bottom));
	if (pBitmap)
	{
		DrawMandelbrot(pBitmap);
		Gdiplus::Graphics g(dc);
		g.DrawImage(pBitmap.get(), 0, 0);
	}
#endif

	// 不要为绘制消息而调用 CWnd::OnPaint()
}

#ifdef CancelDraw

/** 取消任何现有绘制任务，并针对更新后的客户端窗口大小创建一个新的绘制任务 */
void CChildView::OnSize(UINT, int cx, int cy)
{
	// 窗口尺寸已经改变，取消任何存在的绘图任务
	mDrawTasks.cancel();
	// 等待已经执行的任务结束
	mDrawTasks.wait();

	// 如果新尺寸不是 0，那么异步创建新的绘图任务
	if (cx && cy)
	{
		mDrawTasks.run([cx, cy, this]() -> void
		{ DrawMandelbrot(BitmapPtr(new Gdiplus::Bitmap(cx, cy))); });
	}
}

/** 取消任何现有绘制任务 */
void CChildView::OnSizing(UINT, LPRECT)
{
	// 窗口尺寸正在改变，取消存在的绘图任务
	mDrawTasks.cancel();
}

/** 取消任何现有绘制任务 */
void CChildView::OnDstory()
{
	mDrawTasks.cancel();
	mDrawTasks.wait();
}

#endif

/** 向指定的 Bitmap 对象绘制 Mandelbrot 分形 */
void CChildView::DrawMandelbrot(BitmapPtr pBitmap)
{
	using namespace Gdiplus;
	using namespace Concurrency;
	if (!pBitmap) return;

	UINT const width = pBitmap->GetWidth();
	UINT const height = pBitmap->GetHeight();
	if (!(width && height)) return;

	// 锁住位图数据
	BitmapData bitmap;
	Rect rect(0, 0, width, height);
	pBitmap->LockBits(&rect, ImageLockModeWrite, PixelFormat32bppRGB, &bitmap);
#ifdef CancelDraw
	ScopeGuard bitmapGuader([&pBitmap, &bitmap]() -> void
	{ pBitmap->UnlockBits(&bitmap); });
#endif
	unsigned* data = reinterpret_cast<unsigned*>(bitmap.Scan0);

	// 复平面边界的实部和虚部
	float minRe = -2.1f, maxRe = 2.1f, minIm = -2.1f, maxIm = 2.1f;

	// 映射图像坐标到复平面坐标
	float scaleRe = (maxRe - minRe) / (width - 1u);
	float scaleIm = (maxIm - minIm) / (height - 1u);

	// 每个点的最大迭代次数
	unsigned const maxIteration = 0xfffu; // 12 位精度

	// http://www.matrix67.com/blog/archives/292
	// http://www.matrix67.com/blog/archives/4570
	// 计算每个点是否在 Mandelbrot 集里面
#ifdef AsyncUI
	parallel_for(0u, height, [&](UINT r) -> void
#else
	for (UINT r = 0u; r < height; ++r)
#endif
	{
		unsigned* D = data + r * width;
		float y0 = maxIm - r * scaleIm;

		for (UINT c = 0u; c < width; ++c)
		{
			float x0 = minRe + c * scaleRe;

			unsigned iter = 0;
			float x = x0, y = y0, xsq, ysq;
			for (; iter < maxIteration; ++iter)
			{
				xsq = x * x; ysq = y * y;
				if (xsq + ysq >= 4.f)
					break;
				float newx = xsq - ysq + x0;
				y = 2.f * x * y + y0;
				x = newx;
			}

			if (iter == maxIteration) // 在集合里面
				D[c] = 0u;
			else // 不在集合里面
			{
				unsigned cr, cg, cb;
				// cr = iter > 0x3fu ? 0xffu : iter << 2; iter >>= 4;
				// cg = iter > 0x3fu ? 0xffu : iter << 2; iter >>= 4;
				// cb = iter > 0x3fu ? 0xffu : iter << 2; iter >>= 4;
				cb = getGray(iter, maxIteration);
				cg = getGray(iter << 2, maxIteration);
				cr = getGray(iter << 4, maxIteration);
				D[c] = (cr << 16) | (cg << 8) | cb;
			}
		}
	}
#ifdef AsyncUI
	);
#endif

	// 释放数据锁
	pBitmap->UnlockBits(&bitmap);
#ifdef CancelDraw
	bitmapGuader.dismiss();
#endif

#ifdef Async_UI
	// 添加位图对象到图像队列
	send(mMandelbortImages, pBitmap);
	// 发送绘图消息给 UI 线程
	PostMessage(WM_PAINT);
	// 使工作区无效
	InvalidateRect(NULL, FALSE);
#endif
}

