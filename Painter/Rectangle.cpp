#include "stdafx.h"
#include "Rectangle.h"
#include <algorithm>

IMPLEMENT_SERIAL(CRectangle, CElement, VERSION_NUMBER)
CRectangle::CRectangle()
{
}


CRectangle::~CRectangle()
{
}

void CRectangle::Draw(CDC * pDC, std::shared_ptr<CElement> pElement)
{
	//创建一个画笔并初始化
	CPen aPen;
	CreatePen(aPen, pElement);
	CBrush aBrush;
	CreateBrush(aBrush, pElement);
	CPen *pOldPen{ pDC->SelectObject(&aPen) };
	CBrush *pOldBrush;
	//如果按下填充按钮则选择实心画刷，否则选择空画刷
	if (Filler)
	{
		pOldBrush = pDC->SelectObject(&aBrush);
	}
	else
	{
		pOldBrush = dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));
	}
	//画这个矩形
	pDC->Rectangle(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
	//保存旧画笔与画刷
	pDC->SelectObject(pOldPen);	
	pDC->SelectObject(pOldBrush);
}

void CRectangle::Move(const CSize & aSize)
{
	m_StartPoint += aSize;
	m_BottomRight += aSize;
	m_EnclosingRect += aSize;
}

CRectangle::CRectangle(const CPoint & start, const CPoint & end, COLORREF color, int PenWidth) :
	CElement{ start, color, PenWidth }
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
	int width = { PenWidth == 0 ? 1 : PenWidth };
	//定义矩形的边界矩形
	m_EnclosingRect = CRect{ m_StartPoint, m_BottomRight };
	m_EnclosingRect.InflateRect(width, width);
}


void CRectangle::Serialize(CArchive& ar)
{
	CElement::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar << m_BottomRight;
	}
	else
	{	// loading code
		ar >> m_BottomRight;
	}
}
