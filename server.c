#include <assert.h>
#include <stdio.h>
#include <windows.h>

#define USE_CONNECT

int main() {
    printf("Start the named pipe server\n");

    LPCSTR pipename = "\\\\.\\pipe\\name";
    DWORD maxInstances = 2;
    DWORD maxMessageLength = 32 * 1024;
    DWORD defaultTimeout = 10000;
    HANDLE pipe = CreateNamedPipe(
        pipename,
        PIPE_ACCESS_OUTBOUND,
        PIPE_TYPE_BYTE,
        maxInstances,
        maxMessageLength,
        0,
        defaultTimeout,
        NULL
    );
    assert(pipe != INVALID_HANDLE_VALUE);
    assert(GetLastError() == ERROR_SUCCESS);

    BOOL success;

    printf("Wait for the client\n");

    // We don't have to call Connect
    // In that case, the client blocks while waiting for read
#ifdef USE_CONNECT
    success = ConnectNamedPipe(pipe, NULL);
    assert(success == TRUE);
    assert(GetLastError() == ERROR_SUCCESS);
#else
    Sleep(defaultTimeout);
#endif

    printf("Send over data\n");

    LPCSTR buffer = "Data here";
    DWORD data_size = (strlen(buffer) + 1) * sizeof(CHAR);
    DWORD bytes_written = 0;
    success = WriteFile(
        pipe,
        (LPCVOID)buffer,
        data_size,
        &bytes_written,
        NULL
    );
    assert(success == TRUE);
    assert(bytes_written == data_size);
    assert(GetLastError() == ERROR_SUCCESS);

    printf("Cleanup\n");

    FlushFileBuffers(pipe);
    DisconnectNamedPipe(pipe);
    CloseHandle(pipe);
    return 0;
}
