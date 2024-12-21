#pragma once
#include "afxdialogex.h"

#include <opencv2/opencv.hpp>
#include <opencv2/freetype.hpp>
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
	cv::Ptr<cv::freetype::FreeType2> ft2;
	
	// poly 관련
	poly::PolyDetector poly_detector;


	// 스레드 관련
	std::vector<std::thread> thr_list;

	// raw_img
	cv::Mat raw_img;
	bool raw_img_ready = false;
	std::mutex raw_img_mtx;
	std::condition_variable raw_img_cv;

	// ana_img
	cv::Mat ana_img;
	bool ana_img_ready = false;
	std::mutex ana_img_mtx;
	std::condition_variable ana_img_cv;




public:
	void erase_DC(int nID, COLORREF fill_color = RGB(240, 240, 240));

	void img_producer();
	void grab_img();

	void img_analyst();

	void img_painter();
	void draw_matimg_PC(const cv::Mat& mat_img, int nID);
	void draw_c_img_PC(const CImage& c_img, int nID, CRect* drawing_rect = nullptr, COLORREF fill_color = RGB(240, 240, 240));
	void mat_to_cimg(const cv::Mat& mat_img, CImage& c_img);


};
