#pragma once
#include "Element.h"
class CRectangle :
	public CElement
{
public:
	virtual ~CRectangle();
	virtual void Draw(CDC *pDC) override;	//��ʾһ�����Σ����Ǹ����Draw����

	//���캯��
	CRectangle(const CPoint& start, const CPoint& end, COLORREF color);

protected:
	CPoint m_BottomRight;
	CRectangle();
};

