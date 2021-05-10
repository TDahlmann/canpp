rem @echo off

set SCRIPT="%TEMP%\%RANDOM%-%RANDOM%-%RANDOM%-%RANDOM%.vbs"

echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%USERPROFILE%\Desktop\can++.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
rem echo oLink.TargetPath = "D:\canpp\canpp\_start_here\can++.exe" >> %SCRIPT%

echo Dim sCurPath  >> %SCRIPT%
echo Dim sCurPathPlusExe  >> %SCRIPT%
echo sCurPath = CreateObject("Scripting.FileSystemObject").GetAbsolutePathName(".")  >> %SCRIPT%

echo oLink.WorkingDirectory = sCurPath  >> %SCRIPT%

echo sCurPathPlusExe =  sCurPath + "\can++.exe"  >> %SCRIPT%

echo oLink.TargetPath = sCurPathPlusExe >> %SCRIPT%
echo oLink.Save >> %SCRIPT%

cscript /nologo %SCRIPT%
del %SCRIPT%

