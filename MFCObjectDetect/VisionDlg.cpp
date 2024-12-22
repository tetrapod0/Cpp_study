// VisionDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCObjectDetect.h"
#include "afxdialogex.h"
#include "VisionDlg.h"

#include <thread>
#include <chrono>
#include <mutex>
#include <queue>
#include <opencv2/opencv.hpp>
#include <random>
#include <tuple>

#include "polyDetector.h"

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

// CVisionDlg 대화 상자

IMPLEMENT_DYNAMIC(CVisionDlg, CDialogEx)

CVisionDlg::CVisionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VISION_DLG, pParent)
{
}

CVisionDlg::~CVisionDlg()
{
}

void CVisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionDlg, CDialogEx)
    ON_BN_CLICKED(IDC_TEST_BTN, &CVisionDlg::OnBnClickedTestBtn)
	ON_BN_CLICKED(IDC_START_BTN, &CVisionDlg::OnBnClickedStartBtn)
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
    ON_WM_SIZE()
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CVisionDlg 메시지 처리기


BOOL CVisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

    // 버튼 - 소유자 그리기 (속성창에 있네)
	//CWnd* pWnd = GetDlgItem(IDC_START_BTN);
	//if (pWnd != nullptr) {
	//	pWnd->ModifyStyle(0, BS_OWNERDRAW);
	//}

    // opencv 관련 초기화
    this->ft2 = cv::freetype::createFreeType2();
    this->ft2->loadFontData("./NanumGothic.ttf", 0); // 0은 해당 파일 내에서 기본 글꼴

    // poly_detector 초기화
    try {
        this->poly_detector = poly::PolyDetector("./dataset");
    }
    catch (const std::runtime_error& e) {
        // runtime_error 예외 처리
        std::cerr << "Caught a runtime_error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        // 모든 표준 예외 처리 (fallback)
        std::cerr << "Caught a standard exception: " << e.what() << std::endl;
    }
    catch (...) {
        // 알 수 없는 예외 처리
        std::cerr << "Caught an unknown exception!" << std::endl;
    }

    // poly_detector 테스트
    std::cout << "poly_detector 테스트 시작" << std::endl;
    cv::Mat img = cv::imread("./dataset/c_port.jpg");
    //cv::Mat img = cv::imread("./dataset/c_port.jpg");
    if (img.empty()) std::cout << "img is empty!" << std::endl;
    poly::ObjInfo obj;
    cv::Mat M;
    bool result = this->poly_detector.predict(img, obj, M);
    std::cout << M.rows << " " << M.cols << std::endl;
    std::cout << "result : " << result << std::endl;
    std::cout << "poly_detector 테스트 완료" << std::endl;


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CVisionDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
    if (nType == SIZE_MINIMIZED) return;

    //if (m_pGroup != nullptr && IsWindow(m_pGroup->GetSafeHwnd()))
    //{
    //    CRect group_rect;
    //    m_pGroup->GetClientRect(&group_rect);
    //    //group_rect.DeflateRect(10, 15);
    //    //m_pGObject->MoveWindow(&group_rect);
    //    //m_pDlgList[m_selected_tab]->MoveWindow(0, 20, rect.Width(), rect.Height() - 20);
    //}
}


void CVisionDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    if (nIDCtl == IDC_START_BTN) {
        CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
        //RECT rect = lpDrawItemStruct->rcItem;
        CRect rect = lpDrawItemStruct->rcItem;

        // 버튼 배경색
        //pDC->FillSolidRect(&rect, RGB(240, 240, 240)); // 밝은 회색
        CString srcText;
        if (this->running) {
            srcText = L"STOP";
            pDC->FillSolidRect(&rect, RGB(231, 85, 75)); // 빨강
        }
        else {
            srcText = L"START";
            pDC->FillSolidRect(&rect, RGB(85, 177, 85)); // 초록
        }
        

        // 폰트
        CFont font;
        font.CreatePointFont((int)(rect.Height() * 6.66), L"굴림");
        CFont* pOldFont = pDC->SelectObject(&font); // 폰트 적용

        // 버튼 텍스트
        pDC->SetTextColor(RGB(0, 0, 0)); // 텍스트 색상: 검정
        pDC->SetBkMode(TRANSPARENT); // 배경 투명
        pDC->DrawText(srcText, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        // 테두리 그리기
        UINT uState = lpDrawItemStruct->itemState;
        // 버튼이 눌려있을 때
        if (uState & ODS_SELECTED) pDC->DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);
        // 버튼이 평상시 상태일 때
        else pDC->DrawEdge(&rect, EDGE_RAISED, BF_RECT);

        // 뒤처리
        pDC->SelectObject(pOldFont); // 이전 폰트 복원
        font.DeleteObject();

        return; // 기본 처리는 하지 않음
    }

	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CVisionDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    if (nIDEvent == 1) { // 비전 실행

    }


    CDialogEx::OnTimer(nIDEvent);
}


void CVisionDlg::OnBnClickedStartBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 버튼 업데이트
    this->running ^= true;
    GetDlgItem(IDC_START_BTN)->Invalidate(); // 해당영역 무효화후 WM_PAINT 발생
    GetDlgItem(IDC_START_BTN)->UpdateWindow(); // 현재 대기중인 WM_PAINT 즉시 처리

    // 시작
    if (this->running) {
        // 
        this->poly_detector.update();

        // 카메라 오픈
        this->cap.open(0);
        this->cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
        this->cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

        // 큐 초기화
        while (!this->raw_q.empty()) this->raw_q.pop();
        while (!this->pred_q.empty()) this->pred_q.pop();
        while (!this->show_q.empty()) this->show_q.pop();
        while (!this->dataimg_q.empty()) this->dataimg_q.pop();

        // 영상 쓰레드 실행
        this->thr_list.push_back(std::thread(&CVisionDlg::grab_img_proc, this));
        this->thr_list.push_back(std::thread(&CVisionDlg::detect_poly_proc, this));
        this->thr_list.push_back(std::thread(&CVisionDlg::crop_and_draw_proc, this));
        this->thr_list.push_back(std::thread(&CVisionDlg::paint_img_proc, this));
        this->thr_list.push_back(std::thread(&CVisionDlg::recog_img_proc, this));
        
    }
    // 중지
    else {
        // 쓰레드 중지 신호
        this->raw_q_cv.notify_all();
        this->pred_q_cv.notify_all();
        this->show_q_cv.notify_all();
        this->dataimg_q_cv.notify_all();

        // 쓰레드 종료 대기
        for (auto& t : this->thr_list) t.join();
        this->thr_list.clear();

        // 카메라 닫기
        this->cap.release();
        erase_DC(IDC_VISION_MAIN);
        erase_DC(IDC_PIC_OBJ);
        erase_DC(IDC_PIC_NUM);
        erase_DC(IDC_PIC_BAR);
        SetDlgItemText(IDC_TXT_NUM, L"");
        SetDlgItemText(IDC_TXT_BAR, L"");
    }
}


void CVisionDlg::erase_DC(int nID, COLORREF fill_color) {
    // 컨트롤 포인터 가져오기
    CWnd* pWnd = GetDlgItem(nID);
    if (!pWnd) return;

    // 화면 DC 가져오기
    CDC* pDC = pWnd->GetDC();
    if (!pDC) return;

    // 컨트롤 클라이언트 영역 크기 가져오기
    CRect rect;
    pWnd->GetClientRect(&rect);

    // 메모리 DC 생성
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);

    // 메모리 DC에 사용할 비트맵 생성
    CBitmap memBitmap;
    memBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

    // 새로 객체 연결하면서 이전에 연결된 객체 반환
    CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);

    // 메모리 DC 클리어 (배경 색 설정)
    memDC.FillSolidRect(&rect, RGB(240, 240, 240));

    // 메모리 DC의 내용을 화면 DC로 복사
    pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

    // DC 해제
    pWnd->ReleaseDC(pDC);
}


