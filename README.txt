HỆ THỐNG QUẢN LÍ CHI TIÊU
1. Quản Lý Tài Khoản
- Đăng ký/Đăng nhập: Hệ thống xác thực an toàn.
- Đa người dùng: Hỗ trợ nhiều tài khoản trên cùng một ứng dụng.
2. Quản Lý Thu Chi
- Dashboard: Tổng quan tài chính với các chỉ số quan trọng (Tổng chi, chi tiêu tháng, trung bình ngày).
- Biểu đồ trực quan:
  + Biểu đồ tròn (Pie Chart): Phân bổ chi tiêu theo danh mục.
  + Biểu đồ cột (Bar Chart): Xu hướng chi tiêu 7 ngày qua.
- Thao tác đầy đủ: Thêm, sửa, xóa các khoản chi tiêu nhanh chóng.
3. Tiện Ích & Giao Diện
- Bộ lọc nâng cao: Tìm kiếm và lọc theo ngày, số tiền, danh mục.
- Xuất dữ liệu: Hỗ trợ xuất dữ liệu ra file CSV.
- Theme Đa Dạng:
  + Mặc định (Hiện đại, tối giản)
  + Giáng Sinh (Hiệu ứng tuyết rơi)
  + Tết Nguyên Đán (Hoa mai, lồng đèn)
#Cấu Trúc Dự Án 
├── include/               # Các file header (.h)
│   ├── Expense.h          # Định nghĩa cấu trúc dữ liệu
│   ├── ExpenseManager.h   # Lớp quản lý logic nghiệp vụ
│   ├── GlobalContext.h    # Biến toàn cục và trạng thái
│   ├── HtmlContent.h      # Khai báo nội dung HTML
│   ├── ServerSetup.h      # Cấu hình server và routing
│   ├── Utils.h            # Các hàm tiện ích
│   └── index_html_embedded.h # Mã nguồn Frontend nhúng
├── src/                   # Các file mã nguồn (.cpp)
│   ├── main.cpp           # Điểm khởi chạy ứng dụng
│   ├── Expense.cpp        # Cài đặt Expense
│   ├── ExpenseManager.cpp # Cài đặt ExpenseManager
│   ├── ServerSetup.cpp    # Cài đặt Server & API
│   └── Utils.cpp          # Cài đặt tiện ích
├── external/              # Thư viện bên thứ 3 (httplib, json)
├── data/                  # Dữ liệu người dùng (Tự tạo)
└── users.json             # Cơ sở dữ liệu tài khoản (Tự tạo)
# Hướng Dẫn Cài Đặt & Biên Dịch
-Yêu Cầu
  + Hệ điều hành: Windows.
  + Trình biên dịch: g++ (MinGW-w64) hỗ trợ C++17.
# Lệnh Biên Dịch
Chạy lệnh sau tại thư mục gốc của dự án:

```bash
g++ -std=c++17 -D_WIN32_WINNT=0x0A00 -I./include -I. src/*.cpp -o expense_manager.exe -lws2_32 -static -static-libgcc -static-libstdc++
```
# Cách Chạy
1. Chạy file `expense_manager.exe` sau khi biên dịch thành công.
2. Ứng dụng sẽ tự động mở trình duyệt tại `http://127.0.0.1:8080`.
3. Đăng nhập với tài khoản mặc định hoặc tạo mới.
## Tài Khoản Mặc Định

| Username | Password |
|----------|----------|
| `admin`  | `admin`  |
| `user`   | `123456` |

## Công Nghệ
- **Backend**: C++17
- **Frontend**: HTML5, CSS3, JavaScript (Single Page Application)
- **Libraries**: `cpp-httplib` (Server), `nlohmann/json` (JSON)