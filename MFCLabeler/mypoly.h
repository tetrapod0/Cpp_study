#pragma once


#include <vector>
#include <opencv2/opencv.hpp>
#include <cassert>

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

	std::vector<cv::Point2f> get_points() const {
		std::vector<cv::Point2f> new_points;
		for (int i = 0; i < points.size(); ++i) {
			new_points.push_back(cv::Point2f(points[i]));
		}
		return new_points;
	}

	cv::Point2f get_point(int idx) const {
		assert(0 <= idx && idx < points.size());
		return cv::Point2f(points[idx]);
	}

	template <typename T>
	T get_point(int idx) const {
		assert(0 <= idx && idx < points.size());
		return T(points[idx].x, points[idx].y);
	}

	Poly& operator+=(const Poly& poly) {
		for (int i = 0; i < points.size(); ++i) {
			points[i] += poly.points[i];
		}
		return *this;
	}

	Poly& operator+=(const cv::Point2f& pt) { //move
		for (int i = 0; i < points.size(); ++i) {
			points[i] += pt;
		}
		return *this;
	}

	Poly& operator*=(const float v) {
		for (int i = 0; i < points.size(); ++i) {
			points[i] *= v;
		}
		return *this;
	}

	void move_point(float x, float y, int idx) {
		assert(0 <= idx && idx < points.size());
		//if (idx < 0 || points.size() <= idx) {
		//	throw std::invalid_argument("인덱스 범위 벗어남");
		//}
		points[idx].x += x;
		points[idx].y += y;
	}

	void move_poly(float x, float y) {
		for (int i = 0; i < points.size(); ++i) {
			move_point(x, y, i);
		}
	}
};



#include "afxdialogex.h"
#include <random>

class PolyControl : public Poly {
private:
	int m_pt_size = 8;
	COLORREF m_color;
	std::vector<int> seq_list;

	void set_color() {
		// 난수 생성 엔진과 분포 정의
		std::random_device rd; // 실제 랜덤 시드
		std::mt19937 gen(rd()); // Mersenne Twister 엔진
		std::uniform_int_distribution<int> dis(100, 200);
		m_color = RGB(dis(gen), dis(gen), dis(gen));
	}


public:
	PolyControl(cv::Point2f tl, cv::Point2f tr, cv::Point2f br, cv::Point2f bl)
		: Poly(tl, tr, br, bl) {
		set_color();
		seq_list.assign({ 0,1,2,3 });
	}
	PolyControl(float tl_x, float tl_y, float tr_x, float tr_y, float br_x, float br_y, float bl_x, float bl_y)
		: Poly(tl_x, tl_y, tr_x, tr_y, br_x, br_y, bl_x, bl_y) {
		set_color();
		seq_list.assign({ 0,1,2,3 });
	}
	PolyControl(const PolyControl& pc) : Poly(pc) {
		m_color = pc.m_color;
		//seq_list = pc.seq_list;
		seq_list.insert(seq_list.end(), pc.seq_list.begin(), pc.seq_list.end());
	}


	void draw_poly(CDC* pDC) {
		// 펜 교체
		CPen pen(PS_SOLID, 2, m_color);
		CPen* pOldPen = pDC->SelectObject(&pen);

		// 그리기
		pDC->MoveTo(this->get_point<CPoint>(0));
		for (int i = 1; i < this->points.size(); ++i) {
			pDC->LineTo(this->get_point<CPoint>(i));
		}
		pDC->LineTo(this->get_point<CPoint>(0));

		// 펜 복원
		pDC->SelectObject(pOldPen);
	}


	void draw_points(CDC* pDC) {
		// 펜, 브러쉬 교체
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		//CBrush brush(m_color);
		CBrush brush(RGB(0, 255, 0));
		CPen* pOldPen = pDC->SelectObject(&pen);
		CBrush* pOldBrush = pDC->SelectObject(&brush);

		// 그리기
		CPoint pos;
		CRect rect;
		CString str;
		pDC->SetBkMode(TRANSPARENT); // 글자 배경 투명
		for (int i = 0; i < this->points.size(); ++i) {
			pos = this->get_point<CPoint>(i);
			rect.SetRect(pos, pos);
			rect.InflateRect(m_pt_size, m_pt_size);
			pDC->Ellipse(rect);
			str.Format(L"%d", seq_list[i]);
			pDC->DrawText(str, &rect, DT_CENTER | DT_VCENTER);
		}

		// 펜, 브러쉬 복원
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
	}


	bool cur_in_point(CPoint& cur, int idx) {
		assert(0 <= idx && idx < this->points.size());
		CPoint pos = this->get_point<CPoint>(idx);
		CRect rect;
		rect.SetRect(pos, pos);
		rect.InflateRect(m_pt_size, m_pt_size);
		return rect.PtInRect(cur);
	}


	bool cur_in_poly(CPoint& cur) {
		CPoint pos1, pos2;

		pos1 = this->get_point<CPoint>(0);
		pos2 = this->get_point<CPoint>(1);
		int sign = get_sign_cross_product<CPoint>(pos2 - pos1, cur - pos1);

		// AB X AP 가 모두 같으면 pt는 안에 있음
		for (int i = 1; i < points.size(); ++i) {
			pos1 = this->get_point<CPoint>(i);
			pos2 = this->get_point<CPoint>((i+1)%points.size());
			int sign2 = get_sign_cross_product<CPoint>(pos2 - pos1, cur - pos1);
			if (sign != sign2) return false;
		}
		return true;
	}


	template <typename T>
	int get_sign_cross_product(T vec1, T vec2) {
		float result = vec1.x * vec2.y - vec1.y * vec2.x;
		return (result >= 0 ? 1 : -1);
	}


	// override
	void move_point(float x, float y, int idx) {
		static auto min3 = [](float a, float b, float c) {return std::min<float>(std::min<float>(a, b), c);};
		static auto max3 = [](float a, float b, float c) {return std::max<float>(std::max<float>(a, b), c);};
		if (idx < 0 || 4 <= idx) return;

		cv::Point2f& pos = points[idx];
		pos += cv::Point2f(x, y);
		const cv::Point2f& pos1 = points[(idx + 1) % 4];
		const cv::Point2f& pos2 = points[(idx + 2) % 4];
		const cv::Point2f& pos3 = points[(idx + 3) % 4];
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
	}


	CRect get_surrounding_rect() {
		CPoint pos1 = this->get_point<CPoint>(0);
		CPoint pos2 = this->get_point<CPoint>(0);
		
		// pos1은 최소 좌표, pos2은 최대 좌표
		for (int i = 0; i < points.size(); ++i) {
			if (pos1.x > points[i].x) pos1.x = points[i].x;
			if (pos1.y > points[i].y) pos1.y = points[i].y;
			if (pos2.x < points[i].x) pos2.x = points[i].x;
			if (pos2.y < points[i].y) pos2.y = points[i].y;
		}

		CRect rect(pos1, pos2);
		rect.InflateRect(m_pt_size, m_pt_size);
		return rect;
	}


	void rotate_sequence() {
		seq_list.push_back(seq_list.front());
		seq_list.erase(seq_list.begin());
	}
};