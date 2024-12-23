#pragma once
#include "afxdialogex.h"

#include <opencv2/opencv.hpp>
#include <opencv2/freetype.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <tuple>

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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
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

	// raw_q
	std::queue<cv::Mat> raw_q;
	std::mutex raw_q_mtx;
	std::condition_variable raw_q_cv;

	// pred_q
	std::queue<std::tuple<bool, cv::Mat, poly::ObjInfo, cv::Mat>> pred_q;
	std::mutex pred_q_mtx;
	std::condition_variable pred_q_cv;

	// show_q
	std::queue<std::tuple<cv::Mat, std::map<std::string, cv::Mat>>> show_q;
	std::mutex show_q_mtx;
	std::condition_variable show_q_cv;

	// nimg_q
	std::queue<std::tuple<cv::Mat, cv::Mat>> dataimg_q;
	std::mutex dataimg_q_mtx;
	std::condition_variable dataimg_q_cv;




public:
	void erase_DC(int nID, COLORREF fill_color = RGB(240, 240, 240));
	void draw_matimg_PC(const cv::Mat& mat_img, int nID);
	void draw_c_img_PC(const CImage& c_img, int nID, CRect* drawing_rect = nullptr, COLORREF fill_color = RGB(240, 240, 240));
	void mat_to_cimg(const cv::Mat& mat_img, CImage& c_img);

	void grab_img_proc(); // raw_q -> detect_poly_proc
	bool grab_img(cv::Mat& raw_img);
	void detect_poly_proc(); // pred_q -> crop_and_draw_proc
	void crop_and_draw_proc(); // show_q -> paint_img_proc, dataimg_q -> recog_img_proc
	void paint_img_proc();
	void recog_img_proc();

};
