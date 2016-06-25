
// PainterView.h : interface of the CPainterView class
//

#pragma once
#include "atltypes.h"
#include <memory>
#include "Element.h"

class CPainterView : public CScrollView
{
protected: // create from serialization only
	CPainterView();
	DECLARE_DYNCREATE(CPainterView)

// Attributes
public:
	CPainterDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPainterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//����һ����ͼ��
	std::shared_ptr<CElement> CreateElement() const;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	CPoint m_FirstPoint;	//��¼���ͼ�εĵ�һ����
	CPoint m_SecondPoint;	//��¼���ͼ�εĵڶ�����
	CPoint m_CursorPos;		//���λ��
	CPoint m_FirstPos;		//��ǰ��λ��
	BOOL use_eraser{ FALSE };		//����Ƿ�ʹ����Ƥ
	BOOL m_MoveMode{ FALSE };		//����Ƿ����ƶ�ģʽ
	BOOL use_filler{ FALSE };
	//�洢��ʱͼ��
	std::shared_ptr<CElement> m_pTempElement;
	//ָ��ѡ�е�ͼ��
	std::shared_ptr<CElement> m_pSelected;
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnElementMove();
	afx_msg void OnElementDelete();
	afx_msg void OnToolsEraser();
	afx_msg void OnToolsFiller();
protected:
	void MoveElement(CClientDC& aDC, const CPoint& point);
public:
	afx_msg void OnElementCancel();
	afx_msg void OnToolsPen();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateToolsEraser(CCmdUI *pCmdUI);
	afx_msg void OnUpdateToolsFiller(CCmdUI *pCmdUI);
	afx_msg void OnUpdateToolsPen(CCmdUI *pCmdUI);
	afx_msg void OnSettingsDrawingscale();
};

#ifndef _DEBUG  // debug version in PainterView.cpp
inline CPainterDoc* CPainterView::GetDocument() const
   { return reinterpret_cast<CPainterDoc*>(m_pDocument); }
#endif

