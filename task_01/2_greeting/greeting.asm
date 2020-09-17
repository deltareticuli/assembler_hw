format PE console

entry start

include 'win32a.inc'

section '.code' code readable executable
        start:
                push question
                call [printf]

                push name
                push formatStr
                call [scanf]

                push name
                push greeting
                call [printf]

                call [getch]

                push 0
                call [ExitProcess]

section '.rdata' data readable writable
        question db 'What is your name?', 10, 0
        greeting db 'Hello, %s!', 0

        formatStr db '%s', 0

        name db ?

section '.idata' data readable import
        library kernel32, 'kernel32.dll', \
                msvcrt,   'msvcrt.dll'

        import kernel32, \
               ExitProcess, 'ExitProcess'

        import msvcrt, \
               printf, 'printf', \
               getch, '_getch', \
               scanf, 'scanf'