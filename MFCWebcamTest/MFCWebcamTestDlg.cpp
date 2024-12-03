
// MFCWebcamTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCWebcamTest.h"
#include "MFCWebcamTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCWebcamTestDlg 대화 상자



CMFCWebcamTestDlg::CMFCWebcamTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCWEBCAMTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCWebcamTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCWebcamTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCWebcamTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCWebcamTestDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCWebcamTestDlg 메시지 처리기

BOOL CMFCWebcamTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	InitializeDrawing();
	erase_memDC();
	//m_cap.open(0);
	//m_cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
	//m_cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCWebcamTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCWebcamTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



#include <opencv2/opencv.hpp>


void CMFCWebcamTestDlg::InitializeDrawing() {
	// 컨트롤 포인터 가져오기
	CWnd* pWnd = GetDlgItem(IDC_PIC1);
	if (!pWnd) return;

	// 컨트롤 클라이언트 영역 크기 가져오기
	CRect pic_rect;
	pWnd->GetClientRect(&pic_rect);

	// 화면 Dc 가져오기
	CDC* pDC = pWnd->GetDC();
	if (!pDC) return;

	// 메모리 DC 생성
	m_memDC.CreateCompatibleDC(pDC);

	// 메모리 DC에 사용할 비트맵 생성
	m_memBitmap.CreateCompatibleBitmap(pDC, pic_rect.Width(), pic_rect.Height());
	// 새로 객체 연결하면서 이전에 연결된 객체 반환
	m_pOldBitmap = m_memDC.SelectObject(&m_memBitmap);

	// DC 해제
	pWnd->ReleaseDC(pDC);
}


void CMFCWebcamTestDlg::CleanupDrawing() {
	// 리소스 정리
	if (m_memDC.GetSafeHdc()) {
		// 다시 원래 객체로 복원
		// m_memBitmap의 주소값이 반환되지만 이미 가지고 있으므로 패스
		m_memDC.SelectObject(m_pOldBitmap); 
		// m_memBitmap 리소스 해제
		m_memBitmap.DeleteObject();
		m_memDC.DeleteDC();
	}
}


void CMFCWebcamTestDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//show_img();
	m_cap.open(0);
	m_cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
	m_cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
	StartDrawingLoop();
}


void CMFCWebcamTestDlg::StartDrawingLoop() {
	SetTimer(1, 1000 / 30, nullptr); // 1번 타이머, 30 FPS
}

void CMFCWebcamTestDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 타이머 중지
	StopDrawingLoop();

	// 비디오 캡쳐 닫기
	m_cap.release();

	// 그림 지우기
	erase_memDC();
}


void CMFCWebcamTestDlg::StopDrawingLoop() {
	KillTimer(1);
}


void CMFCWebcamTestDlg::erase_memDC() {
	// 컨트롤 포인터 가져오기
	CWnd* pWnd = GetDlgItem(IDC_PIC1);
	if (!pWnd) return;

	// 화면 DC 가져오기
	CDC* pDC = pWnd->GetDC();
	if (!pDC) return;

	// 컨트롤 클라이언트 영역 크기 가져오기
	CRect pic_rect;
	pWnd->GetClientRect(&pic_rect);

	// 메모리 DC 클리어 (배경 색 설정)
	m_memDC.FillSolidRect(&pic_rect, RGB(255, 255, 255));

	// 메모리 DC의 내용을 화면 DC로 복사
	pDC->BitBlt(0, 0, pic_rect.Width(), pic_rect.Height(), &m_memDC, 0, 0, SRCCOPY);

	// DC 해제
	pWnd->ReleaseDC(pDC);
}


void CMFCWebcamTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1) {
		show_img();
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CMFCWebcamTestDlg::show_img() {
	// 이미지 가져오기
	m_cap >> m_matimg;
	if (!m_matimg.data) {
		AfxMessageBox(L"Image Not Loaded.");
		OnBnClickedButton2();
		return;
	}

	// 컨트롤 포인터 가져오기
	CWnd* pWnd = GetDlgItem(IDC_PIC1);
	if (!pWnd) return;

	// 컨트롤 클라이언트 영역 크기 가져오기
	CRect pic_rect;
	pWnd->GetClientRect(&pic_rect);

	// 이미지 리사이즈
	float ratio1 = pic_rect.Width() / (float)m_matimg.cols; // 가로 배율
	float ratio2 = pic_rect.Height() / (float)m_matimg.rows; // 세로 배율
	float scale = std::min<float>(ratio1, ratio2);
	cv::resize(m_matimg, m_matimg, cv::Size(), scale, scale, cv::INTER_LINEAR);

	// Mat -> CImage
	MatToCImage(m_matimg, m_cimg);

	// 이미지 중앙 맞춤 영역 계산
	int w = m_cimg.GetWidth();
	int h = m_cimg.GetHeight();
	int c_w = pic_rect.Width() / 2;
	int c_h = pic_rect.Height() / 2;
	CRect drawing_rect = {
		std::max<int>(0, c_w - w / 2),
		std::max<int>(0, c_h - h / 2),
		std::min<int>(pic_rect.right, c_w + w / 2),
		std::min<int>(pic_rect.bottom, c_h + h / 2)
	};

	// 그리기
	DrawImageIoControl(m_cimg, pic_rect, drawing_rect);
}


void CMFCWebcamTestDlg::MatToCImage(const cv::Mat& mat, CImage& c_img) {
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();
	if (mat.empty()) return;

	// CImage 객체에 할당할 공간 만듦
	c_img.Create(width, height, 24);

	// CImage의 비트맵 데이터를 얻어서 Mat 데이터를 복사
	BYTE* pDest = (BYTE*)c_img.GetBits();
	int step = mat.step;  // Mat의 한 행의 바이트 크기

	for (int y = 0; y < mat.rows; ++y) {
		// 한 행의 데이터를 복사
		memcpy(pDest + y * c_img.GetPitch(), mat.ptr(y), mat.cols * 3); // 3은 RGB 채널 수
	}

}


void CMFCWebcamTestDlg::DrawImageIoControl(const CImage& c_img, const CRect& pic_rect, const CRect& drawing_rect) {
	// 컨트롤 포인터 가져오기
	CWnd* pWnd = GetDlgItem(IDC_PIC1);
	if (!pWnd) return;

	// 화면 DC 가져오기
	CDC* pDC = pWnd->GetDC();
	if (!pDC) return;

	// 메모리 DC 클리어 (배경 색 설정)
	m_memDC.FillSolidRect(&pic_rect, RGB(255, 255, 255));

	// CImage를 메모리 DC에 그리기
	c_img.Draw(m_memDC.m_hDC, drawing_rect);

	// 메모리 DC의 내용을 화면 DC로 복사
	pDC->BitBlt(0, 0, pic_rect.Width(), pic_rect.Height(), &m_memDC, 0, 0, SRCCOPY);

	// DC 해제
	pWnd->ReleaseDC(pDC);
}
