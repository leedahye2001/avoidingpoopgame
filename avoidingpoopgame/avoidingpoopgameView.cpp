
// avoidingpoopgameView.cpp: CavoidingpoopgameView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "avoidingpoopgame.h"
#endif

#include "avoidingpoopgameDoc.h"
#include "avoidingpoopgameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <windows.h> 

// CavoidingpoopgameView

IMPLEMENT_DYNCREATE(CavoidingpoopgameView, CView)

BEGIN_MESSAGE_MAP(CavoidingpoopgameView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_CTLCOLOR()
ON_WM_TIMER()
ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CavoidingpoopgameView 생성/소멸

CavoidingpoopgameView::CavoidingpoopgameView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	srand((unsigned)time(NULL));
	f = 0;
	i = 0;
	move = false;
}

CavoidingpoopgameView::~CavoidingpoopgameView()
{
}

BOOL CavoidingpoopgameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CavoidingpoopgameView 그리기

void CavoidingpoopgameView::OnDraw(CDC* /*pDC*/)
{
	CavoidingpoopgameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
	game_screen();
	Player();
	//falling_poop();
	//SetTimer(0, 500, NULL);
	
}


// CavoidingpoopgameView 인쇄

BOOL CavoidingpoopgameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CavoidingpoopgameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CavoidingpoopgameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

// CavoidingpoopgameView 진단

#ifdef _DEBUG
void CavoidingpoopgameView::AssertValid() const
{
	CView::AssertValid();
}

void CavoidingpoopgameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CavoidingpoopgameDoc* CavoidingpoopgameView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CavoidingpoopgameDoc)));
	return (CavoidingpoopgameDoc*)m_pDocument;
}
#endif //_DEBUG

// CavoidingpoopgameView 메시지 처리기

void CavoidingpoopgameView::falling_poop()
{
	// TODO: 여기에 구현 코드 추가.
	CClientDC dc(this);
	
	while (i < 10)
	{
		CBrush poopc(RGB(255, 255, 255));
		dc.SelectObject(&poopc);
		
		poop.push_back(rand() % 1201 + 110);
		dc.Ellipse(poop[f].x - 10, (120+poop[f].y) - 10, poop[f].x + 10, (120+poop[f].y) + 10);
		f++;
		i++;
		delay(1000);
		
	}
	
}

void CavoidingpoopgameView::game_screen()
{
	// TODO: 여기에 구현 코드 추가.
	CClientDC dc(this);
	CRect rect;
	GetClientRect(rect);
	CBrush screen(RGB(0, 0, 0));
	dc.SelectObject(&screen);
	dc.Rectangle( rect.left, rect.top , rect.right, rect.bottom);

	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(255, 255, 255));   

	CPen* Pen2 = dc.SelectObject(&pen);
	dc.MoveTo(100, 100);
	dc.LineTo(100, 550);

	dc.MoveTo(100, 550);
	dc.LineTo(1320, 550);

	dc.MoveTo(1320, 550);
	dc.LineTo(1320, 100);

	dc.MoveTo(1320, 100);
	dc.LineTo(100, 100);

	dc.SelectObject(Pen2);				
}

void CavoidingpoopgameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	/*for (int i = 0; i < f; i++) {
		poop[i].y += 10;
	}
	
	Invalidate();	*/

	CView::OnTimer(nIDEvent);
}

void CavoidingpoopgameView::delay(DWORD dwMillisecond)
{
	// TODO: 여기에 구현 코드 추가.
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}


void CavoidingpoopgameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*if (nChar == VK_SPACE) {
		move = !move;
		if (move) SetTimer(0, 50, NULL);
		else KillTimer(0);
	}*/

	if (nChar == VK_RIGHT) {
		player.left += 10;
		player.right += 10;
		Invalidate();
	}
	if (nChar == VK_LEFT) {
		player.left -= 10;
		player.right -= 10;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CavoidingpoopgameView::Player()
{
	// TODO: 여기에 구현 코드 추가.
	CClientDC dc(this);

	CBrush bs(RGB(255, 255, 255));
	dc.SelectObject(bs);
	player.right = 735;
	player.bottom = 540;
	player.left = 685;
	player.top = 490;
	dc.Rectangle(player.left, player.top, player.right, player.bottom);
}
