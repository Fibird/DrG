
// PainterView.cpp : implementation of the CPainterView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Painter.h"
#endif

#include "PainterDoc.h"
#include "PainterView.h"
#include "Curve.h"
#include "Circle.h"
#include "Line.h"
#include "Rectangle.h"
#include "Ellipse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPainterView

IMPLEMENT_DYNCREATE(CPainterView, CScrollView)

BEGIN_MESSAGE_MAP(CPainterView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ELEMENT_MOVE, &CPainterView::OnElementMove)
	ON_COMMAND(ID_ELEMENT_DELETE, &CPainterView::OnElementDelete)
	ON_COMMAND(ID_TOOLS_ERASER, &CPainterView::OnToolsEraser)
	ON_COMMAND(ID_TOOLS_FILLER, &CPainterView::OnToolsFiller)
END_MESSAGE_MAP()

// CPainterView construction/destruction

CPainterView::CPainterView()
	: m_FirstPoint{CPoint{}}
{
	// TODO: add construction code here

}

CPainterView::~CPainterView()
{
}

BOOL CPainterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPainterView drawing

void CPainterView::OnDraw(CDC* pDC)
{
	CPainterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//����ͼ��
	for (auto it = pDoc->begin(); it != pDoc->end(); ++it)	//ʹ���˵�����
		for (const auto& pElement : *pDoc)
		{
			//ȷ���������ε��κβ����Ǵ�����ʾ������֮�������
			if (pDC->RectVisible(pElement->GetEnclosingRect()))
			{
				pElement->Draw(pDC, m_pSelected);
			}
		}
}


// CPainterView printing

BOOL CPainterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPainterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPainterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CPainterView diagnostics

#ifdef _DEBUG
void CPainterView::AssertValid() const
{
	CView::AssertValid();
}

void CPainterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

std::shared_ptr<CElement> CPainterView::CreateElement() const
{
	//��ȡָ��ǰ��ͼ�ĵ���ָ��
	CPainterDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);		//Vertify the pointer is good

	//��õ�ǰͼ�ε���ɫ
	COLORREF color{ static_cast<COLORREF>(pDoc->GetElementColor()) };

	//���ݴ洢���ĵ��е�ͼ��������ѡ��ͼ��
	switch (pDoc->GetElementType())
	{
	case ElementType::RECTANGLE:
		return std::make_shared<CRectangle>(m_FirstPoint, m_SecondPoint, color);
	case ElementType::CIRCLE:
		return std::make_shared<CCircle>(m_FirstPoint, m_SecondPoint, color);
	case ElementType::CURVE:
		return std::make_shared<CCurve>(m_FirstPoint, m_SecondPoint, color);
	case ElementType::LINE:
		return std::make_shared<CLine>(m_FirstPoint, m_SecondPoint, color);
	case ElementType::ELLIPSE:
		return std::make_shared<CEllipse>(m_FirstPoint, m_SecondPoint, color);
	default:
		AfxMessageBox(_T("Bad Element code"), MB_OK);
		AfxAbort();
		return nullptr;
	}
}

CPainterDoc* CPainterView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPainterDoc)));
	return (CPainterDoc*)m_pDocument;
}
#endif //_DEBUG


// CPainterView message handlers


void CPainterView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		ReleaseCapture();		//ֹͣ���������Ϣ
	}

	if (m_pTempElement)
	{
		CRect aRect{ m_pTempElement->GetEnclosingRect() };	//��ȡ�߽����
		//�����յ�ͼ����ӵ��ĵ���������ʾ
		GetDocument()->AddElement(m_pTempElement);

		CClientDC aDC{ this };
		OnPrepareDC(&aDC);
		aDC.LPtoDP(aRect);
		InvalidateRect(aRect);
		m_pTempElement.reset();
	}
}


void CPainterView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC aDC{ this };	//�����豸������
	OnPrepareDC(&aDC);		//����ԭ��λ��
	aDC.DPtoLP(&point);		//ת��Ϊ�߼�����
	m_FirstPoint = point;	//��¼����λ��
	SetCapture();			//�������������Ϣ
	//ע�������OnLButtonUp���ͷ���Ϣ
}


