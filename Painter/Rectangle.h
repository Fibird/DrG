#pragma once
#include "Element.h"
class CRectangle :
	public CElement
{
public:
	//CRectangle();
	virtual ~CRectangle();
	virtual void Draw(CDC *pDC) override;	//Display a rectangle

	//Constructor for a rectangle object
	CRectangle(const CPoint& start, const CPoint& end, COLORREF color);

protected:
	CPoint m_BottomRight;
	CRectangle();
};

