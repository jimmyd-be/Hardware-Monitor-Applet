; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{3263A9C9-C0E1-4BA7-88F4-A1525C050900}
AppName=Hardware Monitor Applet
AppVersion=2.0
AppVerName=Hardware Monitor Applet
AppPublisher=JimmyD.
AppPublisherURL=https://github.com/lonelobo0070/Hardware-Monitor-Applet/releases
AppSupportURL=https://github.com/lonelobo0070/Hardware-Monitor-Applet/issues
AppUpdatesURL=https://github.com/lonelobo0070/Hardware-Monitor-Applet/releases
DefaultDirName={commonpf}\Hardware Monitor Applet
DefaultGroupName=Hardware Monitor Applet
AllowNoIcons=yes
LicenseFile=license.txt
InfoBeforeFile=README.md
OutputDir=build\installer
OutputBaseFilename=HMA_v2.0_Setup
Compression=lzma2/max 
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64
UninstallDisplayIcon={app}\Hardware-Monitor-Applet.exe
ArchitecturesAllowed=x64

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "brazilianportuguese"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"
Name: "catalan"; MessagesFile: "compiler:Languages\Catalan.isl"
Name: "corsican"; MessagesFile: "compiler:Languages\Corsican.isl"
Name: "czech"; MessagesFile: "compiler:Languages\Czech.isl"
Name: "danish"; MessagesFile: "compiler:Languages\Danish.isl"
Name: "dutch"; MessagesFile: "compiler:Languages\Dutch.isl"
Name: "finnish"; MessagesFile: "compiler:Languages\Finnish.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "german"; MessagesFile: "compiler:Languages\German.isl"
Name: "hebrew"; MessagesFile: "compiler:Languages\Hebrew.isl"
Name: "italian"; MessagesFile: "compiler:Languages\Italian.isl"
Name: "japanese"; MessagesFile: "compiler:Languages\Japanese.isl"
Name: "norwegian"; MessagesFile: "compiler:Languages\Norwegian.isl"
Name: "polish"; MessagesFile: "compiler:Languages\Polish.isl"
Name: "portuguese"; MessagesFile: "compiler:Languages\Portuguese.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"
Name: "turkish"; MessagesFile: "compiler:Languages\Turkish.isl"
Name: "ukrainian"; MessagesFile: "compiler:Languages\Ukrainian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
; Place all x64 files here
Source: "release\Hardware-Monitor-Applet.exe"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: ignoreversion  overwritereadonly
Source: "release\*"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: ignoreversion overwritereadonly recursesubdirs createallsubdirs
Source: "release\vcredist_x64.exe"; DestDir: {tmp}; Check: Is64BitInstallMode; Flags: deleteafterinstall

; Place all common files here, first one should be marked 'solidbreak'
Source: "README.md"; DestDir: "{app}"; Flags: ignoreversion  overwritereadonly solidbreak
Source: "license.txt"; DestDir: "{app}"; Flags: ignoreversion  overwritereadonly
Source: "G15.ttf"; DestDir: "{fonts}"; FontInstall: "G15"; Flags: onlyifdoesntexist uninsneveruninstall

; attempt to remove previous versions
[InstallDelete]
Type: filesandordirs; Name: {app}\*;

[Icons]
; start menu
Name: "{group}\Run Hardware Monitor Applet Background Proces"; Filename: "{app}\Hardware-Monitor-Applet.exe"
Name: "{group}\Hardware Monitor Applet Settings"; Filename: "{app}\Hardware-Monitor-Applet.exe"; Parameters:" Settings"
Name: "{group}\Close Hardware Monitor Applet"; Filename: "{app}\Hardware-Monitor-Applet.exe"; Parameters:" Quit"
Name: "{group}\{cm:ProgramOnTheWeb,Hardware Monitor Applet}"; Filename: "https://github.com/lonelobo0070/Hardware-Monitor-Applet"
Name: "{group}\{cm:UninstallProgram,Hardware Monitor Applet}"; Filename: "{uninstallexe}"

; desktop icon
Name: "{commondesktop}\Hardware Monitor Applet"; Filename: "{app}\Hardware-Monitor-Applet.exe"; Tasks: desktopicon; Parameters:" Settings"

; app folder
Name: "{app}\Settings"; Filename: "{app}\Hardware-Monitor-Applet.exe"; Parameters:" Settings"
Name: "{app}\Quit"; Filename: "{app}\Hardware-Monitor-Applet.exe"; Parameters:" Quit"

[Run]
;StatusMsg: "Installing Microsoft Visual C++ 2013 Redistributable Package v12.0.30501..."
;Filename: "{tmp}\vcredist_x86.exe"; Check: not Is64BitInstallMode; Parameters: "{tmp}\vcredist_x86.exe /q /norestart "
Filename: "{tmp}\vcredist_x64.exe"; Check: Is64BitInstallMode; Parameters: "{tmp}\vcredist_x64.exe /q /norestart "

;StatusMsg: "Starting Hardware Monitor Applet Settings Application..."
Filename: "{app}\Hardware-Monitor-Applet"; Description: "{cm:LaunchProgram,Hardware Monitor Applet Settings}"; Flags: nowait postinstall skipifsilent; Parameters:" Settings"