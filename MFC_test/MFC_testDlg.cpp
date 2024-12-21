
// MFC_testDlg.cpp: 구현 파일
//


#include "pch.h"
#include "framework.h"
#include "MFC_test.h"
#include "MFC_testDlg.h"
#include "afxdialogex.h"



#include <opencv2/opencv.hpp>
#include "myspace.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCtestDlg 대화 상자



CMFCtestDlg::CMFCtestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, m_pic_con);
}

BEGIN_MESSAGE_MAP(CMFCtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCtestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCtestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCtestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDOK, &CMFCtestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCtestDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCtestDlg 메시지 처리기

BOOL CMFCtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	cv::Mat mat = cv::imread("apple.jpg");  // 이미지 파일 경로
	if (mat.empty()) AfxMessageBox(L"empty!");
	else AfxMessageBox(L"load!");


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCtestDlg::OnPaint()
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
HCURSOR CMFCtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}







void CMFCtestDlg::OnBnClickedButton2()
{
	// OpenCV로 이미지를 읽어옴
	cv::Mat mat = cv::imread("apple.jpg");  // 이미지 파일 경로

	// OpenCV 이미지가 정상적으로 로드되었는지 확인
	if (mat.empty()) {
		AfxMessageBox(_T("이미지 로드 실패"));
		return;
	}
	
	// cv::Mat -> CImage 변환
	CImage image;

	// cv::Mat의 데이터 포인터를 CImage로 변환
	image.Create(mat.cols, mat.rows, 24); // 24 비트 컬러 이미지 생성 (BGR)

	// OpenCV의 Mat 데이터를 CImage에 복사
	for (int y = 0; y < mat.rows; y++) {
		for (int x = 0; x < mat.cols; x++) {
			// OpenCV는 BGR 포맷, MFC는 RGB 포맷
			cv::Vec3b color = mat.at<cv::Vec3b>(y, x);
			COLORREF rgb = RGB(color[2], color[1], color[0]);  // OpenCV는 BGR, MFC는 RGB
			image.SetPixel(x, y, rgb);
		}
	}

	// 픽쳐 컨트롤의 크기 얻기
	CRect rect;
	m_pic_con.GetWindowRect(rect);
	CDC* dc = m_pic_con.GetDC();  // DC 얻기

	// 이미지 그리기
	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);

	// DC 해제
	ReleaseDC(dc);
}


void CMFCtestDlg::OnBnClickedButton1()
{
	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_pic_con.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* dc = m_pic_con.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
	CImage image;//불러오고 싶은 이미지를 로드할 CImage 
	image.Load(_T("apple.jpg"));//이미지 로드

	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
	ReleaseDC(dc);//DC 해제

	
	//AfxMessageBox(_T("이미지 로드!"));
}



#include <string>

void CMFCtestDlg::OnBnClickedButton3()
{
	int a = 32;
	int b = 5;
	a / b;
	std::string aa("123");
	const char* bb = aa.c_str();

	CString msg;
	msg.Format(_T("%d"), b);
	AfxMessageBox(msg);
}


void CMFCtestDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CMFCtestDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CMFCtestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CMFCtestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);


}
