#pragma once

#include "../Src/EZ_LCD.h"
#include "WMI.h"
#include "Bitmap.h"

// CColorAndMonoDlg dialog
class CColorAndMonoDlg : public CDialog
{
    // Construction
public:
    CColorAndMonoDlg(CWnd* pParent = NULL);	// standard constructor

    // Dialog Data
    enum { IDD = IDD_COLORANDMONO_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


    // Implementation
protected:
    HICON m_hIcon;

    CEzLcd m_lcd;

   // INT m_currentHighlightPosition;

    // LCD object handles

    // Monochrome
    vector<HANDLE> screen;
	//vector<HANDLE> GPUScreen;
	//vector<HANDLE> HDDScreen;
	//vector<HANDLE> OtherScreen;

	int currentPage;

	WMI * wmi;
	int time;
	
	int scrollCPUScreen;
	int scrollGPUScreen;
	int scrollHDDScreen;

	//vector<string> CPUText;
	//vector<string> GPUText;
	//vector<string> HDDText;
	//vector<string> OtherText;

	// Bitmaps
	cBitmap m_background;

	vector<string> text;

    VOID InitLCDObjectsMonochrome();
    VOID InitLCDObjectsColor();

    VOID CheckButtonPresses();
    bool CheckbuttonPressesMonochrome();
    bool CheckbuttonPressesColor();


    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnDestroy( );
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
    DECLARE_MESSAGE_MAP()
};
