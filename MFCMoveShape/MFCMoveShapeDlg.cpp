
// MFCMoveShapeDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCMoveShape.h"
#include "MFCMoveShapeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCMoveShapeDlg 대화 상자



CMFCMoveShapeDlg::CMFCMoveShapeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCMOVESHAPE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMoveShapeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCMoveShapeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCMoveShapeDlg 메시지 처리기

BOOL CMFCMoveShapeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_rect.SetRect(0, 0, 100, 100);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCMoveShapeDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{

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
		dc.Rectangle(m_rect);
		//OnDraw(&dc);
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCMoveShapeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCMoveShapeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//if (m_rect.left <= point.x && point.x < m_rect.right &&
	//	m_rect.top <= point.y && point.y < m_rect.bottom) {
	if(m_rect.PtInRect(point)){
		m_is_clicked = true;
		m_prev_pos = point;
		SetCapture(); // 밖으로 나가더라도 마우스 가져오기
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMFCMoveShapeDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_is_clicked) {
		m_is_clicked = false;
		ReleaseCapture();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}



void CMFCMoveShapeDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_is_clicked) {
		CPoint diff_pos = point - m_prev_pos;
		CRect prev_rect = m_rect;
		m_rect += diff_pos;
		//m_rect.left += diff_pos.x;
		//m_rect.right += diff_pos.x;
		//m_rect.top += diff_pos.y;
		//m_rect.bottom += diff_pos.y;
		m_prev_pos = point;

		//Invalidate(false); // WM_PAINT? 다시 그리기 // false면 화면안지우고 덮어씀
		//InvalidateRect(); // 전체 갱신
		CRect union_rect;
		union_rect.UnionRect(&prev_rect, &m_rect);
		InvalidateRect(&union_rect, TRUE); // 부분 갱신
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCMoveShapeDlg::OnDraw(CDC* pDC)
{
	//pDC->Rectangle(m_rect); // 사각형 그리기
}
