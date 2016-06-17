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

void CEllipse::Move(const CSize & aSize)
{
	m_StartPoint += aSize;
	m_BottomRight += aSize;
	m_EnclosingRect += aSize;
}

CEllipse::CEllipse(const CPoint & center, const CPoint & end, COLORREF color, int PenWidth) :
	CElement{ center, color, PenWidth }
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
	int width = { PenWidth == 0 ? 1 : PenWidth };
	//����߽����
	m_EnclosingRect = CRect{ m_StartPoint, m_BottomRight };
	m_EnclosingRect.NormalizeRect();
	m_EnclosingRect.InflateRect(width, width);
}
