#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include "json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;


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


	void crop_img(const cv::Mat& src_img, cv::Mat& dst_img, const std::vector<cv::Point2f>& poly, float w=0, float h=0) {
		// ������ ���� w,h�� ������
		w = (w)? w : get_pseudo_width(poly);
		h = (h)? h : get_pseudo_height(poly);
		// �̹��� ũ��
		std::vector<cv::Point2f> dst_poly = { {0,0},{w,0},{w,h},{0,h} };
		cv::Mat convertor_M = cv::getPerspectiveTransform(poly, dst_poly);
		cv::warpPerspective(src_img, dst_img, convertor_M, cv::Size(w, h));
	}


	struct ObjInfo {
		// first - label, second - polys // ����! object�� ���簢����
		std::unordered_map<std::string, std::vector<cv::Point2f>> src_poly_dic;
		std::unordered_map<std::string, cv::Size> src_poly_size_dic;
		std::vector<cv::KeyPoint> keypoints;
		cv::Mat descriptors;

		ObjInfo() {};
		ObjInfo(fs::path img_path, fs::path json_path, cv::ORB* detector) {
			// �̹��� �ҷ�����
			cv::Mat img_mat = cv::imread(img_path.string());
			cv::cvtColor(img_mat, img_mat, cv::COLOR_BGR2GRAY);

			// keypoints, descriptors �Ҵ�
			detector->detectAndCompute(img_mat, 0, keypoints, descriptors);

			// json �ҷ�����
			std::ifstream i(json_path.string(), std::ios::in);
			json data;
			i >> data;

			// shapes Ű �˻�
			if (!data.contains("shapes")) throw "json �����Ϳ� \"shapes\"�� �����ϴ�.";

			// src_poly_dic �Ҵ�
			for (auto& poly_data : data["shapes"]) {
				// Ű �˻�
				if (!poly_data.contains("label"))
					throw "json �����Ϳ� \"label\"�� �����ϴ�.";
				if (!poly_data.contains("points"))
					throw "json �����Ϳ� \"points\"�� �����ϴ�.";

				// �� �̸� ��� // map key
				std::string label_name = poly_data["label"].get<std::string>();

				// �� ��� // map value
				this->src_poly_dic[label_name] = {
					{poly_data["points"][0][0], poly_data["points"][0][1]},
					{poly_data["points"][1][0], poly_data["points"][1][1]},
					{poly_data["points"][2][0], poly_data["points"][2][1]},
					{poly_data["points"][3][0], poly_data["points"][3][1]}
				};
			}

			// src_poly_size_dic �Ҵ�
			for (const auto& [name, poly] : this->src_poly_dic) {
				int w = poly::get_pseudo_width(poly);
				int h = poly::get_pseudo_height(poly);
				this->src_poly_size_dic[name] = { w, h };
			}

		}
		ObjInfo(std::unordered_map<std::string, std::vector<cv::Point2f>> src_poly_dic,
			std::vector<cv::KeyPoint> keypoints, cv::Mat descriptors) {
			this->src_poly_dic = src_poly_dic;
			this->keypoints = keypoints;
			this->descriptors = descriptors;
			for (const auto& [name, poly] : src_poly_dic) {
				int w = poly::get_pseudo_width(poly);
				int h = poly::get_pseudo_height(poly);
				this->src_poly_size_dic[name] = { w, h };
			}
		}
		ObjInfo(const ObjInfo& o) {
			this->src_poly_dic = o.src_poly_dic;
			this->keypoints = o.keypoints;
			this->descriptors = o.descriptors;
			this->src_poly_size_dic = o.src_poly_size_dic;
		}
		~ObjInfo() {
			this->src_poly_dic.clear();
			this->src_poly_size_dic.clear();
			this->keypoints.clear();
			this->descriptors.release();
		}
	};


	class PolyDetector {
	private:
		cv::ORB* detector;
		cv::BFMatcher* matcher;
		std::unordered_map<std::string, ObjInfo> obj_info_dic;
		fs::path data_dir_path;


	public:
		PolyDetector() {
			this->detector = nullptr;
			this->matcher = nullptr;
		}
		PolyDetector(fs::path data_dir_path, std::unordered_set<std::string>* pick_names_set = nullptr, int n_features = 2000) {
			this->detector = cv::ORB::create(n_features);
			this->matcher = cv::BFMatcher::create(cv::NormTypes::NORM_HAMMING2, true);
			this->data_dir_path = data_dir_path;
			// obj_info_dic ������Ʈ
			update(pick_names_set);
		}

		~PolyDetector() {
			this->detector->clear();
			this->matcher->clear();
			this->obj_info_dic.clear();
		}


		void update(std::unordered_set<std::string>* pick_names_set = nullptr) {
			std::unordered_set<std::string> exist_img_set;
			std::unordered_set<std::string> exist_json_set;
			std::unordered_set<std::string> union_name_set1;
			std::unordered_set<std::string> union_name_set2;

			// ���͸� �����̸� �����ؼ� set �ֱ�
			for (const auto& entry : fs::directory_iterator(this->data_dir_path)) {
				fs::path p = entry.path();
				if (p.extension() == ".json") {
					exist_json_set.insert(p.filename().stem().string());
				}
				else if (p.extension() == ".jpg") {
					exist_img_set.insert(p.filename().stem().string());
				}
				else if (p.extension() == ".png") {
					exist_img_set.insert(p.filename().stem().string());
				}
			}

			// img_set�� json_set ������
			for (const auto& v : exist_img_set) {
				if (exist_json_set.find(v) != exist_json_set.end()) {
					union_name_set1.insert(v);
				}
			}

			// union_set�� pick_names_set ������
			if (pick_names_set != nullptr) {
				for (const auto& v : union_name_set1) {
					if (pick_names_set->find(v) != pick_names_set->end()) {
						union_name_set2.insert(v);
					}
				}
			}
			else {
				union_name_set2 = union_name_set1;
			}

			// ���õ� �̸��� ��ü ������ map�� �ֱ�
			for (const auto& name : union_name_set2) {
				// �̹��� ���
				fs::path img_path = data_dir_path / name;
				img_path.replace_extension(".jpg");
				if (!fs::exists(img_path)) img_path.replace_extension(".png");
				// json ���
				fs::path json_path = data_dir_path / name;
				json_path.replace_extension(".json");
				// �ֱ�
				obj_info_dic[name] = ObjInfo(img_path, json_path, this->detector);
			}
		}


		bool predict(const cv::Mat& bgr_img_mat, ObjInfo& output_obj, cv::OutputArray output_M=cv::noArray()) {
			cv::Mat gray_img_mat;
			cv::cvtColor(bgr_img_mat, gray_img_mat, cv::COLOR_BGR2GRAY);
			std::vector<cv::KeyPoint> kp;
			cv::Mat desc;
			this->detector->detectAndCompute(gray_img_mat, 0, kp, desc);
			// Ư¡�� ����
			if (kp.size() < 50) return false;

			// ���� ��ġ�ϴ� obj ����
			ObjInfo best_obj;
			float best_acc = 0;
			cv::Mat best_M;
			for (const auto& [name, obj] : this->obj_info_dic) {
				// ���� �����Ϳ� ���� ������ ��Ī
				std::vector<cv::DMatch> matches;
				this->matcher->match(obj.descriptors, desc, matches);
				// ���� ����� Ư¡�� �� ����
				if (matches.size() < 30) continue;

				// ���� ����� Ư¡�� ����ǥ ���ϱ� // �����ǥ�� ������ǥ ���ϱ�
				std::vector<cv::Point2f> src_pts, dst_pts;
				for (const auto& m : matches) {
					src_pts.push_back(obj.keypoints[m.queryIdx].pt);
					dst_pts.push_back(kp[m.trainIdx].pt);
				}

				// ��ȯ��� ���ϱ�
				cv::Mat mask;
				cv::Mat convertor_M = cv::findHomography(src_pts, dst_pts, cv::RHO, 5.0, mask);
				float acc = cv::countNonZero(mask) / (float)mask.rows;
				
				// �ְ� ��ġ�� ����
				if (best_acc < acc) {
					best_obj = obj;
					best_acc = acc;
					best_M = convertor_M;
				}
			}
			// ��ġ�� ����
			if (best_acc < 0.2) return false;

			// return
			output_obj = best_obj;
			output_M.create(best_M.size(), best_M.type());
			best_M.copyTo(output_M);
		}
	};

}