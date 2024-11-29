
// MFCNotepadDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCNotepad.h"
#include "MFCNotepadDlg.h"
#include "afxdialogex.h"

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


// CMFCNotepadDlg 대화 상자



CMFCNotepadDlg::CMFCNotepadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCNOTEPAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCNotepadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCNotepadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPEN_, &CMFCNotepadDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_, &CMFCNotepadDlg::OnFileSave)
	ON_COMMAND(ID_ABOUT_, &CMFCNotepadDlg::OnAbout)
	ON_COMMAND(ID_FILE_SAVE_AS_, &CMFCNotepadDlg::OnFileSaveAs)
END_MESSAGE_MAP()


// CMFCNotepadDlg 메시지 처리기

BOOL CMFCNotepadDlg::OnInitDialog()
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCNotepadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCNotepadDlg::OnPaint()
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
HCURSOR CMFCNotepadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 기본 버전
//void CMFCNotepadDlg::OnFileOpen()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	CString filter_str = L"Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
//	CFileDialog dlg(TRUE, L"txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter_str);
//
//	if (dlg.DoModal() != IDOK) return;
//
//	CString path = dlg.GetPathName();
//	CStdioFile file;
//	if (!file.Open(path, CFile::modeRead | CFile::typeText)) return;
//
//	CString line, content;
//	while (file.ReadString(line)) content += line + L"\n";
//	file.Close();
//
//	SetDlgItemText(IDC_EDIT1, content);
//	UpdateData(FALSE);
//}


// 통쨰로 버전 - ANSI 텍스트 파일이면 한글가능
//void CMFCNotepadDlg::OnFileOpen()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	CString filter_str = L"Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
//	CFileDialog dlg(TRUE, L"txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter_str);
//	if (dlg.DoModal() != IDOK) return;
//
//	// 파일 열기
//	CString path = dlg.GetPathName();
//	CStdioFile file;
//	//if (!file.Open(path, CFile::modeRead | CFile::typeText)) return;
//	if (!file.Open(path, CFile::modeRead | CFile::typeBinary)) return;
//
//	// 파일 크기 가져오기
//	ULONGLONG fileLength = file.GetLength(); // 파일 크기
//	if (fileLength == 0) {
//		file.Close();
//		return;
//	}
//
//	// 버퍼에 파일 내용 읽기
//	char* buffer = new char[(size_t)fileLength + 1]; // null terminator 포함
//	memset(buffer, 0, fileLength + 1);
//	file.Read(buffer, (size_t)fileLength);
//	file.Close();
//
//
//	SetDlgItemText(IDC_EDIT1, CString(buffer));
//	UpdateData(FALSE);
//	delete[] buffer;
//}


// 통쨰로 버전 - utf-8 버전
//void CMFCNotepadDlg::OnFileOpen()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	CString filter_str = L"Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
//	CFileDialog dlg(TRUE, L"txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter_str);
//	if (dlg.DoModal() != IDOK) return;
//	
//	// 파일 열기
//	CString path = dlg.GetPathName();
//	CStdioFile file;
//	//if (!file.Open(path, CFile::modeRead | CFile::typeText)) return;
//	if (!file.Open(path, CFile::modeRead | CFile::typeBinary)) return;
//
//	// 파일 크기 가져오기
//	ULONGLONG file_length = file.GetLength(); // 파일 크기
//	if (file_length == 0) {
//		file.Close();
//		return;
//	}
//
//	// 버퍼에 파일 내용 읽기
//	char* buffer = new char[(size_t)file_length + 1]; // null terminator 포함
//	memset(buffer, 0, file_length + 1);
//	file.Read(buffer, (size_t)file_length);
//	file.Close();
//
//	// UTF-8 -> UTF-16 변환
//	int required_size = MultiByteToWideChar(CP_UTF8, 0, buffer, -1, NULL, 0);
//	wchar_t* wide_buffer = new wchar_t[required_size]; // null terminator 포함되어있음
//	MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wide_buffer, required_size);
//
//	CString content(wide_buffer);
//	delete[] buffer;
//	delete[] wide_buffer;
//
//	SetDlgItemText(IDC_EDIT1, content);
//	UpdateData(FALSE);
//}


