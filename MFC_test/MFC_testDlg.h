
// MFC_testDlg.h: 헤더 파일
//

#pragma once

#include <string>

// CMFCtestDlg 대화 상자
class CMFCtestDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCtestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton testest;
	afx_msg void OnBnClickedButton2();
	CStatic m_pic_con;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	std::wstring StringToWString(const std::string& str);
	std::string WStringToString(const std::wstring& wstr);
	std::string ANSIToUTF8(const std::string& ansiStr);
	std::string UTF8ToANSI(const std::string& utf8Str);
};
