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
	CBrush aBrush;
	CreatePen(aPen, pElement);
	CPen *pOldPen{ pDC->SelectObject(&aPen) };  //ѡ��һ����
	CBrush *pOldBrush;
	//���������䰴ť��ѡ��ʵ�Ļ�ˢ������ѡ��ջ�ˢ
	if (Filler)
	{
		CreateBrush(aBrush, pElement);
		pOldBrush = pDC->SelectObject(&aBrush);
	}
	else
	{
		pOldBrush = dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));
	}
	
	//ʹ�ö���ͳ�����ȵ���Բ������Բ
	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
	//������ǰ�ıʺͻ���
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

void CCircle::Move(const CSize & aSize)
{
	m_StartPoint += aSize;
	m_BottomRight += aSize;
	m_EnclosingRect += aSize;
}

CCircle::CCircle(const CPoint& start, const CPoint& end, COLORREF color, int PenWidth) :
	CElement{ start, color, PenWidth }
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
	int width{ PenWidth == 0 ? 1 : PenWidth };
	//����߽����
	m_EnclosingRect = CRect{ m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y };
	m_EnclosingRect.InflateRect(width, width);
}
