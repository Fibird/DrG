#include "stdafx.h"
#include "Ellipse.h"


CEllipse::CEllipse()
{
}


CEllipse::~CEllipse()
{
}

void CEllipse::Draw(CDC * pDC)
{
	// Create a pen for this object and initialize it
	CPen aPen;
	CreatePen(aPen);

	CPen* pOldPen{ pDC->SelectObject(&aPen) };  // Select the pen

												// Select a null brush
	CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

	//Draw the circle
	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y,
		m_BottomRight.x, m_BottomRight.y);

	pDC->SelectObject(pOldPen);                // Restore the old pen
	pDC->SelectObject(pOldBrush);              // Restore the old brush
}

CEllipse::CEllipse(const CPoint & center, const CPoint & end, COLORREF color) :
	CElement{ center, color }
{
	//Create the rectangle enclosing the ellipse
	int halfWidth{ abs(center.x - end.x) };		//Half the width of the defining rectangle
	int halfHeight{ abs(center.y - end.y) };	//Half the height of the defining rectangle

	m_StartPoint = m_BottomRight = center;
	m_StartPoint.Offset(-halfWidth, -halfHeight);
	m_BottomRight.Offset(halfWidth, halfHeight);

	//Points must differ by 2 in x and y for valid rectangle
	if (m_StartPoint.x - m_BottomRight.x < 2)
	{
		m_BottomRight.x += 2;
	}
	if (m_StartPoint.y - m_BottomRight.y < 2)
	{
		m_BottomRight.y += 2;
	}

	m_EnclosingRect = CRect{ m_StartPoint, m_BottomRight };
	m_EnclosingRect.NormalizeRect();
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}
