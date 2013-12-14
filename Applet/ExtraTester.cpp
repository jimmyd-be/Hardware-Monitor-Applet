//************************************************************************
//  The Logitech LCD SDK, including all acompanying documentation,
//  is protected by intellectual property laws.  All use of the Logitech
//  LCD SDK is subject to the License Agreement found in the
//  "Logitech LCD SDK License Agreement" file and in the Reference Manual.  
//  All rights not expressly granted by Logitech are reserved.
//************************************************************************

#include "stdafx.h"

#include "ExtraTester.h"

VOID ExtraTester::DoButtonTestingMono(CEzLcd &lcd)
{
    if (lcd.ButtonTriggered(LG_BUTTON_1))
    {
        TRACE(_T("LG_BUTTON_1 triggered\n"));
    }
    if (lcd.ButtonTriggered(LG_BUTTON_2))
    {
        TRACE(_T("LG_BUTTON_2 triggered\n"));
    }
    if (lcd.ButtonTriggered(LG_BUTTON_3))
    {
        TRACE(_T("LG_BUTTON_3 triggered\n"));
    }
    if (lcd.ButtonTriggered(LG_BUTTON_4))
    {
        TRACE(_T("LG_BUTTON_4 triggered\n"));
    }

    if (lcd.ButtonIsPressed(LG_BUTTON_1))
    {
        TRACE(_T("LG_BUTTON_1 is pressed\n"));
    }
    if (lcd.ButtonIsPressed(LG_BUTTON_2))
    {
        TRACE(_T("LG_BUTTON_2 is pressed\n"));
    }
    if (lcd.ButtonIsPressed(LG_BUTTON_3))
    {
        TRACE(_T("LG_BUTTON_3 is pressed\n"));
    }
    if (lcd.ButtonIsPressed(LG_BUTTON_4))
    {
        TRACE(_T("LG_BUTTON_4 is pressed\n"));
    }

    if (lcd.ButtonReleased(LG_BUTTON_1))
    {
        TRACE(_T("LG_BUTTON_1 released\n"));
    }
    if (lcd.ButtonReleased(LG_BUTTON_2))
    {
        TRACE(_T("LG_BUTTON_2 released\n"));
    }
    if (lcd.ButtonReleased(LG_BUTTON_3))
    {
        TRACE(_T("LG_BUTTON_3 released\n"));
    }
    if (lcd.ButtonReleased(LG_BUTTON_4))
    {
        TRACE(_T("LG_BUTTON_4 released\n"));
    }
}

