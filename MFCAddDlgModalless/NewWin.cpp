// CNewWin.cpp: 구현 파일
//

#include "pch.h"
#include "MFCAddNewWin.h"
#include "afxdialogex.h"
#include "NewWin.h"

// 클래스 static 변수 초기화는 꼭 외부에서!
CNewWin* CNewWin::m_SelfPtr = nullptr;

// CNewWin 대화 상자

IMPLEMENT_DYNAMIC(CNewWin, CDialogEx)

CNewWin::CNewWin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_SelfPtr = this; // sigleton
}

CNewWin::~CNewWin()
{
}

void CNewWin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewWin, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CNewWin::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNewWin::OnBnClickedCancel)
END_MESSAGE_MAP()


// CNewWin 메시지 처리기

#include "MFCAddNewWinDlg.h"


bool CNewWin::check_opened() {
	return m_SelfPtr != nullptr;
}

void CNewWin::OnClose()
{
	//CWnd* pWnd = GetParent();
	//CMFCAddNewWinDlg* pParent = dynamic_cast<CMFCAddNewWinDlg*>(pWnd); // cast 변환실패하면 nullptr
	//if (pParent != nullptr) pParent->notice_close_child();
	//CDialogEx::OnClose();
	DestroyWindow();
	m_SelfPtr = nullptr;
	delete this;
}

void CNewWin::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
	// 여기에 부모콜백함수 추가하면될듯
	OnClose();
}

void CNewWin::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
	OnClose();
}
