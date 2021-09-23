#include <assert.h>
#include <stdio.h>
#include <windows.h>

int main() {
    printf("Start the named pipe client\n");

    LPCSTR pipename = "\\\\.\\pipe\\name";
    HANDLE pipe = CreateFile(
        pipename,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    assert(pipe != INVALID_HANDLE_VALUE);
    assert(GetLastError() == ERROR_SUCCESS);

    BOOL success;

    printf("Read from the server\n");

    LPCSTR expected_data = "Data here";
    DWORD bytes_to_read = (strlen(expected_data) + 1) * sizeof(CHAR);
    DWORD bytes_read = 0;
    DWORD maxMessageLength = 32 * 1024;
    CHAR buffer[maxMessageLength];
    success = ReadFile(
        pipe,
        (LPVOID)buffer,
        bytes_to_read,
        &bytes_read,
        NULL
    );
    assert(success == TRUE);
    assert(bytes_to_read == bytes_read);
    assert(strncmp(buffer, expected_data, bytes_to_read) == 0);
    assert(GetLastError() == ERROR_SUCCESS);

    printf("Cleanup\n");

    CloseHandle(pipe);
    return 0;
}
