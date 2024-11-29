#pragma once
#include "afxdialogex.h"


// CNewWin 대화 상자

class CNewWin : public CDialogEx
{
	DECLARE_DYNAMIC(CNewWin)

public:
	CNewWin(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNewWin();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

protected:
	static CNewWin* m_SelfPtr; // singleton // 초기화는 외부에서
public:
	static bool check_opened();
};
