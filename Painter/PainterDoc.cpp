
// PainterDoc.cpp : implementation of the CPainterDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Painter.h"
#endif

#include "PainterDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPainterDoc

IMPLEMENT_DYNCREATE(CPainterDoc, CDocument)

BEGIN_MESSAGE_MAP(CPainterDoc, CDocument)
	ON_COMMAND(ID_ELEMENT_LINE, &CPainterDoc::OnElementLine)
	ON_COMMAND(ID_ELEMENT_RECTANGLE, &CPainterDoc::OnElementRectangle)
	ON_COMMAND(ID_ELEMENT_CIRCLE, &CPainterDoc::OnElementCircle)
	ON_COMMAND(ID_ELEMENT_CURVE, &CPainterDoc::OnElementCurve)
	ON_COMMAND(ID_ELEMENT_ELLIPSE, &CPainterDoc::OnElementEllipse)
	ON_COMMAND(ID_COLOR_BLACK, &CPainterDoc::OnColorBlack)
	ON_COMMAND(ID_COLOR_RED, &CPainterDoc::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CPainterDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CPainterDoc::OnColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CPainterDoc::OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CPainterDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CPainterDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CPainterDoc::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, &CPainterDoc::OnUpdateElementLine)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, &CPainterDoc::OnUpdateElementRectangle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CIRCLE, &CPainterDoc::OnUpdateElementCircle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CURVE, &CPainterDoc::OnUpdateElementCurve)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_ELLIPSE, &CPainterDoc::OnUpdateElementEllipse)
END_MESSAGE_MAP()


// CPainterDoc construction/destruction

CPainterDoc::CPainterDoc()
{
	// TODO: add one-time construction code here

}

CPainterDoc::~CPainterDoc()
{
}

BOOL CPainterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPainterDoc serialization

void CPainterDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPainterDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPainterDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPainterDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPainterDoc diagnostics

#ifdef _DEBUG
void CPainterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPainterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPainterDoc commands


void CPainterDoc::OnElementLine()
{
	// Set type of element to line
	m_Element = ElementType::LINE;
}


void CPainterDoc::OnElementRectangle()
{
	// Set type of element to rectangle
	m_Element = ElementType::RECTANGLE;
}


void CPainterDoc::OnElementCircle()
{
	// Set type of element to circle
	m_Element = ElementType::CIRCLE;
}


void CPainterDoc::OnElementCurve()
{
	// Set type of element to curve
	m_Element = ElementType::CURVE;
}


void CPainterDoc::OnElementEllipse()
{
	// Set type of element to ellipse
	m_Element = ElementType::ELLIPSE;
}


void CPainterDoc::OnColorBlack()
{
	// Set color of element to black
	m_Color = ElementColor::BLACK;
}


void CPainterDoc::OnColorRed()
{
	// Set color of element to red
	m_Color = ElementColor::RED;
}


void CPainterDoc::OnColorGreen()
{
	// Set color of element to green
	m_Color = ElementColor::GREEN;
}


void CPainterDoc::OnColorBlue()
{
	// Set color of element to blue
	m_Color = ElementColor::BLUE;
}


void CPainterDoc::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	// Set the menu item checked if current color is black
	pCmdUI->SetCheck(m_Color == ElementColor::BLACK);
}


void CPainterDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// Set the menu item checked if current color is red
	pCmdUI->SetCheck(m_Color == ElementColor::RED);
}


void CPainterDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// Set the menu item checked if current color is green
	pCmdUI->SetCheck(m_Color == ElementColor::GREEN);
}


void CPainterDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// Set the menu item checked if current color is blue
	pCmdUI->SetCheck(m_Color == ElementColor::BLUE);
}


void CPainterDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
	// Set the menu item checked if current type is line
	pCmdUI->SetCheck(m_Element == ElementType::LINE);
}


void CPainterDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	// Set the menu item checked if current type is rectangle
	pCmdUI->SetCheck(m_Element == ElementType::RECTANGLE);
}


void CPainterDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
	// Set the menu item checked if current type is circle
	pCmdUI->SetCheck(m_Element == ElementType::CIRCLE);
}


void CPainterDoc::OnUpdateElementCurve(CCmdUI *pCmdUI)
{
	// Set the menu item checked if current type is curve
	pCmdUI->SetCheck(m_Element == ElementType::CURVE);
}


void CPainterDoc::OnUpdateElementEllipse(CCmdUI *pCmdUI)
{
	// Set the menu item checked if current type is ellipse
	pCmdUI->SetCheck(m_Element == ElementType::ELLIPSE);
}
