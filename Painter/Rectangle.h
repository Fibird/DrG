#pragma once
#include "Element.h"
class CRectangle :
	public CElement
{
public:
	virtual ~CRectangle();
	virtual void Draw(CDC *pDC, std::shared_ptr<CElement> pElement = nullptr) override;	//显示一个矩形，覆盖父类的Draw函数
	virtual void Move(const CSize &aSize) override;
	//构造函数
	CRectangle(const CPoint& start, const CPoint& end, COLORREF color, int PenWidth);

protected:
	CPoint m_BottomRight;
	CRectangle();
};

