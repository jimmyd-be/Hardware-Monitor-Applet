//-----------------------------------------------------------------
// CColorAndMonoDlg Object
// C++ Header - CColorAndMonoDlg.h - version v3.0 (2013-12-29)
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "EZ_LCD.h"
#include "Bitmap.h"
#include "WMI.h"
#include "Settings.h"
#include "WMI.h"
#include <vector>

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// CColorAndMonoDlg Class
//-----------------------------------------------------------------
class CColorAndMonoDlg : public CDialog
{
	typedef unsigned long DWORD, *PDWORD, *LPDWORD;
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
    CColorAndMonoDlg(CWnd* pParent = NULL);	// standard constructor

    // Dialog Data
    enum { IDD = IDD_COLORANDMONO_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


    // Implementation
protected:
    HICON icon_;

    CEzLcd lcd_;

    int currentPage_;
	int time_;

	Settings* settings_;
	WMI* wmi_;

    // LCD object handles

	vector<HANDLE> * textLines_;

    // Color
    //HANDLE m_tinyTextColor1;
    //HANDLE m_tinyTextColor2;
    //HANDLE m_smallTextColor;
    //HANDLE m_mediumTextColor;
    //HANDLE m_bigTextColor;
    //HANDLE m_leftColor1;
    //HANDLE m_leftColor2;
    //HANDLE m_rightColor1;
    //HANDLE m_rightColor2;
    //HANDLE m_highlightColor1;
    //HANDLE m_highlightColor2;
    //HANDLE m_progressbar1Color;
    //HANDLE m_progressbar2Color;
    //HANDLE m_progressbar3Color;
    //HANDLE m_progressbar4Color;
    //HANDLE m_logoColor;

    // Bitmaps
    vector<cBitmap> backgrounds_;
 /*   cBitmap m_next;
    cBitmap m_previous;
    cBitmap m_highlight;
    cBitmap m_logoSmall;
    cBitmap m_sliderBase;
    cBitmap m_sliderHighlight;
    cBitmap m_sliderLeft;
    cBitmap m_sliderMid;
    cBitmap m_sliderRight;
    cBitmap m_sliderBase2;
    cBitmap m_sliderHighlight2;
    cBitmap m_next2;
    cBitmap m_previous2;
    cBitmap m_highlight2;*/


    VOID initLCDObjectsMonochrome();
    VOID initLCDObjectsColor();

    VOID checkButtonPresses();
    VOID checkbuttonPressesMonochrome();
    VOID checkbuttonPressesColor();

    VOID updatePage();
    VOID updatePageMonochrome();
    VOID updatePageColor();

	DWORD OpenSettings(int, const PVOID);

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy( );
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
    DECLARE_MESSAGE_MAP()

private:
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	CColorAndMonoDlg(const CColorAndMonoDlg& t);
	CColorAndMonoDlg& operator=(const CColorAndMonoDlg& t);
};