VOID ExtraTester::DoButtonTestingColor(CEzLcd &lcd)
{
    if (lcd.ButtonTriggered(LG_BUTTON_LEFT))
    {
        TRACE(_T("LG_BUTTON_LEFT triggered\n"));
    }
    if (lcd.ButtonTriggered(LG_BUTTON_RIGHT))
    {
        TRACE(_T("LG_BUTTON_RIGHT triggered\n"));
    }
    if (lcd.ButtonTriggered(LG_BUTTON_UP))
    {
        TRACE(_T("LG_BUTTON_UP triggered\n"));
    }
    if (lcd.ButtonTriggered(LG_BUTTON_DOWN))
    {
        TRACE(_T("LG_BUTTON_DOWN triggered\n"));
    }
    if (lcd.ButtonTriggered(LG_BUTTON_OK))
    {
        TRACE(_T("LG_BUTTON_OK triggered\n"));
    }
    if (lcd.ButtonTriggered(LG_BUTTON_CANCEL))
    {
        TRACE(_T("LG_BUTTON_CANCEL triggered\n"));
    }
    if (lcd.ButtonTriggered(LG_BUTTON_MENU))
    {
        TRACE(_T("LG_BUTTON_MENU triggered\n"));
    }

    if (lcd.ButtonIsPressed(LG_BUTTON_LEFT))
    {
        TRACE(_T("LG_BUTTON_LEFT is pressed\n"));
    }
    if (lcd.ButtonIsPressed(LG_BUTTON_RIGHT))
    {
        TRACE(_T("LG_BUTTON_RIGHT is pressed\n"));
    }
    if (lcd.ButtonIsPressed(LG_BUTTON_UP))
    {
        TRACE(_T("LG_BUTTON_UP is pressed\n"));
    }
    if (lcd.ButtonIsPressed(LG_BUTTON_DOWN))
    {
        TRACE(_T("LG_BUTTON_DOWN is pressed\n"));
    }
    if (lcd.ButtonIsPressed(LG_BUTTON_OK))
    {
        TRACE(_T("LG_BUTTON_OK is pressed\n"));
    }
    if (lcd.ButtonIsPressed(LG_BUTTON_CANCEL))
    {
        TRACE(_T("LG_BUTTON_CANCEL is pressed\n"));
    }
    if (lcd.ButtonIsPressed(LG_BUTTON_MENU))
    {
        TRACE(_T("LG_BUTTON_MENU is pressed\n"));
    }

    if (lcd.ButtonReleased(LG_BUTTON_LEFT))
    {
        TRACE(_T("LG_BUTTON_LEFT released\n"));
    }
    if (lcd.ButtonReleased(LG_BUTTON_RIGHT))
    {
        TRACE(_T("LG_BUTTON_RIGHT released\n"));
    }
    if (lcd.ButtonReleased(LG_BUTTON_UP))
    {
        TRACE(_T("LG_BUTTON_UP released\n"));
    }
    if (lcd.ButtonReleased(LG_BUTTON_DOWN))
    {
        TRACE(_T("LG_BUTTON_DOWN released\n"));
    }
    if (lcd.ButtonReleased(LG_BUTTON_OK))
    {
        TRACE(_T("LG_BUTTON_OK released\n"));
    }
    if (lcd.ButtonReleased(LG_BUTTON_CANCEL))
    {
        TRACE(_T("LG_BUTTON_CANCEL released\n"));
    }
    if (lcd.ButtonReleased(LG_BUTTON_MENU))
    {
        TRACE(_T("LG_BUTTON_MENU released\n"));
    }
}

VOID ExtraTester::DoScreenPriorityTesting(CEzLcd &lcd)
{
    static DWORD lastScreenPriority_ = 0xFFFFFFFF;

    DWORD currentScreenPriority_ = lcd.GetScreenPriority();

    switch(currentScreenPriority_)
    {
    case LGLCD_PRIORITY_IDLE_NO_SHOW:
        if (lastScreenPriority_ != currentScreenPriority_)
        {
            TRACE(_T("Current screenpriority is LGLCD_PRIORITY_IDLE_NO_SHOW\n"));
        }
        break;
    case LGLCD_PRIORITY_BACKGROUND:
        if (lastScreenPriority_ != currentScreenPriority_)
        {
            TRACE(_T("Current screenpriority is LGLCD_PRIORITY_BACKGROUND\n"));
        }
        break;
    case LGLCD_PRIORITY_NORMAL:
        if (lastScreenPriority_ != currentScreenPriority_)
        {
            TRACE(_T("Current screenpriority is LGLCD_PRIORITY_NORMAL\n"));
        }
        break;
    case LGLCD_PRIORITY_ALERT:
        if (lastScreenPriority_ != currentScreenPriority_)
        {
            TRACE(_T("Current screenpriority is LGLCD_PRIORITY_ALERT\n"));
        }
        break;
    }

    lastScreenPriority_ = currentScreenPriority_;

    if (lcd.ButtonTriggered(LG_BUTTON_LEFT) || lcd.ButtonTriggered(LG_BUTTON_1))
    {
        TRACE(_T("Setting screenpriority to LGLCD_PRIORITY_IDLE_NO_SHOW\n"));
        lcd.SetScreenPriority(LGLCD_PRIORITY_IDLE_NO_SHOW);
    }
    if (lcd.ButtonTriggered(LG_BUTTON_RIGHT) || lcd.ButtonTriggered(LG_BUTTON_2))
    {
        TRACE(_T("Setting screenpriority to LGLCD_PRIORITY_BACKGROUND\n"));
        lcd.SetScreenPriority(LGLCD_PRIORITY_BACKGROUND);
    }
    if (lcd.ButtonTriggered(LG_BUTTON_UP) || lcd.ButtonTriggered(LG_BUTTON_3))
    {
        TRACE(_T("Setting screenpriority to LGLCD_PRIORITY_NORMAL\n"));
        lcd.SetScreenPriority(LGLCD_PRIORITY_NORMAL);
    }
    if (lcd.ButtonTriggered(LG_BUTTON_DOWN) || lcd.ButtonTriggered(LG_BUTTON_4))
    {
        TRACE(_T("Setting screenpriority to LGLCD_PRIORITY_ALERT\n"));
        lcd.SetScreenPriority(LGLCD_PRIORITY_ALERT);
    }
}

