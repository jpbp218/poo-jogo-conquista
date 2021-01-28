#include "consola.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void limpa()
{
    COORD topLeft = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(hConsole, &screen);
    FillConsoleOutputCharacterA(
        hConsole, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(
        hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(hConsole, topLeft);
}

void cCiano() { SetConsoleTextAttribute(hConsole, CIANO); }

void cBranco() { SetConsoleTextAttribute(hConsole, BRANCO); }

void cVermelho() { SetConsoleTextAttribute(hConsole, VERMELHO); }

void cAzul() { SetConsoleTextAttribute(hConsole, AZUL); }

void cAmarelo() { SetConsoleTextAttribute(hConsole, AMARELO); }

void cVerde() { SetConsoleTextAttribute(hConsole, VERDE); }

void espera()
{
    string lixo;
    cout << "Por favor, carregue no [ENTER] para continuar...";
    getline(cin, lixo);
}

void erro(string const &texto)
{
    cVermelho();
    cout << texto << endl;
    cBranco();
}

void aviso(string const &texto)
{
    cAmarelo();
    cout << texto << endl;
    cBranco();
}

void titulo(string const &texto)
{
    cCiano();
    cout << texto << endl;
    cBranco();
}
