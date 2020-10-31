;--------------------------------------------------------------------------
; macro used to input the matrix by its columns
macro VInputMacro vecAddr, len {
VectorInput:
        mov eax, [len]
        cmp eax, 0
        jg  getVector
        getVector:
        xor ecx, ecx            ; ecx = 0
        mov ebx, vecAddr        ; ebx = &vecAddr
getVecLoop:
        mov [tmp], ebx
        cmp ecx, [len]
        jge endInputVector       ; to end of loop

        ; input element
        mov [i], ecx
        push ecx
        push strVecElemI
        call [printf]

        push ebx
        push strScanInt
        call [scanf]

        mov edx, [ebx]
        cmp edx, -50
        jg endVecLoop

IncorrectSize:
        push edx
        push strIncorValue
        call [printf]

        call [getch]

        push 0
        call [ExitProcess]

endVecLoop:
        cmp edx, 50
        jg IncorrectSize

        add esp, 8

        mov ecx, [i]
        inc ecx
        mov ebx, [tmp]
        add ebx, 4
        jmp getVecLoop
endInputVector:
}

;--------------------------------------------------------------------------
; macro used to multiply 6 vector items with given indices
macro TermMultiply vec, i1, i2, i3, i4, i5, i6 {
        mov eax, [vec + 4*i1]
        imul eax, [vec + 4*i2]
        imul eax, [vec + 4*i3]
        imul eax, [vec + 4*i4]
        imul eax, [vec + 4*i5]
        imul eax, [vec + 4*i6]
}

;-------------------------------------- ------------------------------------
; macro used to add multiplication product to given variable
macro DetAdd vec, det, i1, i2, i3, i4, i5, i6 {
        TermMultiply vec, i1, i2, i3, i4, i5, i6
        add [det], eax
}

;--------------------------------------------------------------------------
; macro used to subtract multiplication product from given variable
macro DetSub vec, det, i1, i2, i3, i4, i5, i6 {
        TermMultiply vec, i1, i2, i3, i4, i5, i6
        sub [det], eax
}

