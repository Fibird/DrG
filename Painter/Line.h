#pragma once
#include "Element.h"
class CLine :
	public CElement
{
public:
	virtual ~CLine();
	virtual void Draw(CDC *pDC) override;	//���Ǹ����Draw()����
	//���캯��
	CLine(const CPoint& start, const CPoint& end, COLORREF color);

protected:
	CPoint m_EndPoint;		//�ߵ�ĩβ��

protected:
	CLine();
};

