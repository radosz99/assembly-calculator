.section .bss
.equ BYTES, 1024
.equ BYTES_2, 2048
.equ LENGTH, 4
.equ BYTE, 1
.lcomm number_1, BYTES
.lcomm number_2, BYTES
.lcomm licznik, BYTES
.lcomm base, LENGTH
.lcomm operation, LENGTH
.lcomm answer_1, LENGTH
.lcomm firstNumberCurrentValue, LENGTH

.lcomm lengthNumber1, LENGTH
.lcomm lengthNumber2, LENGTH
.lcomm lengthNumber2_2, LENGTH
.lcomm result, BYTES_2
.lcomm finalResult, BYTES_2
.lcomm carry, BYTE
.lcomm finalCarry, BYTE

.section .data
    size: .long 256
    elasticSize: .long 0
    sizeCounter: .long 0

.section .text
.global P_multiplication
.type P_multiplication, @function
P_multiplication:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx

    movl size, %eax
    movl %eax, elasticSize
    xorl %eax, %eax

setFinalResult:
    movl size, %edi
	decl %edi

resetFinalResult:
    movb $0, finalResult(,%edi,1)
    decl %edi
    cmpl $0, %edi
    jge resetFinalResult	

askBase:
    movl 8(%ebp), %ecx
    movl %ecx, base

	orl %ebx, %ebx		# zerowanie %ebx
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

    xorl %edx, %edx
    movl lengthNumber2, %edx
    movl %edx, lengthNumber2_2
    xorl %edx, %edx

prepareResult: 
    cmpl $0, lengthNumber1
    jl outcome3
    xorl %edi, %edi
    movl size, %edi

resetResult: 
    movb $0, result(,%edi,1)
    decl %edi
    cmpl $0, %edi
    je afterResetResult
    jmp resetResult

afterResetResult:
    movl size, %edi
	xorl %ecx, %ecx 	
	movb $0xA, result(,%edi,1) # lf
	incl %edi
	movb $0xD, result(,%edi,1) # cr
	decl %edi	
	decl %edi # wpisywanie bedziemy zaczynac od 3 pozycji od konca
    movl size, %ecx
    subl elasticSize, %ecx
    decl elasticSize

loop:
    cmpl $0, %ecx
    je calculatorBegin
    movb $0, result(,%edi,1)
    decl %edi
    decl %ecx
    jmp loop
    
calculatorBegin:
    xorl %ecx, %ecx
    xorl %edx, %edx
 

    movl $0, firstNumberCurrentValue
	movl lengthNumber1, %edx	# pobierz dlugosc pierwszej liczby do rejestru
	cmpl $0, %edx
	jl firstNumberEnd
	xorl %ebx, %ebx	# wyzeruj ebx
	decl lengthNumber1		# dekrementacja dlugosci liczby by wczytac kolejna cyfre w nowej petli
	movb number_1(,%edx,1), %bl # pobieranie znaku do ebx


	pushl $base
	pushl %ebx
	call charToInt
	addl $8, %esp    
    movl %eax, firstNumberCurrentValue
	jmp calculatorCont

firstNumberEnd:
	xorl %eax, %eax	# przejscie po calej pierwszej liczbie
    movl %eax, firstNumberCurrentValue
    
calculatorCont:
    movl lengthNumber2_2, %edx
    movl %edx, lengthNumber2  
  
calculatorContinue:
	xorl %eax, %eax	
	movl lengthNumber2, %edx	# pobierz dlugosc drugiej liczby do rejestru
	cmpl $0, %edx	
	jl secondNumberEnd	
	decl lengthNumber2		
	movb number_2(,%edx,1), %bl # pobieranie znaku do ebx

	pushl $base
	pushl %ebx
	call charToInt
	addl $8, %esp
    jmp multiBegin

secondNumberEnd:
	cmpl $0, lengthNumber1
	jge multiBegin
	cmpl $0, lengthNumber2
	jge multiBegin
	cmpl $0, carry
	jg multiBegin
	jmp outcome

multiBegin:
    xorl %ecx, %ecx
	imull firstNumberCurrentValue, %eax	
	addl carry, %eax # dodajemy ewentualne przeniesienie
	movb $0, carry # zerujemy przeniesienie

compare:
	cmpl base, %eax	
	jb savingResult
	subl base, %eax #jezeli wynik jest wiekszy od podstawy to odejmujemy podstawe...
	incl %ecx
	jmp compare

savingResult:
    movl %ecx, carry

	#pushl %eax
	#call intToChar
	#addl $4, %esp

	movb %al, result(,%edi,1) #zapisujemy wynik do result
	decl %edi # i dekrementujemy nasz rejestr przechodzacy po result
    
    xorl %ecx, %ecx
    movl lengthNumber2, %ecx
    addl $1, %ecx
    cmpl $0, %ecx 
	jg calculatorContinue   # jesli lengthNumber > -1 to kontynuujemy mnozenie przez druga liczbe

    xorl %ecx, %ecx
    movl carry, %ecx
    cmpl $0, %ecx   
    jne calculatorContinue  # jesli mamy jeszcze przeniesienie to lecimy dalej

outcome:
    decl %edi
    cmpl $0, %edi
    jl outcome2
    movb $0, result(,%edi,1) #zapisujemy wynik do result
    jmp outcome

outcome2:
    call addToFinalResult  
    jmp prepareResult

outcome3:
    call findInitialZeros

    movl $finalResult, %eax
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

.type addToFinalResult,@function
addToFinalResult:
	pushl %ebp
	movl %esp, %ebp
    xorl %edx, %edx
    movl size, %edx
    decl %edx

addToFinalResult1:
    xorl %ebx, %ebx
    movb result(,%edx,1), %bl # pobieranie znaku do ebx
    movb finalResult(,%edx,1), %al
    addl %ebx, %eax
    addl finalCarry, %eax
    movl $0, finalCarry
    cmpl base, %eax
    jl addToFinalResult2

    xorl %ecx, %ecx
    subl base, %eax
    incl %ecx
    movl %ecx, finalCarry
    
addToFinalResult2:
    cmpl $0, lengthNumber1
    jl addToFinalResult3

addToFinalResult2_5:
    movb %al, finalResult(,%edx,1)
    decl %edx
    cmpl $0, %edx
    jge addToFinalResult1
    jmp addToFinalResultEnd

addToFinalResult3:
    pushl %eax
    call intToChar
    addl $4, %esp
    movb %al, finalResult(,%edx,1)
    decl %edx
    cmpl $0, %edx
    jge addToFinalResult1

addToFinalResultEnd:
    movl %ebp, %esp
	popl %ebp
	ret

.type findInitialZeros,@function
findInitialZeros:
    xorl %eax, %eax
    xorl %ecx, %ecx
    movl size, %eax
    movl %eax, sizeCounter
    xorl %eax, %eax

findInitialZerosBegin:
    xorl %edx, %edx
    decl sizeCounter
    movb finalResult(,%edx,1), %al
    incl %edx
    cmpl $'0', %eax
    je deleteInitialZeros
    jmp findInitialZerosEnd
    
deleteInitialZeros:
    xorl %eax, %eax
    movb finalResult(,%edx,1), %al
    decl %edx
    movb %al, finalResult(,%edx,1)
    addl $2, %edx
    cmpl sizeCounter, %edx
    jle deleteInitialZeros

deleteRedundand:
    decl %edx
    movl $0, finalResult(,%edx,1)
    jmp findInitialZerosBegin

findInitialZerosEnd:
	ret
    