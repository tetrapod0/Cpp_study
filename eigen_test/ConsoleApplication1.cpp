#include <iostream>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>

using namespace std;
using namespace cv;
using namespace Eigen;

int main() {
    // 1. OpenCV에서 이미지를 불러오기
    Mat img = imread("apple.jpg", IMREAD_GRAYSCALE); // 흑백 이미지로 불러오기
    if (img.empty()) {
        cout << "이미지를 불러올 수 없습니다." << endl;
        return -1;
    }

    // 2. OpenCV의 cv::Mat을 Eigen::Matrix로 변환
    // OpenCV의 cv::Mat을 Eigen::MatrixXd로 변환
    MatrixXd eigenImg;
    eigenImg = MatrixXd::Zero(img.rows, img.cols);

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            eigenImg(i, j) = img.at<uchar>(i, j); // uchar 타입을 double로 변환하여 저장
        }
    }

    // 3. Eigen에서 행렬 연산 수행 (예: 전체 픽셀 값을 50씩 증가)
    eigenImg = eigenImg.array() + 50;

    // 4. Eigen::Matrix를 OpenCV의 cv::Mat으로 변환
    Mat resultImg(img.rows, img.cols, CV_8UC1); // 결과를 저장할 OpenCV 이미지 생성
    for (int i = 0; i < resultImg.rows; i++) {
        for (int j = 0; j < resultImg.cols; j++) {
            // 범위를 [0, 255] 사이로 클램핑 후 uint8 타입으로 변환하여 저장
            resultImg.at<uchar>(i, j) = saturate_cast<uchar>(eigenImg(i, j));
        }
    }

    // 5. 결과 출력
    imshow("Original Image", img);
    imshow("Modified Image", resultImg);
    waitKey(0);
    return 0;
}
