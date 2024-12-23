#pragma once
#include "afxdialogex.h"

#include <opencv2/opencv.hpp>
#include <filesystem>
#include "polyLabeler.h"

namespace fs = std::filesystem;

// CLabelerDlg 대화 상자

class CLabelerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLabelerDlg)

public:
	CLabelerDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLabelerDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LABELER_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedLoadBtn();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedCopyBtn();
	afx_msg void OnBnClickedDelBtn();
	afx_msg void OnBnClickedRotateBtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);

private:
	const std::string m_dataset_path = "dataset";
	std::vector<PolyControl> m_poly_list;
	bool m_vertex_is_clicked = false;
	bool m_poly_is_clicked = false;
	bool m_bg_is_clicked = false;
	int m_seleted_point = -1;
	CPoint m_prev_cur;
	CImage m_bg_img;
	cv::Point2f m_bg_pos; // 캔버스에서 이미지 시작 위치
	cv::Mat m_origin_bg;
	float m_bg_mag = 1;
	fs::path m_img_extension = ".jpg";
	//fs::path m_img_path; // 저장할 img 경로
	//fs::path m_json_path; // 저장할 json 경로

public:
	void draw_canvas_PC();
	void draw_crop_PC();
	void set_label_edit();
	bool mouse_pt_in_control(const CPoint& point, int nID);
	void mat_to_cimg(const cv::Mat& mat, CImage& c_img);
	void zoom_canvas(CPoint cur, float& current_mag, float add_mag);
	void init_values();
	void open_file_path(CString file_path);
	void fit_font_size(int nID);
	std::wstring StringToWString(const std::string& str);
	std::string WStringToString(const std::wstring& wstr);
};
