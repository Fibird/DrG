#pragma once
#include "Element.h"
class CCircle :
	public CElement
{
public:
	//CCircle();
	virtual ~CCircle();
	virtual void Draw(CDC *pDC) override;  //display a circle

	//Constructor for a circle object
	CCircle(const CPoint& start, const CPoint& end, COLORREF color);

protected:
	CPoint m_BottomRight;
	CCircle();
};

