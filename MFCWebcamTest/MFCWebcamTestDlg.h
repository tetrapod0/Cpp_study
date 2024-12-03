
// MFCWebcamTestDlg.h: 헤더 파일
//

#pragma once
#include <opencv2/opencv.hpp>

// CMFCWebcamTestDlg 대화 상자
class CMFCWebcamTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCWebcamTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCWEBCAMTEST_DIALOG };
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
	CDC m_memDC;
	CBitmap m_memBitmap;
	CBitmap* m_pOldBitmap;
	//CRect m_PicRect;
	//CRect m_DrawingRect;
	CImage m_cimg;
	cv::Mat m_matimg;
	cv::VideoCapture m_cap;

public:
	void InitializeDrawing();
	void CleanupDrawing();
	void DrawImageIoControl(const CImage& c_img, const CRect& pic_rect, const CRect& drawing_rect);
	void StartDrawingLoop();
	void StopDrawingLoop();
	void MatToCImage(const cv::Mat& mat, CImage& c_img);
	void show_img();
	void erase_memDC();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};


