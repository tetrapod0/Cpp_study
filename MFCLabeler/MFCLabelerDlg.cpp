
// MFCLabelerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCLabeler.h"
#include "MFCLabelerDlg.h"
#include "afxdialogex.h"

#include "mypoly.h"
#include <opencv2/opencv.hpp>
#include <filesystem>
#include "json.hpp"
#include <fstream>

namespace fs = std::filesystem;
using json = nlohmann::json;

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
	//m_poly_list.push_back(PolyControl(100, 100, 200, 200, 100, 300, 0, 200));
	//m_poly_list.push_back(PolyControl(300, 300, 350, 300, 350, 350, 300, 350));

	
	// 임시 이미지 추가
	//m_origin_bg = cv::imread("./data/c_port.jpg");
	//if (m_origin_bg.empty()) AfxMessageBox(L"이미지 불러오기 실패");
	
	init_values();

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
		set_name_edit();

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
	// 파일 경로 얻기 // 파일 대화상자 // TRUE면 열기모드
	CString filter_str = L"Json Files (*.json)|*.json|Image Files (*.jpg;*.png)|*.jpg;*.png|All Files (*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter_str);
	if (dlg.DoModal() != IDOK) return;
	open_file_path(dlg.GetPathName());
	draw_canvas_PC();
	draw_crop_PC();
	set_name_edit();
}


void CMFCLabelerDlg::OnFileSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_json_path.empty()) {
		AfxMessageBox(L"이미지 또는 JSON 파일을 먼저 열어주세요.");
		return;
	}

	// json 만들기
	json data;
	data["shapes"] = json::array();
	for (auto& poly : m_poly_list) {
		json shape;
		// 이름 넣기
		CString name = poly.get_name();
		shape["label"] = WStringToString(name.GetString());
		// 폴리곤 넣기
		poly -= m_bg_pos;
		poly /= m_bg_mag;
		auto& pts = poly.get_points();
		shape["points"] = json::array({ 
			{pts[0].x, pts[0].y},{pts[1].x, pts[1].y},
			{pts[2].x, pts[2].y},{pts[3].x, pts[3].y}
		});
		// 추가하기
		data["shapes"].push_back(shape);
	}
	
	// 저장하기
	std::ofstream o(m_json_path, std::ios::out);
	o << data.dump(2);
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

	// 파일 경로 열기
	open_file_path(filePath);

	// 
	draw_canvas_PC();
	draw_crop_PC();
	set_name_edit();

	CDialogEx::OnDropFiles(hDropInfo);
}


void CMFCLabelerDlg::OnBnClickedAddBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_poly_list.push_back(PolyControl(300, 300, 350, 300, 350, 350, 300, 350));
	draw_canvas_PC();
	draw_crop_PC();
	set_name_edit();
}


void CMFCLabelerDlg::OnBnClickedCopyBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_poly_list.size()) return;
	PolyControl poly = m_poly_list.back(); // 복사 생성자
	m_poly_list.push_back(poly.move_poly(10, 10));
	draw_canvas_PC();
	draw_crop_PC();
	set_name_edit();
}


void CMFCLabelerDlg::OnBnClickedDelBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_poly_list.size()) return;
	m_poly_list.pop_back();
	draw_canvas_PC();
	draw_crop_PC();
	set_name_edit();
}


