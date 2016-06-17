#pragma once
#include "Element.h"
class CRectangle :
	public CElement
{
public:
	virtual ~CRectangle();
	virtual void Draw(CDC *pDC, std::shared_ptr<CElement> pElement = nullptr) override;	//��ʾһ�����Σ����Ǹ����Draw����
	virtual void Move(const CSize &aSize) override;
	//���캯��
	CRectangle(const CPoint& start, const CPoint& end, COLORREF color, int PenWidth);

protected:
	CPoint m_BottomRight;
	CRectangle();
};

