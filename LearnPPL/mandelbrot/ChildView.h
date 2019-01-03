
// ChildView.h : CChildView 类的接口
//


#pragma once

typedef std::shared_ptr<Gdiplus::Bitmap> BitmapPtr;

#define AsyncUI
#define CancelDraw
#ifndef AsyncUI
#  undef CancelDraw
#endif

// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();

	// 支持取消
#if defined CancelDraw
	afx_msg void OnSize(UINT, int, int);
	afx_msg void OnSizing(UINT, LPRECT);
	afx_msg void OnDstory();
#endif

	DECLARE_MESSAGE_MAP()

	// 画 mandelbrot 分形到指定的位图对象
	void DrawMandelbrot(BitmapPtr);
	ULONG_PTR mGdiplusToken;


#ifdef AsyncUI
	Concurrency::task_group mDrawTasks;
	Concurrency::unbounded_buffer<BitmapPtr> mMandelbortImages;
#endif


};