void CVisionDlg::draw_matimg_PC(const cv::Mat& mat_img, int nID) {
    // 이미지가 없으면 지우기
    if (mat_img.empty()) {
        draw_c_img_PC(CImage(), nID);
        return;
    }

    // 컨트롤 클라이언트 영역 크기 가져오기
    CWnd* pWnd = GetDlgItem(nID);
    if (!pWnd) return;
    CRect rect;
    pWnd->GetClientRect(&rect);

    // 이미지 리사이즈
    cv::Mat resized_mat_img;
    float ratio1 = rect.Width() / (float)mat_img.cols; // 가로 배율
    float ratio2 = rect.Height() / (float)mat_img.rows; // 세로 배율
    float scale = std::min<float>(ratio1, ratio2);
    cv::resize(mat_img, resized_mat_img, cv::Size(), scale, scale, cv::INTER_LINEAR);

    // Mat -> CImage
    CImage c_img;
    mat_to_cimg(resized_mat_img, c_img);

    // 이미지 중앙 맞춤 영역 계산
    CRect drawing_rect = {
        std::max<int>(0, rect.Width() / 2 - c_img.GetWidth() / 2),
        std::max<int>(0, rect.Height() / 2 - c_img.GetHeight() / 2),
        std::min<int>(rect.right, rect.Width() / 2 + c_img.GetWidth() / 2),
        std::min<int>(rect.bottom, rect.Height() / 2 + c_img.GetHeight() / 2)
    };

    // 이미지 그리기
    draw_c_img_PC(c_img, nID, &drawing_rect);
}


void CVisionDlg::draw_c_img_PC(const CImage& c_img, int nID, CRect* drawing_rect, COLORREF fill_color) {
    // 컨트롤 포인터 가져오기
    CWnd* pWnd = GetDlgItem(nID);
    if (!pWnd) return;
    // 컨트롤 클라이언트 영역 크기 가져오기
    CRect rect;
    pWnd->GetClientRect(&rect);
    // 화면 Dc 가져오기
    CDC* pDC = pWnd->GetDC();
    if (!pDC) return;

    // 메모리 DC 생성
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    // 메모리 DC에 사용할 비트맵 생성
    CBitmap memBitmap;
    memBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
    // 새로 객체 연결하면서 이전에 연결된 객체 반환
    CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);

    // 메모리 DC에 그리기
    memDC.FillSolidRect(&rect, fill_color);
    if (!c_img.IsNull()) {
        if (drawing_rect == nullptr) c_img.Draw(memDC, 0, 0);
        else c_img.Draw(memDC, *drawing_rect);
    }

    // 화면 DC에 옮기기
    pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

    // DC 해제
    pWnd->ReleaseDC(pDC);
}


void CVisionDlg::mat_to_cimg(const cv::Mat& mat_img, CImage& c_img) {
    int width = mat_img.cols;
    int height = mat_img.rows;
    int channels = mat_img.channels();
    if (mat_img.empty()) return;

    // CImage 객체에 할당할 공간 만듦
    c_img.Create(width, height, 8 * channels);

    // CImage의 비트맵 데이터를 얻어서 Mat 데이터를 복사
    BYTE* pDest = (BYTE*)c_img.GetBits();
    int step = mat_img.step;  // Mat의 한 행의 바이트 크기

    for (int y = 0; y < mat_img.rows; ++y) {
        // 한 행의 데이터를 복사
        memcpy(pDest + y * c_img.GetPitch(), mat_img.ptr(y), mat_img.cols * channels); // 3은 RGB 채널 수
    }
}


void CVisionDlg::grab_img_proc() {
    cv::Mat raw_img;
    while (this->running) {
        // 시간 대기
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30)); // 30 fps
        // 이미지 얻기
        bool result = grab_img(raw_img);
        // raw_img 전달
        std::lock_guard<std::mutex> lock(this->raw_q_mtx);
        this->raw_q.push(raw_img);
        this->raw_q_cv.notify_one();
    }
}


bool CVisionDlg::grab_img(cv::Mat& raw_img) {
    cv::Mat temp = cv::imread("./dataset/c_port.jpg");
    if (this->cap.isOpened()) {
        // raw_img 얻기
        this->cap >> raw_img;
        //raw_img = temp;
    }
    if (!raw_img.data) return false;
    return true;
}


