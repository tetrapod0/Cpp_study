#pragma once
#include "afxdialogex.h"

#include <opencv2/opencv.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "polyDetector.h"

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

// 자동 생성 함수 관련
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStartBtn();
	afx_msg void OnBnClickedTestBtn();

private:
	// 실행, 종료
	bool running = false;

	// opencv 관련
	cv::VideoCapture cap;
	cv::Mat raw_img;
	
	// poly 관련
	poly::PolyDetector* poly_detector = nullptr;


	// 스레드 관련
	std::vector<std::thread> thr_list;
	std::mutex raw_img_lock;
	std::condition_variable cv;


	CImage m_cimg;


public:
	void erase_memDC();
	void img_producer();
	void grab_img();
	void show_main_img();


};
