#pragma once
#include "Element.h"
class CEllipse :
	public CElement
{
public:
	virtual ~CEllipse();
	virtual void Draw(CDC *pDC, std::shared_ptr<CElement> pElement = nullptr) override;	//���Ǹ����Draw����
	virtual void Move(const CSize &aSize) override;
	//���캯��
	CEllipse(const CPoint& center, const CPoint& end, COLORREF color);

protected:
	CPoint m_BottomRight;
	CEllipse();
};

