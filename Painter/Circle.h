#pragma once
#include "Element.h"
class CCircle :
	public CElement
{
public:
	virtual ~CCircle();
	virtual void Draw(CDC *pDC) override;  //覆盖父类的Draw函数

	//构造函数
	CCircle(const CPoint& start, const CPoint& end, COLORREF color);

protected:
	CPoint m_BottomRight;
	CCircle();
};

