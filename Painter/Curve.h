#pragma once
#include "Element.h"
#include <vector>

class CCurve :
	public CElement
{
public:
	//CCurve();
	virtual ~CCurve();
	virtual void Draw(CDC *pDC) override;  //Display a curve

	//Constructor for curve object
	CCurve(const CPoint& first, const CPoint& second, COLORREF color);

	void AddSegment(const CPoint& point);		//Add a segment to the curve
protected:
	std::vector<CPoint> m_Points;
	CCurve();
};

