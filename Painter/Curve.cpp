#include "stdafx.h"
#include "Curve.h"
#include <algorithm>

CCurve::CCurve()
{
}


CCurve::~CCurve()
{
}

void CCurve::Draw(CDC * pDC)
{
	//�������ʲ���ʼ��
	CPen aPen;
	CreatePen(aPen);

	CPen* pOldPen{ pDC->SelectObject(&aPen) };

	pDC->MoveTo(m_StartPoint);
	//ÿ����һ����ͻ�һ����
	for (auto& point : m_Points)
		pDC->LineTo(point);

	pDC->SelectObject(pOldPen);
}

CCurve::CCurve(const CPoint & first, const CPoint & second, COLORREF color) :
	CElement{ first, color }
{
	//�ѵ�ѹ�뵽vector��
	m_Points.push_back(second);
	//����߽����
	m_EnclosingRect = CRect{
		(std::min)(first.x, second.x), (std::min)(first.y, second.y),
		(std::max)(first.x, second.x), (std::max)(first.y, second.y) };
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

//�����ߵ�ÿһ�ζ���������������������ʽ���¼���
void CCurve::AddSegment(const CPoint& point)
{
	m_Points.push_back(point);	//���µ�ѹջ 
	//�����µ����¼���߽����
	m_EnclosingRect.DeflateRect(m_PenWidth, m_PenWidth);
	m_EnclosingRect = CRect{ (std::min)(point.x, m_EnclosingRect.left),
		(std::min)(point.y, m_EnclosingRect.top),
		(std::max)(point.x, m_EnclosingRect.right),
		(std::max)(point.y, m_EnclosingRect.bottom) };
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}
