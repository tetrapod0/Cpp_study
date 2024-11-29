
// MFCDrawStarDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCDrawStar.h"
#include "MFCDrawStarDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDrawStarDlg 대화 상자



CMFCDrawStarDlg::CMFCDrawStarDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDRAWSTAR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDrawStarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCDrawStarDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFCDrawStarDlg 메시지 처리기

BOOL CMFCDrawStarDlg::OnInitDialog()
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

void CMFCDrawStarDlg::OnPaint()
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
		// 별을 그릴 수 있는 점들의 좌표를 정의합니다.
		POINT points[5] = {
			{100, 0},
			{cos(3.141592 * 2 * 0.2) * 100, sin(3.141592 * 2 * 0.2) * 100},
			{cos(3.141592 * 2 * 0.4) * 100, sin(3.141592 * 2 * 0.4) * 100},
			{cos(3.141592 * 2 * 0.6) * 100, sin(3.141592 * 2 * 0.6) * 100},
			{cos(3.141592 * 2 * 0.8) * 100, sin(3.141592 * 2 * 0.8) * 100},
		};
		for (int i = 0; i < 5; i++) {
			points[i].x += 100;
			points[i].y += 100;
		}
		
		// 별의 외곽선 그리기 (다섯 꼭짓점을 연결)
		dc.MoveTo(points[0]);
		dc.LineTo(points[2]);
		dc.LineTo(points[4]);
		dc.LineTo(points[1]);
		dc.LineTo(points[3]);
		dc.LineTo(points[0]); // 첫 번째 꼭짓점으로 돌아가서 선을 닫음


		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCDrawStarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

