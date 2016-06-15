#include "stdafx.h"
#include "Ellipse.h"


CEllipse::CEllipse()
{
}


CEllipse::~CEllipse()
{
}

void CEllipse::Draw(CDC * pDC, std::shared_ptr<CElement> pElement)
{
	//����һ�����ʲ���ʼ��
	CPen aPen;
	CreatePen(aPen, pElement);

	CPen* pOldPen{ pDC->SelectObject(&aPen) };

	CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

	//��Բ
	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y,
		m_BottomRight.x, m_BottomRight.y);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

CEllipse::CEllipse(const CPoint & center, const CPoint & end, COLORREF color) :
	CElement{ center, color }
{
	//������Χ��Բ�ľ���
	int halfWidth{ abs(center.x - end.x) };		//�õ����εĿ��һ��
	int halfHeight{ abs(center.y - end.y) };	//�õ����εĸߵ�һ��

	m_StartPoint = m_BottomRight = center;
	m_StartPoint.Offset(-halfWidth, -halfHeight);
	m_BottomRight.Offset(halfWidth, halfHeight);

	//��С����Ϊ2
	if (m_StartPoint.x - m_BottomRight.x < 2)
	{
		m_BottomRight.x += 2;
	}
	if (m_StartPoint.y - m_BottomRight.y < 2)
	{
		m_BottomRight.y += 2;
	}
	//����߽����
	m_EnclosingRect = CRect{ m_StartPoint, m_BottomRight };
	m_EnclosingRect.NormalizeRect();
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}
