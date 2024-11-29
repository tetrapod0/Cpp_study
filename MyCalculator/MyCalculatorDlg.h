
// MyCalculatorDlg.h: 헤더 파일
//

#pragma once


// CMyCalculatorDlg 대화 상자
class CMyCalculatorDlg : public CDialogEx
{
// 생성입니다.
public:
	CMyCalculatorDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYCALCULATOR_DIALOG };
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

protected:
	void on_clicked_number(char sNum);
	void on_clicked_operator(char sOper);
	CString RemoveTrailingZeroes(CString str);
	wchar_t m_sBeforeOp = L'=';
	bool m_bChangeFlag = false;
	double m_dValue = 0;

public:
	//afx_msg void OnBnClickedNum0Btn();
	//afx_msg void OnBnClickedNum1Btn();
	//afx_msg void OnBnClickedNum2Btn();
	//afx_msg void OnBnClickedNum3Btn();
	//afx_msg void OnBnClickedNum4Btn();
	//afx_msg void OnBnClickedNum5Btn();
	//afx_msg void OnBnClickedNum6Btn();
	//afx_msg void OnBnClickedNum7Btn();
	//afx_msg void OnBnClickedNum8Btn();
	//afx_msg void OnBnClickedNum9Btn();
	//afx_msg void OnBnClickedPointBtn();
	void OnBnClickedNumBtn(UINT id);
	void OnBnClickedOperBtn(UINT id);

	//afx_msg void OnBnClickedResultBtn();
	//afx_msg void OnBnClickedAddBtn();
	//afx_msg void OnBnClickedSubBtn();
	//afx_msg void OnBnClickedMulBtn();
	//afx_msg void OnBnClickedDivBtn();

	afx_msg void OnBnClickedClearBtn();
};
