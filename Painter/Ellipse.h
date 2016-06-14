#pragma once
#include "Element.h"
class CEllipse :
	public CElement
{
public:
	virtual ~CEllipse();
	virtual void Draw(CDC *pDC) override;	//覆盖父类的Draw函数

	//构造函数
	CEllipse(const CPoint& center, const CPoint& end, COLORREF color);

protected:
	CPoint m_BottomRight;
	CEllipse();
};

