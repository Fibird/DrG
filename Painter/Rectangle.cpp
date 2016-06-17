#include "stdafx.h"
#include "Rectangle.h"
#include <algorithm>

CRectangle::CRectangle()
{
}


CRectangle::~CRectangle()
{
}

void CRectangle::Draw(CDC * pDC, std::shared_ptr<CElement> pElement)
{
	//����һ�����ʲ���ʼ��
	CPen aPen;
	CreatePen(aPen, pElement);

	//ѡ��һ�����ʺͿջ�ˢ
	//Ŀǰ���ò�����ˢ
	CPen *pOldPen{ pDC->SelectObject(&aPen) };
	CBrush *pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

	//���������
	pDC->Rectangle(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
	//����ɻ����뻭ˢ
	pDC->SelectObject(pOldPen);	
	pDC->SelectObject(pOldBrush);
}

void CRectangle::Move(const CSize & aSize)
{
	m_StartPoint += aSize;
	m_BottomRight += aSize;
	m_EnclosingRect += aSize;
}

CRectangle::CRectangle(const CPoint & start, const CPoint & end, COLORREF color, int PenWidth) :
	CElement{ start, color, PenWidth }
{
	//�淶�����εĵ�
	m_StartPoint = CPoint{ (std::min)(start.x, end.x), (std::min)(start.y, end.y) };
	m_BottomRight = CPoint{ (std::max)(start.x, end.x), (std::max)(start.y, end.y) };

	//ȷ�����εĸ߶ȺͿ������Ϊ2
	if ((m_BottomRight.x - m_StartPoint.x) < 2)
	{
		m_BottomRight.x = m_StartPoint.x + 2;
	}
	if ((m_BottomRight.y - m_StartPoint.y) < 2)
	{
		m_BottomRight.y = m_StartPoint.y + 2;
	}
	int width = { PenWidth == 0 ? 1 : PenWidth };
	//������εı߽����
	m_EnclosingRect = CRect{ m_StartPoint, m_BottomRight };
	m_EnclosingRect.InflateRect(width, width);
}
