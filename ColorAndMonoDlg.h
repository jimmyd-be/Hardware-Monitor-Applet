//************************************************************************
//  The Logitech LCD SDK, including all acompanying documentation,
//  is protected by intellectual property laws.  All use of the Logitech
//  LCD SDK is subject to the License Agreement found in the
//  "Logitech LCD SDK License Agreement" file and in the Reference Manual.  
//  All rights not expressly granted by Logitech are reserved.
//************************************************************************

// ColorAndMonoDlg.h : header file
//

#pragma once

#include "../Src/EZ_LCD.h"
#include "WMI.h"

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

    INT m_currentHighlightPosition;

    // LCD object handles

    // Monochrome
    vector<HANDLE> CPUScreen;
	vector<HANDLE> GPUScreen;
	vector<HANDLE> HDDScreen;
	vector<HANDLE> OtherScreen;

	int currentPage;

    // Color
    HANDLE m_tinyTextColor1;
    HANDLE m_tinyTextColor2;
    HANDLE m_smallTextColor;
    HANDLE m_mediumTextColor;
    HANDLE m_bigTextColor;
    HANDLE m_leftColor1;
    HANDLE m_leftColor2;
    HANDLE m_rightColor1;
    HANDLE m_rightColor2;
    HANDLE m_highlightColor1;
    HANDLE m_highlightColor2;
    HANDLE m_progressbar1Color;
    HANDLE m_progressbar2Color;
    HANDLE m_progressbar3Color;
    HANDLE m_progressbar4Color;
    HANDLE m_logoColor;

	WMI * wmi;

    VOID InitLCDObjectsMonochrome();
    VOID InitLCDObjectsColor();

    VOID CheckButtonPresses();
    VOID CheckbuttonPressesMonochrome();
    VOID CheckbuttonPressesColor();


    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnDestroy( );
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
    DECLARE_MESSAGE_MAP()
};
