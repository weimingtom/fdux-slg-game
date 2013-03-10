; 脚本由 Inno Setup 脚本向导 生成！
; 有关创建 Inno Setup 脚本文件的详细资料请查阅帮助文档！

#define MyAppName "忘却的战场-翼骑团"
#define MyAppVersion "609"
#define MyAppPublisher "幻爵工作室"
#define MyAppURL "http://fdux.sinaapp.com/"
#define MyAppExeName "ForgottenBattlefield.exe"

[Setup]
; 注: AppId的值为单独标识该应用程序。
; 不要为其他安装程序使用相同的AppId值。
; (生成新的GUID，点击 工具|在IDE中生成GUID。)
AppID={{B1B68475-2D66-485E-BFE7-993B05E84AD5}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\ForgottenBattlefield
DefaultGroupName={#MyAppName}
OutputDir=F:\C++\SLGGame\Deploy
OutputBaseFilename=setup
Compression=lzma/Max
SolidCompression=true
WizardImageFile=F:\C++\SLGGame\Deploy\Title.bmp
AppVerName=v1.0

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "F:\C++\SLGGame\Deploy\CD11\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; 注意: 不要在任何共享系统文件上使用“Flags: ignoreversion”

[Icons]
Name: {group}\{#MyAppName}启动器; Filename: {app}\Release\Launcher.exe; WorkingDir: {app}\Release; 
Name: {group}\{#MyAppName}; Filename: {app}\Release\{#MyAppExeName}; WorkingDir: {app}\Release; 
Name: {group}\{#MyAppName}(全屏模式); Filename: "{app}\Release\{#MyAppExeName}";Parameters:"-FullScene"; WorkingDir: {app}\Release;
Name: {group}\ReadMe; Filename: {app}\readme不读木有小JJ.txt; WorkingDir: {app}\; 
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: {userdesktop}\{#MyAppName}; Filename: {app}\Release\Launcher.exe; WorkingDir: {app}\Release; 

[Run]
Filename: {app}\readme不读木有小JJ.txt; Description: 查看显示自述文件; Flags: postinstall skipifsilent shellexec; 
Filename: {app}\Support\vcredist_x86.exe; Description: 安装VC++2008运行库(建议安装); Flags: nowait postinstall skipifsilent; 
Filename: {app}\Support\DirectX\DXSETUP.exe; Description: "安装DirectX9运行库"; Flags: nowait postinstall skipifsilent;
Filename: {app}\Support\vcredist2010_x86.exe; Description: 安装VC++2010运行库(建议安装); Flags: PostInstall NoWait SkipIfSilent; 
Filename: {app}\Support\K-Lite_Codec_Pack_975_Full.exe; Description: 安装视频解码器(XP必须安装); Flags: PostInstall NoWait SkipIfSilent;
