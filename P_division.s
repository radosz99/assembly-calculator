.section .bss
.equ BYTES, 1024
.equ BYTES_2, 2048
.equ LENGTH, 4
.equ BYTE, 1
.lcomm number_1, BYTES
.lcomm number_2, BYTES
.lcomm base, LENGTH
.lcomm operation, LENGTH
.lcomm answer_1, LENGTH

.lcomm lengthNumber_1, LENGTH
.lcomm lengthNumber_2, LENGTH
.lcomm lengthNumber1, LENGTH
.lcomm lengthNumber2, LENGTH
.lcomm lengthNumber, LENGTH
.lcomm result, BYTES_2
.lcomm carry, BYTE

.section .data
    size: .long 0
    sizeCounter: .long 0
    sizeFinalResult: .long 128
    lengthResult: .long 0

.section .text
.global P_division
.type P_division, @function
P_division:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx

askBase:
    movl 8(%ebp), %ecx
    movl %ecx, base

	xorl %ebx, %ebx		# zerowanie %ebx
	movb base, %bl
	cmpb $0x62, %bl
	je binary
	cmpb $0x64, %bl		
	je decimal
	cmpb $'x', %bl		
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
    movl %edi, lengthNumber1
   
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
    movl %edi, lengthNumber2
    xorl %eax, %eax

prepareFinalResult:
    movl $'0', result(,%eax,1)
    incl %eax
    cmpl %eax, sizeFinalResult
    jg prepareFinalResult
#	movb $0xA, result(,%eax,1) # lf
#	incl %eax
#	movb $0xD, result(,%eax,1) # cr

operationBegin:
    xorl %eax, %eax
    movl lengthNumber1, %eax
    movl %eax, lengthNumber_1
    xorl %eax, %eax
    movl lengthNumber2, %eax
    movl %eax, lengthNumber_2
    cmpl lengthNumber1, %eax
    jg end
    cmpl lengthNumber1, %eax
    jl designateLoopLenght

checkIfHigher:
    xorl %eax, %eax
    xorl %ebx, %ebx
    xorl %ecx, %ecx
    movl $0, %edx
    movl lengthNumber2, %ecx

checkIfHigherBegin:
    cmpl %edx, %ecx
    jge checkIfHigherBegin2
    jmp designateLoopLenght

checkIfHigherBegin2:
    xorl %ebx, %ebx
    movb number_1(,%edx,1), %bl
    pushl $base
	pushl %ebx
	call charToInt
	addl $8, %esp
    
    movb number_2(,%edx,1), %bl
    pushl %eax
    pushl $base
	pushl %ebx
	call charToInt
	addl $8, %esp
	
	movl %eax, %ebx	# w ebx mamy teraz cyfre z drugiej liczby
	popl %eax		# przywracamy cyfre z pierwszej liczby

    incl %edx
    cmpl %eax, %ebx
    je checkIfHigherBegin
    cmpl %eax, %ebx
    jg end

designateLoopLenght:
	movb $0, carry	# zerujemy ewentualne przeniesienie
	movl lengthNumber_1, %edi	
	movl %edi, lengthNumber # dlugosc wyniku
    movl %edi, size

calculatorBegin:
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
	jge subtractor
	cmpl $0, lengthNumber_2
	jge subtractor
	cmpl $0, %eax   # dlugosc zostanie najpierw wyzerowana ale wartosci jeszcze beda
	jne subtractor
	cmpl $0, %ebx
	jne subtractor
	cmpl $1, carry
	je subtractor
	jmp calculatorEnd

subtractor:
	subl %ebx, %eax	# odejmujemy wartosci rejestrow
	subl carry, %eax # odejmujemy ewentualna pozyczke
	movb $0, carry 
	cmpl $0, %eax
	jge savingResult
	
	addl base, %eax # jezeli wynik jest mniejszy od 0 to dodajemy podstawe...
	movb $1, carry # ... i aktywujemy pozyczke

savingResult:
	pushl %eax
	call intToChar
	addl $4, %esp
    
    xorl %edx, %edx
    incl lengthNumber_1
    movl lengthNumber_1, %edx
    movb $0, number_1(,%edx,1)
	movb %al, number_1(,%edx,1) #zapisujemy wynik do result
	decl %edi # i dekrementujemy nasz rejestr przechodzacy po result
    decl lengthNumber_1
	jmp calculatorBegin

calculatorEnd:    
    call findInitialZeros
    xorl %eax, %eax
    movl $0, carry
    xorl %edx, %edx

countResult:
    movl sizeFinalResult, %edx
    subl $1, %edx

countResultBegin:
    xorl %ebx, %ebx
    movb result(,%edx,1), %bl
    pushl $base
	pushl %ebx
	call charToInt
	addl $8, %esp

    xorl %ebx, %ebx
    cmpl %ebx, carry
    jg countResultBegin1
    addb $1, %al

countResultBegin1:
    addb carry, %al
    movb $0, carry

    cmpl base, %eax
    jge countResult1
    jmp countResultEnd

countResult1:
    subb base, %al
    pushl %eax
	call intToChar
	addl $4, %esp

    movb %al,result(,%edx,1)
    movl $1, carry
    decl %edx
    jmp countResultBegin
    
countResultEnd:
    pushl %eax
	call intToChar
	addl $4, %esp
    movb %al,result(,%edx,1)
    jmp operationBegin

end:   
    call findInitialZeros1
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
    movb number_1(,%edx,1), %al
    incl %edx
    cmpl $0, lengthNumber1
    je findInitialZerosEnd
    cmpl $'0', %eax
    je shorterLength
    jmp findInitialZerosEnd
    
shorterLength:
    decl lengthNumber1

deleteInitialZeros:
    xorl %eax, %eax
    movb number_1(,%edx,1), %al
    decl %edx
    movb %al, number_1(,%edx,1)
    addl $2, %edx
    cmpl sizeCounter, %edx
    jle deleteInitialZeros

deleteRedundand:
    decl %edx
    movl $0, number_1(,%edx,1)
    jmp findInitialZerosBegin

findInitialZerosEnd:
    #movl %ebp, %esp
	#popl %ebp
	ret


.type findInitialZeros1,@function
findInitialZeros1:
    xorl %edx, %edx
    xorl %eax, %eax
    xorl %ecx, %ecx
    movl sizeFinalResult, %eax
    movl %eax, lengthResult
    movl %eax, sizeCounter
    addl $3, sizeCounter
    xorl %eax, %eax

findInitialZerosBegin1:
    movl $0, %edx #indeksowanie od zera, w mnozeniu od 1
    decl sizeCounter
    movb result(,%edx,1), %al
    incl %edx
    cmpl $0, lengthResult
    je findInitialZerosEnd1
    cmpl $'0', %eax
    je shorterLength1
    jmp findInitialZerosEnd1
    
shorterLength1:
    decl lengthResult

deleteInitialZeros1:
    xorl %eax, %eax
    movb result(,%edx,1), %al
    decl %edx
    movb %al, result(,%edx,1)
    addl $2, %edx
    cmpl sizeCounter, %edx
    jle deleteInitialZeros1

deleteRedundand1:
    decl %edx
    movl $0, result(,%edx,1)
    jmp findInitialZerosBegin1

findInitialZerosEnd1:
    #movl %ebp, %esp
	#popl %ebp
	ret