void CMFCLabelerDlg::OnBnClickedRotateBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_poly_list.size()) return;
	// 점 회전
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

		// 같은 폴리곤 또 선택시
		if (i >= 0 && m_poly_list[i].cur_in_poly(cur)) {
			auto& l = m_poly_list;
			// 맨 앞으로 보내기
			l.insert(l.begin(), l.back());
			l.pop_back();
		}

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
		set_name_edit();
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
			zoom_canvas(cur, m_bg_mag, 0.2);
		}
		else if (zDelta < 0) {
			zoom_canvas(cur, m_bg_mag, -0.2);
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
		// Ctrl + S 감지
		else if ((GetKeyState(VK_CONTROL) & 0x8000) && pMsg->wParam == 'S') {
			OnFileSave();
			return TRUE;
		}
		else if (pMsg->wParam == VK_DELETE) {
			OnBnClickedDelBtn();
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
	
	if (!m_bg_img.IsNull()) {
		m_bg_img.Draw(memDC, CPoint(m_bg_pos.x, m_bg_pos.y)); // CPoint 부터 이미지 원본 크기로 그리기
		//m_bg_img.Draw(memDC, CRect(10, 10, 200, 200)); // 이미지를 강제로 리사이즈하여 rect영역에 그리기
		//m_bg_img.Draw(memDC, 0, 0, 500, 500, 0, 0, 500, 500); // 이미지 특정 영역 크롭하여 강제로 리사이즈하여 dst 좌표에 그리기 (src와 dst 사이즈가 같으면 리사이즈 안함)
	}

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

	if (m_poly_list.size() && !m_origin_bg.empty()) {
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
	}

	// 화면 DC에 옮기기
	pPicDC->BitBlt(0, 0, pic_rect.Width(), pic_rect.Height(), &memDC, 0, 0, SRCCOPY);

	// DC 해제
	pWnd->ReleaseDC(pPicDC);
}


void CMFCLabelerDlg::set_name_edit() {
	if (m_poly_list.empty()) return;
	CString name = m_poly_list.back().get_name();
	SetDlgItemText(IDC_NAME_EDIT, name);
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
	if (!m_origin_bg.empty())
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


void CMFCLabelerDlg::init_values() {
	m_poly_list.clear();

	// 마우스 관련 초기화
	m_vertex_is_clicked = false;
	m_poly_is_clicked = false;
	m_bg_is_clicked = false;
	m_seleted_point = -1;
	m_prev_cur.SetPoint(0, 0);

	// 배경 이미지 설정
	mat_to_cimg(m_origin_bg, m_bg_img);

	// CImage 좌표와 배율 초기화
	m_bg_pos.x = 0;
	m_bg_pos.y = 0;
	m_bg_mag = 1.0;

	// 이름 edit control 초기화
	SetDlgItemText(IDC_NAME_EDIT, L"");
}


void CMFCLabelerDlg::open_file_path(CString file_path) {
	// 경로 검사
	fs::path p(file_path.GetString());
	if (!fs::exists(p)) {
		AfxMessageBox(L"존재하지 않는 파일입니다.");
		return;
	}

	// 이미지 파일 검사
	fs::path json_path(p.replace_extension(".json"));
	fs::path img_path;
	if (fs::exists(p.replace_extension(".jpg"))) img_path = p;
	else if (fs::exists(p.replace_extension(".png"))) img_path = p;
	else {
		AfxMessageBox(L"이미지 파일을 찾지 못했습니다.");
		return;
	}

	// 이미지 불러오기
	m_origin_bg = cv::imread(img_path.string());
	if (m_origin_bg.empty()) {
		AfxMessageBox(L"이미지 파일은 존재하지만 이미지 불러오기 실패");
		return;
	}
	init_values();
	m_json_path = json_path;

	// json 없으면 패스
	if (!fs::exists(json_path)) return;

	// json 열기
	std::ifstream i(json_path, std::ios::in);
	json data;
	i >> data;

	try {
		// 키 검사
		if (!data.contains("shapes")) 
			throw L"json 데이터에 \"shapes\"가 없습니다.";

		for (auto& poly_data : data["shapes"]) {
			// 키 검사
			if (!poly_data.contains("label")) 
				throw L"json 데이터에 \"label\"가 없습니다.";
			if (!poly_data.contains("points"))
				throw L"json 데이터에 \"points\"가 없습니다.";


			// 이름 얻기
			std::string str = poly_data["label"].get<std::string>();
			std::wstring wstr = StringToWString(str);
			CString name = wstr.c_str();

			// 값 얻기
			json flat_pts = poly_data["points"].flatten();
			if (flat_pts.size() != 8)
				throw L"json 데이터의 어떤 \"points\"의 값이 8개가 아닙니다.";
			float args[8] = {0,0,0,0,0,0,0,0};
			int i = 0;
			for (auto& v : flat_pts.items())
				args[i++] = v.value();

			// poly를 list에 넣기
			m_poly_list.push_back({ args[0], args[1], args[2], args[3], 
				args[4], args[5], args[6], args[7] });
			m_poly_list.back().set_name(name);
		}
	}
	catch (const CString& e) {
		AfxMessageBox(e);
	}
	catch (...) {
		AfxMessageBox(L"json 데이터가 잘못되었습니다.");
	}
}


// std::string -> std::wstring 변환
std::wstring CMFCLabelerDlg::StringToWString(const std::string& str) {
	// ANSI 문자열을 wchar_t로 변환
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0) - 1;
	std::wstring wstr(size_needed, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);
	return wstr;
}


// std::wstring -> std::string 변환
std::string CMFCLabelerDlg::WStringToString(const std::wstring& wstr) {
	// wchar_t 문자열을 UTF-8로 변환
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL) - 1;
	std::string str(size_needed, '\0');
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size_needed, NULL, NULL);
	return str;
}

