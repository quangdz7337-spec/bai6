# bai6
# STM32F103C8T6 + BH1750 (I2C) + UART

Dự án này sử dụng **STM32F103C8T6 (Blue Pill)** để đọc dữ liệu cường độ ánh sáng từ cảm biến **BH1750** thông qua giao tiếp **I2C1**, sau đó gửi dữ liệu về máy tính qua **USART1** để hiển thị trên terminal.

---

## Tính năng
- Cấu hình **I2C1** (PB6 = SCL, PB7 = SDA) để giao tiếp với BH1750.
- Cấu hình **USART1** (PA9 = TX, PA10 = RX) với tốc độ **9600 baud**.
- Đọc giá trị **Lux** bằng chế độ **One-Time Measurement**.
- Gửi dữ liệu đo được qua UART theo chu kỳ **500 ms**.

---

## Kết nối phần cứng

### BH1750 → STM32
| BH1750 Pin | STM32F103 Pin |
|------------|---------------|
| VCC        | 3.3V          |
| GND        | GND           |
| SDA        | PB7           |
| SCL        | PB6           |

> ⚠️ SDA và SCL cần **điện trở kéo lên (pull-up)** khoảng 4.7kΩ lên 3.3V.

### UART → PC (qua USB-to-UART)
| STM32 Pin  | USB-UART Pin |
|------------|--------------|
| PA9 (TX)   | RX           |
| PA10 (RX)  | TX           |
| GND        | GND          |

---

## Giải thích code

### Cấu hình I2C1
- Bật clock cho **GPIOB** và **I2C1**.
- Thiết lập **PB6 (SCL)** và **PB7 (SDA)** ở chế độ **Alternate Function Open-Drain**.
- Cấu hình tốc độ I2C = **100kHz** (Standard Mode).
- Địa chỉ STM32 khi làm Slave = `0x00` (không quan trọng vì STM32 là Master).
- Cho phép **ACK** để xác nhận dữ liệu.

### Cấu hình USART1
- Bật clock cho **GPIOA** và **USART1**.
- Thiết lập **PA9 (TX)** ở chế độ **AF Push-Pull**, **PA10 (RX)** ở chế độ **Floating Input**.
- Baudrate = **9600**, định dạng **8N1**.

### Vòng lặp chính
- Gửi thông báo `"BH1750 One-Time Lux Test"`.
- Đọc giá trị ánh sáng từ BH1750 bằng `BH1750_ReadLux_OneTime()`.
- Gửi dữ liệu qua UART theo định dạng:
BH1750 One-Time Lux Test
Lux: 45.78
Lux: 46.21
Lux: 47.02
