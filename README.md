# OpenGL C++ Development Setup Guide (คู่มือการตั้งค่าสภาพแวดล้อม OpenGL)

โปรเจกต์นี้เป็นโครงสร้างสำหรับการทำแล็บและการพัฒนาโปรแกรมกราฟิก 3 มิติด้วย **C++ และ OpenGL (โดยใช้ FreeGLUT)** 
คู่มือนี้จะแนะนำวิธีการตั้งค่าสภาพแวดล้อมเพื่อให้สามารถคอมไพล์และรันโค้ดของแล็บต่าง ๆ ได้ ทั้งบน **Visual Studio 2022** (แนะนำสำหรับ Windows) และ **Visual Studio Code (VS Code) ร่วมกับ MSYS2**

---

## 📂 โครงสร้างของโปรเจกต์ (Project Structure)
* **`src/`**: โฟลเดอร์ที่เก็บซอร์สโค้ดของแต่ละแล็บ (เช่น `662110158_Lab1`, `662110158_Lab2` ฯลฯ) ซึ่งจะมีไฟล์โปรเจกต์ `.sln` และ `.vcxproj` สำหรับ Visual Studio
* **`docs/`**: เอกสารคำอธิบายแล็บและทฤษฎีในรูปแบบไฟล์ PDF
* **`.vscode/`**: ไฟล์การตั้งค่างานคอมไพล์ (Build Tasks) สำหรับ VS Code

---

## 🛠️ วิธีที่ 1: ตั้งค่าและใช้งานผ่าน Visual Studio 2022 (แนะนำสำหรับ Windows)
เนื่องจากโปรเจกต์นี้มีไฟล์ Solution (`.sln`) และ Project (`.vcxproj`) ของ Visual Studio เตรียมไว้ให้แล้ว วิธีนี้จึงเป็นวิธีที่ง่ายและเร็วที่สุด

