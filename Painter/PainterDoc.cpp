
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

		//����list�Ĵ�С
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
	//����ͼ������Ϊֱ��
	m_Element = ElementType::LINE;
	SetModifiedFlag();
}


void CPainterDoc::OnElementRectangle()
{
	//����ͼ������Ϊ����
	m_Element = ElementType::RECTANGLE;
	SetModifiedFlag();
}


void CPainterDoc::OnElementCircle()
{
	//����ͼ������ΪԲ
	m_Element = ElementType::CIRCLE;
	SetModifiedFlag();
}


void CPainterDoc::OnElementCurve()
{
	//����ͼ������Ϊ����
	m_Element = ElementType::CURVE;
	SetModifiedFlag();
}


void CPainterDoc::OnElementEllipse()
{
	//����ͼ������Ϊ��Բ
	m_Element = ElementType::ELLIPSE;
	SetModifiedFlag();
}


void CPainterDoc::OnColorBlack()
{
	//��ͼ����ɫ����Ϊ��ɫ
	m_Color = ElementColor::BLACK;
	SetModifiedFlag();
}


void CPainterDoc::OnColorRed()
{
	//��ͼ����ɫ����Ϊ��ɫ
	m_Color = ElementColor::RED;
	SetModifiedFlag();
}


void CPainterDoc::OnColorGreen()
{
	//��ͼ����ɫ����Ϊ��ɫ
	m_Color = ElementColor::GREEN;
	SetModifiedFlag();
}


void CPainterDoc::OnColorBlue()
{
	//��ͼ����ɫ����Ϊ��ɫ
	m_Color = ElementColor::BLUE;
	SetModifiedFlag();
}


void CPainterDoc::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	//�����ɫ�Ǻ�ɫ����ѡ�к�ɫ��ť
	pCmdUI->SetCheck(m_Color == ElementColor::BLACK);
}


void CPainterDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	//�����ɫ�Ǻ�ɫ����ѡ�к�ɫ��ť
	pCmdUI->SetCheck(m_Color == ElementColor::RED);
}


void CPainterDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	//�����ɫ����ɫ����ѡ����ɫ��ť
	pCmdUI->SetCheck(m_Color == ElementColor::GREEN);
}


void CPainterDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	//�����ɫ����ɫ����ѡ����ɫ��ť
	pCmdUI->SetCheck(m_Color == ElementColor::BLUE);
}


void CPainterDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
	//���������ֱ�ߣ���ѡ��ֱ�߰�ť
	pCmdUI->SetCheck(m_Element == ElementType::LINE);
}


void CPainterDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	//��������Ǿ��Σ���ѡ�о��ΰ�ť
	pCmdUI->SetCheck(m_Element == ElementType::RECTANGLE);
}


void CPainterDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
	//���������Բ�Σ���ѡ��Բ�ΰ�ť
	pCmdUI->SetCheck(m_Element == ElementType::CIRCLE);
}


void CPainterDoc::OnUpdateElementCurve(CCmdUI *pCmdUI)
{
	//������������ߣ���ѡ�����߰�ť
	pCmdUI->SetCheck(m_Element == ElementType::CURVE);
}


void CPainterDoc::OnUpdateElementEllipse(CCmdUI *pCmdUI)
{
	//�����������Բ����ѡ����Բ��ť
	pCmdUI->SetCheck(m_Element == ElementType::ELLIPSE);
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
