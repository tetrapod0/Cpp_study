#pragma once
#include "afxdialogex.h"

// CVisionDlg 대화 상자

class CVisionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionDlg)

public:
	CVisionDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CVisionDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBnClickedStartBtn();
	afx_msg void OnBnClickedTestBtn();

private:
	bool m_running = false;
	CWnd* m_pGroup = nullptr;
	CWnd* m_pGObject = nullptr;
	CWnd* m_pGNumber = nullptr;
	CWnd* m_pGBarcode = nullptr;

	CStatic s;
public:
};
