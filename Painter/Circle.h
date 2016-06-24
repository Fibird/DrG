#pragma once
#include "Element.h"
#include "ElementType.h"
class CCircle :
	public CElement
{
public:
	virtual ~CCircle();
	virtual void Draw(CDC *pDC, std::shared_ptr<CElement> pElement = nullptr) override;  //���Ǹ����Draw����
	virtual void Move(const CSize &aSize) override;
	//���캯��
	CCircle(const CPoint& start, const CPoint& end, COLORREF color, int PenWidth);

protected:
	CPoint m_BottomRight;
	CCircle(); 
};

