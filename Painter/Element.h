#pragma once
#include <memory>

//高亮颜色
static const COLORREF SELECT_COLOR{ RGB(255, 0, 180) };

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
	virtual void Draw(CDC *pDC, std::shared_ptr<CElement> pElement = nullptr) {}	//这里Draw类型为虚函数
	virtual void Move(const CSize &aSize) {}
	//获取界定图形占用区域的矩形
	const CRect& GetEnclosingRect() const { return m_EnclosingRect; }
protected:
	CElement();
	CElement(const CPoint& start, COLORREF color, int penWidth = 1);
	//创建一个笔
	void CreatePen(CPen& aPen, std::shared_ptr<CElement> pElement = nullptr)
	{
		if (!aPen.CreatePen(PS_SOLID, m_PenWidth, this == pElement.get() ? SELECT_COLOR : m_Color))
		{
			//笔创建失败
			AfxMessageBox(_T("笔创建失败！"), MB_OK);
			AfxAbort();
		}
	}
};


