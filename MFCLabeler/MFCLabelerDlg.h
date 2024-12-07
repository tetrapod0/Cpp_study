﻿
// MFCLabelerDlg.h: 헤더 파일
//

#pragma once


// CMFCLabelerDlg 대화 상자
class CMFCLabelerDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCLabelerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCLABELER_DIALOG };
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
public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedDelBtn();
	afx_msg void OnBnClickedRotateBtn();
	afx_msg void OnBnClickedClearBtn();
};


