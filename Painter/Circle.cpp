#include "stdafx.h"
#include "Circle.h"
#include <cmath>

CCircle::CCircle()
{
}


CCircle::~CCircle()
{
}

void CCircle::Draw(CDC * pDC, std::shared_ptr<CElement> pElement)
{
	//����һ����Ȼ���ʼ��
	CPen aPen;
	CreatePen(aPen, pElement);
	CPen *pOldPen{ pDC->SelectObject(&aPen) };  //ѡ��һ����

	//Ŀǰ���ò�����ˢ������ѡ��һ���յĻ��ʣ�Ȼ��ǿ��ת����CBrush*��
	CBrush *pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

	//ʹ�ö���ͳ�����ȵ���Բ������Բ
	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
	//������ǰ�ıʺͻ���
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

CCircle::CCircle(const CPoint& start, const CPoint& end, COLORREF color) :
	CElement{ start, color }
{
	//����Բ�İ뾶
	long radius{ static_cast<long> (sqrt(
		static_cast<double>((end.x - start.x) * (end.x - start.x) +
		(end.y - start.y) * (end.y - start.y)))) };
	if (radius < 1L)
	{
		radius = 1L;	//Բ�İ뾶�������1
	}

	//����MM_TEXTģʽ�°�ΧԲ�ľ��ε�����
	m_StartPoint = CPoint{ start.x - radius, start.y - radius };
	m_BottomRight = CPoint{ start.x + radius, start.y + radius };

	//����߽����
	m_EnclosingRect = CRect{ m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y };
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}
