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
}


BEGIN_MESSAGE_MAP(CPenDialog, CDialogEx)
END_MESSAGE_MAP()


// CPenDialog message handlers


void CPenDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}
