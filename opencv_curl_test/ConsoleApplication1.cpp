
//#include <iostream>
//#include <opencv2/highgui.hpp>
//#include "mytool.h"
//
//int main()
//{
//	cv::Mat img = cv::imread("apple.jpg");
//	cv::imshow("img", img);
//	cv::waitKey(0);
//
//
//}


#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <curl/curl.h>

// libcurl 콜백 함수: 데이터를 받아서 vector에 저장
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::vector<uchar>*)userp)->insert(((std::vector<uchar>*)userp)->end(),
        (uchar*)contents, (uchar*)contents + size * nmemb);
    return size * nmemb;
}

// HTTP에서 이미지를 다운로드하고 OpenCV에서 처리
cv::Mat downloadImage(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::vector<uchar> buffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return cv::Mat();
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    // 받은 데이터를 OpenCV에서 처리할 수 있는 형식으로 변환
    cv::Mat img = cv::imdecode(buffer, cv::IMREAD_COLOR);
    return img;
}

int main() {
    std::string url = "http://192.168.35.106:8090/shot.jpg";

    // 이미지를 주기적으로 가져오는 루프
    while (true) {
        cv::Mat frame = downloadImage(url);  // 이미지 다운로드

        if (frame.empty()) {
            std::cerr << "Error: No image data received!" << std::endl;
            break;
        }

        // 이미지를 화면에 표시
        cv::imshow("Captured Image", frame);

        // 'q' 키를 눌러서 종료
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // OpenCV 창을 닫습니다.
    cv::destroyAllWindows();

    return 0;
}

