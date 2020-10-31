format PE console
entry start

include 'win32a.inc'
include 'det_macro.inc'

;--------------------------------------------------------------------------
section '.data' data readable writable

        strInputMsg  db 'Input the matrix A by its columns: ', 10, 0
        strVecElemI  db 'A[%d] = ', 0
        strScanInt   db '%d', 0
        strDetValue  db 'det(A) = %d', 10, 0
        strIncorValue db 'Incorrect value = %d (must be in [-50, 50])', 10, 0

        vec_size     dd 36
        det          dd 0
        i            dd ?
        tmp          dd ?
        vec          rd 100

;--------------------------------------------------------------------------
section '.code' code readable executable
start:
; 1) matrix input
        push strInputMsg
        call [printf]
        VInputMacro vec, vec_size
; 2) get the matrix determinant
        VDetMacro vec, vec_size, det
; 3) print the determinant
        push [det]
        push strDetValue
        call [printf]

finish:
        call [getch]

        push 0
        call [ExitProcess]

;--------------------------------------------------------------------------
                                                 
section '.idata' import data readable
    library kernel, 'kernel32.dll',\
            msvcrt, 'msvcrt.dll',\
            user32,'USER32.DLL'

include 'api\user32.inc'

include 'api\kernel32.inc'
    import kernel,\
           ExitProcess, 'ExitProcess'

include 'api\kernel32.inc'
    import msvcrt,\
           printf, 'printf',\
           scanf, 'scanf',\
           getch, '_getch'