#pragma once
#include "Element.h"
#include "ElementType.h"
class CCircle :
	public CElement
{
public:
	virtual ~CCircle();
	virtual void Draw(CDC *pDC, std::shared_ptr<CElement> pElement = nullptr) override;  //覆盖父类的Draw函数
	virtual void Move(const CSize &aSize) override;
	//构造函数
	CCircle(const CPoint& start, const CPoint& end, COLORREF color, int PenWidth);

protected:
	CPoint m_BottomRight;
	CCircle(); 
};

