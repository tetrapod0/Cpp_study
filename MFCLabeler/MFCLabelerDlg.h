
// MFCLabelerDlg.h: 헤더 파일
//

#pragma once

#include "mypoly.h"
#include <opencv2/opencv.hpp>
#include <filesystem>

namespace fs = std::filesystem;


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
	afx_msg void OnBnClickedCopyBtn();
	afx_msg void OnBnClickedDelBtn();
	afx_msg void OnBnClickedRotateBtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
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
	fs::path m_json_path;
	
public:
	void draw_canvas_PC();
	void draw_crop_PC();
	void set_name_edit();
	bool mouse_pt_in_control(const CPoint& point, int nID);
	void mat_to_cimg(const cv::Mat& mat, CImage& c_img);
	void zoom_canvas(CPoint cur, float& current_mag, float add_mag);
	void init_values();
	void open_file_path(CString file_path);
	std::wstring StringToWString(const std::string& str);
	std::string WStringToString(const std::wstring& wstr);
};
