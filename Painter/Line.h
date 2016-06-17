#pragma once
#include "Element.h"
#include <memory>

class CLine :
	public CElement
{
public:
	virtual ~CLine();
	virtual void Draw(CDC *pDC, std::shared_ptr<CElement> pElement = nullptr) override;	//覆盖父类的Draw()函数
	//构造函数
	CLine(const CPoint& start, const CPoint& end, COLORREF color, int penWidth);
	virtual void Move(const CSize &aSize) override;
protected:
	CPoint m_EndPoint;		//线的末尾点

protected:
	CLine();
};

