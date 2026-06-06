# 🛠️ Script สำหรับตั้งค่าสภาพแวดล้อม OpenGL (FreeGLUT) ผ่าน VS Code + MSYS2
# กรุณารันสคริปต์นี้ใน PowerShell โดยกดปุ่ม F5 หรือรัน .\setup_msys2.ps1 ใน Terminal

$ErrorActionPreference = "Stop"

Write-Host "==================================================" -ForegroundColor Cyan
Write-Host "      OpenGL & FreeGLUT MSYS2 Setup Script        " -ForegroundColor Cyan
Write-Host "==================================================" -ForegroundColor Cyan

# 1. ตรวจสอบว่ามี MSYS2 ติดตั้งอยู่ในระบบหรือไม่
$msysPath = "C:\msys64"
if (-not (Test-Path $msysPath)) {
    Write-Host "[!] ไม่พบโฟลเดอร์ MSYS2 ที่ $msysPath" -ForegroundColor Yellow
    $confirm = Read-Host "ต้องการติดตั้ง MSYS2 ผ่าน winget หรือไม่? (Y/N)"
    if ($confirm -eq "Y" -or $confirm -eq "y") {
        Write-Host "[*] กำลังติดตั้ง MSYS2 ผ่าน winget..." -ForegroundColor Cyan
        winget install MSYS2.MSYS2 --silent
        Write-Host "[✓] ติดตั้ง MSYS2 สำเร็จแล้ว กรุณารันสคริปต์นี้ใหม่อีกครั้ง" -ForegroundColor Green
        exit
    } else {
        Write-Host "[X] ยกเลิกการติดตั้ง กรุณาติดตั้ง MSYS2 ด้วยตนเองจาก https://www.msys2.org/" -ForegroundColor Red
        exit
    }
} else {
    Write-Host "[✓] พบระบบ MSYS2 ที่ $msysPath" -ForegroundColor Green
}

# 2. ทำการอัปเดตฐานข้อมูลแพ็คเกจ และติดตั้ง Toolchain + FreeGLUT
Write-Host "[*] กำลังอัปเดตและติดตั้ง C++ Toolchain และ FreeGLUT (อาจใช้เวลาสักครู่)..." -ForegroundColor Cyan

try {
    # อัปเดตฐานข้อมูลแพ็คเกจก่อน
    Write-Host "[*] กำลังอัปเดตฐานข้อมูลแพ็คเกจ MSYS2..." -ForegroundColor Gray
    Start-Process -FilePath "$msysPath\usr\bin\bash.exe" -ArgumentList "-lc", "'pacman -Sy --noconfirm'" -NoNewWindow -Wait

    # ติดตั้ง C++ compiler toolchain (g++, make, gdb)
    Write-Host "[*] กำลังติดตั้ง UCRT64 C++ Toolchain..." -ForegroundColor Gray
    Start-Process -FilePath "$msysPath\usr\bin\bash.exe" -ArgumentList "-lc", "'pacman -S --needed --noconfirm mingw-w64-ucrt-x86_64-toolchain'" -NoNewWindow -Wait

    # ติดตั้ง FreeGLUT
    Write-Host "[*] กำลังติดตั้ง FreeGLUT..." -ForegroundColor Gray
    Start-Process -FilePath "$msysPath\usr\bin\bash.exe" -ArgumentList "-lc", "'pacman -S --needed --noconfirm mingw-w64-ucrt-x86_64-freeglut'" -NoNewWindow -Wait

    Write-Host "[✓] ติดตั้งแพ็คเกจ MSYS2 เรียบร้อยแล้ว!" -ForegroundColor Green
} catch {
    Write-Host "[X] เกิดข้อผิดพลาดในการติดตั้งแพ็คเกจผ่าน pacman: $_" -ForegroundColor Red
    exit
}

# 3. เพิ่ม UCRT64 binaries ไปยัง User PATH เพื่อให้ VS Code และโปรแกรมหา DLL เจอ
Write-Host "[*] กำลังตรวจสอบและตั้งค่า Environment PATH..." -ForegroundColor Cyan
$binPath = "C:\msys64\ucrt64\bin"
$userPath = [Environment]::GetEnvironmentVariable("Path", "User")

