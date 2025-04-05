@echo off
chcp 65001 >nul
echo 正在为源文件添加许可证...

rem 创建临时许可证文件
echo /* > "%TEMP%\gpl_header.txt"
echo  * Copyright (C) 2024 [Wang] >> "%TEMP%\gpl_header.txt"
echo  * >> "%TEMP%\gpl_header.txt"
echo  * This program is free software: you can redistribute it and/or modify >> "%TEMP%\gpl_header.txt"
echo  * it under the terms of the GNU General Public License as published by >> "%TEMP%\gpl_header.txt"
echo  * the Free Software Foundation, either version 3 of the License, or >> "%TEMP%\gpl_header.txt"
echo  * (at your option) any later version. >> "%TEMP%\gpl_header.txt"
echo  * >> "%TEMP%\gpl_header.txt"
echo  * This program is distributed in the hope that it will be useful, >> "%TEMP%\gpl_header.txt"
echo  * but WITHOUT ANY WARRANTY; without even the implied warranty of >> "%TEMP%\gpl_header.txt"
echo  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the >> "%TEMP%\gpl_header.txt"
echo  * GNU General Public License for more details. >> "%TEMP%\gpl_header.txt"
echo  * >> "%TEMP%\gpl_header.txt"
echo  * You should have received a copy of the GNU General Public License >> "%TEMP%\gpl_header.txt"
echo  * along with this program.  If not, see https://www.gnu.org/licenses/. >> "%TEMP%\gpl_header.txt"
echo  */ >> "%TEMP%\gpl_header.txt"
echo. >> "%TEMP%\gpl_header.txt"

rem 创建一个简单的PS脚本
echo $sourceDir = 'd:\UE_Project\AnabiosisOrigin\Source' > "%TEMP%\add_license.ps1"
echo $licenseText = Get-Content -Path $env:TEMP\gpl_header.txt -Raw >> "%TEMP%\add_license.ps1"
echo $extensions = @('*.cpp', '*.h', '*.cs') >> "%TEMP%\add_license.ps1"
echo $files = Get-ChildItem -Path $sourceDir -Recurse -Include $extensions >> "%TEMP%\add_license.ps1"
echo $processed = 0 >> "%TEMP%\add_license.ps1"
echo $skipped = 0 >> "%TEMP%\add_license.ps1"
echo. >> "%TEMP%\add_license.ps1"
echo foreach ($file in $files) { >> "%TEMP%\add_license.ps1"
echo     try { >> "%TEMP%\add_license.ps1"
echo         # 使用UTF8编码直接读取，保留中文字符 >> "%TEMP%\add_license.ps1"
echo         $content = [System.IO.File]::ReadAllText($file.FullName, [System.Text.Encoding]::UTF8) >> "%TEMP%\add_license.ps1"
echo         if ($content -match 'Copyright') { >> "%TEMP%\add_license.ps1"
echo             Write-Host ("License exists: " + $file.Name) -ForegroundColor Cyan >> "%TEMP%\add_license.ps1"
echo             $skipped++ >> "%TEMP%\add_license.ps1"
echo         } else { >> "%TEMP%\add_license.ps1"
echo             $newContent = $licenseText + $content >> "%TEMP%\add_license.ps1"
echo             # 使用UTF8编码写入，不添加BOM >> "%TEMP%\add_license.ps1"
echo             $utf8NoBom = New-Object System.Text.UTF8Encoding $false >> "%TEMP%\add_license.ps1"
echo             [System.IO.File]::WriteAllText($file.FullName, $newContent, $utf8NoBom) >> "%TEMP%\add_license.ps1"
echo             Write-Host ("Added license: " + $file.Name) -ForegroundColor Green >> "%TEMP%\add_license.ps1"
echo             $processed++ >> "%TEMP%\add_license.ps1"
echo         } >> "%TEMP%\add_license.ps1"
echo     } catch { >> "%TEMP%\add_license.ps1"
echo         Write-Host ("Error processing: " + $file.Name + " - " + $_.Exception.Message) -ForegroundColor Red >> "%TEMP%\add_license.ps1"
echo     } >> "%TEMP%\add_license.ps1"
echo } >> "%TEMP%\add_license.ps1"
echo. >> "%TEMP%\add_license.ps1"
echo Write-Host "License processing results:" -ForegroundColor Yellow >> "%TEMP%\add_license.ps1"
echo Write-Host ("Added: " + $processed + " files") -ForegroundColor Green >> "%TEMP%\add_license.ps1"
echo Write-Host ("Skipped: " + $skipped + " files") -ForegroundColor Cyan >> "%TEMP%\add_license.ps1"

rem 执行PS脚本
powershell -NoProfile -ExecutionPolicy Bypass -File "%TEMP%\add_license.ps1"

rem 清理
del "%TEMP%\gpl_header.txt" >nul 2>&1
del "%TEMP%\add_license.ps1" >nul 2>&1

echo.
echo 许可证添加完成!
pause