// 통쨰로 버전 - utf-8의 BOM 체크를 하여 ANSI와 utf-8(BOM) 둘 다 호환 버전
void CMFCNotepadDlg::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 파일 대화상자
	CString filter_str = L"Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
	CFileDialog dlg(TRUE, L"txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter_str);
	if (dlg.DoModal() != IDOK) return;

	// 파일 열기
	CString path = dlg.GetPathName();
	m_currentFilePath = path;
	CStdioFile file;
	if (!file.Open(path, CFile::modeRead | CFile::typeBinary)) return;

	// 파일 크기 가져오기
	ULONGLONG file_length = file.GetLength(); // 파일 크기
	if (file_length == 0) {
		file.Close();
		return;
	}

	// 버퍼에 파일 내용 읽기
	char* buffer = new char[(size_t)file_length + 1]; // null terminator 포함
	memset(buffer, 0, file_length + 1);
	file.Read(buffer, (size_t)file_length);
	file.Close();

	// BOM 검사
	bool is_utf_8 = false;
	const int BOM_SIZE = 3;
	if (file_length >= BOM_SIZE && 
		buffer[0] == (char)0xEF && 
		buffer[1] == (char)0xBB && 
		buffer[2] == (char)0xBF) {
		is_utf_8 = true;
	}

	// CString에 담기
	CString content;
	if (is_utf_8) {
		// UTF-8 -> UTF-16 변환
		int required_size = MultiByteToWideChar(CP_UTF8, 0, buffer, -1, NULL, 0);
		wchar_t* wide_buffer = new wchar_t[required_size]; // null terminator 포함되어있음
		MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wide_buffer, required_size);
		content = wide_buffer;
		delete[] wide_buffer;
	}
	else {
		content = buffer;
	}
	delete[] buffer;

	//
	SetDlgItemText(IDC_EDIT1, content);
	//UpdateData(FALSE);
}


void CMFCNotepadDlg::save_file_to_path(const CString& path) {
	// edit control에서 텍스트 가져오기
	CString content;
	GetDlgItemText(IDC_EDIT1, content);

	// CString -> UTF-8 변환
	int utf8_length = WideCharToMultiByte(CP_UTF8, 0, content, -1, NULL, 0, NULL, NULL);
	char* utf8_buffer = new char[utf8_length];
	WideCharToMultiByte(CP_UTF8, 0, content, -1, utf8_buffer, utf8_length, NULL, NULL);

	// 저장할 파일 생성 및 열기
	CStdioFile file;
	if (!file.Open(path, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary)) {
		delete[] utf8_buffer;
		return;
	}

	// UTF-8 BOM 쓰기
	const char BOM[] = { (char)0xEF, (char)0xBB, (char)0xBF };
	file.Write(BOM, sizeof(BOM));

	// UTF-8 데이터 쓰기
	file.Write(utf8_buffer, utf8_length - 1); //null terminator 제외
	file.Close();
	delete[] utf8_buffer;
}


void CMFCNotepadDlg::OnFileSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_currentFilePath.IsEmpty()) OnFileSaveAs();
	else save_file_to_path(m_currentFilePath);
}


void CMFCNotepadDlg::OnFileSaveAs()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 파일 대화상자
	CString filter_str = L"Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
	CFileDialog dlg(FALSE, L"txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter_str);
	if (dlg.DoModal() != IDOK) return;

	// 저장할 파일 경로 가져오기
	CString path = dlg.GetPathName();

	// 저장 작업
	save_file_to_path(path);
}


void CMFCNotepadDlg::OnAbout()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CAboutDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
}


