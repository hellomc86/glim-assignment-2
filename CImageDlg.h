
// CImageDlg.h : header file
//

#pragma once


// CCImageDlg dialog
class CCImageDlg : public CDialogEx
{
	// variable for image
	CImage m_image;

	// function checks if the point in the area of given rectangle
	BOOL validImagePosition(int x, int y);
public:
	// Construction
	CCImageDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CIMAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButton4();
	
	// Draw m_image to device context
	void UpdateDisplay();

	// move Circle
	void moveCircle();
	
	void drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray);

	void drawCircleRandomPosition(int nRadius, int nGray);
	void getRandompoint(int& x, int& y, int nRadius);

	BOOL isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	afx_msg void OnBnClickedButtonRandom();
};
