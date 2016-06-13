
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

IMPLEMENT_DYNCREATE(CPainterView, CView)

BEGIN_MESSAGE_MAP(CPainterView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
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
	//»æÖÆÍ¼Ïñ
	for (auto it = pDoc->begin(); it != pDoc->end(); ++it)
		for (const auto& pElement : *pDoc)
		{
			if (pDC->RectVisible(pElement->GetEnclosingRect()))
			{
				pElement->Draw(pDC);
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
	//Get a pointer to the document for this view
	CPainterDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);		//Vertify the pointer is good

	//Get the current element color
	COLORREF color{ static_cast<COLORREF>(pDoc->GetElementColor()) };

	//Now select the element using the type stored in the document
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
		ReleaseCapture();		//Stop capturing mouse messages
	}
	//Make sure there is a element
	if (m_pTempElement)
	{
		//Add the element pointer to the paint
		GetDocument()->AddElement(m_pTempElement);
		InvalidateRect(&m_pTempElement->GetEnclosingRect());
		m_pTempElement.reset();
	}
	//CView::OnLButtonUp(nFlags, point);
}


void CPainterView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_FirstPoint = point;	//Record the cursor position
	SetCapture();			//Capture subsequent mouse message
	//Must use ReleaseCapture in OnLButtonUp!!!
	//CView::OnLButtonDown(nFlags, point);
}


void CPainterView::OnMouseMove(UINT nFlags, CPoint point)
{
	//Define a device context object for the view
	CClientDC aDC{ this };
	if ((nFlags & MK_LBUTTON) && (this == GetCapture()))
	{
		m_SecondPoint = point;
		if (m_pTempElement)
		{
			//ÅÐ¶ÏÊÇ·ñÊÇÇúÏß
			if (ElementType::CURVE == GetDocument()->GetElementType())
			{
				//Is curve, then add a segment to the existing curve
				std::dynamic_pointer_cast<CCurve>(m_pTempElement)->AddSegment(m_SecondPoint);
				m_pTempElement->Draw(&aDC);
				return;
			}
			else
			{
				//Is not curve, so redraw the old element
				aDC.SetROP2(R2_NOTXORPEN);		//Set the drawing mode
				m_pTempElement->Draw(&aDC);		//Redraw the old element to erase it
			}
		}
		//Create a 
		m_pTempElement = CreateElement();
		m_pTempElement->Draw(&aDC);
	}
	//CView::OnMouseMove(nFlags, point);
}
