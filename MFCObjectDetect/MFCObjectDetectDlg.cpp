
// MFCObjectDetectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCObjectDetect.h"
#include "MFCObjectDetectDlg.h"
#include "afxdialogex.h"

#include "VisionDlg.h"
#include "LabelerDlg.h"
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCObjectDetectDlg 대화 상자



CMFCObjectDetectDlg::CMFCObjectDetectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCOBJECTDETECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCObjectDetectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCObjectDetectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CMFCObjectDetectDlg::OnTcnSelchangeTabMain)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFCObjectDetectDlg 메시지 처리기

BOOL CMFCObjectDetectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	{// 탭 초기화
		// 탭 추가
		m_pTab = (CTabCtrl*)GetDlgItem(IDC_TAB_MAIN);
		m_pTab->InsertItem(0, L"Vision");
		m_pTab->InsertItem(1, L"Labeler");
		m_pTab->InsertItem(2, L"Setting");

		m_pTab->SetCurSel(0);

		CRect tab_rect;
		m_pTab->GetClientRect(&tab_rect);


		CDialogEx* pDlg;
		// 첫번째 탭
		pDlg = new CVisionDlg();
		pDlg->Create(IDD_VISION_DLG, m_pTab);
		pDlg->MoveWindow(0, 20, tab_rect.Width(), tab_rect.Height() - 20);
		pDlg->ShowWindow(SW_SHOW);
		m_pDlgList.push_back(pDlg);
		// 두번째 탭
		pDlg = new CLabelerDlg();
		pDlg->Create(IDD_LABELER_DLG, m_pTab);
		pDlg->ShowWindow(SW_HIDE);
		m_pDlgList.push_back(pDlg);
		// 세번째 탭
		pDlg = new CSettingDlg();
		pDlg->Create(IDD_SETTING_DLG, m_pTab);
		pDlg->ShowWindow(SW_HIDE);
		m_pDlgList.push_back(pDlg);


	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCObjectDetectDlg::OnPaint()
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
HCURSOR CMFCObjectDetectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCObjectDetectDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lpMMI->ptMinTrackSize = CPoint(1280, 720);
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CMFCObjectDetectDlg::OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int sel = m_pTab->GetCurSel();

	// 전환전 상태검사?


	// 탭 전환
	if (sel < m_pDlgList.size()) {
		CRect tab_rect;
		m_pTab->GetClientRect(&tab_rect);
		m_pDlgList[m_selected_tab]->ShowWindow(SW_HIDE);
		m_pDlgList[sel]->ShowWindow(SW_SHOW);
		m_pDlgList[sel]->MoveWindow(0, 20, tab_rect.Width(), tab_rect.Height() - 20);
		m_selected_tab = sel;
	}
}


void CMFCObjectDetectDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	// 최소화 되어있는 경우
	if (nType == SIZE_MINIMIZED) return;

	//
	if (m_pTab != nullptr && IsWindow(m_pTab->GetSafeHwnd()))
	{
		CRect tab_rect;
		m_pTab->GetClientRect(&tab_rect);
		m_pDlgList[m_selected_tab]->MoveWindow(0, 20, tab_rect.Width(), tab_rect.Height() - 20);
	}
}
