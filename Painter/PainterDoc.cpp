
// PainterDoc.cpp : implementation of the CPainterDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Painter.h"
#endif

#include "PainterDoc.h"
#include "PenDialog.h"
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
	ON_COMMAND(ID_SETTINGS_PENWIDTHS, &CPainterDoc::OnSettingsPenwidths)
	ON_COMMAND(ID_TOOLS_ERASER, &CPainterDoc::OnToolsEraser)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ERASER, &CPainterDoc::OnUpdateToolsEraser)
	ON_COMMAND(ID_TOOLS_FILLER, &CPainterDoc::OnToolsFiller)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_FILLER, &CPainterDoc::OnUpdateToolsFiller)
	ON_COMMAND(ID_TOOLS_PEN, &CPainterDoc::OnToolsPen)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_PEN, &CPainterDoc::OnUpdateToolsPen)
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
		ar << static_cast<COLORREF>(m_Color);
		ar << static_cast<int>(m_Element);
		ar << m_PenWidth;

		//保存list的大小
		ar << m_Paint.size();

		for (auto const &p : m_Paint)
		{
			ar << p.get();
		}
	}
	else
	{
		COLORREF color {};
		int type;

		ar >> color;
		m_Color = static_cast<ElementColor>(color);
		ar >> type;
		m_Element = static_cast<ElementType>(type);
		ar >> m_PenWidth;

		size_t m_paint_size{};
		ar >> m_paint_size;
		CElement *t;

		for (size_t i{}; i < m_paint_size; i++)
		{
			ar >> t;
			m_Paint.push_back(std::shared_ptr<CElement>(t));
		}
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
	//设置图形类型为直线
	m_Element = ElementType::LINE;
	SetModifiedFlag();
}


void CPainterDoc::OnElementRectangle()
{
	if (ifUseTools())
		return;
	//设置图形类型为矩形
	m_Element = ElementType::RECTANGLE;
	SetModifiedFlag();
}


void CPainterDoc::OnElementCircle()
{
	if (ifUseTools())
		return;
	//设置图形类型为圆
	m_Element = ElementType::CIRCLE;
	SetModifiedFlag();
}


void CPainterDoc::OnElementCurve()
{
	if (ifUseTools())
		return;
	//设置图形类型为曲线
	m_Element = ElementType::CURVE;
	SetModifiedFlag();
}


void CPainterDoc::OnElementEllipse()
{
	if (ifUseTools())
		return;
	//设置图形类型为椭圆
	m_Element = ElementType::ELLIPSE;
	SetModifiedFlag();
}


void CPainterDoc::OnColorBlack()
{
	//将图形颜色设置为黑色
	m_Color = ElementColor::BLACK;
	SetModifiedFlag();
}


void CPainterDoc::OnColorRed()
{
	//将图形颜色设置为红色
	m_Color = ElementColor::RED;
	SetModifiedFlag();
}


void CPainterDoc::OnColorGreen()
{
	//将图形颜色设置为绿色
	m_Color = ElementColor::GREEN;
	SetModifiedFlag();
}


void CPainterDoc::OnColorBlue()
{
	//将图形颜色设置为蓝色
	m_Color = ElementColor::BLUE;
	SetModifiedFlag();
}


void CPainterDoc::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	//如果颜色是黑色，则选中黑色按钮
	pCmdUI->SetCheck(m_Color == ElementColor::BLACK);
}


void CPainterDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	//如果颜色是红色，则选中红色按钮
	pCmdUI->SetCheck(m_Color == ElementColor::RED);
}


void CPainterDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	//如果颜色是绿色，则选中绿色按钮
	pCmdUI->SetCheck(m_Color == ElementColor::GREEN);
}


void CPainterDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	//如果颜色是蓝色，则选中蓝色按钮
	pCmdUI->SetCheck(m_Color == ElementColor::BLUE);
}


void CPainterDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
	//如果类型是直线，则选中直线按钮
	pCmdUI->SetCheck((m_Element == ElementType::LINE) && !ifUseTools());
}


void CPainterDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	//如果类型是矩形，则选中矩形按钮
	pCmdUI->SetCheck((m_Element == ElementType::RECTANGLE) && !ifUseTools());
}


void CPainterDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
	//如果类型是圆形，则选中圆形按钮
	pCmdUI->SetCheck((m_Element == ElementType::CIRCLE) && !ifUseTools());
}


void CPainterDoc::OnUpdateElementCurve(CCmdUI *pCmdUI)
{
	if (ifUseTools())
	{
		return;
	}
	//如果类型是曲线，则选中曲线按钮
	pCmdUI->SetCheck((m_Element == ElementType::CURVE) && !ifUseTools());
}


void CPainterDoc::OnUpdateElementEllipse(CCmdUI *pCmdUI)
{
	//如果类型是椭圆，则选中椭圆按钮
	pCmdUI->SetCheck((m_Element == ElementType::ELLIPSE) && !ifUseTools());
}


std::shared_ptr<CElement> CPainterDoc::FindElement(const CPoint& point) const
{
	for (const auto& pElement : m_Paint)
	{
		if (pElement->GetEnclosingRect().PtInRect(point))
		{
			return pElement;
		}
	}
	return nullptr;
}

void CPainterDoc::OnSettingsPenwidths()
{
	CPenDialog aDlg;

	aDlg.m_PenWidth = m_PenWidth;
	if (aDlg.DoModal() == IDOK)
	{
		m_PenWidth = aDlg.m_PenWidth;
	}
}


void CPainterDoc::OnToolsEraser()
{
	// TODO: Add your command handler code here
	//使用橡皮擦
	use_eraser = TRUE;
	//不能同时处在m_MoveMode
	//m_MoveMode = FALSE;
	use_filler = FALSE;
}


void CPainterDoc::OnUpdateToolsEraser(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// 将橡皮擦设置为被按下
	pCmdUI->SetCheck(use_eraser);
}


void CPainterDoc::OnToolsFiller()
{
	// TODO: Add your command handler code here
	//使用填充
	use_filler = TRUE;
	//不能同时处在m_MoveMode
	//m_MoveMode = FALSE;
	use_eraser = FALSE;
}


void CPainterDoc::OnUpdateToolsFiller(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// 如果点击填充桶则将按钮设置为被按下
	pCmdUI->SetCheck(use_filler);
}


void CPainterDoc::OnToolsPen()
{
	// TODO: Add your command handler code here
	//取消橡皮擦
	use_eraser = FALSE;
	//取消填充
	use_filler = FALSE;
}


void CPainterDoc::OnUpdateToolsPen(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// 如果点击画笔则将其按钮设置为被按下
	pCmdUI->SetCheck(!(use_eraser || use_filler));
}
