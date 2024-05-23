#include <windows.h>
LRESULT CALLBACK WindowProc(HWND hwnd,
                            UINT uMsg,
                            WPARAM wParam,
                            LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow) {
    const char CLASS_NAME[] = "Sample Window Class";
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);
    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            "Main Window",
            WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            NULL,
            NULL,
            hInstance,
            NULL
    );
    if (hwnd == NULL) {
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
void AddControls(HWND hwnd) {
    CreateWindow("BUTTON",
                 "Modal MessageBox",
                 WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 10,10,150,30,
                 hwnd,
                 (HMENU)1,
                 (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                 NULL);

    CreateWindow("BUTTON",
                 "Non-Modal MessageBox",
                 WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 10, 50, 150, 30,
                 hwnd,
                 (HMENU)2,
                 (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                 NULL);
    CreateWindow("BUTTON",
                 "Multiple MessageBoxes",
                 WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 10, 90, 150, 30,
                 hwnd,
                 (HMENU)3,
                 (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                 NULL);
}
LRESULT CALLBACK WindowProc(HWND hwnd,
                            UINT uMsg,
                            WPARAM wParam,
                            LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            AddControls(hwnd);
            return 0;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 1:
                    MessageBox(hwnd,
                               "This is a modal MessageBox",
                               "Modal",
                               MB_OK);
                    break;
                case 2:
                    MessageBox(hwnd,
                               "This is a non-modal MessageBox",
                               "Non-Modal",
                               MB_OK | MB_SYSTEMMODAL);
                    break;
                case 3:
                    MessageBox(hwnd,
                               "First MessageBox",
                               "Multiple",
                               MB_OK);
                    MessageBox(hwnd,
                               "Second MessageBox",
                               "Multiple",
                               MB_OK);
                    MessageBox(hwnd,
                               "Third MessageBox",
                               "Multiple",
                               MB_OK);
                    break;
            }
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    CreateWindow("BUTTON",
                 "I want 5",
                 WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 10, 200, 150, 30,
                 hwnd,
                 (HMENU)3,
                 (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                 NULL);

    return DefWindowProc(hwnd,
                         uMsg,
                         wParam,
                         lParam);
}
