#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}


CLine::~CLine()
{
}

void CLine::Draw(CDC * pDC, std::shared_ptr<CElement> pElement)
{
	//创建笔并初始化
	CPen aPen;
	CreatePen(aPen, pElement);

	CPen *pOldPen{ pDC->SelectObject(&aPen) };

	//画线
	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);

	//保存以前的画笔
	pDC->SelectObject(pOldPen);
}

CLine::CLine(const CPoint& start, const CPoint& end, COLORREF color, int PenWidth) :
	CElement{ start, color, PenWidth }, m_EndPoint{ end }
{
	//计算界定线条的矩形
	m_EnclosingRect = CRect{ start, end };
	//确保边界矩形是规范化的
	m_EnclosingRect.NormalizeRect();
	//使边界矩形的线宽至少为1
	int width{ PenWidth == 0 ? 1 : PenWidth };
	//定义线条的边界矩形
	m_EnclosingRect.InflateRect(width, width);
}

void CLine::Move(const CSize & aSize)
{
	m_StartPoint += aSize;
	m_EndPoint += aSize;
	m_EnclosingRect += aSize;
}
