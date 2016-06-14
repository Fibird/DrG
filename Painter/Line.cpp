#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}


CLine::~CLine()
{
}

void CLine::Draw(CDC * pDC)
{
	//�����ʲ���ʼ��
	CPen aPen;
	CreatePen(aPen);

	CPen *pOldPen{ pDC->SelectObject(&aPen) };

	//����
	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);

	//������ǰ�Ļ���
	pDC->SelectObject(pOldPen);
}

CLine::CLine(const CPoint& start, const CPoint& end, COLORREF color) :
	CElement{ start, color }, m_EndPoint{ end }
{
	//����綨�����ľ���
	m_EnclosingRect = CRect{ start, end };
	//ȷ���߽�����ǹ淶����
	m_EnclosingRect.NormalizeRect();
	//���������ı߽����
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}
