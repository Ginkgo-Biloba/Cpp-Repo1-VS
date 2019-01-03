
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once

typedef std::shared_ptr<Gdiplus::Bitmap> BitmapPtr;

#define AsyncUI
#define CancelDraw
#ifndef AsyncUI
#  undef CancelDraw
#endif

// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();

	// ֧��ȡ��
#if defined CancelDraw
	afx_msg void OnSize(UINT, int, int);
	afx_msg void OnSizing(UINT, LPRECT);
	afx_msg void OnDstory();
#endif

	DECLARE_MESSAGE_MAP()

	// �� mandelbrot ���ε�ָ����λͼ����
	void DrawMandelbrot(BitmapPtr);
	ULONG_PTR mGdiplusToken;


#ifdef AsyncUI
	Concurrency::task_group mDrawTasks;
	Concurrency::unbounded_buffer<BitmapPtr> mMandelbortImages;
#endif


};

