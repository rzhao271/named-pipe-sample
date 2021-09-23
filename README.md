# named-pipe-example

This sandbox shows an example of using the named pipe API with byte-type pipes.

## Running the code

1. I set up g++ using https://code.visualstudio.com/docs/languages/cpp.
    - Note: After MSYS2 is installed, one must use pacman in the MSYS CLI to install the actual tools such as gdb, gcc, and g++
    - Note: One might have to restart Visual Studio Code in order for the new path variable to be picked up.
    - Also, I couldn't get cl.exe to build in Visual Studio Code even though I had buildtools installed.
2. Run the configured compile task on the client and server C files to generate the executables.
3. Run the server executable in a terminal.
4. Run the client executable in another terminal.
5. If the output doesn't have any line starting with "Assertion failed", the program ran successfully.
