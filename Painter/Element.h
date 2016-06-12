#pragma once

// CElement command target

class CElement : public CObject
{
protected:
	CPoint m_StartPoint;
	int m_PenWidth;		//width of pen
	COLORREF m_Color;	//Color of an element
	CRect m_EnclosingRect;	//Rectangle enclosing an element
public:
	//CElement();
	virtual ~CElement();
	virtual void Draw(CDC *pDC) {}	//Virtual draw operation

	//Get the element enclosing rectangle
	const CRect& GetEnclosingRect() const { return m_EnclosingRect; }
protected:
	CElement();
	CElement(const CPoint& start, COLORREF color, int penWidth = 1);
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


