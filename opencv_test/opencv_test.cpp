#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>
#include <opencv2/freetype.hpp>


int main() {
    // 이미지 크기와 색상 설정 (검은색 배경)
    cv::Mat image = cv::Mat::zeros(500, 500, CV_8UC3);

    //1. 직선 그리기 (startPoint -> endPoint, 흰색, 두께 2)
    cv::line(image, cv::Point(50, 50), cv::Point(450, 50), cv::Scalar(255, 255, 255), 2);

    //2. 사각형 그리기 (topLeft -> bottomRight, 파란색, 두께 2)
    cv::rectangle(image, cv::Point(50, 100), cv::Point(200, 300), cv::Scalar(255, 0, 0), 2);

    // 3. 원 그리기 (center, 반지름 50, 초록색, 두께 3)
    cv::circle(image, cv::Point(350, 200), 50, cv::Scalar(0, 255, 0), 3);

    // 4. 다각형 그리기 (빨간색, 두께 2)
    std::vector<cv::Point> points;
    points.push_back(cv::Point(300, 400));
    points.push_back(cv::Point(350, 450));
    points.push_back(cv::Point(400, 400));
    points.push_back(cv::Point(350, 350));

    // 다각형을 닫음
    cv::polylines(image, points, true, cv::Scalar(0, 0, 255), 2);

    // 5. 텍스트 추가 (흰색, 폰트 크기 1, 두께 2)
    cv::putText(image, "OpenCV Drawing", cv::Point(150, 450), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);

    cv::Ptr<cv::freetype::FreeType2> ft2 = cv::freetype::createFreeType2();
    ft2->loadFontData("./NanumGothic.ttf", 0); // 0은 해당 파일 내에서 기본 글꼴
    ft2->putText(image, u8"悠悠自適", cv::Point(150, 250), 50, cv::Scalar(255, 255, 255), -1, cv::LINE_AA, false);
    ft2->putText(image, u8"안녕!", cv::Point(150, 350), 50, cv::Scalar(255, 255, 255), -1, cv::LINE_AA, false);

    // 이미지 창에 표시
    //cv::namedWindow("Frame", cv::WINDOW_AUTOSIZE);
    cv::imshow("Drawing Shapes", image);
    cv::waitKey(10000); // 키 입력 대기
    //int c = cv::waitKey(1000);
    //std::cout << c << std::endl;
    //cv::destroyAllWindows();
    
    return 0;
}