void CPainterView::OnMouseMove(UINT nFlags, CPoint point)
{
	//�����豸������
	CClientDC aDC{ this };
	OnPrepareDC(&aDC);
	aDC.DPtoLP(&point);
	//����Ҫ�ж��Ƿ����������Լ��Ƿ�ɹ���׽���
	if ((nFlags & MK_LBUTTON) && (this == GetCapture()))
	{
		m_SecondPoint = point;
		if (m_pTempElement)
		{
			//�ж��Ƿ�������
			if (ElementType::CURVE == GetDocument()->GetElementType())
			{
				//��������߾���Ӻ����ĵ�
				std::dynamic_pointer_cast<CCurve>(m_pTempElement)->AddSegment(m_SecondPoint);
				m_pTempElement->Draw(&aDC);
				return;
			}
			else
			{
				//�����������
				aDC.SetROP2(R2_NOTXORPEN);		//���û�ͼģʽ��ʵ�֡���Ƥ�����
				m_pTempElement->Draw(&aDC);		//�ػ�ͼ�񣬲�������ͼ��
			}
		}
		m_pTempElement = CreateElement();
		m_pTempElement->Draw(&aDC);
	}
	else
	{
		auto pOldSelected = m_pSelected;
		//��λ����λ��
		m_pSelected = GetDocument()->FindElement(point);
		if (m_pSelected != pOldSelected)
		{
			if (m_pSelected)
			{
				GetDocument()->UpdateAllViews(nullptr, 0, m_pSelected.get());
			}
			if (pOldSelected)
			{
				GetDocument()->UpdateAllViews(nullptr, 0, pOldSelected.get());
			}
		}
	}
}


void CPainterView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (pHint)
	{
		//�����豸������
		CClientDC aDC{ this };
		OnPrepareDC(&aDC);		//����ԭ��λ��
		//��ȡ�߽���Σ���ת��Ϊ�ͻ�������
		CRect aRect{ dynamic_cast<CElement*>(pHint)->GetEnclosingRect() };
		aDC.LPtoDP(&aRect);
		InvalidateRect(aRect);
	}
	else
	{
		InvalidateRect(nullptr);
	}
}


void CPainterView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	//�ĵ��Ĵ�С
	//CSize Docsize{ 2000, 20000 };
	CSize Docsize{ 3000, 3000 };
	//����ӳ��ģʽ���ĵ��Ĵ�С
	//SetScrollSizes(MM_TEXT, Docsize, CSize{ 500, 500 }, CSize{ 20, 20 });
	SetScrollSizes(MM_LOENGLISH, Docsize);
}


void CPainterView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	
	//�����Ҽ��˵�
	menu.LoadMenuW(IDR_RIGHTCLICK_MENU);
	
	CMenu *pContext{};
	
	ElementColor color{ GetDocument()->GetElementColor() };
	ElementType element{ GetDocument()->GetElementType() };

	if (m_pSelected)
	{
		pContext = menu.GetSubMenu(0);

		//��ǲ˵���
		menu.CheckMenuItem(ID_COLOR_BLACK, (ElementColor::BLACK == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_RED, (ElementColor::RED == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_GREEN, (ElementColor::GREEN == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_BLUE, (ElementColor::BLUE == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);

		menu.CheckMenuItem(ID_ELEMENT_LINE, (ElementType::LINE == element ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_RECTANGLE, (ElementType::RECTANGLE == element ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_CIRCLE, (ElementType::CURVE == element ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_ELLIPSE, (ElementType::ELLIPSE == element ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	}
	else
	{
		pContext = menu.GetSubMenu(1);
		
		//��ǲ˵���
		menu.CheckMenuItem(ID_COLOR_BLACK, (ElementColor::BLACK == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_RED, (ElementColor::RED == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_GREEN, (ElementColor::GREEN == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_BLUE, (ElementColor::BLUE == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);

		menu.CheckMenuItem(ID_ELEMENT_LINE, (ElementType::LINE == element ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_RECTANGLE, (ElementType::RECTANGLE == element ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_CIRCLE, (ElementType::CURVE == element ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_ELLIPSE, (ElementType::ELLIPSE == element ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	}
	//ȷ��pContext��Ϊ��
	ASSERT(pContext != nullptr);
	pContext->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}


void CPainterView::OnElementMove()
{
	CClientDC aDC(this);
	OnPrepareDC(&aDC);
	GetCursorPos(&m_CursorPos);		//��ȡ���λ��
	ScreenToClient(&m_CursorPos);
	aDC.DPtoLP(&m_CursorPos);
	m_FirstPoint = m_CursorPos;
	m_MoveMode = TRUE;
}


void CPainterView::OnElementDelete()
{
	//ɾ��ѡ�е�ͼ��
	if (m_pSelected)
	{
		GetDocument()->DeleteElement(m_pSelected);
		m_pSelected.reset();
	}
}


void CPainterView::OnToolsEraser()
{
	// TODO: Add your command handler code here
	if (m_pSelected)
	{
		if (MK_LBUTTON)
		{
			GetDocument()->DeleteElement(m_pSelected);
			m_pSelected.reset();
		}
	}
}


void CPainterView::OnToolsFiller()
{
	// TODO: Add your command handler code here
}
