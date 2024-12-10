
// MFCLabelerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCLabeler.h"
#include "MFCLabelerDlg.h"
#include "afxdialogex.h"

#include "mypoly.h"
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCLabelerDlg 대화 상자



CMFCLabelerDlg::CMFCLabelerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCLABELER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCLabelerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCLabelerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_DEL_BTN, &CMFCLabelerDlg::OnBnClickedDelBtn)
	ON_COMMAND(ID_FILE_OPEN_, &CMFCLabelerDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_, &CMFCLabelerDlg::OnFileSave)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_ROTATE_BTN, &CMFCLabelerDlg::OnBnClickedRotateBtn)
	ON_BN_CLICKED(IDC_ADD_BTN, &CMFCLabelerDlg::OnBnClickedAddBtn)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_COPY_BTN, &CMFCLabelerDlg::OnBnClickedCopyBtn)
	ON_WM_MOUSEWHEEL()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
END_MESSAGE_MAP()


// CMFCLabelerDlg 메시지 처리기

BOOL CMFCLabelerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 폰트 크기 설정
	CWnd* edit_box = GetDlgItem(IDC_NAME_EDIT);
	CRect rect;
	edit_box->GetClientRect(&rect);
	static CFont font;
	font.CreatePointFont((int)(rect.Height() * 6.66), L"굴림");
	edit_box->SetFont(&font);

	// 임시 poly 추가
	m_poly_list.push_back(PolyControl(100, 100, 200, 200, 100, 300, 0, 200));
	m_poly_list.push_back(PolyControl(300, 300, 350, 300, 350, 350, 300, 350));

	//
	m_vertex_is_clicked = false;
	m_poly_is_clicked = false;
	m_bg_is_clicked = false;
	m_seleted_point = -1;
	m_prev_cur.SetPoint(0, 0);

	// 임시 이미지 추가
	//m_bg_img.Load(L"./c_port.jpg");
	m_origin_bg = cv::imread("./c_port.jpg");
	if (m_origin_bg.empty()) AfxMessageBox(L"이미지 불러오기 실패");
	mat_to_cimg(m_origin_bg, m_bg_img);
	//m_bg_img.Load(L"./c_port.jpg");

	m_bg_pos.x = 0;
	m_bg_pos.y = 0;
	m_bg_mag = 1.0;

	//CString str;
	//str.Format(L"%d, %d", m_origin_bg.rows, m_origin_bg.cols);
	//AfxMessageBox(str);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCLabelerDlg::OnPaint()
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
		draw_canvas_PC();
		draw_crop_PC();

		CDialogEx::OnPaint();
	}
}


// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCLabelerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCLabelerDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	lpMMI->ptMinTrackSize = CPoint(1280, 720);
	//lpMMI->ptMaxTrackSize = CPoint(1400, 1000);

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CMFCLabelerDlg::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMFCLabelerDlg::OnFileSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	//CString str;
	//str.Format(L"%d, %d", point.x, point.y);
	//AfxMessageBox(str);
}


void CMFCLabelerDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 드롭된 파일의 개수 확인
	UINT fileCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

	if (fileCount > 1) {
		AfxMessageBox(L"하나의 파일만 놓아주세요.");
		return;
	}
	// 파일의 경로를 처리
	TCHAR filePath[MAX_PATH];
	DragQueryFile(hDropInfo, 0, filePath, MAX_PATH);
	CString path = filePath;

	// 파일 경로 출력 (혹은 원하는 작업 수행)
	AfxMessageBox(path);

	CDialogEx::OnDropFiles(hDropInfo);
}


void CMFCLabelerDlg::OnBnClickedAddBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_poly_list.push_back(PolyControl(300, 300, 350, 300, 350, 350, 300, 350));
	// 캔버스 업데이트
	draw_canvas_PC();
	// 크롭화면 업데이트
}


void CMFCLabelerDlg::OnBnClickedCopyBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_poly_list.size()) return;
	PolyControl poly = m_poly_list.back(); // 복사 생성자
	m_poly_list.push_back(poly.move_poly(10, 10));
	// 캔버스 업데이트
	draw_canvas_PC();
	// 크롭화면 업데이트
	draw_crop_PC();
}


