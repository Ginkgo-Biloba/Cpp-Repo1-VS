// https://docs.microsoft.com/zh-cn/previous-versions/visualstudio/visual-studio-2010/dd984044(v%3dvs.100)

// mandelbrot.h : mandelbrot Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CmandelbrotApp:
// �йش����ʵ�֣������ mandelbrot.cpp
//

class CmandelbrotApp : public CWinApp
{
public:
	CmandelbrotApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CmandelbrotApp theApp;
