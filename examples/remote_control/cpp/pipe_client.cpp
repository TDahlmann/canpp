// pipe_client.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#include <iostream>

int main()
{
    HANDLE hPipe;
    DWORD dwWritten;


    hPipe = CreateFile(TEXT("\\\\.\\pipe\\CanppServerPipe"),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);
    if (hPipe != INVALID_HANDLE_VALUE)
    {
        // start 
        WriteFile(hPipe,
            "START\n",
            6,   
            &dwWritten,
            NULL);

        // start may take some time
        Sleep(2000);

        // send command
        char buffer[1000];
        strcpy_s(buffer, "COMMAND:TEST1\n");
        WriteFile(hPipe,
            buffer,
            strlen(buffer),
            &dwWritten,
            NULL);

        Sleep(5000);

        // stop
        WriteFile(hPipe,
            "STOP\n",
            5,   
            &dwWritten,
            NULL);


        CloseHandle(hPipe);
    }

    return (0);
}

