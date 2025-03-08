# 🚀 Tiva C Series TM4C123 Labs

A collection of **embedded systems labs** for the **Tiva C Series TM4C123GH6PM** microcontroller, covering **GPIO, timers, interrupts, and UART communication** using **bare-metal programming**.

## 📌 Labs Overview

### **1️⃣ GPIO & LED Control**
- Configure **Port F** and blink an LED.
- Use **bitwise operations** for efficient GPIO control.

### **2️⃣ Switch & LED Interfacing**
- Read **push buttons (SW1 & SW2)** to control LEDs.
- Implement **pull-up resistors**.

### **3️⃣-4️⃣ Memory & Bitwise Operations**
- Work with **pointers & memory-mapped registers**.
- Use macros to define **GPIO register addresses**.

### **5️⃣-7️⃣ Timers & Delays**
- Implement **software delays** and **SysTick timers**.
- Configure **GPTM timers** for periodic and one-shot modes.

### **8️⃣-🔟 Interrupt Handling**
- Configure **GPIO & timer interrupts**.
- Implement **ISR-driven** LED toggling.

### **1️⃣1️⃣-1️⃣2️⃣ UART Communication**
- Configure **UART0** for serial input/output.
- Control LEDs using **terminal commands**.

---

## 🛠️ Setup & Compilation

### **Requirements**
- **Tiva C LaunchPad (TM4C123GXL)**
- **Keil uVision / TI Code Composer Studio (CCS)**
- **PuTTY / Tera Term** (for UART debugging)

### **Running the Labs**
```bash
git clone https://github.com/your-username/TivaC-Labs.git
