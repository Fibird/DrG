#include "stdafx.h"
#include "Curve.h"
#include <algorithm>

CCurve::CCurve()
{
}


CCurve::~CCurve()
{
}

void CCurve::Draw(CDC * pDC, std::shared_ptr<CElement> pElement)
{
	//创建画笔并初始化
	CPen aPen;
	CreatePen(aPen, pElement);

	CPen* pOldPen{ pDC->SelectObject(&aPen) };

	pDC->MoveTo(m_StartPoint);
	//每增加一个点就画一条线
	for (auto& point : m_Points)
		pDC->LineTo(point);

	pDC->SelectObject(pOldPen);
}

CCurve::CCurve(const CPoint & first, const CPoint & second, COLORREF color) :
	CElement{ first, color }
{
	//把点压入到vector中
	m_Points.push_back(second);
	//计算边界矩形
	m_EnclosingRect = CRect{
		(std::min)(first.x, second.x), (std::min)(first.y, second.y),
		(std::max)(first.x, second.x), (std::max)(first.y, second.y) };
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

//把曲线的每一段都保存起来，并以增量方式重新计算
void CCurve::AddSegment(const CPoint& point)
{
	m_Points.push_back(point);	//把新点压栈 
	//根据新点重新计算边界矩形
	m_EnclosingRect.DeflateRect(m_PenWidth, m_PenWidth);
	m_EnclosingRect = CRect{ (std::min)(point.x, m_EnclosingRect.left),
		(std::min)(point.y, m_EnclosingRect.top),
		(std::max)(point.x, m_EnclosingRect.right),
		(std::max)(point.y, m_EnclosingRect.bottom) };
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}
