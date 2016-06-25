#pragma once
#include "Element.h"
class CEllipse :
	public CElement
{
	DECLARE_SERIAL(CEllipse)
public:
	virtual ~CEllipse();
	virtual void Draw(CDC *pDC, std::shared_ptr<CElement> pElement = nullptr) override;	//���Ǹ����Draw����
	virtual void Move(const CSize &aSize) override;
	//���캯��
	CEllipse(const CPoint& center, const CPoint& end, COLORREF color, int PenWidth);

protected:
	CPoint m_BottomRight;
	CEllipse();
public:
	virtual void Serialize(CArchive& ar);
};