void CVisionDlg::detect_poly_proc() {
    cv::Mat show_img;

    while (this->running) {
        // raw_img 받기
        std::unique_lock<std::mutex> lock(this->raw_q_mtx);
        this->raw_q_cv.wait(lock, [&] {return !this->raw_q.empty() || !this->running;});
        if (!this->running) break;
        show_img = this->raw_q.front();
        this->raw_q.pop();
        lock.unlock();
        if (this->raw_q.size() > 5) std::cout << "Warning: " << "this->raw_q.size(): " << this->raw_q.size() << std::endl;
        
        // show_img 분석
        poly::ObjInfo pred_obj;
        cv::Mat convertor_M; // src_poly -> dst_poly로 만드는 변환행렬
        bool result = this->poly_detector.predict(show_img, pred_obj, convertor_M);

        // result, show_img, pred_obj, convertor_M 전달
        std::lock_guard<std::mutex> lock2(this->pred_q_mtx);
        this->pred_q.push({ result, show_img, pred_obj, convertor_M });
        this->pred_q_cv.notify_one();
    }
}


void CVisionDlg::crop_and_draw_proc() {
    static auto set_color = []() -> cv::Scalar {
        // 난수 생성 엔진과 분포 정의
        std::random_device rd; // 실제 랜덤 시드
        std::mt19937 gen(rd()); // Mersenne Twister 엔진
        std::uniform_int_distribution<int> dis(100, 200);
        float b = static_cast<float>(dis(gen));
        float g = static_cast<float>(dis(gen));
        float r = static_cast<float>(dis(gen));
        return { b, g, r };
    };

    // 색깔 사전 정의
    std::map<std::string, cv::Scalar> color_map;
    for (auto& name : this->poly_detector.get_names()) {
        color_map[name] = set_color();
    }


    while (this->running) {
        // result, show_img, pred_obj, convertor_M 전달
        std::unique_lock<std::mutex> lock(this->pred_q_mtx);
        this->pred_q_cv.wait(lock, [&] {return !this->pred_q.empty() || !this->running;});
        if (!this->running) break;
        auto [result, show_img, pred_obj, convertor_M] = this->pred_q.front();
        this->pred_q.pop();
        lock.unlock();
        if (this->pred_q.size() > 5) std::cout << "Warning: " << "this->pred_q.size(): " << this->pred_q.size() << std::endl;

        // 미인식인 경우
        if (!result) {
            {// show_img, crop_img_map 전달
                std::lock_guard<std::mutex> lock(this->show_q_mtx);
                this->show_q.push({ show_img, std::map<std::string, cv::Mat>() });
                this->show_q_cv.notify_one();
            }
            {// 숫자이미지, 바코드이미지 전달
                std::lock_guard<std::mutex> lock(this->dataimg_q_mtx);
                this->dataimg_q.push({ cv::Mat(), cv::Mat() });
                this->dataimg_q_cv.notify_one();
            }
            continue;
        }

        // crop_img_map
        cv::Mat inverse_M;
        cv::invert(convertor_M, inverse_M);
        cv::Mat obj_img;
        cv::warpPerspective(show_img, obj_img, inverse_M, pred_obj.src_poly_size_map["object"]);
        std::map<std::string, cv::Mat> crop_img_map;
        for (const auto& label : pred_obj.get_labels()) {
            auto& poly = pred_obj.src_poly_map[label];
            auto& size = pred_obj.src_poly_size_map[label];
            poly::crop_img_and_get_M(obj_img, crop_img_map[label], poly, size);
        }

        // dst_poly_map
        std::map<std::string, std::vector<cv::Point2f>> dst_poly_map;
        for (const auto& [label, poly] : pred_obj.src_poly_map) {
            cv::perspectiveTransform(poly, dst_poly_map[label], convertor_M);
        }

        // draw in show_img
        cv::Scalar color = color_map[pred_obj.get_name()];
        for (const auto& [label, poly] : dst_poly_map) {
            // draw polygon
            std::vector<cv::Point> poly_int(poly.begin(), poly.end());
            cv::polylines(show_img, { poly_int }, true, color, 3);
            // draw point numbers
            this->ft2->putText(show_img, "1", poly[0], 20, { 0, 255, 0 }, 1, cv::LINE_AA, false);
            this->ft2->putText(show_img, "2", poly[1], 20, { 0, 255, 0 }, 1, cv::LINE_AA, false);
            this->ft2->putText(show_img, "3", poly[2], 20, { 0, 255, 0 }, 1, cv::LINE_AA, false);
            this->ft2->putText(show_img, "4", poly[3], 20, { 0, 255, 0 }, 1, cv::LINE_AA, false);
            // draw label, name
            if (label == "object")
                this->ft2->putText(show_img, pred_obj.get_name(), poly[0], 30, { 255, 255, 0 }, 1, cv::LINE_AA, true);
        }

        {// show_img, crop_img_map 전달
            std::lock_guard<std::mutex> lock(this->show_q_mtx);
            this->show_q.push({ show_img, crop_img_map });
            this->show_q_cv.notify_one();
        }
        {// 숫자이미지, 바코드이미지 전달 // 키가 없으면 빈 생성자?
            std::lock_guard<std::mutex> lock(this->dataimg_q_mtx);
            this->dataimg_q.push({ crop_img_map["number"], crop_img_map["barcode"]});
            this->dataimg_q_cv.notify_one();
        }
    }

}


