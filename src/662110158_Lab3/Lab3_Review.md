# 📝 สรุปเนื้อหาการทบทวน Lab 3: Three-Dimensional Viewing
อ้างอิงจากเอกสารประกอบการเรียน: [03Three-DimensionalViewing.pdf](file:///C:/Users/noppon/source/01-DG/dg202-cgpro/docs/03Three-DimensionalViewing.pdf)

โปรเจกต์ของแล็บนี้: [src/662110158_Lab3](file:///C:/Users/noppon/source/01-DG/dg202-cgpro/src/662110158_Lab3)

---

## 🎯 จุดประสงค์ของปฏิบัติการ Lab 3
1. สามารถอธิบายความแตกต่างและการนำไปประยุกต์ใช้ของภาพมุมมองขนาน (Orthographic Projections) และมุมมองมีทัศนมิติ (Perspective Projections) ได้
2. สามารถเขียนโปรแกรมภาษา C++ เพื่อเรนเดอร์ภาพโมเดล 3D แบบทัศนมิติร่วมกับการใช้ฟังก์ชันดีบักกล้องได้
3. สามารถลดภาระความจำของการเรียกใช้งานจุดยอดด้วยระบบ Vertex Arrays ของ OpenGL
4. เข้าใจและเขียนโปรแกรมควบคุมกล้องมุมมองบุคคลที่หนึ่ง (First-Person Camera Movement) โดยใช้ความรู้ด้านเวกเตอร์ตรีโกณมิติ

---

## 🏛️ ทฤษฎีและเนื้อหาหลัก

### 1. Orthographic vs. Perspective Viewing Volume
* **Orthographic (`glOrtho`)**: เหมาะกับงานเขียนแบบ วัตถุขนาดเท่าเดิมแม้จะอยู่ใกล้มุมกล้องหรือไกลพิกัดระนาบ
* **Perspective (`gluPerspective` หรือ `glFrustum`)**: วัตถุที่อยู่ไกลจะดูหดเล็กลงตามลำดับสายตามนุษย์ มีจุดสิ้นสุดสายตา (Vanishing Point)

### 2. ฟังก์ชันควบคุมตำแหน่งมุมมองกล้อง (`gluLookAt`)
ทำหน้าที่เสมือนตัววางตำแหน่งกล้องในระบบพิกัดโลก (World Space) ด้วยพารามิเตอร์ 9 ตัว:
$$\text{gluLookAt}(eyex, eyey, eyez, \text{ // ตำแหน่งกล้อง} \\ centerx, centery, centerz, \text{ // ตำแหน่งจุดที่มอง} \\ upx, upy, upz) \text{ // เวกเตอร์ชี้ขึ้น}$$

---

## 💻 ฟังก์ชันสำคัญและการประยุกต์ใช้งาน

### 1. การตั้งค่าสัดส่วนกล้องทัศนมิติ (Perspective Camera)
ในการ Reshape หน้าต่างจอภาพ:
```cpp
void Reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // ตั้งค่าความกว้างกล้อง 45 องศา, สัดส่วนจอ w/h, ใกล้สุด 1.0, ไกลสุด 500.0
    gluPerspective(45.0f, (float)w / h, 1.0f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
```

### 2. ระบบระบุจุดแบบอาร์เรย์ (Vertex Arrays - Lab3_2)
การวาดวัตถุซับซ้อน เช่น ทรงกระบอก (Cylinder) ในแบบเดิมจะกินทรัพยากร CPU สูง การเก็บข้อมูลลงอาร์เรย์จึงดีกว่า:
```cpp
// 1. ลงทะเบียนการใช้ Vertex Array
glEnableClientState(GL_VERTEX_ARRAY);
// 2. ระบุตัวแปรอาร์เรย์พิกัดพอยน์เตอร์
glVertexPointer(3, GL_FLOAT, 0, vertexArray);
// 3. เรียกวาดตามลำดับดัชนี (Index)
glBegin(GL_TRIANGLE_STRIP);
for(int i = 0; i < numElements; i++) {
    glArrayElement(indices[i]);
}
glEnd();
```

### 3. การสร้างกล้องเคลื่อนที่อิสระ (First-Person Camera - Lab3_3)
การหมุนกล้องคำนวณผ่านพิกัดเชิงมุมวงกลม โดยเมื่อขยับกล้องซ้ายขวา จะได้เวกเตอร์ทิศทางใหม่:
```cpp
// อัปเดตมุมมองกล้อง
float viewX = sin(angle);
float viewZ = -cos(angle);

// เมื่อเคลื่อนกล้องไปข้างหน้า (Walk Forward)
camX += viewX * speed;
camZ += viewZ * speed;

// จัดวางตำแหน่งใน Render Loop
gluLookAt(camX, 1.0f, camZ,       // พิกัดผู้เล่น
          camX + viewX, 1.0f, camZ + viewZ,  // จุดสายตามองไป
          0.0f, 1.0f, 0.0f);      // แกนขึ้นปกติ
```

---

## 📖 สรุปผลแล็บย่อยในบทปฏิบัติการ
* **`Lab3_1.cpp`**: วาดรูปสี่เหลี่ยมและทรงกลม 3 ชิ้นในมุมมอง Perspective
* **`Lab3_2.cpp`**: เรนเดอร์รูปทรงกระบอก 3 มิติโดยใช้ Vertex Array พร้อมฟังก์ชันปรับความละเอียดของ Grid ตาข่ายด้วยปุ่มลูกศร
* **`Lab3_3.cpp`**: เรนเดอร์รูปโดนัทลายเส้น (`glWireTorus`) พร้อมระบบควบคุมกล้องให้สามารถเดินหน้า/ถอยหลัง และเลี้ยวกล้องได้สมบูรณ์
* **`Lab3_4_a.cpp`**: การตอบคำถามและการวาดตัวอักษรชื่อย่อ 3 มิติ พร้อมจัดแสงเงา
