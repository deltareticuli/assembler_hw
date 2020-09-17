format PE console

entry start

include 'win32a.inc'

section '.code' code readable executable
        start:
                push hello
                call [printf]

                push 0

                call [getch]
                call [ExitProcess]

section '.rdata' data readable
        hello db 'Hello World!', 0

section '.idata' data readable import
        library kernel32, 'kernel32.dll', \
                msvcrt,   'msvcrt.dll'

        import kernel32, \
               ExitProcess, 'ExitProcess'

        import msvcrt, \
               printf, 'printf', \
               getch, '_getch'