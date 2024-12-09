
// MFCLabelerDlg.h: 헤더 파일
//

#pragma once

#include "mypoly.h"

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

private:
	std::vector<PolyControl> m_poly_list;
	bool m_vertex_is_clicked = false;
	bool m_poly_is_clicked = false;
	bool m_bg_is_clicked = false;
	int m_seleted_point = -1;
	CPoint m_prev_cur;
	CImage m_bg_img;
	CPoint m_bg_pos;

public:
	void on_draw_PC();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedCopyBtn();
};
