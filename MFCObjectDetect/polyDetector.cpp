#include "pch.h"
#include "polyDetector.h"

namespace poly {
	float get_pseudo_width(const std::vector<cv::Point2f>& pts) {
		cv::Point2f d = pts[0] - pts[1];
		float len = sqrt(pow(d.x, 2) + pow(d.y, 2));
		d = pts[2] - pts[3];
		len += sqrt(pow(d.x, 2) + pow(d.y, 2));
		return len / 2;
	}
	float get_pseudo_height(const std::vector<cv::Point2f>& pts) {
		cv::Point2f d = pts[1] - pts[2];
		float len = sqrt(pow(d.x, 2) + pow(d.y, 2));
		d = pts[0] - pts[3];
		len += sqrt(pow(d.x, 2) + pow(d.y, 2));
		return len / 2;
	}


	cv::Mat crop_img_and_get_M(const cv::Mat& src_img, cv::Mat& dst_crop_img, const std::vector<cv::Point2f>& poly, cv::Size size) {
		// 사전에 구한 w,h가 없으면
		float w = (size.width) ? size.width : poly::get_pseudo_width(poly);
		float h = (size.height) ? size.height : poly::get_pseudo_width(poly);

		// 이미지 크롭
		std::vector<cv::Point2f> dst_poly = {
			{0,0},{w,0},{w,h},{0,h}
		};
		cv::Mat convertor_M = cv::getPerspectiveTransform(poly, dst_poly);
		cv::warpPerspective(src_img, dst_crop_img, convertor_M, cv::Size(w,h));
		return convertor_M;
	}
}