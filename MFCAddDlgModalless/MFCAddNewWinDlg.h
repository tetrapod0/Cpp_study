
// MFCAddNewWinDlg.h: 헤더 파일
//

#pragma once
#include "NewWin.h"
#include <vector>

// CMFCAddNewWinDlg 대화 상자
class CMFCAddNewWinDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCAddNewWinDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCADDNEWWIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	//std::vector<CWnd*> m_vecCWndPtr;
	//CPtrList m_DlgPtrList;

public:
	//void close_child(CWnd* dlg_ptr);
	afx_msg void OnBnClickedButton1();
};
