#pragma once
#include "Element.h"
class CRectangle :
	public CElement
{
public:
	virtual ~CRectangle();
	virtual void Draw(CDC *pDC) override;	//显示一个矩形，覆盖父类的Draw函数

	//构造函数
	CRectangle(const CPoint& start, const CPoint& end, COLORREF color);

protected:
	CPoint m_BottomRight;
	CRectangle();
};

