
// CImageDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CImage.h"
#include "CImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CCImageDlg dialog


CCImageDlg::CCImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCImageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CCImageDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CCImageDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON4, &CCImageDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_RANDOM, &CCImageDlg::OnBnClickedButtonRandom)
END_MESSAGE_MAP()


// CCImageDlg message handlers

BOOL CCImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCImageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCImageDlg::OnBnClickedButton1()
{	
	if (m_image != NULL) m_image.Destroy();
	// width of image
	int nWidth = 640;

	// height of image
	int nHeight = 480;

	// color scale
	int nBpp = 8;

	
	m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8)
	{
		// color values from 0 .. 255
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();

	// address of image memory's first cell (0,0)
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	// set value of cells in array of image
	memset(fm, 0xff, nWidth * nHeight);

	/*for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++)
		{
			fm[j * nPitch + i] = j % 255;
		}
	}*/

	
	
	UpdateDisplay();
}


void CCImageDlg::OnBnClickedButtonSave()
{
	if (m_image == NULL) return;

	m_image.Save(_T(".\\image.bmp"));
}


void CCImageDlg::OnBnClickedButtonLoad()
{
	if (m_image != NULL) m_image.Destroy();

	m_image.Load(_T(".\\image.bmp"));
	UpdateDisplay();
}

void CCImageDlg::UpdateDisplay()
{
	// device context for this dialog
	CClientDC dc(this);

	m_image.Draw(dc, 0, 0);
}

void CCImageDlg::moveCircle()
{
	static int nSttxy = 0;

	int nDiameterOfCircle = 48;

	if (!validImagePosition(nSttxy + nDiameterOfCircle, nSttxy + nDiameterOfCircle)) return;

	int nRadiusOfCircle = nDiameterOfCircle / 2;
	int nGray = 0x7f;
	
	// address of image memory's first cell (0,0)
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	// set value of cells in array of image
	//memset(fm, 0xff, nWidth * nHeight);
		
	drawCircle(fm, nSttxy, nSttxy, nRadiusOfCircle, 0xff);
		drawCircle(fm, ++nSttxy, nSttxy, nRadiusOfCircle, nGray);
		//Ellipse(m_image.GetDC(), nSttxy, nSttxy, nSttxy + nDiameterOfCircle, nSttxy + nDiameterOfCircle);
	
	//nSttxy++;
	UpdateDisplay();
}

void CCImageDlg::OnBnClickedButton4()
{
	if (m_image == NULL) return;
	// height of image
	int nHeight = m_image.GetHeight();
	
	for (int i = 0; i < nHeight; i++) {
		moveCircle();
		Sleep(10);
	}
}

BOOL CCImageDlg::validImagePosition(int x, int y)
{
	// width of image
	int nWidth = m_image.GetWidth();

	// height of image
	int nHeight = m_image.GetHeight();

	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x,y));
}


void CCImageDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;

	int nPitch = m_image.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++)
		for (int i = x; i < x + nRadius * 2; i++)
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = nGray;
}

void CCImageDlg::drawCircleRandomPosition(int nRadius, int nGray)
{
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	int x, y;
	getRandompoint(x, y, nRadius);

	drawCircle(fm, x, y, nRadius, nGray);
}

void CCImageDlg::getRandompoint(int& x, int& y, int nRadius)
{
	// width of image
	int nWidth = m_image.GetWidth();

	// height of image
	int nHeight = m_image.GetHeight();

	int xMin, xMax, yMin, yMax;

	xMin = yMin = 0;
	xMax = nWidth - 2 * nRadius;
	yMax = nHeight - 2 * nRadius;

	x = rand() % (xMax - xMin) + xMin;
	y = rand() % (yMax - yMin) + yMin;
}

BOOL CCImageDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	BOOL bRet = false;

	double dx = i - nCenterX;

	double dy = j - nCenterY;

	double nDistance = dx * dx + dy * dy;

	if (nDistance < nRadius * nRadius)
		bRet = true;

	return bRet;
}

void CCImageDlg::OnBnClickedButtonRandom()
{
	if (m_image == NULL) return;
	int nRadiusOfCircle = 24;
	int nGray = 0x7f;
	drawCircleRandomPosition(nRadiusOfCircle, nGray);

	UpdateDisplay();
}
