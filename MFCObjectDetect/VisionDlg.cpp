// VisionDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCObjectDetect.h"
#include "afxdialogex.h"
#include "VisionDlg.h"
#include "polyDetector.h"

#include <thread>
#include <chrono>
#include <mutex>


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

    // 이중버퍼링 화면 출력 초기화
    erase_memDC();


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
	//AfxMessageBox(L"버튼눌림");

    // 버튼 업데이트
    this->running ^= true;
    GetDlgItem(IDC_START_BTN)->Invalidate(); // 해당영역 무효화후 WM_PAINT 발생
    GetDlgItem(IDC_START_BTN)->UpdateWindow(); // 현재 대기중인 WM_PAINT 즉시 처리

    // 시작
    if (this->running) {
        //SetTimer(1, 1000 / 30, nullptr); // 1번 타이머, 30 FPS
        // 카메라 오픈
        this->cap.open(0);
        this->cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
        this->cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
        // 영상 쓰레드 실행
        this->thr_list.push_back(std::thread(&CVisionDlg::img_producer, this));
        
    }
    // 중지
    else {
        //KillTimer(1);
        // 쓰레드 중지
        this->cv.notify_all();
        for (auto& t : this->thr_list) t.join();
        this->thr_list.clear();

        
        // 카메라 닫기
        this->cap.release();
        erase_memDC();
    }
}


void CVisionDlg::erase_memDC() {
    // 컨트롤 포인터 가져오기
    CWnd* pWnd = GetDlgItem(IDC_VISION_MAIN);
    if (!pWnd) return;

    // 화면 DC 가져오기
    CDC* pDC = pWnd->GetDC();
    if (!pDC) return;

    // 컨트롤 클라이언트 영역 크기 가져오기
    CRect pic_rect;
    pWnd->GetClientRect(&pic_rect);

    // 메모리 DC 생성
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);

    // 메모리 DC에 사용할 비트맵 생성
    CBitmap memBitmap;
    memBitmap.CreateCompatibleBitmap(pDC, pic_rect.Width(), pic_rect.Height());

    // 새로 객체 연결하면서 이전에 연결된 객체 반환
    CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);

    // 메모리 DC 클리어 (배경 색 설정)
    memDC.FillSolidRect(&pic_rect, RGB(240, 240, 240));

    // 메모리 DC의 내용을 화면 DC로 복사
    pDC->BitBlt(0, 0, pic_rect.Width(), pic_rect.Height(), &memDC, 0, 0, SRCCOPY);

    // DC 해제
    pWnd->ReleaseDC(pDC);
}


void CVisionDlg::img_producer() {
    while (this->running) {
        grab_img();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/30)); // 30 fps
    }
}


void CVisionDlg::grab_img() {
    if (this->cap.isOpened()) {
        std::lock_guard<std::mutex> lock(this->raw_img_lock);
        this->cap >> this->raw_img;
    }
}


void CVisionDlg::show_main_img() {

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




