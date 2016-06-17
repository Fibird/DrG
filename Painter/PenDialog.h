#pragma once


// CPenDialog dialog

class CPenDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPenDialog)

public:
	CPenDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPenDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PENWIDTH_DLG };
#endif
	int m_PenWidth;		//记录目前的笔宽
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CSpinButtonCtrl m_Spin;	
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};