VOID ExtraTester::DoForegroundTesting(CEzLcd &lcd)
{
    lcd.ModifyDisplay(LG_MONOCHROME);
    if (lcd.ButtonTriggered(LG_BUTTON_1))
    {
        TRACE(_T("Setting mono foreground to TRUE\n"));
        lcd.SetAsForeground(TRUE);
    }
    if (lcd.ButtonTriggered(LG_BUTTON_2))
    {
        TRACE(_T("Setting mono foreground to FALSE\n"));
        lcd.SetAsForeground(FALSE);
    }

    lcd.ModifyDisplay(LG_COLOR);
    if (lcd.ButtonTriggered(LG_BUTTON_UP))
    {
        TRACE(_T("Setting color foreground to TRUE\n"));
        lcd.SetAsForeground(TRUE);
    }
    if (lcd.ButtonTriggered(LG_BUTTON_DOWN))
    {
        TRACE(_T("Setting color foreground to FALSE\n"));
        lcd.SetAsForeground(FALSE);
    }
}

VOID ExtraTester::DoVisibleTesting(CEzLcd &lcd, std::vector<HANDLE> handles)
{
    if (lcd.ButtonTriggered(LG_BUTTON_1) || lcd.ButtonTriggered(LG_BUTTON_UP))
    {
        TRACE(_T("Setting handles to not visible\n"));
        for (UINT index_ = 0; index_ < handles.size(); index_++)
        {
            lcd.SetVisible(handles[index_], FALSE);
        }
    }

    if (lcd.ButtonTriggered(LG_BUTTON_2) || lcd.ButtonTriggered(LG_BUTTON_DOWN))
    {
        TRACE(_T("Setting handles to visible\n"));
        for (UINT index_ = 0; index_ < handles.size(); index_++)
        {
            lcd.SetVisible(handles[index_], TRUE);
        }
    }
}

VOID ExtraTester::DoPageTesting(CEzLcd &lcd)
{
    lcd.ModifyDisplay(LG_MONOCHROME);
    if (lcd.ButtonTriggered(LG_BUTTON_1))
    {
        TRACE(_T("Current mono page count is %d\n"), lcd.GetPageCount());
        lcd.AddNumberOfPages(3);
        TRACE(_T("Added 3 pages. New mono page count is %d\n"), lcd.GetPageCount());
    }
    if (lcd.ButtonTriggered(LG_BUTTON_2))
    {
        TRACE(_T("Current mono page count is %d. Removing page %d.\n"), lcd.GetPageCount(), lcd.GetPageCount() - 1);
        lcd.RemovePage(lcd.GetPageCount() - 1);
        TRACE(_T("New mono page count is %d\n"), lcd.GetPageCount());
    }

    lcd.ModifyDisplay(LG_COLOR);
    if (lcd.ButtonTriggered(LG_BUTTON_UP))
    {
        TRACE(_T("Current color page count is %d\n"), lcd.GetPageCount());
        lcd.AddNumberOfPages(3);
        TRACE(_T("Added 3 pages. New color page count is %d\n"), lcd.GetPageCount());
    }
    if (lcd.ButtonTriggered(LG_BUTTON_DOWN))
    {
        TRACE(_T("Current color page count is %d. Removing page %d.\n"), lcd.GetPageCount(), lcd.GetPageCount() - 1);
        lcd.RemovePage(lcd.GetPageCount() - 1);
        TRACE(_T("New color page count is %d\n"), lcd.GetPageCount());
    }
}
