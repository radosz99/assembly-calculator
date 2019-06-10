.section .bss
.equ BYTES, 1024
.equ BYTES_2, 2048
.equ LENGTH, 4
.equ BYTE, 1
.lcomm number_1, BYTES
.lcomm number_2, BYTES
.lcomm base, LENGTH
.lcomm answer_1, LENGTH

.lcomm lengthNumber_1, LENGTH
.lcomm lengthNumber_2, LENGTH
.lcomm lengthNumber, LENGTH
.lcomm result, BYTES_2
.lcomm carry, BYTE

.data
    size: .long 0
    sizeCounter: .long 0

.text
.globl P_addition
.type P_addition, @function
P_addition:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx

    movl 8(%ebp), %ecx
    movl %ecx, base

    xorl %ebx, %ebx		# zerowanie %ecx
    movb base, %bl
    cmpb $0x62, %bl
    je binary
    cmpb $0x64, %bl
    je decimal
    cmpb $0x68, %bl
    je hexadecimal

binary:
    movl $2, %eax
    movl %eax, base
    jmp askFirstNumber

decimal:
    movl $10, %eax
    movl %eax, base
    jmp askFirstNumber

hexadecimal:
    movl $0x10, %eax
    movl %eax, base

askFirstNumber:
    movl 12(%ebp), %ecx
    movl $0, %edi

movNumber1:
    movb (%ecx, %edi, 1), %dl
    movb %dl, number_1(,%edi,1)
    incl %edi
    cmpb $0, %dl
    je mov1End
    jmp movNumber1

mov1End:
    subl $3, %edi
    movl %edi, lengthNumber_1

askSecondNumber:
    movl 16(%ebp), %ecx
    movl $0, %edi

movNumber2:
    movb (%ecx, %edi, 1), %dl
    movb %dl, number_2(,%edi,1)
    incl %edi
    cmpb $0, %dl
    je mov2End
    jmp movNumber2

mov2End:
    subl $3, %edi
    movl %edi, lengthNumber_2
    movl lengthNumber_2, %eax

designateLoopLenght:
        movb $0, carry	# zerujemy ewentualne przeniesienie
        movl lengthNumber_1, %edi
        cmpl lengthNumber_2, %edi
        jg calculatorBeginStart
        movl lengthNumber_2, %edi # wyznaczona ilosc petli
        movl %edi, lengthNumber # dlugosc wyniku
        movl %edi, size
        incl %edi	# jesli dodawanie to nalezy powiekszyc o 1, gdyz z n+x (gdzie x<n) moze powstac n+1

calculatorBeginStart:
        incl %edi

calculatorBegin:
        xorl %edx, %edx
        movl lengthNumber_1, %edx	# pobierz dlugosc pierwszej liczby do rejestru
        cmpl $0, %edx
        jl firstNumberEnd
        xorl %ebx, %ebx	# wyzeruj ebx
        decl lengthNumber_1		# dekrementacja dlugosci liczby by wczytac kolejna cyfre w nowej petli
        movb number_1(,%edx,1), %bl # pobieranie znaku do ebx

        pushl $base
        pushl %ebx
        call charToInt
        addl $8, %esp
        cmpb base, %al # niepoprawne wartosci
        jge askFirstNumber # powrot do pytan o liczby

        jmp calculatorContinue

firstNumberEnd:
        xorl %eax, %eax	# przejscie po calej pierwszej liczbie

calculatorContinue:
        xorl %ebx, %ebx
        movl lengthNumber_2, %edx	# pobierz dlugosc drugiej liczby do rejestru
        cmpl $0, %edx
        jl secondNumberEnd
        decl lengthNumber_2
        movb number_2(,%edx,1), %bl # pobieranie znaku do ebx

        pushl %eax		# cyfre z pierwszej liczby wrzucamy na stos

        pushl $base
        pushl %ebx
        call charToInt
        addl $8, %esp
        cmpb base, %al
        jge askFirstNumber

        movl %eax, %ebx	# w ebx mamy teraz cyfre z drugiej liczby
        popl %eax		# przywracamy cyfre z pierwszej liczby

