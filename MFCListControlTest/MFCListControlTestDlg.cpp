
// MFCListControlTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCListControlTest.h"
#include "MFCListControlTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCListControlTestDlg 대화 상자



CMFCListControlTestDlg::CMFCListControlTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCLISTCONTROLTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCListControlTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCListControlTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_BTN, &CMFCListControlTestDlg::OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_DEL_BTN, &CMFCListControlTestDlg::OnBnClickedDelBtn)
END_MESSAGE_MAP()


// CMFCListControlTestDlg 메시지 처리기

BOOL CMFCListControlTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// List Control 초기화
	CRect rt;
	CListCtrl* plc = (CListCtrl*)GetDlgItem(IDC_LIST1);
	plc->GetWindowRect(&rt);
	plc->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	plc->InsertColumn(0, TEXT("순번"), LVCFMT_LEFT, (int)(rt.Width() * 0.3));
	plc->InsertColumn(1, L"항목", LVCFMT_CENTER, rt.Width() * 0.3);
	plc->InsertColumn(2, L"내용", LVCFMT_CENTER, rt.Width() * 0.3);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCListControlTestDlg::OnPaint()
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
HCURSOR CMFCListControlTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCListControlTestDlg::OnBnClickedAddBtn()
{
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST1);
	int num = pList->GetItemCount();

	CString str;
	str.Format(L"%03d", num);

	CString str2;
	GetDlgItemText(IDC_EDIT1, str2);
	SetDlgItemText(IDC_EDIT1, L"");

	pList->InsertItem(num, str);
	pList->SetItemText(num, 1, L"test");
	pList->SetItemText(num, 2, str2);
	//pList->SetItem(num, 1, LVIF_TEXT, L"test", NULL, NULL, NULL, NULL);
	//pList->SetItem(num, 2, LVIF_TEXT, str2, NULL, NULL, NULL, NULL);


}


void CMFCListControlTestDlg::OnBnClickedDelBtn()
{
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST1);

	int nItem = -1; // 초기값, 첫 번째 항목부터 탐색
	while ((nItem = pList->GetNextItem(nItem, LVNI_SELECTED)) != -1) {
		pList->DeleteItem(nItem);
		// 삭제 후 인덱스가 재정렬되므로 nItem을 그대로 사용
		nItem--; // 이미 재정렬된 리스트를 반영해 -1로 맞춤
	}

}
