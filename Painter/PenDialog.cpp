// PenDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Painter.h"
#include "PenDialog.h"
#include "afxdialogex.h"


// CPenDialog dialog

IMPLEMENT_DYNAMIC(CPenDialog, CDialogEx)

CPenDialog::CPenDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PENWIDTH_DLG, pParent), m_PenWidth{}
{

}

CPenDialog::~CPenDialog()
{
}

void CPenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PENWIDTH, m_PenWidth);
	DDV_MinMaxInt(pDX, m_PenWidth, 0, 10);
	DDX_Control(pDX, IDC_SPIN_PENWIDTH, m_Spin);
}


BEGIN_MESSAGE_MAP(CPenDialog, CDialogEx)
END_MESSAGE_MAP()


// CPenDialog message handlers


void CPenDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}


BOOL CPenDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_Spin.SetRange(0, 10);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
