#pragma once
#include <memory>

//������ɫ
static const COLORREF SELECT_COLOR{ RGB(255, 0, 180) };

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
	virtual void Draw(CDC *pDC, std::shared_ptr<CElement> pElement = nullptr) {}	//����Draw����Ϊ�麯��
	virtual void Move(const CSize &aSize) {}
	//��ȡ�綨ͼ��ռ������ľ���
	const CRect& GetEnclosingRect() const { return m_EnclosingRect; }
protected:
	CElement();
	CElement(const CPoint& start, COLORREF color, int penWidth = 1);
	//����һ����
	void CreatePen(CPen& aPen, std::shared_ptr<CElement> pElement = nullptr)
	{
		if (!aPen.CreatePen(PS_SOLID, m_PenWidth, this == pElement.get() ? SELECT_COLOR : m_Color))
		{
			//�ʴ���ʧ��
			AfxMessageBox(_T("�ʴ���ʧ�ܣ�"), MB_OK);
			AfxAbort();
		}
	}
};


