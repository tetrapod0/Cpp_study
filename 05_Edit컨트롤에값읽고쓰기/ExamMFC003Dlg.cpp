
// ExamMFC003Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ExamMFC003.h"
#include "ExamMFC003Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamMFC003Dlg 대화 상자



CExamMFC003Dlg::CExamMFC003Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAMMFC003_DIALOG, pParent)
	//, m_my_value(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExamMFC003Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT1, m_my_value);
}

BEGIN_MESSAGE_MAP(CExamMFC003Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_READ_BTN, &CExamMFC003Dlg::OnBnClickedReadBtn)
	ON_BN_CLICKED(IDC_WRITE_BTN, &CExamMFC003Dlg::OnBnClickedWriteBtn)
END_MESSAGE_MAP()


// CExamMFC003Dlg 메시지 처리기

BOOL CExamMFC003Dlg::OnInitDialog()
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

void CExamMFC003Dlg::OnPaint()
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
HCURSOR CExamMFC003Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExamMFC003Dlg::OnBnClickedReadBtn()
{
	//UpdateData(TRUE); // 컨트롤 -> 변수 // False는 변수 -> 컨트롤

	////AfxMessageBox(m_my_string);
	////int value = _wtoi(m_my_string);

	//CString str;
	//str.Format(L"%d", m_my_value);
	//AfxMessageBox(str);

	CString str;

	int len = GetDlgItemText(IDC_EDIT1, str);

	//int value = GetDlgItemInt(IDC_EDIT1);

	//CString ll;
	//ll.Format(L"%d", len);
	AfxMessageBox(str);

	//CWnd* p = GetDlgItem(IDC_EDIT1);
	//int len = p->GetWindowTextLength();
	//int len = p->SendMessage(WM_GETTEXTLENGTH);

	// 입력 길이 가져오기
	int len1 = GetDlgItem(IDC_EDIT1)->GetWindowTextLength();

}


void CExamMFC003Dlg::OnBnClickedWriteBtn()
{
	////m_my_string = L"testest";
	//m_my_value = 555;
	//UpdateData(FALSE); // False는 변수 -> 컨트롤


	SetDlgItemText(IDC_EDIT1, L"testest");
}
