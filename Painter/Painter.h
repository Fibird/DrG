
// Painter.h : main header file for the Painter application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPainterApp:
// See Painter.cpp for the implementation of this class
//

class CPainterApp : public CWinApp
{
public:
	CPainterApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPainterApp theApp;
