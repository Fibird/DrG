#pragma once
#include "Element.h"
#include <vector>

class CCurve :
	public CElement
{
	DECLARE_SERIAL(CCurve)
public:
	virtual ~CCurve();
	virtual void Draw(CDC *pDC, std::shared_ptr<CElement> pElement = nullptr) override;  //���Ǹ����Draw����
	virtual void Move(const CSize &aSize) override;
	//���캯��
	CCurve(const CPoint& first, const CPoint& second, COLORREF color, int PenWidth);

	void AddSegment(const CPoint& point);		//������ߵ�һ��
protected:
	std::vector<CPoint> m_Points;	//�洢���ߵĵ�
	CCurve();
public:
	virtual void Serialize(CArchive& ar);
};

