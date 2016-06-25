// Element.cpp : implementation file
//

#include "stdafx.h"
#include "Painter.h"
#include "Element.h"

IMPLEMENT_SERIAL(CElement, CObject, VERSION_NUMBER)
// CElement

CElement::CElement()
{
}

CElement::CElement(const CPoint & start, COLORREF color, int penWidth) :
	m_StartPoint{ start }, m_PenWidth{ penWidth }, m_Color{ color }
{
}

CElement::~CElement()
{
}


// CElement member functions


void CElement::Serialize(CArchive& ar)
{
	//������û����serialize����
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{	
		ar << m_Color;
		ar << m_EnclosingRect;
		ar << m_PenWidth;
		ar << m_StartPoint;
		ar << static_cast<int>(type);
		ar << Filler;
	}
	else
	{	// loading code
		ar >> m_Color;
		ar >> m_EnclosingRect;
		ar >> m_PenWidth;
		ar >> m_StartPoint;
		int t;
		ar >> t;
		type = static_cast<ElementType>(t);
		ar >> Filler;
	}
}
