#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <set>
#include <map>
#include <filesystem>
#include <fstream>
#include "json.hpp"
#include <iostream>

namespace fs = std::filesystem;
using json = nlohmann::json;


namespace poly {
	float get_pseudo_width(const std::vector<cv::Point2f>& pts);
	float get_pseudo_height(const std::vector<cv::Point2f>& pts);
	cv::Mat crop_img_and_get_M(const cv::Mat& src_img, cv::Mat& dst_crop_img, const std::vector<cv::Point2f>& poly, const cv::Size& size = {0,0});


	struct ObjInfo {
		// first - label, second - polys // ����! object ���� ���簢���̾����
		std::string name;
		std::map<std::string, std::vector<cv::Point2f>> src_poly_map;
		std::map<std::string, cv::Size> src_poly_size_map;
		std::vector<cv::KeyPoint> keypoints;
		cv::Mat descriptors;

		ObjInfo() {};
		ObjInfo(std::string name, fs::path img_path, fs::path json_path, cv::Ptr<cv::ORB> detector) {
			// �̸� �Ҵ�
			this->name = name;

			// json �ҷ�����
			std::ifstream i(json_path.string(), std::ios::in);
			json data;
			i >> data;

			// shapes Ű �˻�
			if (!data.contains("shapes")) throw std::runtime_error("json �����Ϳ� \"shapes\"�� �����ϴ�.");

			// src_poly_map �Ҵ�
			for (auto& poly_data : data["shapes"]) {
				// Ű �˻�
				if (!poly_data.contains("label")) throw std::runtime_error("json �����Ϳ� \"label\"�� �����ϴ�.");
				if (!poly_data.contains("points")) throw std::runtime_error("json �����Ϳ� \"points\"�� �����ϴ�.");

				// �� �̸� ��� // map key
				std::string label_name = poly_data["label"].get<std::string>();

				// �� ��� // map value
				this->src_poly_map[label_name] = {
					{poly_data["points"][0][0], poly_data["points"][0][1]},
					{poly_data["points"][1][0], poly_data["points"][1][1]},
					{poly_data["points"][2][0], poly_data["points"][2][1]},
					{poly_data["points"][3][0], poly_data["points"][3][1]}
				};
			}

			// object �� ���� �˻�
			auto it = this->src_poly_map.find("object");
			if (it == this->src_poly_map.end()) throw std::runtime_error("object ���� �����ϴ�.");

			// src_poly_size_map �Ҵ�
			for (const auto& [name, poly] : this->src_poly_map) {
				int w = poly::get_pseudo_width(poly);
				int h = poly::get_pseudo_height(poly);
				this->src_poly_size_map[name] = { w, h };
			}

			// �̹��� �ҷ�����
			cv::Mat img_mat = cv::imread(img_path.string(), cv::IMREAD_GRAYSCALE);

			// �̹��� ũ��
			cv::Mat crop_img_mat;
			cv::Mat convertor_M = poly::crop_img_and_get_M(img_mat, crop_img_mat, 
				this->src_poly_map["object"], this->src_poly_size_map["object"]);

			// keypoints, descriptors �Ҵ�
			//detector->detectAndCompute(img_mat, cv::noArray(), keypoints, descriptors);
			detector->detectAndCompute(crop_img_mat, cv::noArray(), keypoints, descriptors);

			// src_poly_map ��ȯ
			for (auto& [_, poly] : this->src_poly_map)
				cv::perspectiveTransform(poly, poly, convertor_M);


		}
		ObjInfo(std::string name, std::map<std::string, std::vector<cv::Point2f>> src_poly_map,
			std::vector<cv::KeyPoint> keypoints, cv::Mat descriptors) {
			this->name = name;
			this->src_poly_map = src_poly_map;
			this->keypoints = keypoints;
			this->descriptors = descriptors;
			for (const auto& [name, poly] : src_poly_map) {
				int w = poly::get_pseudo_width(poly);
				int h = poly::get_pseudo_height(poly);
				this->src_poly_size_map[name] = { w, h };
			}
		}
		ObjInfo(const ObjInfo& o) {
			this->name = o.name;
			this->src_poly_map = o.src_poly_map;
			this->keypoints = o.keypoints;
			this->descriptors = o.descriptors;
			this->src_poly_size_map = o.src_poly_size_map;
		}
		~ObjInfo() = default;


