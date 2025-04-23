#include <windows.h>

// Função para pressionar e soltar a tecla
void pressKey(WORD vk)
{
    // Pressionar a tecla
    keybd_event(vk, 0, 0, 0);

    // Soltar a tecla
    keybd_event(vk, 0, KEYEVENTF_KEYUP, 0);
}

// Função para captar maiúsculo ou minúsculo
int isCapsLockOn()
{
    return (GetKeyState(VK_CAPITAL) & 0x0001);
}

// Função para digitar o texto
void type(const char* text)
{
    // Verifica o estado do Caps Lock
    int capsLockOn = isCapsLockOn();

    // Loop que percorre o texto
    for (int i = 0; text[i] != '\0'; i++)
    {
        // Obtendo código da tecla
        char c = text[i];

        // Checagem de tecla
        SHORT vkNormal = VkKeyScan(c);
        // Criação do evento de pressionar tecla
        INPUT input[2] = {0};

        // Verifica se o caractere é maiúsculo
        int isUpper = (vkNormal & 0x0100) != 0;

        // Se o caractere é maiúsculo e Caps Lock não está ativado, pressione a tecla Shift
        if (isUpper && !capsLockOn) {
            // Pressiona Shift
            keybd_event(VK_SHIFT, 0, 0, 0);
        }

        /// Evento de pressionar a tecla
        input[0].type = INPUT_KEYBOARD;
        //Código da tecla virtual
        input[0].ki.wVk = (WORD)vkNormal;
        //Flags de pressionamento
        input[0].ki.dwFlags = 0;

        // Evento de liberar a tecla
        input[1].type = INPUT_KEYBOARD;
        // Código da tecla virtual
        input[1].ki.wVk = (WORD)vkNormal;
        // Flag para liberar a tecla
        input[1].ki.dwFlags = KEYEVENTF_KEYUP;

        // Enviar os eventos de pressionamento e liberação da tecla
        SendInput(2, input, sizeof(INPUT));

        // Se a tecla for maiúscula e o Caps Lock não estiver ativado, solta o Shift
        if (isUpper && !capsLockOn) {
            // Solta Shift
            keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
        }

        // Sleep entre as teclas
        Sleep(100);
    }
}

int main ()
{
    //SLEEP PARA TESTE
    Sleep(3000);

    // Var do texto
    // TESTE 1
    const char* text = "Hello, this is a test for my typing tool. I hope you enjoy this tool!";

    // TESTE 2
    //const char* text = "Hello! This is a test for my typing tool. !@#$¨¨&&**)_)(*(*@)(#@&#@*@#@$¨@*&$¨@*#@&*#¨@&#¨@##$))";

    // Utilizando função de digitar
    type(text);

    return 0;
}