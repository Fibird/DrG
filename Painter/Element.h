#pragma once

// CElement command target

class CElement : public CObject
{
protected:
	CPoint m_StartPoint;
	int m_PenWidth;		//�ʿ�
	COLORREF m_Color;	//ͼ����ɫ
	CRect m_EnclosingRect;	//��Χͼ�εľ���
public:
	//CElement();
	virtual ~CElement();
	virtual void Draw(CDC *pDC) {}	//����Draw����Ϊ�麯��

	//��ð�Χͼ�εľ���
	const CRect& GetEnclosingRect() const { return m_EnclosingRect; }
protected:
	CElement();
	CElement(const CPoint& start, COLORREF color, int penWidth = 1);
	//����һ����
	void CreatePen(CPen& aPen)
	{
		if (!aPen.CreatePen(PS_SOLID, m_PenWidth, m_Color))
		{
			//�ʴ���ʧ��
			AfxMessageBox(_T("�ʴ���ʧ�ܣ�"), MB_OK);
			AfxAbort();
		}
	}
};


