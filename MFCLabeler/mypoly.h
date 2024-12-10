#pragma once


#include <vector>
#include <opencv2/opencv.hpp>

class Poly {
protected:
	std::vector<cv::Point2f> points;

public:
	Poly(cv::Point2f tl, cv::Point2f tr, cv::Point2f br, cv::Point2f bl) {
		points.push_back(tl);
		points.push_back(tr);
		points.push_back(br);
		points.push_back(bl);
	}
	Poly(float tl_x, float tl_y, float tr_x, float tr_y,
		float br_x, float br_y, float bl_x, float bl_y) {
		points.push_back(cv::Point2f(tl_x, tl_y));
		points.push_back(cv::Point2f(tr_x, tr_y));
		points.push_back(cv::Point2f(br_x, br_y));
		points.push_back(cv::Point2f(bl_x, bl_y));
	}
	Poly(const Poly& p) : points(p.points) {}

	virtual std::vector<cv::Point2f> get_points() const {
		std::vector<cv::Point2f> new_points;
		for (int i = 0; i < points.size(); ++i) {
			new_points.push_back(points[i]);
		}
		return new_points;
	}

	cv::Point2f get_point(int idx) const {
		return cv::Point2f(points[idx]);
	}

	template <typename T>
	T get_point(int idx) const {
		return T(points[idx].x, points[idx].y);
	}

	virtual void operator+=(const Poly& poly) {
		for (int i = 0; i < points.size(); ++i) {
			points[i] += poly.points[i];
		}
	}

	virtual void operator+=(const cv::Point2f& pt) { //move
		for (int i = 0; i < points.size(); ++i) {
			points[i] += pt;
		}
	}

	virtual void operator-=(const Poly& poly) {
		for (int i = 0; i < points.size(); ++i) {
			points[i] -= poly.points[i];
		}
	}

	virtual void operator-=(const cv::Point2f& pt) { //move
		for (int i = 0; i < points.size(); ++i) {
			points[i] -= pt;
		}
	}

	virtual void operator*=(const float v) {
		for (int i = 0; i < points.size(); ++i) {
			points[i] *= v;
		}
	}

	virtual void operator/=(const float v) {
		for (int i = 0; i < points.size(); ++i) {
			points[i] /= v;
		}
	}

	virtual Poly& move_point(float x, float y, int idx) {
		points[idx].x += x;
		points[idx].y += y;
		return *this;
	}

	virtual Poly& move_poly(float x, float y) {
		for (int i = 0; i < points.size(); ++i) {
			this->move_point(x, y, i);
		}
		return *this;
	}
};


#include "afxdialogex.h"
#include <random>
//#include <cmath>

class PolyControl : public Poly {
private:
	int m_pt_size = 8;
	COLORREF m_color;
	std::vector<int> m_show_seq_list = { 0, 1, 2, 3 };
	std::vector<int> m_pick_seq_list = { 0, 1, 2, 3 };
	CString m_name = L"";

	void set_color() {
		// 난수 생성 엔진과 분포 정의
		std::random_device rd; // 실제 랜덤 시드
		std::mt19937 gen(rd()); // Mersenne Twister 엔진
		std::uniform_int_distribution<int> dis(100, 200);
		m_color = RGB(dis(gen), dis(gen), dis(gen));
	}


	template <typename T>
	int get_sign_cross_product(T vec1, T vec2) {
		float result = vec1.x * vec2.y - vec1.y * vec2.x;
		return (result >= 0 ? 1 : -1);
	}


public:
	PolyControl(cv::Point2f tl, cv::Point2f tr, cv::Point2f br, cv::Point2f bl)
		: Poly(tl, tr, br, bl) {
		this->set_color();
	}
	PolyControl(float tl_x, float tl_y, float tr_x, float tr_y, float br_x, float br_y, float bl_x, float bl_y)
		: Poly(tl_x, tl_y, tr_x, tr_y, br_x, br_y, bl_x, bl_y) {
		this->set_color();
	}
	PolyControl(const PolyControl& pc) : Poly(pc) {
		m_color = pc.m_color;
		m_show_seq_list = pc.m_show_seq_list; // vector의 복사생성자?
		m_pick_seq_list = pc.m_pick_seq_list; // vector의 복사생성자?
		m_name = pc.m_name;
		//seq_list.insert(seq_list.end(), pc.seq_list.begin(), pc.seq_list.end());
	}

