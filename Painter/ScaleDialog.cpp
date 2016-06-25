// ScaleDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Painter.h"
#include "ScaleDialog.h"
#include "afxdialogex.h"


// CScaleDialog dialog

IMPLEMENT_DYNAMIC(CScaleDialog, CDialog)

CScaleDialog::CScaleDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SCALE_DLG, pParent)
	, m_Scale(0)
{

}

CScaleDialog::~CScaleDialog()
{
}

void CScaleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SCALE, m_Scale);
	DDV_MinMaxInt(pDX, m_Scale, 1, 8);
	DDX_Control(pDX, IDC_SCALE_SLIDER, m_slider);
}


BEGIN_MESSAGE_MAP(CScaleDialog, CDialog)
END_MESSAGE_MAP()


// CScaleDialog message handlers


BOOL CScaleDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here
	m_slider.SetRange(1, 8);
	//m_slider.SetPos(50);
	m_slider.SetBuddy(GetDlgItem(IDC_SCALE));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
