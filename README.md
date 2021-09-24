# named-pipe-sample

This sandbox shows an example of using the Windows named pipe API with byte-type pipes.

## Running the code in Visual Studio Code

1. Set up a C/C++ compiler
    - You can set up g++ following https://code.visualstudio.com/docs/languages/cpp.
        - Note: After MSYS2 is installed, one must use pacman in the MSYS CLI to install the actual tools such as gdb, gcc, and g++.
        - Note: One might have to restart Visual Studio Code after adding the new path variable in order for the new path variable to be picked up.
    - Alternatively, if you already have C++ buildtools installed from a Visual Studio installation, you can follow https://code.visualstudio.com/docs/cpp/config-msvc to compile using cl.exe.
        - Note: Make sure you launch code or code-insiders from the Developer Command Prompt for VS 2019 (or VS 2017, if you have that version installed instead). Otherwise, the cl.exe compile task will not be able to find some environment variables such as `INCLUDE`.
2. Run the compile task (Ctrl+Shift+B, then select the task) on the client and server C files to generate the executables.
3. Run the server executable in a terminal.
4. Run the client executable in another terminal.
5. If the output doesn't have any line starting with "Assertion failed", the program ran successfully.

## Troubleshooting

- There is a list of Windows error codes at https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes--0-499-.
- A summary of named pipe operations is at https://docs.microsoft.com/en-us/windows/win32/ipc/named-pipe-operations.