	std::vector<cv::Point2f> get_points() const override {
		std::vector<cv::Point2f> new_points;
		for (auto& i : m_pick_seq_list) {
			new_points.push_back(points[i]); // 복사생성자
		}
		return new_points;
	}

	void operator+=(const CPoint& pt) { //move
		Poly::operator+=(cv::Point2f(pt.x, pt.y));
	}
	void operator+=(const cv::Point2f& pt) override { //move
		Poly::operator+=(pt);
	}
	void operator-=(const CPoint& pt) { //move
		Poly::operator-=(cv::Point2f(pt.x, pt.y));
	}
	void operator-=(const cv::Point2f& pt) override { //move
		Poly::operator-=(pt);
	}


	PolyControl& move_poly(float x, float y) override {
		Poly::move_poly(x, y);
		return *this;
	}
	PolyControl& move_point(float x, float y, int idx) override {
		static auto min3 = [](float a, float b, float c) {return std::min<float>(std::min<float>(a, b), c);};
		static auto max3 = [](float a, float b, float c) {return std::max<float>(std::max<float>(a, b), c);};
		if (idx < 0 || 4 <= idx) return *this;

		cv::Point2f& pos = Poly::points[idx];
		pos += cv::Point2f(x, y);
		const cv::Point2f& pos1 = Poly::points[(idx + 1) % 4];
		const cv::Point2f& pos2 = Poly::points[(idx + 2) % 4];
		const cv::Point2f& pos3 = Poly::points[(idx + 3) % 4];
		if (idx == 0) {
			pos.x = min3(pos.x, pos1.x, pos2.x);
			pos.y = min3(pos.y, pos2.y, pos3.y);
		}
		else if (idx == 1) {
			pos.x = max3(pos.x, pos2.x, pos3.x);
			pos.y = min3(pos.y, pos1.y, pos2.y);
		}
		else if (idx == 2) {
			pos.x = max3(pos.x, pos1.x, pos2.x);
			pos.y = max3(pos.y, pos2.y, pos3.y);
		}
		else {
			pos.x = min3(pos.x, pos2.x, pos3.x);
			pos.y = max3(pos.y, pos1.y, pos2.y);
		}
		return *this;
	}


	PolyControl& rotate_sequence() {
		// 정방향
		m_show_seq_list.insert(m_show_seq_list.begin(), m_show_seq_list.back());
		m_show_seq_list.pop_back();
		// 역방향
		m_pick_seq_list.push_back(m_pick_seq_list.front());
		m_pick_seq_list.erase(m_pick_seq_list.begin());
		return *this;
	}


	void draw_poly(CDC* pDC) {
		// 펜 교체
		CPen pen(PS_SOLID, 2, m_color);
		CPen* pOldPen = pDC->SelectObject(&pen);

		// 그리기
		pDC->MoveTo(Poly::get_point<CPoint>(0));
		for (int i = 1; i < Poly::points.size(); ++i) {
			pDC->LineTo(Poly::get_point<CPoint>(i));
		}
		pDC->LineTo(Poly::get_point<CPoint>(0));

		// 펜 복원
		pDC->SelectObject(pOldPen);
	}


	void draw_points(CDC* pDC) {
		// 펜, 브러쉬 등 생성
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		//CBrush brush(m_color);
		CBrush brush(RGB(0, 255, 0));
		CFont font;
		font.CreatePointFont(100, L"Arial");

		// 펜, 브러쉬 등 교체
		CPen* pOldPen = pDC->SelectObject(&pen);
		CBrush* pOldBrush = pDC->SelectObject(&brush);
		COLORREF oldTextColor = pDC->SetTextColor(RGB(0, 0, 0));
		int oldBkMode = pDC->SetBkMode(TRANSPARENT); // 글자 배경 투명
		CFont* pOldFont = pDC->SelectObject(&font);

		// 그리기
		CPoint pos;
		CRect rect;
		CString str;

		for (int i = 0; i < Poly::points.size(); ++i) {
			pos = Poly::get_point<CPoint>(i);
			rect.SetRect(pos, pos);
			rect.InflateRect(m_pt_size, m_pt_size);
			pDC->Ellipse(rect);
			str.Format(L"%d", m_show_seq_list[i]);
			pDC->DrawText(str, &rect, DT_CENTER | DT_VCENTER);
		}

		// 펜, 브러쉬 복원
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
		pDC->SetTextColor(oldTextColor);
		pDC->SetBkMode(oldBkMode);
		pDC->SelectObject(pOldFont);
	}


