#include "stdafx.h"
#include "Circle.h"
#include <cmath>

IMPLEMENT_SERIAL(CCircle, CElement, VERSION_NUMBER)
CCircle::CCircle()
{
}


CCircle::~CCircle()
{
}

void CCircle::Draw(CDC * pDC, std::shared_ptr<CElement> pElement)
{
	//创建一个笔然后初始化
	CPen aPen;
	CBrush aBrush;
	CreatePen(aPen, pElement);
	CPen *pOldPen{ pDC->SelectObject(&aPen) };  //选择一个笔
	CBrush *pOldBrush;
	//如果按下填充按钮则选择实心画刷，否则选择空画刷
	if (Filler)
	{
		CreateBrush(aBrush, pElement);
		pOldBrush = pDC->SelectObject(&aBrush);
	}
	else
	{
		pOldBrush = dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));
	}
	
	//使用短轴和长轴相等的椭圆来绘制圆
	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
	//保存以前的笔和画笔
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
	//计算圆的半径
	long radius{ static_cast<long> (sqrt(
		static_cast<double>((end.x - start.x) * (end.x - start.x) +
		(end.y - start.y) * (end.y - start.y)))) };
	if (radius < 1L)
	{
		radius = 1L;	//圆的半径必须大于1
	}

	//计算MM_TEXT模式下包围圆的矩形的两点
	m_StartPoint = CPoint{ start.x - radius, start.y - radius };
	m_BottomRight = CPoint{ start.x + radius, start.y + radius };
	int width{ PenWidth == 0 ? 1 : PenWidth };
	//定义边界矩形
	m_EnclosingRect = CRect{ m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y };
	m_EnclosingRect.InflateRect(width, width);
}


void CCircle::Serialize(CArchive& ar)
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
