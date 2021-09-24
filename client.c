#include <assert.h>
#include <stdio.h>
#include <windows.h>

#define MAX_MESSAGE_LENGTH 32 * 1024

int main() {
    printf("Start the named pipe client\n");

    LPCSTR pipename = "\\\\.\\pipe\\demoNamedPipe";
    BOOL success;
    DWORD error;

    printf("Wait for the pipe to become available\n");
    success = WaitNamedPipe(pipename, NMPWAIT_USE_DEFAULT_WAIT);
    error = GetLastError();
    printf("WaitNamedPipe error %d\n", error);
    assert(error == ERROR_SUCCESS);
    assert(success == TRUE);

    printf("Create the pipe\n");
    HANDLE pipe = CreateFile(
        pipename,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    error = GetLastError();
    printf("CreateFile error %d\n", error);
    assert(error == ERROR_SUCCESS);
    assert(pipe != INVALID_HANDLE_VALUE);

    printf("Read from the server\n");

    LPCSTR expected_data = "Data here";
    DWORD bytes_to_read = (strlen(expected_data) + 1) * sizeof(CHAR);
    DWORD bytes_read = 0;
    CHAR buffer[MAX_MESSAGE_LENGTH];
    success = ReadFile(
        pipe,
        (LPVOID)buffer,
        MAX_MESSAGE_LENGTH,
        &bytes_read,
        NULL
    );
    error = GetLastError();
    printf("ReadFile error %d\n", error);
    assert(error == ERROR_SUCCESS);
    assert(success == TRUE);
    assert(bytes_to_read == bytes_read);
    assert(strncmp(buffer, expected_data, bytes_to_read) == 0);

    printf("Cleanup\n");

    success = CloseHandle(pipe);
    error = GetLastError();
    printf("CloseHandle error %d\n", error);
    assert(error == ERROR_SUCCESS);
    assert(success == TRUE);

    printf("Exiting\n");
    return 0;
}
