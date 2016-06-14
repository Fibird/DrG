#include "stdafx.h"
#include "Rectangle.h"
#include <algorithm>

CRectangle::CRectangle()
{
}


CRectangle::~CRectangle()
{
}

void CRectangle::Draw(CDC * pDC)
{
	//创建一个画笔并初始化
	CPen aPen;
	CreatePen(aPen);

	//选择一个画笔和空画刷
	//目前还用不到画刷
	CPen *pOldPen{ pDC->SelectObject(&aPen) };
	CBrush *pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

	//画这个矩形
	pDC->Rectangle(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
	//保存旧画笔与画刷
	pDC->SelectObject(pOldPen);	
	pDC->SelectObject(pOldBrush);
}

CRectangle::CRectangle(const CPoint & start, const CPoint & end, COLORREF color) :
	CElement{ start, color }
{
	//规范化矩形的点
	m_StartPoint = CPoint{ (std::min)(start.x, end.x), (std::min)(start.y, end.y) };
	m_BottomRight = CPoint{ (std::max)(start.x, end.x), (std::max)(start.y, end.y) };

	//确保矩形的高度和宽度至少为2
	if ((m_BottomRight.x - m_StartPoint.x) < 2)
	{
		m_BottomRight.x = m_StartPoint.x + 2;
	}
	if ((m_BottomRight.y - m_StartPoint.y) < 2)
	{
		m_BottomRight.y = m_StartPoint.y + 2;
	}

	//定义矩形的边界矩形
	m_EnclosingRect = CRect{ m_StartPoint, m_BottomRight };
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}