		std::string get_name() {
			return this->name;
		}


		std::vector<std::string> get_labels() {
			std::vector<std::string> labels;
			for (const auto& [label, _] : this->src_poly_map)
				labels.push_back(label);
			return labels;
		}

		//float get_pseudo_width(const std::vector<cv::Point2f>& pts) {
		//	cv::Point2f d = pts[0] - pts[1];
		//	float len = sqrt(pow(d.x, 2) + pow(d.y, 2));
		//	d = pts[2] - pts[3];
		//	len += sqrt(pow(d.x, 2) + pow(d.y, 2));
		//	return len / 2;
		//}
		//float get_pseudo_height(const std::vector<cv::Point2f>& pts) {
		//	cv::Point2f d = pts[1] - pts[2];
		//	float len = sqrt(pow(d.x, 2) + pow(d.y, 2));
		//	d = pts[0] - pts[3];
		//	len += sqrt(pow(d.x, 2) + pow(d.y, 2));
		//	return len / 2;
		//}
	};


	class PolyDetector {
	private:
		cv::Ptr<cv::ORB> detector;
		cv::Ptr<cv::BFMatcher> matcher;
		std::map<std::string, ObjInfo> obj_info_map;
		fs::path data_dir_path;


	public:
		PolyDetector() {
			this->detector = nullptr; //cv::Ptr<cv::ORB>();
			this->matcher = nullptr; //cv::Ptr<cv::BFMatcher>();
		}
		PolyDetector(fs::path data_dir_path, std::set<std::string>* pick_names_set = nullptr, int n_features = 2000) {
			this->detector = cv::ORB::create(n_features);
			this->matcher = cv::BFMatcher::create(cv::NormTypes::NORM_HAMMING2, true);
			this->data_dir_path = data_dir_path;
			// obj_info_map ������Ʈ
			update(pick_names_set);
		}
		~PolyDetector() = default;


		void update(std::set<std::string>* pick_names_set = nullptr) {
			std::set<std::string> exist_img_set;
			std::set<std::string> exist_json_set;
			std::set<std::string> union_name_set1;
			std::set<std::string> union_name_set2;

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
				try {
					obj_info_map[name] = ObjInfo(name, img_path, json_path, this->detector);
				}
				catch (const std::runtime_error& e) {
					std::cout << "�ش� Obj ������ܵ�: " << name << "\tError �޽���: " << e.what() << std::endl;
				}
				catch (const std::exception& e) {
					std::cout << "�ش� Obj ������ܵ�: " << name << "\tError �޽���: " << e.what() << std::endl;
				}
				catch (...) {
					std::cout << "�ش� Obj ������ܵ�: " << name << "\tError �޽���: �� �� ���� ����" << std::endl;
				}
				

				std::cout << name << "�����̹��� Ư¡�� ����: " << obj_info_map[name].keypoints.size() << std::endl;
			}
		}


		bool predict(const cv::Mat& bgr_img_mat, ObjInfo& output_obj, cv::OutputArray output_M=cv::noArray()) {
			cv::Mat gray_img_mat;
			cv::cvtColor(bgr_img_mat, gray_img_mat, cv::COLOR_BGR2GRAY);
			//std::cout << "�Է� �̹��� ũ�� : " << gray_img_mat.rows << " " << gray_img_mat.cols << std::endl;
			std::vector<cv::KeyPoint> kp;
			cv::Mat desc;
			this->detector->detectAndCompute(gray_img_mat, cv::noArray(), kp, desc);
			//std::cout << "�Է� �̹��� Ư¡�� ���� : " << kp.size() << std::endl;
			// Ư¡�� ����
			if (kp.size() < 50) return false;

			// ���� ��ġ�ϴ� obj ����
			ObjInfo best_obj;
			float best_acc = 0;
			cv::Mat best_M;
			for (const auto& [name, obj] : this->obj_info_map) {
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
			std::cout << "��ü �νĵ� ----- �����̸�: " << best_obj.get_name() << "\t��ġ��: " << best_acc << std::endl;

			// return
			output_obj = best_obj;
			if (output_M.needed()) {
				output_M.create(best_M.size(), best_M.type());
				best_M.copyTo(output_M);
			}
			return true;
		}


		std::vector<std::string> get_names() {
			std::vector<std::string> names;
			for (const auto& [name, _] : obj_info_map) names.push_back(name);
			return names;
		}


	};

}
