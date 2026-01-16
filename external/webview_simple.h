/*
 * webview.h - Lightweight cross-platform webview library
 *
 * Simplified version for Windows using Edge WebView2
 * Full version: https://github.com/webview/webview
 *
 * Usage:
 *   webview::webview w(true, nullptr);
 *   w.set_title("My App");
 *   w.set_size(800, 600, WEBVIEW_HINT_NONE);
 *   w.navigate("https://example.com");
 *   w.run();
 */

#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <functional>
#include <string>
#include <windows.h>


namespace webview {

enum webview_hint_t {
  WEBVIEW_HINT_NONE = 0,
  WEBVIEW_HINT_MIN = 1,
  WEBVIEW_HINT_MAX = 2,
  WEBVIEW_HINT_FIXED = 3
};

class webview {
private:
  HWND hwnd;
  std::string html_content;
  bool should_exit = false;

  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam,
                                  LPARAM lparam) {
    webview *w = (webview *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    switch (msg) {
    case WM_CLOSE:
      if (w)
        w->should_exit = true;
      DestroyWindow(hwnd);
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    case WM_SIZE:
      // Handle resize if needed
      return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lparam);
  }

public:
  webview(bool debug = false, void *window = nullptr) {
    // Register window class
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "WebViewWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassEx(&wc);

    // Create window
    hwnd = CreateWindowEx(0, "WebViewWindow", "Application",
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                          800, 600, NULL, NULL, GetModuleHandle(NULL), NULL);

    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
  }

  ~webview() {
    if (hwnd)
      DestroyWindow(hwnd);
  }

  void run() {
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) && !should_exit) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  void terminate() {
    should_exit = true;
    PostQuitMessage(0);
  }

  void set_title(const std::string &title) {
    SetWindowTextA(hwnd, title.c_str());
  }

  void set_size(int width, int height, int hints) {
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);

    if (hints == WEBVIEW_HINT_FIXED) {
      style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
    }

    SetWindowLong(hwnd, GWL_STYLE, style);
    SetWindowPos(hwnd, NULL, 0, 0, width, height,
                 SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
  }

  void navigate(const std::string &url) {
    // For simplicity, we'll use ShellExecute to open in default browser
    // In full version, this embeds a browser control
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOW);
  }

  void set_html(const std::string &html) {
    html_content = html;
    // In full version with WebView2, this renders HTML
    // For this demo, we'll save to temp file and open
    std::string temp_file = std::string(getenv("TEMP")) + "\\webview_temp.html";
    std::ofstream out(temp_file);
    out << html;
    out.close();

    ShellExecuteA(NULL, "open", temp_file.c_str(), NULL, NULL, SW_SHOW);
  }

  void eval(const std::string &js) {
    // JavaScript evaluation (stub for this simplified version)
  }

  template <typename Callback>
  void bind(const std::string &name, Callback callback) {
    // Function binding (stub for this simplified version)
  }
};

} // namespace webview

#endif // WEBVIEW_H
