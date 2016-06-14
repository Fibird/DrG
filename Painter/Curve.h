#pragma once
#include "Element.h"
#include <vector>

class CCurve :
	public CElement
{
public:
	virtual ~CCurve();
	virtual void Draw(CDC *pDC) override;  //���Ǹ����Draw����

	//���캯��
	CCurve(const CPoint& first, const CPoint& second, COLORREF color);

	void AddSegment(const CPoint& point);		//������ߵ�һ��
protected:
	std::vector<CPoint> m_Points;	//�洢���ߵĵ�
	CCurve();
};