secondNumberEnd:
        cmpl $0, lengthNumber_1
        jge adderBegin
        cmpl $0, lengthNumber_2
        jge adderBegin
        cmpl $0, %eax   # dlugosc zostanie najpierw wyzerowana ale wartosci jeszcze beda
        jne adderBegin
        cmpl $0, %ebx
        jne adderBegin
        cmpl $1, carry
        je adderBegin
        jmp calculatorEnd

adderBegin:
        addl %ebx, %eax	# dodajemy wartosci rejestrow
        addl carry, %eax # dodajemy ewentualne przeniesienie
        movb $0, carry # zerujemy przeniesienie
        cmpl base, %eax	#
        jb savingResult

        subl base, %eax #jezeli wynik jest wiekszy od podstawy to odejmujemy podstawe...
        movb $1, carry # ... i aktywujemy przeniesienie
        jmp savingResult

savingResult:
        pushl %eax
        call intToChar
        addl $4, %esp

        movb %al, result(,%edi,1) #zapisujemy wynik do result
        decl %edi # i dekrementujemy nasz rejestr przechodzacy po result

        jmp calculatorBegin

calculatorEnd:
        xorl %edi, %edi
        xorl %eax, %eax
        movb result(,%edi,1), %al
        cmpl $'1', %eax
        je calculatorEnd1
        movb $'0', result(,%edi,1)

    call findInitialZeros

calculatorEnd1:
    movl $result, %eax
    popl %ebx
    movl %ebp, %esp
    popl %ebp
    ret

.type charToInt,@function
charToInt:
        pushl %ebp
        movl %esp, %ebp

        xorl %ebx, %ebx		# zeruj ebx
        movl 8(%ebp), %ebx  # wrzucamy znak do ebx
        subb $0x30, %bl		# odejmij wartosc znaku '0' od znaku, zostaje cyfra
        cmpb $10, %bl		# jezeli cyfra mniejsza od 10, przejdz na koniec
        jb charToIntEnd

        subb $0x7, %bl      # mogla zostac podana duza litera, np A
        cmpb $0x10, %bl	    # jesli mniejsza to przeskakujemy dalej
        jb charToIntEnd

        subb $0x20, %bl     # podana zostala mala litera, np a

charToIntEnd:
        movl %ebx, %eax		# powiodla sie konwersja, przepisz ebx do eax
        movl %ebp, %esp
        popl %ebp
        ret

.type intToChar,@function
intToChar:
        pushl %ebp
        movl %esp, %ebp

        movl 8(%ebp), %eax
        addb $0x30, %al
        cmpb $0x39, %al	# wartosc mniejsza lub rowna '9'
        jbe intToCharEnd

        addb $7, %al # dla heksadecymalnego

intToCharEnd:
        movl %ebp, %esp
        popl %ebp
        ret

.type findInitialZeros,@function
findInitialZeros:
    xorl %edx, %edx
    xorl %eax, %eax
    xorl %ecx, %ecx
    movl size, %eax
    movl %eax, sizeCounter
    addl $3, sizeCounter
    xorl %eax, %eax

findInitialZerosBegin:
    movl $0, %edx #indeksowanie od zera, w mnozeniu od 1
    decl sizeCounter
    movb result(,%edx,1), %al
    incl %edx
    cmpl $'0', %eax
    je deleteInitialZeros
    jmp findInitialZerosEnd

deleteInitialZeros:
    xorl %eax, %eax
    movb result(,%edx,1), %al
    decl %edx
    movb %al, result(,%edx,1)
    addl $2, %edx
    cmpl sizeCounter, %edx
    jle deleteInitialZeros

deleteRedundand:
    decl %edx
    movl $0, result(,%edx,1)
    jmp findInitialZerosBegin

findInitialZerosEnd:
    #movl %ebp, %esp
        #popl %ebp
        ret
        