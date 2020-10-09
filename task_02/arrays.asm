; Петров Иван БПИ195-2
; Вариант 4
; --------------------
; Разработать программу, которая вводит одномерный массив A[N],
; формирует из элементов массива A новый массив B, по правилу:
; B[i] = A[i] == 0 ? 0 : (A[i] > 0 ? 1 : -1), и выводит его.
; --------------------    

format PE console
entry start

include 'win32a.inc'

;--------------------------------------------------------------------------
section '.data' data readable writable

        strVecSize   db 'Enter the size of vector: ', 0
        strIncorSize db 'Incorrect size of vector = %d (must be in (0, 100])', 10, 0
        strVecElemI  db '[%d]? ', 0
        strScanInt   db '%d', 0
        strVecElemOut  db '[%d] = %d', 10, 0
        strVec1      db 'Old Vector: ', 10, 0
        strVec2      db 'New Vector: ', 10, 0

        vec_size     dd 0
        i            dd ?
        tmp1         dd ?
        tmp2         dd ?
        tmpStack     dd ?
        vec1          rd 100
        vec2          rd 100

;--------------------------------------------------------------------------
section '.code' code readable executable
start:
        call VectorInput

; process the vector
        call VectorAggregate

; print out the old vector
        push strVec1
        call [printf]
        mov eax, vec1
        call VectorOut

; print out the new vector
        push strVec2
        call [printf]
        mov eax, vec2
        call VectorOut

finish:
        call [getch]

        push 0
        call [ExitProcess]

;--------------------------------------------------------------------------
VectorInput:
        push strVecSize
        call [printf]
        add esp, 4

        push vec_size
        push strScanInt
        call [scanf]
        add esp, 8

        mov eax, [vec_size]
        cmp eax, 0
        jg getVector

; if size is negative
IncorrectSize:
        push eax
        push strIncorSize
        call [printf]

        call [getch]

        push 0
        call [ExitProcess]

getVector:
; if size is too big
        cmp eax, 100
        jg IncorrectSize

; else continue
        xor ecx, ecx
        mov ebx, vec1
getVecLoop:
        mov [tmp1], ebx
        cmp ecx, [vec_size]
        jge endInputVector

        ; input element
        mov [i], ecx
        push ecx
        push strVecElemI
        call [printf]
        add esp, 8

        push ebx
        push strScanInt
        call [scanf]
        add esp, 8

        mov ecx, [i]
        inc ecx
        mov ebx, [tmp1]
        add ebx, 4
        jmp getVecLoop
endInputVector:
        ret
;--------------------------------------------------------------------------
VectorAggregate:
        xor ecx, ecx            ; ecx = 0
        mov ebx, vec1            ; ebx = &vec
        mov edx, vec2

aggregateVecLoop:
        mov [tmp1], ebx
        mov [tmp2], edx
        cmp ecx, [vec_size]
        je endAggregateVecLoop      ; to end of loop

        xor eax, eax

        mov esi, [ebx]
        cmp esi, 0
        jg putOne ; > 0
        je putZero ; == 0
        jl putMinusZero ; < 0

putOne:
        mov eax, 1
        jmp finishAggregate

putZero:
        mov eax, 0
        jmp finishAggregate

putMinusZero:
        mov eax, -1
        jmp finishAggregate

finishAggregate:
        mov [ebx], esi

        mov [edx], eax

        mov [i], ecx

        mov ecx, [i]
        inc ecx
        mov ebx, [tmp1]
        mov edx, [tmp2]

        add ebx, 4
        add edx, 4

        jmp aggregateVecLoop
endAggregateVecLoop:
        ret
;--------------------------------------------------------------------------
VectorOut:
        mov [tmpStack], esp
        xor ecx, ecx            ; ecx = 0
        mov ebx, eax            ; ebx = &vec
outputVecLoop:
        mov [tmp1], ebx
        cmp ecx, [vec_size]
        je endOutputVector      ; to end of loop
        mov [i], ecx

        ; output element
        push dword [ebx]
        push ecx
        push strVecElemOut
        call [printf]

        mov ecx, [i]
        inc ecx
        mov ebx, [tmp1]
        add ebx, 4
        jmp outputVecLoop
endOutputVector:
        mov esp, [tmpStack]
        ret
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
