// NewDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCAddDlg.h"
#include "afxdialogex.h"
#include "NewDlg.h"


// NewDlg 대화 상자

IMPLEMENT_DYNAMIC(NewDlg, CDialogEx)

NewDlg::NewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

NewDlg::~NewDlg()
{
}

void NewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NewDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &NewDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &NewDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// NewDlg 메시지 처리기


BOOL NewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_NEW_EDIT, m_str);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void NewDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_NEW_EDIT, m_str);

	CDialogEx::OnOK();
}


void NewDlg::OnBnClickedButton1()
{
	EndDialog(20);
}
