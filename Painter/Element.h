#pragma once

// CElement command target

class CElement : public CObject
{
protected:
	CPoint m_StartPoint;
	int m_PenWidth;		//笔宽
	COLORREF m_Color;	//图形颜色
	CRect m_EnclosingRect;	//包围图形的矩形
public:
	//CElement();
	virtual ~CElement();
	virtual void Draw(CDC *pDC) {}	//这里Draw类型为虚函数

	//获取界定图形占用区域的矩形
	const CRect& GetEnclosingRect() const { return m_EnclosingRect; }
protected:
	CElement();
	CElement(const CPoint& start, COLORREF color, int penWidth = 1);
	//创建一个笔
	void CreatePen(CPen& aPen)
	{
		if (!aPen.CreatePen(PS_SOLID, m_PenWidth, m_Color))
		{
			//笔创建失败
			AfxMessageBox(_T("笔创建失败！"), MB_OK);
			AfxAbort();
		}
	}
};


