#pragma once
#include "Element.h"
class CLine :
	public CElement
{
public:
	//CLine();
	virtual ~CLine();
	virtual void Draw(CDC *pDC) override;	//why?
	// Constructor for a line object
	CLine(const CPoint& start, const CPoint& end, COLORREF aColor);

protected:
	CPoint m_EndPoint;		//End point of line

protected:
	CLine();
public:

	//Create a pen
	void CreatePen(CPen& aPen)
	{
		if (!aPen.CreatePen(PS_SOLID, m_PenWidth, m_Color))
		{
			//Pen creation failed
			AfxMessageBox(_T("Pen creation failed."), MB_OK);
			AfxAbort();
		}
	}
};

