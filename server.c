#include <assert.h>
#include <stdio.h>
#include <windows.h>

#define USE_CONNECT 1
#define LOOP_FOR_CLIENTS 1

int main() {
    printf("Start the named pipe server\n");

    LPCSTR pipename = "\\\\.\\pipe\\demoNamedPipe";
    DWORD maxInstances = PIPE_UNLIMITED_INSTANCES;
    DWORD maxMessageLength = 32 * 1024;
    DWORD defaultTimeout = 5000;
    BOOL success;
    DWORD error;

    printf("Create the pipe\n");
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
    error = GetLastError();
    printf("CreateNamedPipe error %d\n", error);
    assert(error == ERROR_SUCCESS);
    assert(pipe != INVALID_HANDLE_VALUE);

#if LOOP_FOR_CLIENTS
    while (1) {
#endif
        printf("Wait for the client\n");

        // We don't have to call Connect
        // In that case, the client blocks while waiting for read
#if USE_CONNECT
        success = ConnectNamedPipe(pipe, NULL);
        error = GetLastError();
        printf("ConnectNamedPipe error %d\n", error);
        assert(error == ERROR_SUCCESS);
        assert(success == TRUE);
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
        error = GetLastError();
        printf("WriteFile error %d\n", error);
        assert(error == ERROR_SUCCESS);
        assert(success == TRUE);
        assert(bytes_written == data_size);

        printf("Cleanup\n");

        success = FlushFileBuffers(pipe);
        error = GetLastError();
        printf("FlushFileBuffers error %d\n", error);
        assert(error == ERROR_SUCCESS);
        assert(success == TRUE);

        success = DisconnectNamedPipe(pipe);
        error = GetLastError();
        printf("DisconnectNamedPipe error %d\n", error);
        assert(error == ERROR_SUCCESS);
        assert(success == TRUE);
#if LOOP_FOR_CLIENTS
    }
#endif

    CloseHandle(pipe);
    error = GetLastError();
    printf("CloseHandle error %d\n", error);
    assert(error == ERROR_SUCCESS);
    assert(success == TRUE);

    printf("Exiting\n");
    return 0;
}
