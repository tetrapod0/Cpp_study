﻿
// ExamMFC003Dlg.h: 헤더 파일
//

#pragma once


// CExamMFC003Dlg 대화 상자
class CExamMFC003Dlg : public CDialogEx
{
// 생성입니다.
public:
	CExamMFC003Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXAMMFC003_DIALOG };
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
	afx_msg void OnBnClickedReadBtn();
	afx_msg void OnBnClickedWriteBtn();
//protected:
//	int m_my_value;
};
