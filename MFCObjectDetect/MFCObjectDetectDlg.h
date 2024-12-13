
// MFCObjectDetectDlg.h: 헤더 파일
//

#pragma once

#include <vector>


// CMFCObjectDetectDlg 대화 상자
class CMFCObjectDetectDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCObjectDetectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCOBJECTDETECT_DIALOG };
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
	afx_msg void OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);

private:
	CTabCtrl* m_pTab;
	std::vector<CDialogEx*> m_pDlgList;
	int m_selected_tab = 0;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
