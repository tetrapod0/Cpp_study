
// ExamODBCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ExamODBC.h"
#include "ExamODBCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamODBCDlg 대화 상자



CExamODBCDlg::CExamODBCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAMODBC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExamODBCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExamODBCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CExamODBCDlg 메시지 처리기

BOOL CExamODBCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CExamODBCDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CExamODBCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//LRESULT CExamODBCDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
//{
//	if (message == WM_LBUTTONDOWN) {
//		// 세번째코드
//		CClientDC dc(this);
//
//		int x = LOWORD(lParam); // 32비트 안의 오른쪽 16비트
//		int y = HIWORD(lParam); // 32비트 안의 왼쪽 16비트
//
//		// 컨트롤키 클릭 유무
//		if (wParam & MK_CONTROL) dc.Ellipse(x - 50, y - 50, x + 50, y + 50);
//		else dc.Rectangle(x - 50, y - 50, x + 50, y + 50);
//
//		// Win32 - 첫번째코드
//		//HDC h_dc = ::GetDC(m_hWnd);
//		//Rectangle(h_dc, 10, 10, 100, 100);
//		//::ReleaseDC(m_hWnd, h_dc);
//
//		// MFC 기본 코드 - 두번째코드
//		//CDC* p_dc = GetDC();
//		//p_dc->Rectangle(10, 10, 100, 100);
//		//ReleaseDC(p_dc);
//	}
//
//	return CDialogEx::WindowProc(message, wParam, lParam);
//}


void CExamODBCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 네번째 코드
	CClientDC dc(this);

	// 컨트롤키 클릭 유무
	if (nFlags & MK_CONTROL) dc.Ellipse(point.x - 50, point.y - 50, point.x + 50, point.y + 50);
	else dc.Rectangle(point.x - 50, point.y - 50, point.x + 50, point.y + 50);

	CDialogEx::OnLButtonDown(nFlags, point);
}
