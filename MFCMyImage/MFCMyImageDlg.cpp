
// MFCMyImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCMyImage.h"
#include "MFCMyImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCMyImageDlg 대화 상자



CMFCMyImageDlg::CMFCMyImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCMYIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMyImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCMyImageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCMyImageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCMyImageDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCMyImageDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCMyImageDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCMyImageDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMFCMyImageDlg 메시지 처리기

BOOL CMFCMyImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_image.Load(L"./apple.jpg");


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCMyImageDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{

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
		if (m_pCImage != nullptr) {


			// 크기 조절된 이미지
			m_pCImage;
		}

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCMyImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCMyImageDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}


void CMFCMyImageDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CStatic* pic_con = (CStatic*)GetDlgItem(IDC_PIC1);
	CRect rect;
	pic_con->GetWindowRect(rect);
	CDC* dc;
	dc = pic_con->GetDC();
	CImage image;
	HRESULT hResult = image.Load(L"./apple.jpg");
	if (FAILED(hResult)) {
		// 실패 처리
	}
	// 이미지를 pic_con 크기로 조정
	//image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
	image.BitBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), 0, 0, SRCCOPY);
	ReleaseDC(dc);

}


#include <opencv2/opencv.hpp>


void mat_to_cimage(const cv::Mat& mat, CImage& c_img) {
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();

	if (mat.empty()) {
		AfxMessageBox(L"");
		return;
	}

	// BGR -> RGB
	cv::Mat rgb_mat;
	rgb_mat = mat;
	//if (channels == 3) cv::cvtColor(mat, rgb_mat, cv::COLOR_BGR2RGB);
	//else if (channels == 1) cv::cvtColor(mat, rgb_mat, cv::COLOR_GRAY2RGB);
	//else return;

	// CImage 객체에 할당할 공간 만듦
	c_img.Create(width, height, 24);



	// CImage의 비트맵 데이터를 얻어서 Mat 데이터를 복사
	BYTE* pDest = (BYTE*)c_img.GetBits();
	int step = rgb_mat.step;  // Mat의 한 행의 바이트 크기

	for (int y = 0; y < rgb_mat.rows; ++y)
	{
		// 한 행의 데이터를 복사
		memcpy(pDest + y * c_img.GetPitch(), rgb_mat.ptr(y), rgb_mat.cols * 3); // 3은 RGB 채널 수
	}




	//CString s;
	//s.Format(L"%d, %d, %d, %d, %d", sizeof(unsigned char), rgb_mat.total(), rgb_mat.elemSize(), rgb_mat.cols, rgb_mat.rows);
	//AfxMessageBox(s);

	// Mat 의 데이터 CImage로 복사
	//memcpy(c_img.GetBits(), rgb_mat.data, rgb_mat.total() * rgb_mat.elemSize());
	//c_img.Attach
}


void CMFCMyImageDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cv::Mat mat = cv::imread("apple.jpg");

	CImage c_img;
	mat_to_cimage(mat, c_img);


	//CStatic* pc = (CStatic*)GetDlgItem(IDC_PIC2);
	//CBitmap bitmap;
	//bitmap.Attach(image.Detach()); // CImage를 CBitmap으로 변환
	//pc->SetBitmap(bitmap);

	////////////////////////////////////
	//CDC* dc;
	//dc = GetDlgItem(IDC_PIC2)->GetDC();
	//c_img.Draw(dc->m_hDC, 0, 0);
	//GetDlgItem(IDC_PIC2)->ReleaseDC(dc);

	///////////////////////////////////////////
	//CWnd* pWnd = GetDlgItem(IDC_PIC2);
	//if (!pWnd) return;

	//CRect rect;
	//pWnd->GetClientRect(&rect);

	//CDC* pDC = pWnd->GetDC();
	//if (pDC)
	//{
	//	// CImage 객체를 컨트롤의 DC에 그리기
	//	c_img.Draw(pDC->m_hDC, rect.left, rect.top, rect.Width(), rect.Height());

	//	// DC 해제
	//	pWnd->ReleaseDC(pDC);
	//}

	//////////////////////////////////////////
	// 컨트롤 포인터 가져오기
	CWnd* pWnd = GetDlgItem(IDC_PIC2);
	if (!pWnd) return;

	// 컨트롤 클라이언트 영역 크기 가져오기
	CRect rect;
	pWnd->GetClientRect(&rect);

	// 화면 DC 가져오기
	CDC* pDC = pWnd->GetDC();
	if (!pDC) return;

	// 메모리 DC 생성
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	// 메모리 DC에 사용할 비트맵 생성
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	// 메모리 DC에 비트맵 선택
	CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);

	// 메모리 DC 클리어 (배경 색 설정)
	memDC.FillSolidRect(&rect, RGB(255, 255, 255)); // 흰색 배경

	// CImage를 메모리 DC에 그리기 // 비좁은공간에 그렸네
	c_img.Draw(memDC.m_hDC, 0, 0);//, rect.Width(), rect.Height());

	// 메모리 DC의 내용을 화면 DC로 복사
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	// 리소스 정리
	memDC.SelectObject(pOldBitmap);
	pWnd->ReleaseDC(pDC);

}


void CMFCMyImageDlg::OnBnClickedButton4() // 이미지 불러오기
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pCImage = new CImage();
	m_pCImage->Load(L"./apple.jpg");


	CStatic* pic_con = (CStatic*)GetDlgItem(IDC_PIC1);
}


void CMFCMyImageDlg::OnBnClickedButton5() // 지우기
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}
