#pragma once
#include "Element.h"
class CEllipse :
	public CElement
{
public:
	//CEllipse();
	virtual ~CEllipse();
	virtual void Draw(CDC *pDC) override;	//Display a ellipse

	//Constructor for ellipse
	CEllipse(const CPoint& center, const CPoint& end, COLORREF color);

protected:
	CPoint m_BottomRight;
	CEllipse();
};

