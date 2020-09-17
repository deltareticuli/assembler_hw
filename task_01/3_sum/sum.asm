format PE console

entry start

include 'win32a.inc'

section '.code' code readable executable
        start:
                push firstMessage
                call [printf]

                push num1
                push formatNum
                call [scanf]

                push secondMessage
                call [printf]

                push num2
                push formatNum
                call [scanf]

                mov ecx, [num1]
                add ecx, [num2]

                push ecx
                push formatRes
                call [printf]

                call [getch]

                push 0
                call [ExitProcess]

section '.rdata' data readable writable
        firstMessage db 'Input A: ', 0
        secondMessage db 'Input B: ', 0

        formatNum db '%d', 0
        formatRes db 'A + B = %d', 0

        num1 dd ?
        num2 dd ?

section '.idata' data readable import
        library kernel32, 'kernel32.dll', \
                msvcrt,   'msvcrt.dll'

        import kernel32, \
               ExitProcess, 'ExitProcess'

        import msvcrt, \
               printf, 'printf', \
               getch, '_getch', \
               scanf, 'scanf'