### ทางเลือก A: ติดตั้งผ่าน NuGet Package Manager (ง่ายที่สุด 🌟)
NuGet จะดาวน์โหลดและตั้งค่า Path ต่าง ๆ รวมถึงไฟล์ Header, Library และ DLL ให้กับโปรเจกต์โดยอัตโนมัติ:
1. เปิดไฟล์ `.sln` ของแล็บที่ต้องการ (เช่น [src/662110158_Lab1/662110158_Lab1.sln](file:///C:/Users/noppon/source/01-DG/dg202-cgpro/src/662110158_Lab1/662110158_Lab1.sln)) ด้วย Visual Studio 2022
2. คลิกขวาที่ชื่อโปรเจกต์ในหน้าต่าง **Solution Explorer** (เช่น `662110158_Lab1_1`) แล้วเลือก **Manage NuGet Packages...**
3. ไปที่แท็บ **Browse** ค้นหาคำว่า `freeglut`
4. เลือกแพ็คเกจชื่อ **`freeglut`** (จัดทำโดย *Transmission Zero*) แล้วกด **Install**
5. รอให้การติดตั้งเสร็จสิ้น ระบบจะตั้งค่าลิงก์ไฟล์ให้โดยอัตโนมัติ
6. กด **F5** เพื่อเริ่มคอมไพล์และรันโปรแกรมได้ทันที!

---

### ทางเลือก B: ติดตั้งแบบ Manual (ดาวน์โหลดไฟล์เอง)
หากต้องการตั้งค่าด้วยตัวเองทีละขั้นตอน สามารถทำได้ดังนี้:

1. **ดาวน์โหลด FreeGLUT**:
   * เข้าไปที่เว็บไซต์ [Transmission Zero - FreeGLUT MSVC](https://www.transmissionzero.co.uk/software/freeglut-devel/)
   * ดาวน์โหลดไฟล์ **freeglut MSVC Package** (ไฟล์ ZIP)
   * แตกไฟล์ออกมาไว้ในเครื่อง เช่น `C:\libs\freeglut`

2. **ตั้งค่าใน Visual Studio**:
   * คลิกขวาที่โปรเจกต์ของคุณ -> เลือก **Properties**
   * ตรวจสอบว่าเลือก **Configuration** เป็น *All Configurations* และ **Platform** เป็น *x64* (หรือตามที่ใช้งาน)
   * **การตั้งค่า Include (Header)**:
     * ไปที่ **Configuration Properties -> C/C++ -> General**
     * ในช่อง **Additional Include Directories** ให้ใส่พาธไปยังโฟลเดอร์ include:
       `C:\libs\freeglut\include`
   * **การตั้งค่า Library (.lib)**:
     * ไปที่ **Configuration Properties -> Linker -> General**
     * ในช่อง **Additional Library Directories** ให้ใส่พาธไปยังโฟลเดอร์ lib (เลือกตามสถาปัตยกรรม เช่น x64):
       `C:\libs\freeglut\lib\x64`
   * **การตั้งค่า Linker Input**:
     * ไปที่ **Configuration Properties -> Linker -> Input**
     * ในช่อง **Additional Dependencies** ให้กดแก้ไขและเพิ่มชื่อไฟล์ไลบรารี:
       `freeglut.lib`
   * **การจัดการไฟล์ DLL**:
     * ไปที่โฟลเดอร์ `C:\libs\freeglut\bin\x64` คัดลอกไฟล์ `freeglut.dll`
     * นำไปวางในโฟลเดอร์ที่รันโปรแกรม (เช่น โฟลเดอร์ `x64/Debug` หรือโฟลเดอร์เดียวกับไฟล์ `.vcxproj`) หรือคัดลอกไปไว้ในไดเรกทอรีระบบของ Windows เช่น `C:\Windows\System32` เพื่อให้เปิดใช้งานได้จากทุกโปรเจกต์

---

## 💻 วิธีที่ 2: ตั้งค่าและใช้งานผ่าน VS Code + MSYS2 (MinGW-w64 / UCRT64)
หากต้องการใช้ VS Code ในการเขียนและรันไฟล์ C++ ของ OpenGL คุณต้องใช้ MSYS2 เป็น Compiler และตัวจัดการแพ็คเกจ

### ⚡ วิธีการติดตั้งแบบอัตโนมัติด้วย PowerShell Script (ง่ายที่สุด! 🚀)
โปรเจกต์นี้มีสคริปต์ [setup_msys2.ps1](file:///C:/Users/noppon/source/01-DG/dg202-cgpro/setup_msys2.ps1) สำหรับดาวน์โหลดและติดตั้งคอมไพเลอร์ ไลบรารี FreeGLUT รวมถึงสร้างไฟล์กำหนดค่าระบบของ VS Code ให้คุณแบบอัตโนมัติ:
1. เปิด VS Code ในโฟลเดอร์โปรเจกต์นี้
2. เปิด Terminal ใน VS Code (กด `Ctrl + ~` หรือ `Ctrl + \``)
3. รันคำสั่งต่อไปนี้เพื่อรันสคริปต์:
   ```powershell
   Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
   .\setup_msys2.ps1
   ```
4. สคริปต์จะทำการอัปเดตแพ็คเกจ ติดตั้ง FreeGLUT, เพิ่ม PATH และเขียนไฟล์กำหนดค่าทั้งหมดในโฟลเดอร์ `.vscode` (ได้แก่ `tasks.json`, `launch.json`, และ `c_cpp_properties.json`) ให้ทำงานร่วมกันได้ทันที
5. เมื่อสคริปต์ทำงานเสร็จสิ้น ให้ **ปิดและเปิด VS Code ใหม่อีกครั้ง** เพื่อโหลดค่า Environment PATH และ IntelliSense ใหม่

---

### 🛠️ วิธีการติดตั้งแบบจัดการด้วยตัวเอง (Manual)
หากไม่ต้องการรันสคริปต์อัตโนมัติ สามารถทำตามขั้นตอนต่อไปนี้ได้:

1. **ติดตั้ง Compiler และไลบรารีผ่าน MSYS2**
1. ดาวน์โหลดและติดตั้ง [MSYS2](https://www.msys2.org/) (โดยปกติจะถูกติดตั้งไว้ที่ `C:\msys64`)
2. เปิดแอปพลิเคชัน **MSYS2 UCRT64 Terminal** ขึ้นมา
3. ติดตั้งเครื่องมือพัฒนาภาษา C++ (g++, make, gdb) โดยรันคำสั่ง:
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-toolchain
   ```
4. ติดตั้ง FreeGLUT สำหรับสภาพแวดล้อม UCRT64 โดยรันคำสั่ง:
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-freeglut
   ```
   *(หมายเหตุ: ระบบจะติดตั้ง OpenGL และ GLU ให้อัตโนมัติพร้อมกัน)*

### 2. ตั้งค่า VS Code
1. เปิดโฟลเดอร์โปรเจกต์ [dg202-cgpro](file:///C:/Users/noppon/source/01-DG/dg202-cgpro) ด้วย VS Code
2. ติดตั้งส่วนขยาย (Extension): **C/C++** (จาก Microsoft)
3. ตรวจสอบหรือสร้างไฟล์ [.vscode/tasks.json](file:///C:/Users/noppon/source/01-DG/dg202-cgpro/.vscode/tasks.json) ของคุณให้รองรับการลิงก์ไลบรารี OpenGL โดยปรับแก้ให้เป็นตามนี้:

```json
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
```

### 3. วิธีการรันโปรเจกต์บน VS Code
1. เปิดไฟล์ซอร์สโค้ด `.cpp` ที่ต้องการคอมไพล์ (เช่น `src/662110158_Lab1/662110158_Lab1_1/662110158_Lab1_1.cpp`)
2. กดปุ่ม `Ctrl + Shift + B` เพื่อทำการคอมไพล์ (Build) ไฟล์
3. เปิด Terminal ในตำแหน่งไฟล์นั้นแล้วเปิดไฟล์ `.exe` ที่ได้ขึ้นมา เช่น:
   ```powershell
   .\662110158_Lab1_1.exe
   ```
   หรือจะใช้แถบเมนูด้านบนของ VS Code: **Run -> Start Debugging (F5)** เพื่อรันก็ได้เช่นกัน

---

## 💡 คำแนะนำเพิ่มเติม (Tips)
* **โปรแกรมไม่แสดงภาพ/เด้งออกทันที**: สำหรับการคอมไพล์ผ่าน Visual Studio ตรวจสอบให้มั่นใจว่าไฟล์ `freeglut.dll` อยู่ในโฟลเดอร์เดียวกับตัวโปรแกรมที่สร้างออกมา (`.exe`) หรือถูกคัดลอกไปไว้ใน `C:\Windows\System32` แล้ว
* **การเรียกใช้ OpenGL Header**: ในระบบปฏิบัติการ Windows ควรมีบรรทัด `#include <windows.h>` ก่อน `#include <GL/glut.h>` เสมอ เพื่อป้องกันข้อผิดพลาดในการแปลคำสั่ง (Compilation Error)
