// Setting.cpp: 구현 파일
//

#include "pch.h"
#include "MFCObjectDetect.h"
#include "afxdialogex.h"
#include "SettingDlg.h"


// CSetting 대화 상자

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_DLG, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
END_MESSAGE_MAP()


// CSetting 메시지 처리기


BOOL CSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    if (pMsg->message == WM_KEYDOWN) {
        // 단순 ESC 키 입력시 창 닫힘 제거
        if (pMsg->wParam == VK_ESCAPE) return TRUE;
        // 단순 Enter 키 입력시 창 닫힘 제거
        else if (pMsg->wParam == VK_RETURN) return TRUE;
    }

	return CDialogEx::PreTranslateMessage(pMsg);
}
