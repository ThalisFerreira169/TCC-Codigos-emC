#include <windows.h>

void typeText(const char* text)
{
    // Percorrer caracteres
    for (int i = 0; text[i] != '\0'; i++)
    {
        // Obtendo código da tecla
        SHORT key = VkKeyScan(text[i]);

        // Criar o evento para pressionar tecla
        INPUT input[2] = {0};

        // Evento de pressioanr a tecla
        input[0].type = INPUT_KEYBOARD;
        //Código da tecla virtual
        input[0].ki.wVk = (WORD)key;
        //Flags de pressionamento
        input[0].ki.dwFlags = 0;

        // Evento de liberar a tecla
        input[1].type = INPUT_KEYBOARD;
        // Código da tecla virtual
        input[1].ki.wVk = (WORD)key;
        // Flag para liberar a tecla
        input[1].ki.dwFlags = KEYEVENTF_KEYUP;

        // Enviar os eventos de pressionamento e liberação
        SendInput(2, input, sizeof(INPUT));
        // Pausa para dar tempo entre as teclas
        Sleep(100);
    }
}

int main ()
{
    //SLEEP PARA TESTE
    Sleep(2000);

    // Digitar texto
    const char* text = "Teste para digitação";
    typeText(text);

    return 0;
}