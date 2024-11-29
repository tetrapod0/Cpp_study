
// MFCMoveShapeDlg.h: 헤더 파일
//

#pragma once


// CMFCMoveShapeDlg 대화 상자
class CMFCMoveShapeDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCMoveShapeDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCMOVESHAPE_DIALOG };
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
	CRect m_rect;
	bool m_is_clicked = false;
	CPoint m_prev_pos;

	void CMFCMoveShapeDlg::OnDraw(CDC* pDC);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