	void draw_name(CDC* pDC) {
		// 폰트 생성
		CFont font;
		font.CreatePointFont(200, L"Arial");

		// 글자색, 모드, 폰트 교체
		COLORREF oldTextColor = pDC->SetTextColor(m_color);
		int oldBkMode = pDC->SetBkMode(TRANSPARENT); // 글자 배경 투명
		CFont* pOldFont = pDC->SelectObject(&font);

		// 글자 크기 계산후 그리기
		if (Poly::points.size() && !m_name.IsEmpty()) {
			CPoint pos = Poly::get_point<CPoint>(0);
			pos.y -= 30;
			CRect rect(0, 0, 0, 0);
			pDC->DrawText(m_name, &rect, DT_SINGLELINE | DT_CALCRECT);
			rect.OffsetRect(pos);
			pDC->DrawText(m_name, &rect, DT_SINGLELINE | DT_LEFT | DT_TOP);
		}

		// 글자색, 모드, 폰트 복원
		pDC->SetTextColor(oldTextColor);
		pDC->SetBkMode(oldBkMode);
		pDC->SelectObject(pOldFont);
	}


	bool cur_in_point(CPoint& cur, int idx) {
		assert(0 <= idx && idx < Poly::points.size());
		CPoint pos = Poly::get_point<CPoint>(idx);
		CRect rect;
		rect.SetRect(pos, pos);
		rect.InflateRect(m_pt_size, m_pt_size);
		return rect.PtInRect(cur);
	}


	bool cur_in_poly(CPoint& cur) {
		CPoint pos1, pos2;

		pos1 = Poly::get_point<CPoint>(0);
		pos2 = Poly::get_point<CPoint>(1);
		int sign = this->get_sign_cross_product<CPoint>(pos2 - pos1, cur - pos1);

		// AB X AP 가 모두 같으면 pt는 안에 있음 // 모든 내각이 180도 이하인 경우만 성립
		for (int i = 1; i < Poly::points.size(); ++i) {
			pos1 = Poly::get_point<CPoint>(i);
			pos2 = Poly::get_point<CPoint>((i + 1) % Poly::points.size());
			int sign2 = this->get_sign_cross_product<CPoint>(pos2 - pos1, cur - pos1);
			if (sign != sign2) return false;
		}
		return true;
	}


	CRect get_surrounding_rect() {
		CPoint pos1 = Poly::get_point<CPoint>(0);
		CPoint pos2 = Poly::get_point<CPoint>(0);
		
		// pos1은 최소 좌표, pos2은 최대 좌표
		for (int i = 0; i < Poly::points.size(); ++i) {
			if (pos1.x > Poly::points[i].x) pos1.x = Poly::points[i].x;
			if (pos1.y > Poly::points[i].y) pos1.y = Poly::points[i].y;
			if (pos2.x < Poly::points[i].x) pos2.x = Poly::points[i].x;
			if (pos2.y < Poly::points[i].y) pos2.y = Poly::points[i].y;
		}

		CRect rect(pos1, pos2);
		rect.InflateRect(m_pt_size, m_pt_size);
		return rect;
	}


	PolyControl& set_name(const CString& name) {
		m_name = name;
		return *this;
	}


	cv::Mat get_crop_img_and_M(const cv::Mat& src_img, cv::Mat& dst_img) const {

		auto src_pts = this->get_points();
		float w = get_semi_width(src_pts);
		float h = get_semi_height(src_pts);
		std::vector<cv::Point2f> dst_pts = { {0,0},{w,0},{w,h},{0,h} };
		cv::Mat convertor_M = cv::getPerspectiveTransform(src_pts, dst_pts);
		cv::warpPerspective(src_img, dst_img, convertor_M, cv::Size(w, h));
		return convertor_M;
	}


	float get_semi_width(const std::vector<cv::Point2f>& pts) const {
		cv::Point2f d = pts[0] - pts[1];
		float len = sqrt(pow(d.x, 2) + pow(d.y, 2));
		d = pts[2] - pts[3];
		len += sqrt(pow(d.x, 2) + pow(d.y, 2));
		return len / 2;
	}
	float get_semi_height(const std::vector<cv::Point2f>& pts) const {
		cv::Point2f d = pts[1] - pts[2];
		float len = sqrt(pow(d.x, 2) + pow(d.y, 2));
		d = pts[0] - pts[3];
		len += sqrt(pow(d.x, 2) + pow(d.y, 2));
		return len / 2;
	}
	float get_semi_width() const {
		return get_semi_width(this->get_points());
	}
	float get_semi_height() const {
		return get_semi_width(this->get_points());
	}
};