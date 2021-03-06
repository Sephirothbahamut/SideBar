; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "SideBar"
#define MyAppVersion "1"
#define MyAppPublisher "Barnack"
#define MyAppExeName "SideBar.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{BB74F804-60F1-4E7B-BCC0-90C23BBD0A15}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputBaseFilename=SideBarSetup    
UninstallDisplayIcon={app}\SideBar.exe
Compression=lzma
SolidCompression=yes
; "ArchitecturesInstallIn64BitMode=x64" requests that the install be
; done in "64-bit mode" on x64, meaning it should use the native
; 64-bit Program Files directory and the 64-bit view of the registry.
; On all other architectures it will install in "32-bit mode".
ArchitecturesInstallIn64BitMode=x64
; Note: We don't set ProcessorsAllowed because we want this
; installation to run on all architectures (including Itanium,
; since it's capable of running 32-bit code too).

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
; Install MyProg-x64.exe if running in 64-bit mode (x64; see above),
; MyProg.exe otherwise.
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\x64\Release\SideBar.exe"; DestDir: "{app}"; Flags: ignoreversion; Check: Is64BitInstallMode
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\x64\Release\sfgui.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: Is64BitInstallMode
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\x64\Release\sfml-audio-2.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: Is64BitInstallMode
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\x64\Release\sfml-graphics-2.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: Is64BitInstallMode
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\x64\Release\sfml-network-2.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: Is64BitInstallMode
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\x64\Release\sfml-system-2.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: Is64BitInstallMode
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\x64\Release\sfml-window-2.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: Is64BitInstallMode
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\Release\SideBar.exe"; DestDir: "{app}"; Flags: ignoreversion; Check: not Is64BitInstallMode
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\Release\sfgui.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: not Is64BitInstallMode
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\Release\sfml-audio-2.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: not Is64BitInstallMode
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\Release\sfml-graphics-2.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: not Is64BitInstallMode
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\Release\sfml-network-2.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: not Is64BitInstallMode
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\Release\sfml-system-2.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: not Is64BitInstallMode
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\Release\sfml-window-2.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: not Is64BitInstallMode

Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\x64\Release\files\*"; DestDir: "{app}\files"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\x64\Release\fonts\*"; DestDir: "{app}\fonts"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Users\Sephirothbahamut\Documents\Programming\VS\Projects\SFML\SideBar\x64\Release\textures\*"; DestDir: "{app}\textures"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"  
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{commonstartup}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

