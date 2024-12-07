﻿
// MFCLabelerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCLabeler.h"
#include "MFCLabelerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCLabelerDlg 대화 상자



CMFCLabelerDlg::CMFCLabelerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCLABELER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCLabelerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCLabelerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_DEL_BTN, &CMFCLabelerDlg::OnBnClickedDelBtn)
	ON_COMMAND(ID_FILE_OPEN_, &CMFCLabelerDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_, &CMFCLabelerDlg::OnFileSave)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_ROTATE_BTN, &CMFCLabelerDlg::OnBnClickedRotateBtn)
	ON_BN_CLICKED(IDC_ADD_BTN, &CMFCLabelerDlg::OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_CLEAR_BTN, &CMFCLabelerDlg::OnBnClickedClearBtn)
END_MESSAGE_MAP()


// CMFCLabelerDlg 메시지 처리기

BOOL CMFCLabelerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 폰트 크기 설정
	CWnd* edit_box = GetDlgItem(IDC_NAME_EDIT);
	CRect rect;
	edit_box->GetClientRect(&rect);
	static CFont font;
	font.CreatePointFont((int)(rect.Height() * 6.66), L"굴림");
	edit_box->SetFont(&font);




	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCLabelerDlg::OnPaint()
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
HCURSOR CMFCLabelerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCLabelerDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	lpMMI->ptMinTrackSize = CPoint(1280, 720);
	//lpMMI->ptMaxTrackSize = CPoint(1400, 1000);


	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CMFCLabelerDlg::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMFCLabelerDlg::OnFileSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
}


void CMFCLabelerDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 드롭된 파일의 개수 확인
	UINT fileCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

	if (fileCount > 1) {
		AfxMessageBox(L"하나의 파일만 놓아주세요.");
		return;
	}
	// 파일의 경로를 처리
	TCHAR filePath[MAX_PATH];
	DragQueryFile(hDropInfo, 0, filePath, MAX_PATH);
	CString path = filePath;

	// 파일 경로 출력 (혹은 원하는 작업 수행)
	AfxMessageBox(path);

	CDialogEx::OnDropFiles(hDropInfo);
}


void CMFCLabelerDlg::OnBnClickedAddBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCLabelerDlg::OnBnClickedDelBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCLabelerDlg::OnBnClickedRotateBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCLabelerDlg::OnBnClickedClearBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