void CMFCLabelerDlg::OnBnClickedDelBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_poly_list.size()) return;
	m_poly_list.pop_back();
	// 캔버스 업데이트
	draw_canvas_PC();
	// 크롭화면 업데이트
	draw_crop_PC();
}


void CMFCLabelerDlg::OnBnClickedRotateBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_poly_list.size()) return;
	m_poly_list.back().rotate_sequence();
	// 캔버스 업데이트
	draw_canvas_PC();
	// 크롭화면 업데이트
	draw_crop_PC();
}


void CMFCLabelerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (mouse_pt_in_control(point, IDC_SHOW_PIC)) {
		// point를 pic_con 좌표계로 변환
		CPoint cur = point; // 복사 생성자
		CWnd* pWnd = GetDlgItem(IDC_SHOW_PIC);
		ClientToScreen(&cur);
		pWnd->ScreenToClient(&cur);

		// 마지막꺼 선택
		int i = m_poly_list.size() - 1;

		// 점 선택 체크
		for (int j = 0; j < 4; ++j) {
			if (i >= 0 && m_poly_list[i].cur_in_point(cur, j)) {
				m_vertex_is_clicked = true;
				m_prev_cur = cur;
				m_seleted_point = j;
				break;
			}
		}
		if (m_vertex_is_clicked) return;

		// 폴리곤 선택 체크
		for (; i >= 0; --i) {
			if (m_poly_list[i].cur_in_poly(cur)) {
				m_poly_is_clicked = true;
				m_prev_cur = cur;

				// 자리 옮기기
				PolyControl poly(m_poly_list[i]);
				m_poly_list.erase(m_poly_list.begin() + i);
				m_poly_list.push_back(poly);

				// 화면 업데이트 // 선택된 폴리곤의 점 그리기
				draw_canvas_PC();
				//CRect update_rect = poly.get_surrounding_rect();
				//GetDlgItem(IDC_SHOW_PIC)->ClientToScreen(&update_rect);
				//ScreenToClient(&update_rect);
				//InvalidateRect(&update_rect, FALSE); // 부분 갱신
				//InvalidateRect(&update_rect, TRUE); // 부분 갱신
				//draw_canvas_PC();

				break;
			}
		}
		if (m_poly_is_clicked) return;

		// pic_con 선택 체크
		CRect pic_rect;
		pWnd->GetClientRect(&pic_rect);
		if (pic_rect.PtInRect(cur)) {
			m_bg_is_clicked = true;
			m_prev_cur = cur;
		}
		return;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCLabelerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// point를 pic_con 좌표계로 변환
	//CPoint cur = point; // 복사 생성자
	//CWnd* pWnd = GetDlgItem(IDC_SHOW_PIC);
	//ClientToScreen(&cur);
	//pWnd->ScreenToClient(&cur);

	if (m_vertex_is_clicked || m_poly_is_clicked) {
		// 크롭화면 업데이트
		draw_crop_PC();
	}
	if (m_vertex_is_clicked) {
		m_seleted_point = -1;
		m_vertex_is_clicked = false;
	}
	if (m_poly_is_clicked) m_poly_is_clicked = false;
	if (m_bg_is_clicked) m_bg_is_clicked = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCLabelerDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (mouse_pt_in_control(point, IDC_SHOW_PIC)) {
		// point를 pic_con 좌표계로 변환
		CPoint cur = point; // 복사 생성자
		CWnd* pWnd = GetDlgItem(IDC_SHOW_PIC);
		ClientToScreen(&cur);
		pWnd->ScreenToClient(&cur);

		// 마우스 위치 현재와 과거 차이
		CPoint diff_cur = cur - m_prev_cur;
		m_prev_cur = cur;

		// 점 또는 폴리곤 이동
		if (m_vertex_is_clicked || m_poly_is_clicked) {
			PolyControl& poly = m_poly_list.back();
			CRect prev_rect = poly.get_surrounding_rect();

			// 점 이동
			if (m_vertex_is_clicked) {
				poly.move_point(diff_cur.x, diff_cur.y, m_seleted_point);
			}
			// 폴리곤 이동
			else if (m_poly_is_clicked) {
				poly.move_poly(diff_cur.x, diff_cur.y);
			}

			// 캔버스 업데이트
			draw_canvas_PC();
		}

		// 그림 이동
		if (m_bg_is_clicked) {

			// 그림이동
			m_bg_pos.x += diff_cur.x;
			m_bg_pos.y += diff_cur.y;
			// 폴리곤 이동
			for (auto& poly : m_poly_list) {
				poly.move_poly(diff_cur.x, diff_cur.y);
			}

			// 캔버스 업데이트
			draw_canvas_PC();
			//Invalidate(FALSE); // 덮어씌우기
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CMFCLabelerDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 화면 좌표계를 클라이언트 좌표계로 변환
	CPoint cur(pt); // 여기 pt는 화면 좌표계
	ScreenToClient(&cur);

	if (mouse_pt_in_control(cur, IDC_SHOW_PIC)) {
		if (zDelta > 0) {
			zoom_canvas(cur, m_bg_mag, 0.1);
		}
		else if (zDelta < 0) {
			zoom_canvas(cur, m_bg_mag, -0.1);
		}
		draw_canvas_PC();
		return TRUE;
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CMFCLabelerDlg::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (mouse_pt_in_control(point, IDC_SHOW_PIC)) {
		// point를 pic_con 좌표계로 변환
		CPoint cur = point; // 복사 생성자
		CWnd* pWnd = GetDlgItem(IDC_SHOW_PIC);
		ClientToScreen(&cur);
		pWnd->ScreenToClient(&cur);

		// pic_con 선택 체크
		CRect pic_rect;
		pWnd->GetClientRect(&pic_rect);
		if (pic_rect.PtInRect(cur)) {
			m_bg_is_clicked = true;
			m_prev_cur = cur;
		}
		return;
	}

	CDialogEx::OnMButtonDown(nFlags, point);
}


void CMFCLabelerDlg::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bg_is_clicked) m_bg_is_clicked = false;

	CDialogEx::OnMButtonUp(nFlags, point);
}


BOOL CMFCLabelerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN) {
		// edit con에서 엔터시
		if (pMsg->wParam == VK_RETURN && GetFocus()->GetDlgCtrlID() == IDC_NAME_EDIT) {
			if (!m_poly_list.size()) return TRUE;

			CString str;
			GetDlgItemText(IDC_NAME_EDIT, str);
			m_poly_list.back().set_name(str);
			draw_canvas_PC();
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMFCLabelerDlg::draw_canvas_PC() {
	// 컨트롤 포인터 가져오기
	CWnd* pWnd = GetDlgItem(IDC_SHOW_PIC);
	if (!pWnd) return;
	// 컨트롤 클라이언트 영역 크기 가져오기
	CRect pic_rect;
	pWnd->GetClientRect(&pic_rect);
	// 화면 Dc 가져오기
	CDC* pPicDC = pWnd->GetDC();
	if (!pPicDC) return;

	// 메모리 DC 생성
	CDC memDC;
	memDC.CreateCompatibleDC(pPicDC);
	// 메모리 DC에 사용할 비트맵 생성
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(pPicDC, pic_rect.Width(), pic_rect.Height());
	// 새로 객체 연결하면서 이전에 연결된 객체 반환
	CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);

	// 메모리 DC에 그리기
	memDC.FillSolidRect(&pic_rect, RGB(255, 255, 255));
	//m_bg_img.Draw(memDC, 0, 0); // 0,0 부터 이미지 원본크기로 그리기
	m_bg_img.Draw(memDC, CPoint(m_bg_pos.x, m_bg_pos.y)); // CPoint 부터 이미지 원본 크기로 그리기
	//m_bg_img.Draw(memDC, CRect(10, 10, 200, 200)); // 이미지를 강제로 리사이즈하여 rect영역에 그리기
	//m_bg_img.Draw(memDC, 0, 0, 500, 500, 0, 0, 500, 500); // 이미지 특정 영역 크롭하여 강제로 리사이즈하여 dst 좌표에 그리기 (src와 dst 사이즈가 같으면 리사이즈 안함)

	int i;
	for (i = 0; i < m_poly_list.size(); ++i) {
		m_poly_list[i].draw_poly(&memDC);
		m_poly_list[i].draw_name(&memDC);
	}
	if (i) m_poly_list[i - 1].draw_points(&memDC);

	// 화면 DC에 옮기기
	pPicDC->BitBlt(0, 0, pic_rect.Width(), pic_rect.Height(), &memDC, 0, 0, SRCCOPY);

	// DC 해제
	pWnd->ReleaseDC(pPicDC);
}


void CMFCLabelerDlg::draw_crop_PC() {
	// 컨트롤 포인터 가져오기
	CWnd* pWnd = GetDlgItem(IDC_CROP_PIC);
	if (!pWnd) return;
	// 컨트롤 클라이언트 영역 크기 가져오기
	CRect pic_rect;
	pWnd->GetClientRect(&pic_rect);
	// 화면 Dc 가져오기
	CDC* pPicDC = pWnd->GetDC();
	if (!pPicDC) return;
	// 메모리 DC 생성
	CDC memDC;
	memDC.CreateCompatibleDC(pPicDC);
	// 메모리 DC에 사용할 비트맵 생성
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(pPicDC, pic_rect.Width(), pic_rect.Height());
	// 새로 객체 연결하면서 이전에 연결된 객체 반환
	CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);
	// 메모리 DC 초기화
	memDC.FillSolidRect(&pic_rect, RGB(255, 255, 255));

	if (!m_poly_list.size()) return;

	// 이미지 크롭
	PolyControl crop_poly(m_poly_list.back());
	crop_poly -= m_bg_pos;
	crop_poly /= m_bg_mag;
	cv::Mat crop_img, convertor_M;
	convertor_M = crop_poly.get_crop_img_and_M(m_origin_bg, crop_img);

	// 이미지 리사이즈
	float ratio1 = pic_rect.Width() / (float)crop_img.cols;
	float ratio2 = pic_rect.Height() / (float)crop_img.rows;
	float min_ratio = std::min<float>(ratio1, ratio2);
	cv::resize(crop_img, crop_img, { 0,0 }, min_ratio, min_ratio);

	// 이미지 그리기
	CImage show_img;
	mat_to_cimg(crop_img, show_img);
	show_img.Draw(memDC, 0, 0); // 0,0 부터 이미지 원본크기로 그리기

	// 화면 DC에 옮기기
	pPicDC->BitBlt(0, 0, pic_rect.Width(), pic_rect.Height(), &memDC, 0, 0, SRCCOPY);

	// DC 해제
	pWnd->ReleaseDC(pPicDC);
}