if ($userPath -notlike "*$binPath*") {
    $newPath = $userPath + ";" + $binPath
    # ทำความสะอาดเครื่องหมายเซมิโคลอนซ้ำซ้อน
    $newPath = $newPath -replace ";+", ";"
    [Environment]::SetEnvironmentVariable("Path", $newPath, "User")
    Write-Host "[✓] เพิ่ม $binPath ไปยัง User PATH สำเร็จ!" -ForegroundColor Green
    Write-Host "[!] หมายเหตุ: คุณอาจต้องปิดและเปิด VS Code ใหม่อีกครั้งเพื่อให้ค่า PATH มีผล" -ForegroundColor Yellow
} else {
    Write-Host "[✓] $binPath มีอยู่ใน User PATH อยู่แล้ว" -ForegroundColor Green
}

# 4. เขียนไฟล์การตั้งค่าต่าง ๆ ในโฟลเดอร์ .vscode
Write-Host "[*] กำลังสร้างและกำหนดค่าไฟล์ในโฟลเดอร์ .vscode..." -ForegroundColor Cyan

$vscodeDir = Join-Path $PSScriptRoot ".vscode"
if (-not (Test-Path $vscodeDir)) {
    New-Item -ItemType Directory -Force -Path $vscodeDir | Out-Null
}

# 4.1 เขียนไฟล์ tasks.json
$tasksJsonPath = Join-Path $vscodeDir "tasks.json"
$tasksContent = @'
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: g++.exe build active file with OpenGL",
            "command": "C:\\msys64\\ucrt64\\bin\\g++.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-lfreeglut",
                "-lglu32",
                "-lopengl32"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Compiler: MSYS2 UCRT64 g++ with FreeGLUT, GLU, OpenGL"
        }
    ]
}
'@
Set-Content -Path $tasksJsonPath -Value $tasksContent -Force
Write-Host "[✓] เขียนไฟล์ .vscode/tasks.json สำเร็จ!" -ForegroundColor Green

# 4.2 เขียนไฟล์ launch.json
$launchJsonPath = Join-Path $vscodeDir "launch.json"
$launchContent = @'
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "g++.exe - Build and debug active file",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:\\msys64\\ucrt64\\bin\\gdb.exe",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "Set Disassembly Flavor to Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: g++.exe build active file with OpenGL"
        }
    ]
}
'@
Set-Content -Path $launchJsonPath -Value $launchContent -Force
Write-Host "[✓] เขียนไฟล์ .vscode/launch.json สำเร็จ!" -ForegroundColor Green

# 4.3 เขียนไฟล์ c_cpp_properties.json
$cCppPropertiesPath = Join-Path $vscodeDir "c_cpp_properties.json"
$cCppPropertiesContent = @'
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/msys64/ucrt64/include"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "C:/msys64/ucrt64/bin/g++.exe",
            "cStandard": "c17",
            "cppStandard": "gnu++17",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
'@
Set-Content -Path $cCppPropertiesPath -Value $cCppPropertiesContent -Force
Write-Host "[✓] เขียนไฟล์ .vscode/c_cpp_properties.json สำเร็จ!" -ForegroundColor Green

# 5. ตรวจสอบความพร้อมของไฟล์สำหรับคอมไพล์
Write-Host "--------------------------------------------------" -ForegroundColor Cyan
Write-Host "[*] กำลังตรวจสอบไฟล์ระบบ..." -ForegroundColor Cyan

$gppExists = Test-Path "$msysPath\ucrt64\bin\g++.exe"
$glutExists = Test-Path "$msysPath\ucrt64\include\GL\glut.h"

if ($gppExists -and $glutExists) {
    Write-Host "[✓] ทุกอย่างพร้อมใช้งานแล้ว!" -ForegroundColor Green
    Write-Host "    - Compiler: C:\msys64\ucrt64\bin\g++.exe" -ForegroundColor Gray
    Write-Host "    - OpenGL Header: C:\msys64\ucrt64\include\GL\glut.h" -ForegroundColor Gray
    Write-Host "==================================================" -ForegroundColor Green
    Write-Host "ตั้งค่าสภาพแวดล้อม OpenGL และ VS Code สำเร็จแล้ว! คุณสามารถเปิดไฟล์ .cpp ในแล็บแล้วกด Ctrl + Shift + B เพื่อ Build หรือกด F5 เพื่อ Debug ได้ทันที" -ForegroundColor Green
} else {
    if (-not $gppExists) { Write-Host "[X] ไม่พบ g++.exe ที่ C:\msys64\ucrt64\bin\" -ForegroundColor Red }
    if (-not $glutExists) { Write-Host "[X] ไม่พบ glut.h ที่ C:\msys64\ucrt64\include\GL\" -ForegroundColor Red }
    Write-Host "[X] การตั้งค่าไม่สมบูรณ์ กรุณาตรวจสอบข้อผิดพลาดด้านบน" -ForegroundColor Red
}
