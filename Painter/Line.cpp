#include "stdafx.h"
#include "Line.h"

IMPLEMENT_SERIAL(CLine, CElement, VERSION_NUMBER)

CLine::CLine()
{
}


CLine::~CLine()
{
}

void CLine::Draw(CDC * pDC, std::shared_ptr<CElement> pElement)
{
	//�����ʲ���ʼ��
	CPen aPen;
	CreatePen(aPen, pElement);

	CPen *pOldPen{ pDC->SelectObject(&aPen) };

	//����
	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);

	//������ǰ�Ļ���
	pDC->SelectObject(pOldPen);
}

CLine::CLine(const CPoint& start, const CPoint& end, COLORREF color, int PenWidth) :
	CElement{ start, color, PenWidth }, m_EndPoint{ end }
{
	//����綨�����ľ���
	m_EnclosingRect = CRect{ start, end };
	//ȷ���߽�����ǹ淶����
	m_EnclosingRect.NormalizeRect();
	//ʹ�߽���ε��߿�����Ϊ1
	int width{ PenWidth == 0 ? 1 : PenWidth };
	//���������ı߽����
	m_EnclosingRect.InflateRect(width, width);
}

void CLine::Move(const CSize & aSize)
{
	m_StartPoint += aSize;
	m_EndPoint += aSize;
	m_EnclosingRect += aSize;
}


void CLine::Serialize(CArchive& ar)
{
	CElement::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar << m_EndPoint;
	}
	else
	{	// loading code
		ar >> m_EndPoint;
	}
}