;--------------------------------------------------------------------------
; macro used to calculate the matrix determinant
macro VDetMacro vecAddr, len, result {
        xor ecx, ecx            ; ecx = 0
        mov ebx, vecAddr        ; ebx = &vecAddr

        DetAdd vec, det, 0, 7, 14, 21, 28, 35
        DetSub vec, det, 0, 7, 14, 21, 29, 34
        DetSub vec, det, 0, 7, 14, 22, 27, 35
        DetAdd vec, det, 0, 7, 14, 22, 29, 33
        DetAdd vec, det, 0, 7, 14, 23, 27, 34
        DetSub vec, det, 0, 7, 14, 23, 28, 33
        DetSub vec, det, 0, 7, 15, 20, 28, 35
        DetAdd vec, det, 0, 7, 15, 20, 29, 34
        DetAdd vec, det, 0, 7, 15, 22, 26, 35
        DetSub vec, det, 0, 7, 15, 22, 29, 32
        DetSub vec, det, 0, 7, 15, 23, 26, 34
        DetAdd vec, det, 0, 7, 15, 23, 28, 32
        DetAdd vec, det, 0, 7, 16, 20, 27, 35
        DetSub vec, det, 0, 7, 16, 20, 29, 33
        DetSub vec, det, 0, 7, 16, 21, 26, 35
        DetAdd vec, det, 0, 7, 16, 21, 29, 32
        DetAdd vec, det, 0, 7, 16, 23, 26, 33
        DetSub vec, det, 0, 7, 16, 23, 27, 32
        DetSub vec, det, 0, 7, 17, 20, 27, 34
        DetAdd vec, det, 0, 7, 17, 20, 28, 33
        DetAdd vec, det, 0, 7, 17, 21, 26, 34
        DetSub vec, det, 0, 7, 17, 21, 28, 32
        DetSub vec, det, 0, 7, 17, 22, 26, 33
        DetAdd vec, det, 0, 7, 17, 22, 27, 32
        DetSub vec, det, 0, 8, 13, 21, 28, 35
        DetAdd vec, det, 0, 8, 13, 21, 29, 34
        DetAdd vec, det, 0, 8, 13, 22, 27, 35
        DetSub vec, det, 0, 8, 13, 22, 29, 33
        DetSub vec, det, 0, 8, 13, 23, 27, 34
        DetAdd vec, det, 0, 8, 13, 23, 28, 33
        DetAdd vec, det, 0, 8, 15, 19, 28, 35
        DetSub vec, det, 0, 8, 15, 19, 29, 34
        DetSub vec, det, 0, 8, 15, 22, 25, 35
        DetAdd vec, det, 0, 8, 15, 22, 29, 31
        DetAdd vec, det, 0, 8, 15, 23, 25, 34
        DetSub vec, det, 0, 8, 15, 23, 28, 31
        DetSub vec, det, 0, 8, 16, 19, 27, 35
        DetAdd vec, det, 0, 8, 16, 19, 29, 33
        DetAdd vec, det, 0, 8, 16, 21, 25, 35
        DetSub vec, det, 0, 8, 16, 21, 29, 31
        DetSub vec, det, 0, 8, 16, 23, 25, 33
        DetAdd vec, det, 0, 8, 16, 23, 27, 31
        DetAdd vec, det, 0, 8, 17, 19, 27, 34
        DetSub vec, det, 0, 8, 17, 19, 28, 33
        DetSub vec, det, 0, 8, 17, 21, 25, 34
        DetAdd vec, det, 0, 8, 17, 21, 28, 31
        DetAdd vec, det, 0, 8, 17, 22, 25, 33
        DetSub vec, det, 0, 8, 17, 22, 27, 31
        DetAdd vec, det, 0, 9, 13, 20, 28, 35
        DetSub vec, det, 0, 9, 13, 20, 29, 34
        DetSub vec, det, 0, 9, 13, 22, 26, 35
        DetAdd vec, det, 0, 9, 13, 22, 29, 32
        DetAdd vec, det, 0, 9, 13, 23, 26, 34
        DetSub vec, det, 0, 9, 13, 23, 28, 32
        DetSub vec, det, 0, 9, 14, 19, 28, 35
        DetAdd vec, det, 0, 9, 14, 19, 29, 34
        DetAdd vec, det, 0, 9, 14, 22, 25, 35
        DetSub vec, det, 0, 9, 14, 22, 29, 31
        DetSub vec, det, 0, 9, 14, 23, 25, 34
        DetAdd vec, det, 0, 9, 14, 23, 28, 31
        DetAdd vec, det, 0, 9, 16, 19, 26, 35
        DetSub vec, det, 0, 9, 16, 19, 29, 32
        DetSub vec, det, 0, 9, 16, 20, 25, 35
        DetAdd vec, det, 0, 9, 16, 20, 29, 31
        DetAdd vec, det, 0, 9, 16, 23, 25, 32
        DetSub vec, det, 0, 9, 16, 23, 26, 31
        DetSub vec, det, 0, 9, 17, 19, 26, 34
        DetAdd vec, det, 0, 9, 17, 19, 28, 32
        DetAdd vec, det, 0, 9, 17, 20, 25, 34
        DetSub vec, det, 0, 9, 17, 20, 28, 31
        DetSub vec, det, 0, 9, 17, 22, 25, 32
        DetAdd vec, det, 0, 9, 17, 22, 26, 31
        DetSub vec, det, 0, 10, 13, 20, 27, 35
        DetAdd vec, det, 0, 10, 13, 20, 29, 33
        DetAdd vec, det, 0, 10, 13, 21, 26, 35
        DetSub vec, det, 0, 10, 13, 21, 29, 32
        DetSub vec, det, 0, 10, 13, 23, 26, 33
        DetAdd vec, det, 0, 10, 13, 23, 27, 32
        DetAdd vec, det, 0, 10, 14, 19, 27, 35
        DetSub vec, det, 0, 10, 14, 19, 29, 33
        DetSub vec, det, 0, 10, 14, 21, 25, 35
        DetAdd vec, det, 0, 10, 14, 21, 29, 31
        DetAdd vec, det, 0, 10, 14, 23, 25, 33
        DetSub vec, det, 0, 10, 14, 23, 27, 31
        DetSub vec, det, 0, 10, 15, 19, 26, 35
        DetAdd vec, det, 0, 10, 15, 19, 29, 32
        DetAdd vec, det, 0, 10, 15, 20, 25, 35
        DetSub vec, det, 0, 10, 15, 20, 29, 31
        DetSub vec, det, 0, 10, 15, 23, 25, 32
        DetAdd vec, det, 0, 10, 15, 23, 26, 31
        DetAdd vec, det, 0, 10, 17, 19, 26, 33
        DetSub vec, det, 0, 10, 17, 19, 27, 32
        DetSub vec, det, 0, 10, 17, 20, 25, 33
        DetAdd vec, det, 0, 10, 17, 20, 27, 31
        DetAdd vec, det, 0, 10, 17, 21, 25, 32
        DetSub vec, det, 0, 10, 17, 21, 26, 31
        DetAdd vec, det, 0, 11, 13, 20, 27, 34
        DetSub vec, det, 0, 11, 13, 20, 28, 33
        DetSub vec, det, 0, 11, 13, 21, 26, 34
        DetAdd vec, det, 0, 11, 13, 21, 28, 32
        DetAdd vec, det, 0, 11, 13, 22, 26, 33
        DetSub vec, det, 0, 11, 13, 22, 27, 32
        DetSub vec, det, 0, 11, 14, 19, 27, 34
        DetAdd vec, det, 0, 11, 14, 19, 28, 33
        DetAdd vec, det, 0, 11, 14, 21, 25, 34
        DetSub vec, det, 0, 11, 14, 21, 28, 31
        DetSub vec, det, 0, 11, 14, 22, 25, 33
        DetAdd vec, det, 0, 11, 14, 22, 27, 31
        DetAdd vec, det, 0, 11, 15, 19, 26, 34
        DetSub vec, det, 0, 11, 15, 19, 28, 32
        DetSub vec, det, 0, 11, 15, 20, 25, 34
        DetAdd vec, det, 0, 11, 15, 20, 28, 31
        DetAdd vec, det, 0, 11, 15, 22, 25, 32
        DetSub vec, det, 0, 11, 15, 22, 26, 31
        DetSub vec, det, 0, 11, 16, 19, 26, 33
        DetAdd vec, det, 0, 11, 16, 19, 27, 32
        DetAdd vec, det, 0, 11, 16, 20, 25, 33
        DetSub vec, det, 0, 11, 16, 20, 27, 31
        DetSub vec, det, 0, 11, 16, 21, 25, 32
        DetAdd vec, det, 0, 11, 16, 21, 26, 31
        DetSub vec, det, 1, 6, 14, 21, 28, 35
        DetAdd vec, det, 1, 6, 14, 21, 29, 34
        DetAdd vec, det, 1, 6, 14, 22, 27, 35
        DetSub vec, det, 1, 6, 14, 22, 29, 33
        DetSub vec, det, 1, 6, 14, 23, 27, 34
        DetAdd vec, det, 1, 6, 14, 23, 28, 33
        DetAdd vec, det, 1, 6, 15, 20, 28, 35
        DetSub vec, det, 1, 6, 15, 20, 29, 34
        DetSub vec, det, 1, 6, 15, 22, 26, 35
        DetAdd vec, det, 1, 6, 15, 22, 29, 32
        DetAdd vec, det, 1, 6, 15, 23, 26, 34
        DetSub vec, det, 1, 6, 15, 23, 28, 32
        DetSub vec, det, 1, 6, 16, 20, 27, 35
        DetAdd vec, det, 1, 6, 16, 20, 29, 33
        DetAdd vec, det, 1, 6, 16, 21, 26, 35
        DetSub vec, det, 1, 6, 16, 21, 29, 32
        DetSub vec, det, 1, 6, 16, 23, 26, 33
        DetAdd vec, det, 1, 6, 16, 23, 27, 32
        DetAdd vec, det, 1, 6, 17, 20, 27, 34
        DetSub vec, det, 1, 6, 17, 20, 28, 33
        DetSub vec, det, 1, 6, 17, 21, 26, 34
        DetAdd vec, det, 1, 6, 17, 21, 28, 32
        DetAdd vec, det, 1, 6, 17, 22, 26, 33
        DetSub vec, det, 1, 6, 17, 22, 27, 32
        DetAdd vec, det, 1, 8, 12, 21, 28, 35
        DetSub vec, det, 1, 8, 12, 21, 29, 34
        DetSub vec, det, 1, 8, 12, 22, 27, 35
        DetAdd vec, det, 1, 8, 12, 22, 29, 33
        DetAdd vec, det, 1, 8, 12, 23, 27, 34
        DetSub vec, det, 1, 8, 12, 23, 28, 33
        DetSub vec, det, 1, 8, 15, 18, 28, 35
        DetAdd vec, det, 1, 8, 15, 18, 29, 34
        DetAdd vec, det, 1, 8, 15, 22, 24, 35
        DetSub vec, det, 1, 8, 15, 22, 29, 30
        DetSub vec, det, 1, 8, 15, 23, 24, 34
        DetAdd vec, det, 1, 8, 15, 23, 28, 30
        DetAdd vec, det, 1, 8, 16, 18, 27, 35
        DetSub vec, det, 1, 8, 16, 18, 29, 33
        DetSub vec, det, 1, 8, 16, 21, 24, 35
        DetAdd vec, det, 1, 8, 16, 21, 29, 30
        DetAdd vec, det, 1, 8, 16, 23, 24, 33
        DetSub vec, det, 1, 8, 16, 23, 27, 30
        DetSub vec, det, 1, 8, 17, 18, 27, 34
        DetAdd vec, det, 1, 8, 17, 18, 28, 33
        DetAdd vec, det, 1, 8, 17, 21, 24, 34
        DetSub vec, det, 1, 8, 17, 21, 28, 30
        DetSub vec, det, 1, 8, 17, 22, 24, 33
        DetAdd vec, det, 1, 8, 17, 22, 27, 30
        DetSub vec, det, 1, 9, 12, 20, 28, 35
        DetAdd vec, det, 1, 9, 12, 20, 29, 34
        DetAdd vec, det, 1, 9, 12, 22, 26, 35
        DetSub vec, det, 1, 9, 12, 22, 29, 32
        DetSub vec, det, 1, 9, 12, 23, 26, 34
        DetAdd vec, det, 1, 9, 12, 23, 28, 32
        DetAdd vec, det, 1, 9, 14, 18, 28, 35
        DetSub vec, det, 1, 9, 14, 18, 29, 34
        DetSub vec, det, 1, 9, 14, 22, 24, 35
        DetAdd vec, det, 1, 9, 14, 22, 29, 30
        DetAdd vec, det, 1, 9, 14, 23, 24, 34
        DetSub vec, det, 1, 9, 14, 23, 28, 30
        DetSub vec, det, 1, 9, 16, 18, 26, 35
        DetAdd vec, det, 1, 9, 16, 18, 29, 32
        DetAdd vec, det, 1, 9, 16, 20, 24, 35
        DetSub vec, det, 1, 9, 16, 20, 29, 30
        DetSub vec, det, 1, 9, 16, 23, 24, 32
        DetAdd vec, det, 1, 9, 16, 23, 26, 30
        DetAdd vec, det, 1, 9, 17, 18, 26, 34
        DetSub vec, det, 1, 9, 17, 18, 28, 32
        DetSub vec, det, 1, 9, 17, 20, 24, 34
        DetAdd vec, det, 1, 9, 17, 20, 28, 30
        DetAdd vec, det, 1, 9, 17, 22, 24, 32
        DetSub vec, det, 1, 9, 17, 22, 26, 30
        DetAdd vec, det, 1, 10, 12, 20, 27, 35
        DetSub vec, det, 1, 10, 12, 20, 29, 33
        DetSub vec, det, 1, 10, 12, 21, 26, 35
        DetAdd vec, det, 1, 10, 12, 21, 29, 32
        DetAdd vec, det, 1, 10, 12, 23, 26, 33
        DetSub vec, det, 1, 10, 12, 23, 27, 32
        DetSub vec, det, 1, 10, 14, 18, 27, 35
        DetAdd vec, det, 1, 10, 14, 18, 29, 33
        DetAdd vec, det, 1, 10, 14, 21, 24, 35
        DetSub vec, det, 1, 10, 14, 21, 29, 30
        DetSub vec, det, 1, 10, 14, 23, 24, 33
        DetAdd vec, det, 1, 10, 14, 23, 27, 30
        DetAdd vec, det, 1, 10, 15, 18, 26, 35
        DetSub vec, det, 1, 10, 15, 18, 29, 32
        DetSub vec, det, 1, 10, 15, 20, 24, 35
        DetAdd vec, det, 1, 10, 15, 20, 29, 30
        DetAdd vec, det, 1, 10, 15, 23, 24, 32
        DetSub vec, det, 1, 10, 15, 23, 26, 30
        DetSub vec, det, 1, 10, 17, 18, 26, 33
        DetAdd vec, det, 1, 10, 17, 18, 27, 32
        DetAdd vec, det, 1, 10, 17, 20, 24, 33
        DetSub vec, det, 1, 10, 17, 20, 27, 30
        DetSub vec, det, 1, 10, 17, 21, 24, 32
        DetAdd vec, det, 1, 10, 17, 21, 26, 30
        DetSub vec, det, 1, 11, 12, 20, 27, 34
        DetAdd vec, det, 1, 11, 12, 20, 28, 33
        DetAdd vec, det, 1, 11, 12, 21, 26, 34
        DetSub vec, det, 1, 11, 12, 21, 28, 32
        DetSub vec, det, 1, 11, 12, 22, 26, 33
        DetAdd vec, det, 1, 11, 12, 22, 27, 32
        DetAdd vec, det, 1, 11, 14, 18, 27, 34
        DetSub vec, det, 1, 11, 14, 18, 28, 33
        DetSub vec, det, 1, 11, 14, 21, 24, 34
        DetAdd vec, det, 1, 11, 14, 21, 28, 30
        DetAdd vec, det, 1, 11, 14, 22, 24, 33
        DetSub vec, det, 1, 11, 14, 22, 27, 30
        DetSub vec, det, 1, 11, 15, 18, 26, 34
        DetAdd vec, det, 1, 11, 15, 18, 28, 32
        DetAdd vec, det, 1, 11, 15, 20, 24, 34
        DetSub vec, det, 1, 11, 15, 20, 28, 30
        DetSub vec, det, 1, 11, 15, 22, 24, 32
        DetAdd vec, det, 1, 11, 15, 22, 26, 30
        DetAdd vec, det, 1, 11, 16, 18, 26, 33
        DetSub vec, det, 1, 11, 16, 18, 27, 32
        DetSub vec, det, 1, 11, 16, 20, 24, 33
        DetAdd vec, det, 1, 11, 16, 20, 27, 30
        DetAdd vec, det, 1, 11, 16, 21, 24, 32
        DetSub vec, det, 1, 11, 16, 21, 26, 30
        DetAdd vec, det, 2, 6, 13, 21, 28, 35
        DetSub vec, det, 2, 6, 13, 21, 29, 34
        DetSub vec, det, 2, 6, 13, 22, 27, 35
        DetAdd vec, det, 2, 6, 13, 22, 29, 33
        DetAdd vec, det, 2, 6, 13, 23, 27, 34
        DetSub vec, det, 2, 6, 13, 23, 28, 33
        DetSub vec, det, 2, 6, 15, 19, 28, 35
        DetAdd vec, det, 2, 6, 15, 19, 29, 34
        DetAdd vec, det, 2, 6, 15, 22, 25, 35
        DetSub vec, det, 2, 6, 15, 22, 29, 31
        DetSub vec, det, 2, 6, 15, 23, 25, 34
        DetAdd vec, det, 2, 6, 15, 23, 28, 31
        DetAdd vec, det, 2, 6, 16, 19, 27, 35
        DetSub vec, det, 2, 6, 16, 19, 29, 33
        DetSub vec, det, 2, 6, 16, 21, 25, 35
        DetAdd vec, det, 2, 6, 16, 21, 29, 31
        DetAdd vec, det, 2, 6, 16, 23, 25, 33
        DetSub vec, det, 2, 6, 16, 23, 27, 31
        DetSub vec, det, 2, 6, 17, 19, 27, 34
        DetAdd vec, det, 2, 6, 17, 19, 28, 33
        DetAdd vec, det, 2, 6, 17, 21, 25, 34
        DetSub vec, det, 2, 6, 17, 21, 28, 31
        DetSub vec, det, 2, 6, 17, 22, 25, 33
        DetAdd vec, det, 2, 6, 17, 22, 27, 31
        DetSub vec, det, 2, 7, 12, 21, 28, 35
        DetAdd vec, det, 2, 7, 12, 21, 29, 34
        DetAdd vec, det, 2, 7, 12, 22, 27, 35
        DetSub vec, det, 2, 7, 12, 22, 29, 33
        DetSub vec, det, 2, 7, 12, 23, 27, 34
        DetAdd vec, det, 2, 7, 12, 23, 28, 33
        DetAdd vec, det, 2, 7, 15, 18, 28, 35
        DetSub vec, det, 2, 7, 15, 18, 29, 34
        DetSub vec, det, 2, 7, 15, 22, 24, 35
        DetAdd vec, det, 2, 7, 15, 22, 29, 30
        DetAdd vec, det, 2, 7, 15, 23, 24, 34
        DetSub vec, det, 2, 7, 15, 23, 28, 30
        DetSub vec, det, 2, 7, 16, 18, 27, 35
        DetAdd vec, det, 2, 7, 16, 18, 29, 33
        DetAdd vec, det, 2, 7, 16, 21, 24, 35
        DetSub vec, det, 2, 7, 16, 21, 29, 30
        DetSub vec, det, 2, 7, 16, 23, 24, 33
        DetAdd vec, det, 2, 7, 16, 23, 27, 30
        DetAdd vec, det, 2, 7, 17, 18, 27, 34
        DetSub vec, det, 2, 7, 17, 18, 28, 33
        DetSub vec, det, 2, 7, 17, 21, 24, 34
        DetAdd vec, det, 2, 7, 17, 21, 28, 30
        DetAdd vec, det, 2, 7, 17, 22, 24, 33
        DetSub vec, det, 2, 7, 17, 22, 27, 30
        DetAdd vec, det, 2, 9, 12, 19, 28, 35
        DetSub vec, det, 2, 9, 12, 19, 29, 34
        DetSub vec, det, 2, 9, 12, 22, 25, 35
        DetAdd vec, det, 2, 9, 12, 22, 29, 31
        DetAdd vec, det, 2, 9, 12, 23, 25, 34
        DetSub vec, det, 2, 9, 12, 23, 28, 31
        DetSub vec, det, 2, 9, 13, 18, 28, 35
        DetAdd vec, det, 2, 9, 13, 18, 29, 34
        DetAdd vec, det, 2, 9, 13, 22, 24, 35
        DetSub vec, det, 2, 9, 13, 22, 29, 30
        DetSub vec, det, 2, 9, 13, 23, 24, 34
        DetAdd vec, det, 2, 9, 13, 23, 28, 30
        DetAdd vec, det, 2, 9, 16, 18, 25, 35
        DetSub vec, det, 2, 9, 16, 18, 29, 31
        DetSub vec, det, 2, 9, 16, 19, 24, 35
        DetAdd vec, det, 2, 9, 16, 19, 29, 30
        DetAdd vec, det, 2, 9, 16, 23, 24, 31
        DetSub vec, det, 2, 9, 16, 23, 25, 30
        DetSub vec, det, 2, 9, 17, 18, 25, 34
        DetAdd vec, det, 2, 9, 17, 18, 28, 31
        DetAdd vec, det, 2, 9, 17, 19, 24, 34
        DetSub vec, det, 2, 9, 17, 19, 28, 30
        DetSub vec, det, 2, 9, 17, 22, 24, 31
        DetAdd vec, det, 2, 9, 17, 22, 25, 30
        DetSub vec, det, 2, 10, 12, 19, 27, 35
        DetAdd vec, det, 2, 10, 12, 19, 29, 33
        DetAdd vec, det, 2, 10, 12, 21, 25, 35
        DetSub vec, det, 2, 10, 12, 21, 29, 31
        DetSub vec, det, 2, 10, 12, 23, 25, 33
        DetAdd vec, det, 2, 10, 12, 23, 27, 31
        DetAdd vec, det, 2, 10, 13, 18, 27, 35
        DetSub vec, det, 2, 10, 13, 18, 29, 33
        DetSub vec, det, 2, 10, 13, 21, 24, 35
        DetAdd vec, det, 2, 10, 13, 21, 29, 30
        DetAdd vec, det, 2, 10, 13, 23, 24, 33
        DetSub vec, det, 2, 10, 13, 23, 27, 30
        DetSub vec, det, 2, 10, 15, 18, 25, 35
        DetAdd vec, det, 2, 10, 15, 18, 29, 31
        DetAdd vec, det, 2, 10, 15, 19, 24, 35
        DetSub vec, det, 2, 10, 15, 19, 29, 30
        DetSub vec, det, 2, 10, 15, 23, 24, 31
        DetAdd vec, det, 2, 10, 15, 23, 25, 30
        DetAdd vec, det, 2, 10, 17, 18, 25, 33
        DetSub vec, det, 2, 10, 17, 18, 27, 31
        DetSub vec, det, 2, 10, 17, 19, 24, 33
        DetAdd vec, det, 2, 10, 17, 19, 27, 30
        DetAdd vec, det, 2, 10, 17, 21, 24, 31
        DetSub vec, det, 2, 10, 17, 21, 25, 30
        DetAdd vec, det, 2, 11, 12, 19, 27, 34
        DetSub vec, det, 2, 11, 12, 19, 28, 33
        DetSub vec, det, 2, 11, 12, 21, 25, 34
        DetAdd vec, det, 2, 11, 12, 21, 28, 31
        DetAdd vec, det, 2, 11, 12, 22, 25, 33
        DetSub vec, det, 2, 11, 12, 22, 27, 31
        DetSub vec, det, 2, 11, 13, 18, 27, 34
        DetAdd vec, det, 2, 11, 13, 18, 28, 33
        DetAdd vec, det, 2, 11, 13, 21, 24, 34
        DetSub vec, det, 2, 11, 13, 21, 28, 30
        DetSub vec, det, 2, 11, 13, 22, 24, 33
        DetAdd vec, det, 2, 11, 13, 22, 27, 30
        DetAdd vec, det, 2, 11, 15, 18, 25, 34
        DetSub vec, det, 2, 11, 15, 18, 28, 31
        DetSub vec, det, 2, 11, 15, 19, 24, 34
        DetAdd vec, det, 2, 11, 15, 19, 28, 30
        DetAdd vec, det, 2, 11, 15, 22, 24, 31
        DetSub vec, det, 2, 11, 15, 22, 25, 30
        DetSub vec, det, 2, 11, 16, 18, 25, 33
        DetAdd vec, det, 2, 11, 16, 18, 27, 31
        DetAdd vec, det, 2, 11, 16, 19, 24, 33
        DetSub vec, det, 2, 11, 16, 19, 27, 30
        DetSub vec, det, 2, 11, 16, 21, 24, 31
        DetAdd vec, det, 2, 11, 16, 21, 25, 30
        DetSub vec, det, 3, 6, 13, 20, 28, 35
        DetAdd vec, det, 3, 6, 13, 20, 29, 34
        DetAdd vec, det, 3, 6, 13, 22, 26, 35
        DetSub vec, det, 3, 6, 13, 22, 29, 32
        DetSub vec, det, 3, 6, 13, 23, 26, 34
        DetAdd vec, det, 3, 6, 13, 23, 28, 32
        DetAdd vec, det, 3, 6, 14, 19, 28, 35
        DetSub vec, det, 3, 6, 14, 19, 29, 34
        DetSub vec, det, 3, 6, 14, 22, 25, 35
        DetAdd vec, det, 3, 6, 14, 22, 29, 31
        DetAdd vec, det, 3, 6, 14, 23, 25, 34
        DetSub vec, det, 3, 6, 14, 23, 28, 31
        DetSub vec, det, 3, 6, 16, 19, 26, 35
        DetAdd vec, det, 3, 6, 16, 19, 29, 32
        DetAdd vec, det, 3, 6, 16, 20, 25, 35
        DetSub vec, det, 3, 6, 16, 20, 29, 31
        DetSub vec, det, 3, 6, 16, 23, 25, 32
        DetAdd vec, det, 3, 6, 16, 23, 26, 31
        DetAdd vec, det, 3, 6, 17, 19, 26, 34
        DetSub vec, det, 3, 6, 17, 19, 28, 32
        DetSub vec, det, 3, 6, 17, 20, 25, 34
        DetAdd vec, det, 3, 6, 17, 20, 28, 31
        DetAdd vec, det, 3, 6, 17, 22, 25, 32
        DetSub vec, det, 3, 6, 17, 22, 26, 31
        DetAdd vec, det, 3, 7, 12, 20, 28, 35
        DetSub vec, det, 3, 7, 12, 20, 29, 34
        DetSub vec, det, 3, 7, 12, 22, 26, 35
        DetAdd vec, det, 3, 7, 12, 22, 29, 32
        DetAdd vec, det, 3, 7, 12, 23, 26, 34
        DetSub vec, det, 3, 7, 12, 23, 28, 32
        DetSub vec, det, 3, 7, 14, 18, 28, 35
        DetAdd vec, det, 3, 7, 14, 18, 29, 34
        DetAdd vec, det, 3, 7, 14, 22, 24, 35
        DetSub vec, det, 3, 7, 14, 22, 29, 30
        DetSub vec, det, 3, 7, 14, 23, 24, 34
        DetAdd vec, det, 3, 7, 14, 23, 28, 30
        DetAdd vec, det, 3, 7, 16, 18, 26, 35
        DetSub vec, det, 3, 7, 16, 18, 29, 32
        DetSub vec, det, 3, 7, 16, 20, 24, 35
        DetAdd vec, det, 3, 7, 16, 20, 29, 30
        DetAdd vec, det, 3, 7, 16, 23, 24, 32
        DetSub vec, det, 3, 7, 16, 23, 26, 30
        DetSub vec, det, 3, 7, 17, 18, 26, 34
        DetAdd vec, det, 3, 7, 17, 18, 28, 32
        DetAdd vec, det, 3, 7, 17, 20, 24, 34
        DetSub vec, det, 3, 7, 17, 20, 28, 30
        DetSub vec, det, 3, 7, 17, 22, 24, 32
        DetAdd vec, det, 3, 7, 17, 22, 26, 30
        DetSub vec, det, 3, 8, 12, 19, 28, 35
        DetAdd vec, det, 3, 8, 12, 19, 29, 34
        DetAdd vec, det, 3, 8, 12, 22, 25, 35
        DetSub vec, det, 3, 8, 12, 22, 29, 31
        DetSub vec, det, 3, 8, 12, 23, 25, 34
        DetAdd vec, det, 3, 8, 12, 23, 28, 31
        DetAdd vec, det, 3, 8, 13, 18, 28, 35
        DetSub vec, det, 3, 8, 13, 18, 29, 34
        DetSub vec, det, 3, 8, 13, 22, 24, 35
        DetAdd vec, det, 3, 8, 13, 22, 29, 30
        DetAdd vec, det, 3, 8, 13, 23, 24, 34
        DetSub vec, det, 3, 8, 13, 23, 28, 30
        DetSub vec, det, 3, 8, 16, 18, 25, 35
        DetAdd vec, det, 3, 8, 16, 18, 29, 31
        DetAdd vec, det, 3, 8, 16, 19, 24, 35
        DetSub vec, det, 3, 8, 16, 19, 29, 30
        DetSub vec, det, 3, 8, 16, 23, 24, 31
        DetAdd vec, det, 3, 8, 16, 23, 25, 30
        DetAdd vec, det, 3, 8, 17, 18, 25, 34
        DetSub vec, det, 3, 8, 17, 18, 28, 31
        DetSub vec, det, 3, 8, 17, 19, 24, 34
        DetAdd vec, det, 3, 8, 17, 19, 28, 30
        DetAdd vec, det, 3, 8, 17, 22, 24, 31
        DetSub vec, det, 3, 8, 17, 22, 25, 30
        DetAdd vec, det, 3, 10, 12, 19, 26, 35
        DetSub vec, det, 3, 10, 12, 19, 29, 32
        DetSub vec, det, 3, 10, 12, 20, 25, 35
        DetAdd vec, det, 3, 10, 12, 20, 29, 31
        DetAdd vec, det, 3, 10, 12, 23, 25, 32
        DetSub vec, det, 3, 10, 12, 23, 26, 31
        DetSub vec, det, 3, 10, 13, 18, 26, 35
        DetAdd vec, det, 3, 10, 13, 18, 29, 32
        DetAdd vec, det, 3, 10, 13, 20, 24, 35
        DetSub vec, det, 3, 10, 13, 20, 29, 30
        DetSub vec, det, 3, 10, 13, 23, 24, 32
        DetAdd vec, det, 3, 10, 13, 23, 26, 30
        DetAdd vec, det, 3, 10, 14, 18, 25, 35
        DetSub vec, det, 3, 10, 14, 18, 29, 31
        DetSub vec, det, 3, 10, 14, 19, 24, 35
        DetAdd vec, det, 3, 10, 14, 19, 29, 30
        DetAdd vec, det, 3, 10, 14, 23, 24, 31
        DetSub vec, det, 3, 10, 14, 23, 25, 30
        DetSub vec, det, 3, 10, 17, 18, 25, 32
        DetAdd vec, det, 3, 10, 17, 18, 26, 31
        DetAdd vec, det, 3, 10, 17, 19, 24, 32
        DetSub vec, det, 3, 10, 17, 19, 26, 30
        DetSub vec, det, 3, 10, 17, 20, 24, 31
        DetAdd vec, det, 3, 10, 17, 20, 25, 30
        DetSub vec, det, 3, 11, 12, 19, 26, 34
        DetAdd vec, det, 3, 11, 12, 19, 28, 32
        DetAdd vec, det, 3, 11, 12, 20, 25, 34
        DetSub vec, det, 3, 11, 12, 20, 28, 31
        DetSub vec, det, 3, 11, 12, 22, 25, 32
        DetAdd vec, det, 3, 11, 12, 22, 26, 31
        DetAdd vec, det, 3, 11, 13, 18, 26, 34
        DetSub vec, det, 3, 11, 13, 18, 28, 32
        DetSub vec, det, 3, 11, 13, 20, 24, 34
        DetAdd vec, det, 3, 11, 13, 20, 28, 30
        DetAdd vec, det, 3, 11, 13, 22, 24, 32
        DetSub vec, det, 3, 11, 13, 22, 26, 30
        DetSub vec, det, 3, 11, 14, 18, 25, 34
        DetAdd vec, det, 3, 11, 14, 18, 28, 31
        DetAdd vec, det, 3, 11, 14, 19, 24, 34
        DetSub vec, det, 3, 11, 14, 19, 28, 30
        DetSub vec, det, 3, 11, 14, 22, 24, 31
        DetAdd vec, det, 3, 11, 14, 22, 25, 30
        DetAdd vec, det, 3, 11, 16, 18, 25, 32
        DetSub vec, det, 3, 11, 16, 18, 26, 31
        DetSub vec, det, 3, 11, 16, 19, 24, 32
        DetAdd vec, det, 3, 11, 16, 19, 26, 30
        DetAdd vec, det, 3, 11, 16, 20, 24, 31
        DetSub vec, det, 3, 11, 16, 20, 25, 30
        DetAdd vec, det, 4, 6, 13, 20, 27, 35
        DetSub vec, det, 4, 6, 13, 20, 29, 33
        DetSub vec, det, 4, 6, 13, 21, 26, 35
        DetAdd vec, det, 4, 6, 13, 21, 29, 32
        DetAdd vec, det, 4, 6, 13, 23, 26, 33
        DetSub vec, det, 4, 6, 13, 23, 27, 32
        DetSub vec, det, 4, 6, 14, 19, 27, 35
        DetAdd vec, det, 4, 6, 14, 19, 29, 33
        DetAdd vec, det, 4, 6, 14, 21, 25, 35
        DetSub vec, det, 4, 6, 14, 21, 29, 31
        DetSub vec, det, 4, 6, 14, 23, 25, 33
        DetAdd vec, det, 4, 6, 14, 23, 27, 31
        DetAdd vec, det, 4, 6, 15, 19, 26, 35
        DetSub vec, det, 4, 6, 15, 19, 29, 32
        DetSub vec, det, 4, 6, 15, 20, 25, 35
        DetAdd vec, det, 4, 6, 15, 20, 29, 31
        DetAdd vec, det, 4, 6, 15, 23, 25, 32
        DetSub vec, det, 4, 6, 15, 23, 26, 31
        DetSub vec, det, 4, 6, 17, 19, 26, 33
        DetAdd vec, det, 4, 6, 17, 19, 27, 32
        DetAdd vec, det, 4, 6, 17, 20, 25, 33
        DetSub vec, det, 4, 6, 17, 20, 27, 31
        DetSub vec, det, 4, 6, 17, 21, 25, 32
        DetAdd vec, det, 4, 6, 17, 21, 26, 31
        DetSub vec, det, 4, 7, 12, 20, 27, 35
        DetAdd vec, det, 4, 7, 12, 20, 29, 33
        DetAdd vec, det, 4, 7, 12, 21, 26, 35
        DetSub vec, det, 4, 7, 12, 21, 29, 32
        DetSub vec, det, 4, 7, 12, 23, 26, 33
        DetAdd vec, det, 4, 7, 12, 23, 27, 32
        DetAdd vec, det, 4, 7, 14, 18, 27, 35
        DetSub vec, det, 4, 7, 14, 18, 29, 33
        DetSub vec, det, 4, 7, 14, 21, 24, 35
        DetAdd vec, det, 4, 7, 14, 21, 29, 30
        DetAdd vec, det, 4, 7, 14, 23, 24, 33
        DetSub vec, det, 4, 7, 14, 23, 27, 30
        DetSub vec, det, 4, 7, 15, 18, 26, 35
        DetAdd vec, det, 4, 7, 15, 18, 29, 32
        DetAdd vec, det, 4, 7, 15, 20, 24, 35
        DetSub vec, det, 4, 7, 15, 20, 29, 30
        DetSub vec, det, 4, 7, 15, 23, 24, 32
        DetAdd vec, det, 4, 7, 15, 23, 26, 30
        DetAdd vec, det, 4, 7, 17, 18, 26, 33
        DetSub vec, det, 4, 7, 17, 18, 27, 32
        DetSub vec, det, 4, 7, 17, 20, 24, 33
        DetAdd vec, det, 4, 7, 17, 20, 27, 30
        DetAdd vec, det, 4, 7, 17, 21, 24, 32
        DetSub vec, det, 4, 7, 17, 21, 26, 30
        DetAdd vec, det, 4, 8, 12, 19, 27, 35
        DetSub vec, det, 4, 8, 12, 19, 29, 33
        DetSub vec, det, 4, 8, 12, 21, 25, 35
        DetAdd vec, det, 4, 8, 12, 21, 29, 31
        DetAdd vec, det, 4, 8, 12, 23, 25, 33
        DetSub vec, det, 4, 8, 12, 23, 27, 31
        DetSub vec, det, 4, 8, 13, 18, 27, 35
        DetAdd vec, det, 4, 8, 13, 18, 29, 33
        DetAdd vec, det, 4, 8, 13, 21, 24, 35
        DetSub vec, det, 4, 8, 13, 21, 29, 30
        DetSub vec, det, 4, 8, 13, 23, 24, 33
        DetAdd vec, det, 4, 8, 13, 23, 27, 30
        DetAdd vec, det, 4, 8, 15, 18, 25, 35
        DetSub vec, det, 4, 8, 15, 18, 29, 31
        DetSub vec, det, 4, 8, 15, 19, 24, 35
        DetAdd vec, det, 4, 8, 15, 19, 29, 30
        DetAdd vec, det, 4, 8, 15, 23, 24, 31
        DetSub vec, det, 4, 8, 15, 23, 25, 30
        DetSub vec, det, 4, 8, 17, 18, 25, 33
        DetAdd vec, det, 4, 8, 17, 18, 27, 31
        DetAdd vec, det, 4, 8, 17, 19, 24, 33
        DetSub vec, det, 4, 8, 17, 19, 27, 30
        DetSub vec, det, 4, 8, 17, 21, 24, 31
        DetAdd vec, det, 4, 8, 17, 21, 25, 30
        DetSub vec, det, 4, 9, 12, 19, 26, 35
        DetAdd vec, det, 4, 9, 12, 19, 29, 32
        DetAdd vec, det, 4, 9, 12, 20, 25, 35
        DetSub vec, det, 4, 9, 12, 20, 29, 31
        DetSub vec, det, 4, 9, 12, 23, 25, 32
        DetAdd vec, det, 4, 9, 12, 23, 26, 31
        DetAdd vec, det, 4, 9, 13, 18, 26, 35
        DetSub vec, det, 4, 9, 13, 18, 29, 32
        DetSub vec, det, 4, 9, 13, 20, 24, 35
        DetAdd vec, det, 4, 9, 13, 20, 29, 30
        DetAdd vec, det, 4, 9, 13, 23, 24, 32
        DetSub vec, det, 4, 9, 13, 23, 26, 30
        DetSub vec, det, 4, 9, 14, 18, 25, 35
        DetAdd vec, det, 4, 9, 14, 18, 29, 31
        DetAdd vec, det, 4, 9, 14, 19, 24, 35
        DetSub vec, det, 4, 9, 14, 19, 29, 30
        DetSub vec, det, 4, 9, 14, 23, 24, 31
        DetAdd vec, det, 4, 9, 14, 23, 25, 30
        DetAdd vec, det, 4, 9, 17, 18, 25, 32
        DetSub vec, det, 4, 9, 17, 18, 26, 31
        DetSub vec, det, 4, 9, 17, 19, 24, 32
        DetAdd vec, det, 4, 9, 17, 19, 26, 30
        DetAdd vec, det, 4, 9, 17, 20, 24, 31
        DetSub vec, det, 4, 9, 17, 20, 25, 30
        DetAdd vec, det, 4, 11, 12, 19, 26, 33
        DetSub vec, det, 4, 11, 12, 19, 27, 32
        DetSub vec, det, 4, 11, 12, 20, 25, 33
        DetAdd vec, det, 4, 11, 12, 20, 27, 31
        DetAdd vec, det, 4, 11, 12, 21, 25, 32
        DetSub vec, det, 4, 11, 12, 21, 26, 31
        DetSub vec, det, 4, 11, 13, 18, 26, 33
        DetAdd vec, det, 4, 11, 13, 18, 27, 32
        DetAdd vec, det, 4, 11, 13, 20, 24, 33
        DetSub vec, det, 4, 11, 13, 20, 27, 30
        DetSub vec, det, 4, 11, 13, 21, 24, 32
        DetAdd vec, det, 4, 11, 13, 21, 26, 30
        DetAdd vec, det, 4, 11, 14, 18, 25, 33
        DetSub vec, det, 4, 11, 14, 18, 27, 31
        DetSub vec, det, 4, 11, 14, 19, 24, 33
        DetAdd vec, det, 4, 11, 14, 19, 27, 30
        DetAdd vec, det, 4, 11, 14, 21, 24, 31
        DetSub vec, det, 4, 11, 14, 21, 25, 30
        DetSub vec, det, 4, 11, 15, 18, 25, 32
        DetAdd vec, det, 4, 11, 15, 18, 26, 31
        DetAdd vec, det, 4, 11, 15, 19, 24, 32
        DetSub vec, det, 4, 11, 15, 19, 26, 30
        DetSub vec, det, 4, 11, 15, 20, 24, 31
        DetAdd vec, det, 4, 11, 15, 20, 25, 30
        DetSub vec, det, 5, 6, 13, 20, 27, 34
        DetAdd vec, det, 5, 6, 13, 20, 28, 33
        DetAdd vec, det, 5, 6, 13, 21, 26, 34
        DetSub vec, det, 5, 6, 13, 21, 28, 32
        DetSub vec, det, 5, 6, 13, 22, 26, 33
        DetAdd vec, det, 5, 6, 13, 22, 27, 32
        DetAdd vec, det, 5, 6, 14, 19, 27, 34
        DetSub vec, det, 5, 6, 14, 19, 28, 33
        DetSub vec, det, 5, 6, 14, 21, 25, 34
        DetAdd vec, det, 5, 6, 14, 21, 28, 31
        DetAdd vec, det, 5, 6, 14, 22, 25, 33
        DetSub vec, det, 5, 6, 14, 22, 27, 31
        DetSub vec, det, 5, 6, 15, 19, 26, 34
        DetAdd vec, det, 5, 6, 15, 19, 28, 32
        DetAdd vec, det, 5, 6, 15, 20, 25, 34
        DetSub vec, det, 5, 6, 15, 20, 28, 31
        DetSub vec, det, 5, 6, 15, 22, 25, 32
        DetAdd vec, det, 5, 6, 15, 22, 26, 31
        DetAdd vec, det, 5, 6, 16, 19, 26, 33
        DetSub vec, det, 5, 6, 16, 19, 27, 32
        DetSub vec, det, 5, 6, 16, 20, 25, 33
        DetAdd vec, det, 5, 6, 16, 20, 27, 31
        DetAdd vec, det, 5, 6, 16, 21, 25, 32
        DetSub vec, det, 5, 6, 16, 21, 26, 31
        DetAdd vec, det, 5, 7, 12, 20, 27, 34
        DetSub vec, det, 5, 7, 12, 20, 28, 33
        DetSub vec, det, 5, 7, 12, 21, 26, 34
        DetAdd vec, det, 5, 7, 12, 21, 28, 32
        DetAdd vec, det, 5, 7, 12, 22, 26, 33
        DetSub vec, det, 5, 7, 12, 22, 27, 32
        DetSub vec, det, 5, 7, 14, 18, 27, 34
        DetAdd vec, det, 5, 7, 14, 18, 28, 33
        DetAdd vec, det, 5, 7, 14, 21, 24, 34
        DetSub vec, det, 5, 7, 14, 21, 28, 30
        DetSub vec, det, 5, 7, 14, 22, 24, 33
        DetAdd vec, det, 5, 7, 14, 22, 27, 30
        DetAdd vec, det, 5, 7, 15, 18, 26, 34
        DetSub vec, det, 5, 7, 15, 18, 28, 32
        DetSub vec, det, 5, 7, 15, 20, 24, 34
        DetAdd vec, det, 5, 7, 15, 20, 28, 30
        DetAdd vec, det, 5, 7, 15, 22, 24, 32
        DetSub vec, det, 5, 7, 15, 22, 26, 30
        DetSub vec, det, 5, 7, 16, 18, 26, 33
        DetAdd vec, det, 5, 7, 16, 18, 27, 32
        DetAdd vec, det, 5, 7, 16, 20, 24, 33
        DetSub vec, det, 5, 7, 16, 20, 27, 30
        DetSub vec, det, 5, 7, 16, 21, 24, 32
        DetAdd vec, det, 5, 7, 16, 21, 26, 30
        DetSub vec, det, 5, 8, 12, 19, 27, 34
        DetAdd vec, det, 5, 8, 12, 19, 28, 33
        DetAdd vec, det, 5, 8, 12, 21, 25, 34
        DetSub vec, det, 5, 8, 12, 21, 28, 31
        DetSub vec, det, 5, 8, 12, 22, 25, 33
        DetAdd vec, det, 5, 8, 12, 22, 27, 31
        DetAdd vec, det, 5, 8, 13, 18, 27, 34
        DetSub vec, det, 5, 8, 13, 18, 28, 33
        DetSub vec, det, 5, 8, 13, 21, 24, 34
        DetAdd vec, det, 5, 8, 13, 21, 28, 30
        DetAdd vec, det, 5, 8, 13, 22, 24, 33
        DetSub vec, det, 5, 8, 13, 22, 27, 30
        DetSub vec, det, 5, 8, 15, 18, 25, 34
        DetAdd vec, det, 5, 8, 15, 18, 28, 31
        DetAdd vec, det, 5, 8, 15, 19, 24, 34
        DetSub vec, det, 5, 8, 15, 19, 28, 30
        DetSub vec, det, 5, 8, 15, 22, 24, 31
        DetAdd vec, det, 5, 8, 15, 22, 25, 30
        DetAdd vec, det, 5, 8, 16, 18, 25, 33
        DetSub vec, det, 5, 8, 16, 18, 27, 31
        DetSub vec, det, 5, 8, 16, 19, 24, 33
        DetAdd vec, det, 5, 8, 16, 19, 27, 30
        DetAdd vec, det, 5, 8, 16, 21, 24, 31
        DetSub vec, det, 5, 8, 16, 21, 25, 30
        DetAdd vec, det, 5, 9, 12, 19, 26, 34
        DetSub vec, det, 5, 9, 12, 19, 28, 32
        DetSub vec, det, 5, 9, 12, 20, 25, 34
        DetAdd vec, det, 5, 9, 12, 20, 28, 31
        DetAdd vec, det, 5, 9, 12, 22, 25, 32
        DetSub vec, det, 5, 9, 12, 22, 26, 31
        DetSub vec, det, 5, 9, 13, 18, 26, 34
        DetAdd vec, det, 5, 9, 13, 18, 28, 32
        DetAdd vec, det, 5, 9, 13, 20, 24, 34
        DetSub vec, det, 5, 9, 13, 20, 28, 30
        DetSub vec, det, 5, 9, 13, 22, 24, 32
        DetAdd vec, det, 5, 9, 13, 22, 26, 30
        DetAdd vec, det, 5, 9, 14, 18, 25, 34
        DetSub vec, det, 5, 9, 14, 18, 28, 31
        DetSub vec, det, 5, 9, 14, 19, 24, 34
        DetAdd vec, det, 5, 9, 14, 19, 28, 30
        DetAdd vec, det, 5, 9, 14, 22, 24, 31
        DetSub vec, det, 5, 9, 14, 22, 25, 30
        DetSub vec, det, 5, 9, 16, 18, 25, 32
        DetAdd vec, det, 5, 9, 16, 18, 26, 31
        DetAdd vec, det, 5, 9, 16, 19, 24, 32
        DetSub vec, det, 5, 9, 16, 19, 26, 30
        DetSub vec, det, 5, 9, 16, 20, 24, 31
        DetAdd vec, det, 5, 9, 16, 20, 25, 30
        DetSub vec, det, 5, 10, 12, 19, 26, 33
        DetAdd vec, det, 5, 10, 12, 19, 27, 32
        DetAdd vec, det, 5, 10, 12, 20, 25, 33
        DetSub vec, det, 5, 10, 12, 20, 27, 31
        DetSub vec, det, 5, 10, 12, 21, 25, 32
        DetAdd vec, det, 5, 10, 12, 21, 26, 31
        DetAdd vec, det, 5, 10, 13, 18, 26, 33
        DetSub vec, det, 5, 10, 13, 18, 27, 32
        DetSub vec, det, 5, 10, 13, 20, 24, 33
        DetAdd vec, det, 5, 10, 13, 20, 27, 30
        DetAdd vec, det, 5, 10, 13, 21, 24, 32
        DetSub vec, det, 5, 10, 13, 21, 26, 30
        DetSub vec, det, 5, 10, 14, 18, 25, 33
        DetAdd vec, det, 5, 10, 14, 18, 27, 31
        DetAdd vec, det, 5, 10, 14, 19, 24, 33
        DetSub vec, det, 5, 10, 14, 19, 27, 30
        DetSub vec, det, 5, 10, 14, 21, 24, 31
        DetAdd vec, det, 5, 10, 14, 21, 25, 30
        DetAdd vec, det, 5, 10, 15, 18, 25, 32
        DetSub vec, det, 5, 10, 15, 18, 26, 31
        DetSub vec, det, 5, 10, 15, 19, 24, 32
        DetAdd vec, det, 5, 10, 15, 19, 26, 30
        DetAdd vec, det, 5, 10, 15, 20, 24, 31
        DetSub vec, det, 5, 10, 15, 20, 25, 30
}
