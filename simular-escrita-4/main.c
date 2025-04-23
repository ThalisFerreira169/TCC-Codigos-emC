// Acesso a API do Windows
#include <windows.h>
// Controles de botão e caixa de texto
#include <commctrl.h>
// Incluindo o typeText
#include "typeText.c"

// Definir o processo de criação da janela
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_COMMAND:
            // Se o botão foi clicado
            if (LOWORD(wParam) == 1)
            {
                char text[1024];
                // Obtém o texto da caixa de texto
                GetWindowText(GetDlgItem(hwnd, 2), text, sizeof(text));
                // Chama a função de digitar
                Sleep(3000);
                type(text);
            }
            return 0;

        case WM_CREATE:
            // Criar a caixa de texto para o texto
            CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 
                         10, 10, 380, 100, hwnd, (HMENU)2, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

            // Criar o botão
            CreateWindow("BUTTON", "Simulate Typing", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         10, 120, 150, 30, hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main()
{
    // Registrar a classe da janela
    const char* className = "TypingToolClass";
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = className;
    RegisterClass(&wc);

    // Criar a janela
    HWND hwnd = CreateWindowEx(0, className, "Typing Tool", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
                               NULL, NULL, wc.hInstance, NULL);

    // Mostrar a janela
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // Loop de mensagens da janela
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}