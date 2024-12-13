#pragma once
#include "afxdialogex.h"


// CLabelerDlg 대화 상자

class CLabelerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLabelerDlg)

public:
	CLabelerDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLabelerDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LABELER_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
