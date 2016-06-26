#pragma once
#include "afxcmn.h"


// CScaleDialog dialog

class CScaleDialog : public CDialog
{
	DECLARE_DYNAMIC(CScaleDialog)

public:
	CScaleDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScaleDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCALE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	int m_Scale{ 1 };
	virtual BOOL OnInitDialog();
protected:
	CSliderCtrl m_slider;
};
