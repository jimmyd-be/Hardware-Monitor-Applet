QT       += core gui network printsupport

win32 {
QT += winextras
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = Logo/HWMA_Logo.ico

win32 {
SOURCES += \
    external/Logitech/EZ_LCD.cpp \
    external/Logitech/EZ_LCD_Page.cpp \
    external/Logitech/LCDUI/LCDAnimatedBitmap.cpp \
    external/Logitech/LCDUI/LCDBase.cpp \
    external/Logitech/LCDUI/LCDBitmap.cpp \
    external/Logitech/LCDUI/LCDCollection.cpp \
    external/Logitech/LCDUI/LCDColorProgressBar.cpp \
    external/Logitech/LCDUI/LCDColorText.cpp \
    external/Logitech/LCDUI/LCDConnection.cpp \
    external/Logitech/LCDUI/LCDGfxBase.cpp \
    external/Logitech/LCDUI/LCDGfxColor.cpp \
    external/Logitech/LCDUI/LCDGfxMono.cpp \
    external/Logitech/LCDUI/LCDIcon.cpp \
    external/Logitech/LCDUI/LCDOutput.cpp \
    external/Logitech/LCDUI/LCDPage.cpp \
    external/Logitech/LCDUI/LCDPaginateText.cpp \
    external/Logitech/LCDUI/LCDPopup.cpp \
    external/Logitech/LCDUI/LCDProgressBar.cpp \
    external/Logitech/LCDUI/LCDScrollingText.cpp \
    external/Logitech/LCDUI/LCDSkinnedProgressBar.cpp \
    external/Logitech/LCDUI/LCDStreamingText.cpp \
    external/Logitech/LCDUI/LCDText.cpp \
    Tools/WMI.cpp \
    Tools/HWiNFO.cpp \

HEADERS += \
    Tools/HWiNFO.h \
    Tools/WMI.h \
    external/HWiNFO/hwisenssm2.h \
    external/Logitech/lglcd.h \
    external/Logitech/EZ_LCD.h \
    external/Logitech/EZ_LCD_Defines.h \
    external/Logitech/EZ_LCD_Page.h \
    external/Logitech/LCDUI/LCDAnimatedBitmap.h \
    external/Logitech/LCDUI/LCDBase.h \
    external/Logitech/LCDUI/LCDBitmap.h \
    external/Logitech/LCDUI/LCDCollection.h \
    external/Logitech/LCDUI/LCDColorProgressBar.h \
    external/Logitech/LCDUI/LCDColorText.h \
    external/Logitech/LCDUI/LCDConnection.h \
    external/Logitech/LCDUI/LCDGfxBase.h \
    external/Logitech/LCDUI/LCDGfxColor.h \
    external/Logitech/LCDUI/LCDGfxMono.h \
    external/Logitech/LCDUI/LCDIcon.h \
    external/Logitech/LCDUI/LCDOutput.h \
    external/Logitech/LCDUI/LCDPage.h \
    external/Logitech/LCDUI/LCDPaginateText.h \
    external/Logitech/LCDUI/LCDPopup.h \
    external/Logitech/LCDUI/LCDProgressBar.h \
    external/Logitech/LCDUI/LCDScrollingText.h \
    external/Logitech/LCDUI/LCDSkinnedProgressBar.h \
    external/Logitech/LCDUI/LCDStreamingText.h \
    external/Logitech/LCDUI/LCDText.h \
    external/Logitech/LCDUI/LCDUI.h \
}

SOURCES += \
    AppletThread.cpp \
    Controller.cpp \
    Defines.cpp \
    Logitech.cpp \
    Screen/GraphScreen.cpp \
    Screen/LegendScreen.cpp \
    Screen/NormalScreen.cpp \
    Screen/Screen.cpp \
    Screen/StartScreen.cpp \
    Settings.cpp \
    Tools/Data.cpp \
    Tools/MonitorTool.cpp \
    external/QCustomPlot/qcustomplot.cpp \
    external/QSingleApplication/SingleApplication.cpp \
    external/QSingleApplication/localserver.cpp \
    main.cpp \
    GUI/AboutDialog.cpp \
    GUI/BackgroundPage.cpp \
    GUI/CreateScreenWizard.cpp \
    GUI/CustomizePage.cpp \
    GUI/CustomizePageLineWidget.cpp \
    GUI/DataPage.cpp \
    GUI/GraphPage.cpp \
    GUI/GraphPageLineWidget.cpp \
    GUI/IntroPage.cpp \
    GUI/LineEditPage.cpp \
    GUI/LineEditPageLineWidget.cpp \
    GUI/MainScreenWidget.cpp \
    GUI/mainwindow.cpp \
    GUI/OrderWindow.cpp \
    GUI/ScreenTypePage.cpp \
    GUI/SortScreenDialog.cpp

HEADERS += \
    AppletThread.h \
    Controller.h \
    Defines.h \
    GUI/AboutDialog.h \
    GUI/BackgroundPage.h \
    GUI/CreateScreenWizard.h \
    GUI/CustomizePage.h \
    GUI/CustomizePageLineWidget.h \
    GUI/DataPage.h \
    GUI/GraphPage.h \
    GUI/GraphPageLineWidget.h \
    GUI/IntroPage.h \
    GUI/LineEditPage.h \
    GUI/LineEditPageLineWidget.h \
    GUI/MainScreenWidget.h \
    GUI/mainwindow.h \
    GUI/OrderWindow.h \
    GUI/ScreenTypePage.h \
    GUI/SortScreenDialog.h \ \
    LegendScreen.h \
    Logitech.h \
    Screen/GraphScreen.h \
    Screen/LegendScreen.h \
    Screen/NormalScreen.h \
    Screen/Screen.h \
    Screen/StartScreen.h \
    Settings.h \
    Tools/Data.h \
    Tools/MonitorTool.h \
    external/QCustomPlot/qcustomplot.h \
    external/QSingleApplication/SingleApplication.h \
    external/QSingleApplication/localserver.h

FORMS += \
    GUI/mainwindow.ui \
    GUI/AboutDialog.ui \
    GUI/BackgroundPageWidget.ui \
    GUI/CustomizePageLineWidget.ui \
    GUI/CustomizePageWidget.ui \
    GUI/DataPageWidget.ui \
    GUI/GraphPageLineWidget.ui \
    GUI/GraphPageWidget.ui \
    GUI/IntroPageWidget.ui \
    GUI/LineEditPageLineWidget.ui \
    GUI/LineEditPageWidget.ui \
    GUI/MainScreenWidget.ui \
    GUI/mainwindow.ui \
    GUI/OrderWindow.ui \
    GUI/ScreenTypePageWidget.ui \
    GUI/SortScreenDialog.ui

TRANSLATIONS += \
    Languages/HMA_en.ts \
    Languages/HMA_nl.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES = mainwindow.qrc

DISTFILES += \
    Languages/en.png \
    Languages/nl.png \
    Logo/HWMA_Logo.ico \
    Resources/Add.png \
    Resources/Add_hover.png \
    Resources/Default.png \
    Resources/Edit.png \
    Resources/Edit_hover.png \
    Resources/Logo.ico \
    Resources/Remove.png \
    Resources/Screenshots/Graph screen.png \
    Resources/Screenshots/NormalScreen.png \
    Resources/Screenshots/settings.png \
    Resources/icon.png \
    Resources/remove_hover.png


win32:contains(QT_ARCH, i386) {
    win32: LIBS += -L$$PWD/Lib/x86/ -llglcd

    INCLUDEPATH += $$PWD/Lib/x86
    DEPENDPATH += $$PWD/Lib/x86
} else {
    win32: LIBS += -L$$PWD/Lib/x64/ -llglcd

    INCLUDEPATH += $$PWD/Lib/x64
    DEPENDPATH += $$PWD/Lib/x64
}

win32: LIBS += -lgdiplus
win32: LIBS += -lgdi32
win32: LIBS += -lmsimg32
win32: LIBS += -lshell32
win32: LIBS += -lAdvapi32
