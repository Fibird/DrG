#pragma once
#include "Element.h"
class CLine :
	public CElement
{
public:
	//CLine();
	virtual ~CLine();
	virtual void Draw(CDC *pDC) override;	//why?
	// Constructor for a line object
	CLine(const CPoint& start, const CPoint& end, COLORREF color);

protected:
	CPoint m_EndPoint;		//End point of line

protected:
	CLine();
};

