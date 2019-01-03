
// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "mandelbrot.h"
#include "ChildView.h"

// �ڵ��԰汾�У�ע������ 3 �п���ֹӦ�ó���ʹ���� GDI+ �����ݵ� DEBUG_NEW ������
// #ifdef _DEBUG
// #  define new DEBUG_NEW
// #endif

inline unsigned getGray(unsigned i, unsigned k)
{
	// return (i >= k) ? 255u :
	return (unsigned)(sqrtf((float)(i & k) / k) * 255.f);
}

/////////////////// ScopeGuard ///////////////////
/** ʵ�� RAII ģʽ����������ʱ��ִ��ָ������ */
class ScopeGuard
{
public:
	explicit ScopeGuard(std::function<void()>&& func)
		: mFunc(std::forward<std::function<void()>>(func))
	{}

	/** �Ͽ��������� */
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

	// ɾ�����ƺ͸�ֵ����
	ScopeGuard(ScopeGuard const&) {}
	ScopeGuard& operator =(ScopeGuard const&) {}
};


/////////////////// CChildView ////////////////////

CChildView::CChildView()
{
	// ��ʼ�� GDI+
	Gdiplus::GdiplusStartupInput startInput;
	Gdiplus::GdiplusStartup(&mGdiplusToken, &startInput, NULL);
}

CChildView::~CChildView()
{
	// �ر� GDI+
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



// CChildView ��Ϣ�������

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
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	// TODO: �ڴ˴������Ϣ����������
	using Gdiplus::Bitmap;

#ifdef AsyncUI
	// �������������ͼ����ô��ͼ
	BitmapPtr pBitmap;
	if (Concurrency::try_receive(mMandelbortImages, pBitmap))
	{
		if (pBitmap) // ��ͼ
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
	// �õ��ͻ��˳ߴ�
	RECT rect;
	GetClientRect(&rect);

	// ������ͬ�ߴ��λͼ������ͼ
	BitmapPtr pBitmap(new Bitmap(rect.right, rect.bottom));
	if (pBitmap)
	{
		DrawMandelbrot(pBitmap);
		Gdiplus::Graphics g(dc);
		g.DrawImage(pBitmap.get(), 0, 0);
	}
#endif

	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}

#ifdef CancelDraw

/** ȡ���κ����л������񣬲���Ը��º�Ŀͻ��˴��ڴ�С����һ���µĻ������� */
void CChildView::OnSize(UINT, int cx, int cy)
{
	// ���ڳߴ��Ѿ��ı䣬ȡ���κδ��ڵĻ�ͼ����
	mDrawTasks.cancel();
	// �ȴ��Ѿ�ִ�е��������
	mDrawTasks.wait();

	// ����³ߴ粻�� 0����ô�첽�����µĻ�ͼ����
	if (cx && cy)
	{
		mDrawTasks.run([cx, cy, this]() -> void
		{ DrawMandelbrot(BitmapPtr(new Gdiplus::Bitmap(cx, cy))); });
	}
}

/** ȡ���κ����л������� */
void CChildView::OnSizing(UINT, LPRECT)
{
	// ���ڳߴ����ڸı䣬ȡ�����ڵĻ�ͼ����
	mDrawTasks.cancel();
}

/** ȡ���κ����л������� */
void CChildView::OnDstory()
{
	mDrawTasks.cancel();
	mDrawTasks.wait();
}

#endif

/** ��ָ���� Bitmap ������� Mandelbrot ���� */
void CChildView::DrawMandelbrot(BitmapPtr pBitmap)
{
	using namespace Gdiplus;
	using namespace Concurrency;
	if (!pBitmap) return;

	UINT const width = pBitmap->GetWidth();
	UINT const height = pBitmap->GetHeight();
	if (!(width && height)) return;

	// ��סλͼ����
	BitmapData bitmap;
	Rect rect(0, 0, width, height);
	pBitmap->LockBits(&rect, ImageLockModeWrite, PixelFormat32bppRGB, &bitmap);
#ifdef CancelDraw
	ScopeGuard bitmapGuader([&pBitmap, &bitmap]() -> void
	{ pBitmap->UnlockBits(&bitmap); });
#endif
	unsigned* data = reinterpret_cast<unsigned*>(bitmap.Scan0);

	// ��ƽ��߽��ʵ�����鲿
	float minRe = -2.1f, maxRe = 2.1f, minIm = -2.1f, maxIm = 2.1f;

	// ӳ��ͼ�����굽��ƽ������
	float scaleRe = (maxRe - minRe) / (width - 1u);
	float scaleIm = (maxIm - minIm) / (height - 1u);

	// ÿ���������������
	unsigned const maxIteration = 0xfffu; // 12 λ����

	// http://www.matrix67.com/blog/archives/292
	// http://www.matrix67.com/blog/archives/4570
	// ����ÿ�����Ƿ��� Mandelbrot ������
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

			if (iter == maxIteration) // �ڼ�������
				D[c] = 0u;
			else // ���ڼ�������
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

	// �ͷ�������
	pBitmap->UnlockBits(&bitmap);
#ifdef CancelDraw
	bitmapGuader.dismiss();
#endif

#ifdef Async_UI
	// ���λͼ����ͼ�����
	send(mMandelbortImages, pBitmap);
	// ���ͻ�ͼ��Ϣ�� UI �߳�
	PostMessage(WM_PAINT);
	// ʹ��������Ч
	InvalidateRect(NULL, FALSE);
#endif
}