void CVisionDlg::paint_img_proc() {
    while (this->running) {
        // show_img, crop_img_map 전달
        std::unique_lock<std::mutex> lock(this->show_q_mtx);
        this->show_q_cv.wait(lock, [&] {return !this->show_q.empty() || !this->running;});
        if (!this->running) break;
        auto [show_img, crop_img_map] = this->show_q.front();
        this->show_q.pop();
        lock.unlock();
        if (this->show_q.size() > 5) std::cout << "Warning: " << "this->show_q.size(): " << this->show_q.size() << std::endl;

        // 이미지 보여주기
        draw_matimg_PC(show_img, IDC_VISION_MAIN);
        draw_matimg_PC(crop_img_map["object"], IDC_PIC_OBJ);
        draw_matimg_PC(crop_img_map["number"], IDC_PIC_NUM);
        draw_matimg_PC(crop_img_map["barcode"], IDC_PIC_BAR);
    }
}


void CVisionDlg::recog_img_proc() {
    while (this->running) {
        // show_img, crop_img_map 전달
        std::unique_lock<std::mutex> lock(this->dataimg_q_mtx);
        this->dataimg_q_cv.wait(lock, [&] {return !this->dataimg_q.empty() || !this->running;});
        if (!this->running) break;
        auto [number_img, barcode_img] = this->dataimg_q.front();
        this->dataimg_q.pop();
        lock.unlock();
        if (this->dataimg_q.size() > 5) std::cout << "Warning: " << "this->dataimg_q.size(): " << this->dataimg_q.size() << std::endl;

        CString number, barcode;
        // 숫자이미지 인식
        if (!number_img.empty()) {

        }
        // 바코드이미지 인식
        if (!barcode_img.empty()) {

        }

        // 값 보여주기
        SetDlgItemText(IDC_TXT_NUM, number);
        SetDlgItemText(IDC_TXT_BAR, barcode);
    }
}






void CVisionDlg::OnBnClickedTestBtn()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    //m_running ^= true;

    //GetDlgItem(IDC_START_BTN)->Invalidate();
    //GetDlgItem(IDC_START_BTN)->UpdateWindow();


    // 이건 일회용이라 
    //CWnd* pWnd = GetDlgItem(IDC_VISION_MAIN);
    //CRect rect;
    //pWnd->GetClientRect(&rect);
    //CDC* pDC = pWnd->GetDC();
    //pDC->DrawText(L"START!!!", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //pWnd->ReleaseDC(pDC);


    CString tt = L"가나다라";
    int aa = tt.Find(L"나다");
    TRACE("\n%d\n", aa);
}