bool CMFCLabelerDlg::mouse_pt_in_control(const CPoint& point, int nID) {
	CWnd* pWnd = GetDlgItem(nID);
	if (pWnd == nullptr) return false;
	CRect rect;
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	return rect.PtInRect(point);
}


void CMFCLabelerDlg::mat_to_cimg(const cv::Mat& mat, CImage& c_img) {
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

void CMFCLabelerDlg::zoom_canvas(CPoint cur, float& current_mag, float add_mag) {
	// 변동된 mag
	float after_mag = current_mag + add_mag;
	after_mag = std::min<float>(after_mag, 3);
	after_mag = std::max<float>(after_mag, 0.5);
	if (after_mag == current_mag) return;

	// 이미지 기준 좌표 변경
	m_bg_pos.x -= cur.x;
	m_bg_pos.y -= cur.y;
	m_bg_pos.x /= current_mag;
	m_bg_pos.y /= current_mag;
	m_bg_pos.x *= after_mag;
	m_bg_pos.y *= after_mag;
	m_bg_pos.x += cur.x;
	m_bg_pos.y += cur.y;

	// 이미지 크기 변경
	cv::Mat temp_mat;
	cv::resize(m_origin_bg, temp_mat, { 0,0 }, after_mag, after_mag);
	mat_to_cimg(temp_mat, m_bg_img);

	// 폴리곤들 좌표 변경
	for (auto& poly : m_poly_list) {
		poly -= cur;
		poly /= current_mag;
		poly *= after_mag;
		poly += cur;
	}

	// mag 저장
	current_mag = after_mag;
}

