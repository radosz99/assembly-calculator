.bss
.lcomm base, 4
.lcomm number, 1024

.text
.global convertNumber
# ------------------------------------------------------
# convertNumber(char from, const char * number, char to)
# ------------------------------------------------------
.type convertNumber, @function
convertNumber:
pushl %ebp
movl %esp, %ebp
pushl %ebx

pushl 8(%ebp)
call getBase
addl $4, %esp

cmpl $0, %eax
je convertEnd

pushl %eax
pushl 12(%ebp)
call str2Int
addl $8, %esp

pushl %eax      # odlozenie liczby na stos
pushl 16(%ebp)
call getBase
addl $4, %esp

cmpl $0, %eax
je convertEnd

movl %eax, %ebx # nowa baza do ebx
popl %eax       # przywrocenie liczby ze stosu

pushl $number
pushl %ebx
pushl %eax
call int2Str
addl $12, %esp

movl $number, %eax

convertEnd:
popl %ebx
movl %ebp, %esp
popl %ebp
ret

.type int2Str, @function
int2Str:
push %ebp
movl %esp, %ebp

subl $4, %esp
movl 12(%ebp), %ebx

# eax - wynik dzielenia
# ecx - liczba cyfr
# edx - reszta z dzielenia
movl 8(%ebp), %eax
movl $0, %ecx
convertLoop1:
cmpl $0, %eax
je convertLoop1End

incl %ecx
xorl %edx, %edx
idivl %ebx
pushl %edx
jmp convertLoop1

convertLoop1End:
movl %ecx, -4(%ebp) # liczba cyfr do zmiennej lokalnej

# eax - aktualna wartosc
# ecx - liczba cyfr
# edx - adres aktualnego znaku

movl 16(%ebp), %edx # adres bufora do edx

convertLoop2:
cmpl $0, %ecx
je convertLoop3End

popl %eax
cmpl $9, %eax   # jesli cyfra jest z przedzialu 0-9
jg convertLoop2Hex

addl $'0', %eax
jmp convertLoop3

convertLoop2Hex:
addl $87, %eax  # otrzymanie liter a-f

convertLoop3:
movb %al, (%edx)
decl %ecx
incl %edx
jmp convertLoop2

convertLoop3End:
movl $0, (%edx)
addl $4, %esp

movl %ebp, %esp
popl %ebp
ret

.type str2Int, @function
str2Int:
pushl %ebp
movl %esp, %ebp

xorl %eax, %eax
xorl %ebx, %ebx
movl 8(%ebp), %ecx
movb (%ecx), %bl
cmpb $32, %bl
jb strFailure

strBegin:
subb $'0', %bl
cmpl 12(%ebp), %ebx
jb strTransform

strHex:
cmpl $10, 12(%ebp)
jb strFailure

orb $0x20, %bl
subb $0x27, %bl # aby a = 10, b = 11 itd.
cmpl 12(%ebp), %ebx
jge strFailure
cmpl $10, %ebx
jl strFailure

strTransform:
addl %ebx, %eax
incl %ecx
xorl %ebx, %ebx
movb (%ecx), %bl
cmpb $0x20, %bl
jle strEnd
imull 12(%ebp), %eax
jmp strBegin

strFailure:
xorl %eax, %eax

strEnd:
movl %ebp, %esp
popl %ebp
ret

.type getBase @function
getBase:
pushl %ebp
movl %esp, %ebp

movl 8(%ebp), %eax
orb $0x20, %al
cmpb $'b', %al
je ret2
# cmpb $'o', %al
# je ret8
cmpb $'d', %al
je ret10
cmpb $'x', %al
je ret16

# nie rozpoznano znaku
xorl %eax, %eax
jmp getBaseEnd

ret2:
movl $2, %eax
jmp getBaseEnd
# ret8:
# movl $8, %eax
# jmp getBaseEnd
ret10:
movl $10, %eax
jmp getBaseEnd
ret16:
movl $16, %eax

getBaseEnd:
movl %ebp, %esp
popl %ebp
ret
