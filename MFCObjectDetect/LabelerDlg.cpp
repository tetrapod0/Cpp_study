// LabelerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCObjectDetect.h"
#include "afxdialogex.h"
#include "LabelerDlg.h"


// CLabelerDlg 대화 상자

IMPLEMENT_DYNAMIC(CLabelerDlg, CDialogEx)

CLabelerDlg::CLabelerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LABELER_DLG, pParent)
{

}

CLabelerDlg::~CLabelerDlg()
{
}

void CLabelerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLabelerDlg, CDialogEx)
END_MESSAGE_MAP()


// CLabelerDlg 메시지 처리기
