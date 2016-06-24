
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
	ON_COMMAND(ID_ELEMENT_CANCEL, &CPainterView::OnElementCancel)
	ON_COMMAND(ID_TOOLS_PEN, &CPainterView::OnToolsPen)
	ON_COMMAND(ID_EDIT_COPY, &CPainterView::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CPainterView::OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ERASER, &CPainterView::OnUpdateToolsEraser)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_FILLER, &CPainterView::OnUpdateToolsFiller)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_PEN, &CPainterView::OnUpdateToolsPen)
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
	//绘制图像
	for (auto it = pDoc->begin(); it != pDoc->end(); ++it)	//使用了迭代器
		for (const auto& pElement : *pDoc)
		{
			//确定给定矩形的任何部分是处于显示上下文之间的区域。
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
	//获取指向当前视图文档的指针
	CPainterDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//获得当前图形的颜色
	COLORREF color{ static_cast<COLORREF>(pDoc->GetElementColor()) };
	int PenWidth{ pDoc->GetPenWidth() };
	//根据存储在文档中的图形类型来选择图形
	switch (pDoc->GetElementType())
	{
	case ElementType::RECTANGLE:
		return std::make_shared<CRectangle>(m_FirstPoint, m_SecondPoint, color, PenWidth);
	case ElementType::CIRCLE:
		return std::make_shared<CCircle>(m_FirstPoint, m_SecondPoint, color, PenWidth);
	case ElementType::CURVE:
		return std::make_shared<CCurve>(m_FirstPoint, m_SecondPoint, color, PenWidth);
	case ElementType::LINE:
		return std::make_shared<CLine>(m_FirstPoint, m_SecondPoint, color, PenWidth);
	case ElementType::ELLIPSE:
		return std::make_shared<CEllipse>(m_FirstPoint, m_SecondPoint, color, PenWidth);
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
		ReleaseCapture();		//停止捕获鼠标消息
	}

	if (m_pTempElement)
	{
		CRect aRect{ m_pTempElement->GetEnclosingRect() };	//获取边界矩形
		//把最终的图形添加到文档对象中显示
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
	CClientDC aDC{ this };	//创建设备上下文
	OnPrepareDC(&aDC);		//调节原点位置
	aDC.DPtoLP(&point);		//转化为逻辑坐标
	CPainterDoc *pDC(GetDocument());
	if (m_MoveMode)
	{
		m_MoveMode = FALSE;

		auto pElement (m_pSelected);
		m_pSelected.reset();
		//pDC->UpdateAllViews(nullptr, 0, pElement.get());
		pDC->UpdateAllViews(NULL);
		pDC->SetModifiedFlag();
	}
	else if (use_eraser && m_pSelected)
	{

		pDC->DeleteElement(m_pSelected);
		m_pSelected.reset();
		//标记为被修改
		pDC->SetModifiedFlag();
	}
	else if (use_filler && m_pSelected)
	{
		m_pSelected.get()->Filler = TRUE;
		COLORREF color{ static_cast<COLORREF>(pDC->GetElementColor()) };
		// 设置画刷颜色
		m_pSelected.get()->m_Color = color;
		auto pElement(m_pSelected);
		m_pSelected.reset();
		pDC->UpdateAllViews(nullptr, 0, pElement.get());
		//use_filler = FALSE;
		pDC->SetModifiedFlag();
	}
	else
	{
		m_FirstPoint = point;	//记录光标的位置
		SetCapture();			//捕获随后的鼠标消息
								//注意必须在OnLButtonUp中释放消息
	}
}


void CPainterView::OnMouseMove(UINT nFlags, CPoint point)
{
	//创建设备上下文
	CClientDC aDC{ this };
	OnPrepareDC(&aDC);
	aDC.DPtoLP(&point);
	
	if (m_MoveMode)
	{
		MoveElement(aDC, point);
	}
	else if ((nFlags & MK_LBUTTON) && (this == GetCapture()) && !use_eraser && !use_filler)	
	{	//判断是否按下鼠标左键以及是否成功捕捉鼠标、是否使用橡皮擦、填充桶
		//因为在使用橡皮擦、填充桶时，不可画图
		m_SecondPoint = point;
		if (m_pTempElement)
		{
			//判断是否是曲线
			if (ElementType::CURVE == GetDocument()->GetElementType())
			{
				//如果是曲线就添加后续的点
				std::dynamic_pointer_cast<CCurve>(m_pTempElement)->AddSegment(m_SecondPoint);
				m_pTempElement->Draw(&aDC);
				return;
			}
			else
			{
				//如果不是曲线
				aDC.SetROP2(R2_NOTXORPEN);		//设置绘图模式以实现“橡皮筋”操作
				m_pTempElement->Draw(&aDC);		//重绘图像，不是最终图像
			}
		}
		m_pTempElement = CreateElement();
		m_pTempElement->Draw(&aDC);
	}
	else
	{
		auto pOldSelected = m_pSelected;
		//定位鼠标的位置
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
		//创建设备上下文
		CClientDC aDC{ this };
		OnPrepareDC(&aDC);		//调整原点位置
		//获取边界矩形，并转化为客户区坐标
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
	//文档的大小
	//CSize Docsize{ 2000, 20000 };
	CSize Docsize{ 3000, 3000 };
	//设置映射模式和文档的大小
	//SetScrollSizes(MM_TEXT, Docsize, CSize{ 500, 500 }, CSize{ 20, 20 });
	SetScrollSizes(MM_LOENGLISH, Docsize);
}


void CPainterView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	
	//加载右键菜单
	menu.LoadMenuW(IDR_RIGHTCLICK_MENU);
	
	CMenu *pContext{};
	
	ElementColor color{ GetDocument()->GetElementColor() };
	ElementType element{ GetDocument()->GetElementType() };

	if (m_pSelected)
	{
		pContext = menu.GetSubMenu(0);

		//标记菜单项
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
		
		//标记菜单项
		menu.CheckMenuItem(ID_COLOR_BLACK, (ElementColor::BLACK == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_RED, (ElementColor::RED == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_GREEN, (ElementColor::GREEN == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_BLUE, (ElementColor::BLUE == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);

		menu.CheckMenuItem(ID_ELEMENT_LINE, (ElementType::LINE == element ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_RECTANGLE, (ElementType::RECTANGLE == element ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_CIRCLE, (ElementType::CURVE == element ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_ELLIPSE, (ElementType::ELLIPSE == element ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	}
	//确保pContext不为空
	ASSERT(pContext != nullptr);
	pContext->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}


void CPainterView::OnElementMove()
{
	CClientDC aDC(this);
	OnPrepareDC(&aDC);
	GetCursorPos(&m_CursorPos);		//获取光标位置
	ScreenToClient(&m_CursorPos);
	aDC.DPtoLP(&m_CursorPos);
	m_FirstPoint = m_CursorPos;
	m_MoveMode = TRUE;
}


void CPainterView::OnElementDelete()
{
	//删除选中的图形
	if (m_pSelected)
	{
		GetDocument()->DeleteElement(m_pSelected);
		m_pSelected.reset();
	}
}


void CPainterView::OnToolsEraser()
{
	//使用橡皮擦
	use_eraser = TRUE;
	//不能同时处在m_MoveMode
	m_MoveMode = FALSE;
	use_filler = FALSE;
}


void CPainterView::OnToolsFiller()
{
	// TODO: Add your command handler code here
	//使用填充
	use_filler = TRUE;
	//不能同时处在m_MoveMode
	m_MoveMode = FALSE;
	use_eraser = FALSE;
}


void CPainterView::MoveElement(CClientDC& aDC, const CPoint& point)
{
	CSize distance{ point - m_CursorPos };		//计算移动距离

	m_CursorPos = point;
	if (m_pSelected)
	{
		CPainterDoc *pDoc{ GetDocument() };

		pDoc->UpdateAllViews(this, 0L, m_pSelected.get());
		aDC.SetROP2(R2_NOTXORPEN);
		m_pSelected->Draw(&aDC, m_pSelected);
		m_pSelected->Move(distance);
		m_pSelected->Draw(&aDC, m_pSelected);
		pDoc->UpdateAllViews(this, 0L, m_pSelected.get());
	}
}


void CPainterView::OnElementCancel()
{
	//取消操作
	if (m_MoveMode)
	{
		CClientDC aDC{ this };
		m_MoveMode = FALSE;
		OnPrepareDC(&aDC);
		MoveElement(aDC, m_FirstPoint);
		m_pSelected.reset();
		GetDocument()->UpdateAllViews(nullptr);
	}
}


void CPainterView::OnToolsPen()
{
	//取消橡皮擦
	use_eraser = FALSE;
	//取消填充
	use_filler = FALSE;
}


void CPainterView::OnEditCopy()
{
	//复制图形
	if (m_pSelected)
	{
		/*switch ()
		{
		case CRectangle::typeid:
			return std::make_shared<CRectangle>(m_FirstPoint, m_SecondPoint, color, PenWidth);
		case ElementType::CIRCLE:
			return std::make_shared<CCircle>(m_FirstPoint, m_SecondPoint, color, PenWidth);
		case ElementType::CURVE:
			return std::make_shared<CCurve>(m_FirstPoint, m_SecondPoint, color, PenWidth);
		case ElementType::LINE:
			return std::make_shared<CLine>(m_FirstPoint, m_SecondPoint, color, PenWidth);
		case ElementType::ELLIPSE:
			return std::make_shared<CEllipse>(m_FirstPoint, m_SecondPoint, color, PenWidth);
		default:
			AfxMessageBox(_T("Bad Element code"), MB_OK);
			AfxAbort();
			return nullptr;
		}*/
	}
}


void CPainterView::OnEditPaste()
{
	//创建设备上下文
	CClientDC aDC{ this };
	//粘贴图形
	if (m_pTempElement)
	{
		m_pTempElement->Draw(&aDC, m_pTempElement);
		CRect aRect{ m_pTempElement->GetEnclosingRect() };	//获取边界矩形
															//把最终的图形添加到文档对象中显示
		GetDocument()->AddElement(m_pTempElement);

		CClientDC aDC{ this };
		OnPrepareDC(&aDC);
		aDC.LPtoDP(aRect);
		InvalidateRect(aRect);
		m_pTempElement.reset();
	}
}


void CPainterView::OnUpdateToolsEraser(CCmdUI *pCmdUI)
{
	// 将橡皮擦设置为被按下
	pCmdUI->SetCheck(use_eraser);
}


void CPainterView::OnUpdateToolsFiller(CCmdUI *pCmdUI)
{
	// 如果点击填充桶则将按钮设置为被按下
	pCmdUI->SetCheck(use_filler);
}


void CPainterView::OnUpdateToolsPen(CCmdUI *pCmdUI)
{
	// 如果点击画笔则将其按钮设置为被按下
	pCmdUI->SetCheck(!(use_eraser || use_filler));
}
