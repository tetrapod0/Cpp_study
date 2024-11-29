
// MyCalculatorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MyCalculator.h"
#include "MyCalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyCalculatorDlg 대화 상자



CMyCalculatorDlg::CMyCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYCALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyCalculatorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_NUM0_BTN, IDC_POINT_BTN, &CMyCalculatorDlg::OnBnClickedNumBtn)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RESULT_BTN, IDC_DIV_BTN, &CMyCalculatorDlg::OnBnClickedOperBtn)
	ON_BN_CLICKED(IDC_CLEAR_BTN, &CMyCalculatorDlg::OnBnClickedClearBtn)
END_MESSAGE_MAP()


// CMyCalculatorDlg 메시지 처리기
BOOL CMyCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 폰트 크기 설정
	CWnd* edit_box = GetDlgItem(IDC_EDIT_NUM);
	CRect rect;
	edit_box->GetClientRect(&rect);
	static CFont font;
	font.CreatePointFont((int)(rect.Height()*6.66), L"굴림");
	edit_box->SetFont(&font);

	// 변수 초기화
	OnBnClickedClearBtn();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMyCalculatorDlg::OnPaint()
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
HCURSOR CMyCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CString CMyCalculatorDlg::RemoveTrailingZeroes(CString str) {
	// 숫자에 소수점이 존재하고, 그 뒤에 0이 있으면 제거
	int dotIndex = str.Find('.');
	if (dotIndex != -1) {
		// 소수점 뒤의 0을 제거
		while (str.GetAt(str.GetLength() - 1) == '0') {
			str = str.Left(str.GetLength() - 1);
		}
		// 마지막 소수점도 제거 (소수점 뒤에 숫자가 없으면)
		if (str.GetAt(str.GetLength() - 1) == '.') {
			str = str.Left(str.GetLength() - 1);
		}
	}
	return str;
}

//void CMyCalculatorDlg::on_clicked_number(char sNum) {
//	if (m_bChangeFlag) { // 이전에 연산자를 눌렀다면 글자초기화
//		SetDlgItemText(IDC_EDIT_NUM, L"0");
//		m_bChangeFlag = false;
//	}
//
//	CString str;
//	GetDlgItemText(IDC_EDIT_NUM, str);
//	if (sNum == '.' && str.Find('.') != -1) return; // '.'있는데 또 누를시
//	if (sNum != '.' && str == L"0") str = L""; // 0 뿐이라면 일단 지워
//	SetDlgItemText(IDC_EDIT_NUM, str+sNum);
//}
//
//void CMyCalculatorDlg::on_clicked_operator(char sOper) {
//
//	CString str;
//	GetDlgItemText(IDC_EDIT_NUM, str);
//	double dValue = _ttof(str);
//	if (m_sBeforeOp == '=') m_dValue = dValue;
//	else if (m_sBeforeOp == '+' && !m_bChangeFlag) m_dValue += dValue;
//	else if (m_sBeforeOp == '-' && !m_bChangeFlag) m_dValue -= dValue;
//	else if (m_sBeforeOp == '*' && !m_bChangeFlag) m_dValue *= dValue;
//	else if (m_sBeforeOp == '/' && !m_bChangeFlag) {
//		if (dValue == 0) {
//			AfxMessageBox(L"0으로 나눌 수 없습니다.");
//			return;
//		}
//		m_dValue /= dValue;
//	}
//
//	str.Format(L"%.8f", m_dValue);
//	str = RemoveTrailingZeroes(str);
//	SetDlgItemText(IDC_EDIT_NUM, str);
//
//	m_sBeforeOp = sOper;
//	m_bChangeFlag = true;
//}


void CMyCalculatorDlg::OnBnClickedNumBtn(UINT id) {
	static const CString sCharList = L"0123456789.";
	wchar_t ch = sCharList.GetAt(id - IDC_NUM0_BTN);

	if (m_bChangeFlag) { // 이전에 연산자를 눌렀다면 글자초기화
		SetDlgItemText(IDC_EDIT_NUM, L"0");
		m_bChangeFlag = false;
	}

	CString sEditStr;
	GetDlgItemText(IDC_EDIT_NUM, sEditStr);
	if (ch == L'.' && sEditStr.Find(L'.') != -1) return; // '.'있는데 또 누를시
	if (ch != L'.' && sEditStr == L"0") sEditStr = L""; // 0 뿐이라면 일단 지워
	SetDlgItemText(IDC_EDIT_NUM, sEditStr + ch);
}

void CMyCalculatorDlg::OnBnClickedOperBtn(UINT id) {
	static const CString sCharList = L"=+-*/";
	wchar_t ch = sCharList.GetAt(id - IDC_RESULT_BTN);

	CString sEditStr;
	GetDlgItemText(IDC_EDIT_NUM, sEditStr);
	double dValue = _ttof(sEditStr);
	if (m_sBeforeOp == L'=') m_dValue = dValue;
	else if (m_sBeforeOp == L'+' && !m_bChangeFlag) m_dValue += dValue;
	else if (m_sBeforeOp == L'-' && !m_bChangeFlag) m_dValue -= dValue;
	else if (m_sBeforeOp == L'*' && !m_bChangeFlag) m_dValue *= dValue;
	else if (m_sBeforeOp == L'/' && !m_bChangeFlag) {
		if (dValue == 0) {
			AfxMessageBox(L"0으로 나눌 수 없습니다.");
			return;
		}
		m_dValue /= dValue;
	}

	sEditStr.Format(L"%.8f", m_dValue);
	sEditStr = RemoveTrailingZeroes(sEditStr);
	SetDlgItemText(IDC_EDIT_NUM, sEditStr);

	m_sBeforeOp = ch;
	m_bChangeFlag = true;
}

//void CMyCalculatorDlg::OnBnClickedNum0Btn() { on_clicked_number('0'); }
//void CMyCalculatorDlg::OnBnClickedNum1Btn() { on_clicked_number('1'); }
//void CMyCalculatorDlg::OnBnClickedNum2Btn() { on_clicked_number('2'); }
//void CMyCalculatorDlg::OnBnClickedNum3Btn() { on_clicked_number('3'); }
//void CMyCalculatorDlg::OnBnClickedNum4Btn() { on_clicked_number('4'); }
//void CMyCalculatorDlg::OnBnClickedNum5Btn() { on_clicked_number('5'); }
//void CMyCalculatorDlg::OnBnClickedNum6Btn() { on_clicked_number('6'); }
//void CMyCalculatorDlg::OnBnClickedNum7Btn() { on_clicked_number('7'); }
//void CMyCalculatorDlg::OnBnClickedNum8Btn() { on_clicked_number('8'); }
//void CMyCalculatorDlg::OnBnClickedNum9Btn() { on_clicked_number('9'); }
//void CMyCalculatorDlg::OnBnClickedPointBtn() { on_clicked_number('.'); }
//
//void CMyCalculatorDlg::OnBnClickedAddBtn() { on_clicked_operator('+'); }
//void CMyCalculatorDlg::OnBnClickedSubBtn() { on_clicked_operator('-'); }
//void CMyCalculatorDlg::OnBnClickedMulBtn() { on_clicked_operator('*'); }
//void CMyCalculatorDlg::OnBnClickedDivBtn() { on_clicked_operator('/'); }
//void CMyCalculatorDlg::OnBnClickedResultBtn() { on_clicked_operator('='); }

void CMyCalculatorDlg::OnBnClickedClearBtn()
{
	SetDlgItemText(IDC_EDIT_NUM, L"0");
	m_dValue = 0;
	m_sBeforeOp = '=';
	m_bChangeFlag = false;
}

