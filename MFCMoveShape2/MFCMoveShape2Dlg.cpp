
// MFCMoveShape2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCMoveShape2.h"
#include "MFCMoveShape2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCMoveShape2Dlg 대화 상자



CMFCMoveShape2Dlg::CMFCMoveShape2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCMOVESHAPE2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMoveShape2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCMoveShape2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CMFCMoveShape2Dlg 메시지 처리기

BOOL CMFCMoveShape2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_rectList.push_back(CRect(50, 50, 100, 100));
	m_rectList.push_back(CRect(30, 30, 80, 80));

	m_img.Load(L"./vitamin_back.jpg");

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCMoveShape2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		// 이미지가 rect로 조정됨
		//CRect rect;
		//GetClientRect(&rect);
		//m_img.Draw(dc, rect); 
		
		// 이미지 원본이 그려짐
		//CRect r(200, 200, 800, 800);
		//m_img.Draw(dc, r, r); // 특정영역크롭하여 목적영역에 그리기
		//m_img.Draw(dc, 0, 0, 100, 100, 0, 0, 100, 100);
		//m_img.Draw(dc, CRect(10, 10, 200, 200));
		OnDraw_(&dc);


		CDialogEx::OnPaint();
	}
}

// 그림 그리는 순간이 보일 수 있다..
//void CMFCMoveShape2Dlg::OnDraw_(CDC* pDC) {
//
//	m_img.Draw(*pDC, 0, 0);
//
//	// 사각형을 그릴 때 내부는 투명하게 설정
//	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH); // 내부를 채우지 않음
//	CPen pen(PS_SOLID, 1, RGB(0, 0, 0)); // 검은색 테두리
//	CPen* pOldPen = pDC->SelectObject(&pen);
//
//	// 네모들 그림
//	//for (auto& rect : m_rectList) {
//	//	pDC->Rectangle(rect);
//	//}
//
//	// 브러시와 펜 복원
//	pDC->SelectObject(pOldBrush);
//	pDC->SelectObject(pOldPen);
//
//	// 네모들 그림
//	for (auto& rect : m_rectList) {
//		pDC->Rectangle(rect);
//	}
//
//}


void CMFCMoveShape2Dlg::OnDraw_(CDC* pDC) {
	// memDC 초기화
	CRect client_rect;
	GetClientRect(&client_rect);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(pDC, client_rect.Width(), client_rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);


	m_img.Draw(memDC, 0, 0);

	for (auto& rect : m_rectList) {
		memDC.Rectangle(rect);
	}

	// 사각형을 그릴 때 내부는 투명하게 설정
	CBrush* pOldBrush = (CBrush*)memDC.SelectStockObject(NULL_BRUSH); // 내부를 채우지 않음
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0)); // 검은색 테두리
	CPen* pOldPen = memDC.SelectObject(&pen);

	// 네모들 그림
	//for (auto& rect : m_rectList) {
	//	memDC.Rectangle(rect);
	//}

	pDC->BitBlt(0, 0, client_rect.Width(), client_rect.Height(), &memDC, 0, 0, SRCCOPY);

	// 원래상태로 복원
	memDC.SelectObject(pOldBrush);
	memDC.SelectObject(pOldPen);
	memDC.SelectObject(pOldBitmap);

}



// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCMoveShape2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCMoveShape2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CString str;
	//str.Format(L"%d, %d, %d", point.x, point.y, s);
	//AfxMessageBox(str);

	int i = m_rectList.size() - 1;
	for (; i >= 0; --i) {
		if (m_rectList[i].PtInRect(point)) {
			m_is_clicked = true;
			m_prev_pos = point;
			break;
		}
	}
	if (i == -1) return; // 빈 벡터

	CRect rect(m_rectList[i]);
	m_rectList.erase(m_rectList.begin() + i);
	m_rectList.push_back(rect);
	InvalidateRect(&m_rectList.back(), TRUE); // 부분 갱신

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCMoveShape2Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_is_clicked) m_is_clicked = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCMoveShape2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_is_clicked) {
		CPoint diff_pos = point - m_prev_pos;
		m_prev_pos = point;
		CRect prev_rect = m_rectList.back();
		m_rectList.back() += diff_pos;

		CRect union_rect;
		union_rect.UnionRect(&prev_rect, &m_rectList.back());
		//InvalidateRect(&union_rect, TRUE); // 지우는 순간이 보일 수 있다..
		InvalidateRect(&union_rect, FALSE); // 덮어씌우기
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCMoveShape2Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//lpMMI->ptMinTrackSize = CPoint(1280, 720);
	lpMMI->ptMinTrackSize = CPoint(640, 480);
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
