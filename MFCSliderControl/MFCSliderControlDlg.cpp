
// MFCSliderControlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCSliderControl.h"
#include "MFCSliderControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSliderControlDlg 대화 상자



CMFCSliderControlDlg::CMFCSliderControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSLIDERCONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSliderControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCSliderControlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMFCSliderControlDlg::OnNMCustomdrawSlider1)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CMFCSliderControlDlg 메시지 처리기

BOOL CMFCSliderControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	pSlider->SetRange(0, 30);
	pSlider->SetTicFreq(5); // 눈금 간격
	pSlider->SetLineSize(5); // 키보드로 움직일시
	pSlider->SetPageSize(5); // Page Up/Down
	pSlider->SetPos(0);
	SetDlgItemInt(IDC_EDIT1, 0);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCSliderControlDlg::OnPaint()
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
HCURSOR CMFCSliderControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// SetPos가 호출되면 이 함수가 호출되는것 같은데
// 그래서 안에 SetPos 작동이 안되는듯, 무한루프 빠지는 느낌
//void CMFCSliderControlDlg::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	*pResult = 0;
//
//	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
//	int pos = pSlider->GetPos();
//	int new_pos = pos / 5 * 5;
//	pSlider->SetPos(new_pos); 
//	SetDlgItemInt(IDC_EDIT1, new_pos);
//}


void CMFCSliderControlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
	if (pSlider->GetDlgCtrlID() == IDC_SLIDER1) {
		int pos = pSlider->GetPos();
		int new_pos = (pos+2) / 5 * 5;
		pSlider->SetPos(new_pos); 
		SetDlgItemInt(IDC_EDIT1, new_pos);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
