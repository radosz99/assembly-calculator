.text
.global addition
.global subtraction
.global multiplication
.global division
.global exponentation
.global squareRoot
.global log
.global sin
.global cos
.global tan

# ---------------------------
# SUMOWANIE
# 8(%ebp) + 16(%ebp)
# double addition(double, double)
# ---------------------------
.type addition, @function
addition:
pushl %ebp
movl %esp, %ebp

finit
fldl 8(%ebp)
fldl 16(%ebp)
faddp

movl %ebp, %esp
popl %ebp
ret

# ---------------------------
# ODEJMOWANIE
# 8(%ebp) - 16(%ebp)
# double subtraction(double, double)
# ---------------------------
.type subtraction, @function
subtraction:
pushl %ebp
movl %esp, %ebp

finit
fldl 8(%ebp)
fldl 16(%ebp)
fsubrp

movl %ebp, %esp
popl %ebp
ret

# ---------------------------
# MNOŻENIE
# 8(%ebp) * 16(%ebp)
# double multiplication(double, double)
# ---------------------------
.type multiplication, @function
multiplication:
pushl %ebp
movl %esp, %ebp

finit
fldl 8(%ebp)
fldl 16(%ebp)
fmulp

movl %ebp, %esp
popl %ebp
ret

# ---------------------------
# DZIELENIE
# 8(%ebp) / 16(%ebp)
# double division(double, double)
# ---------------------------
.type division, @function
division:
pushl %ebp
movl %esp, %ebp

finit
fldl 8(%ebp)
fldl 16(%ebp)
fdivrp

movl %ebp, %esp
popl %ebp
ret

# ---------------------------
# POTĘGOWANIE
# 8(%ebp) ^ 16(%ebp)
# double exponentation(double, int)
# ---------------------------
.type exponentation, @function
exponentation:
pushl %ebp
movl %esp, %ebp

finit
fld1

cmpl $0, 16(%ebp)
jg expLoop
je expEnd

# wykładnik mniejszy od zera
# obliczenie odwrotności
fldl 8(%ebp)
fdivrp
fstpl 8(%ebp)
fld1

movl 16(%ebp), %eax
imull $-1, %eax
movl %eax, 16(%ebp)

expLoop:
fldl 8(%ebp)
fmulp
decl 16(%ebp)
cmpl $0, 16(%ebp)
jne expLoop

expEnd:
movl %ebp, %esp
popl %ebp
ret

# ---------------------------
# PIERWIASTEK KWADRATOWY
# sqrt(8(%ebp))
# double squareRoot(double)
# ---------------------------
.type squareRoot, @function
squareRoot:
pushl %ebp
movl %esp, %ebp

finit
fldl 8(%ebp)
fsqrt

movl %ebp, %esp
popl %ebp
ret

# ---------------------------
# LOGARYTM NATURALNY
# log(8(%ebp))
# double log(double)
# ---------------------------
.type log, @function
log:
pushl %ebp
movl %esp, %ebp

finit
fld1
fldl 8(%ebp)
fyl2x
fldl2e
fdivrp

movl %ebp, %esp
popl %ebp
ret

# ---------------------------
# SINUS
# sin(8(%ebp))
# double sin(double)
# ---------------------------
.type sin, @function
sin:
pushl %ebp
movl %esp, %ebp

finit
fldl 8(%ebp)
fsin

movl %ebp, %esp
popl %ebp
ret

# ---------------------------
# COSINUS
# cos(8(%ebp))
# double cos(double)
# ---------------------------
.type cos, @function
cos:
pushl %ebp
movl %esp, %ebp

finit
fldl 8(%ebp)
fcos

movl %ebp, %esp
popl %ebp
ret

# ---------------------------
# TANGENS
# cos(8(%ebp))
# double cos(double)
# ---------------------------
.type tan, @function
tan:
pushl %ebp
movl %esp, %ebp

finit
fldl 8(%ebp)
fcos
fldl 8(%ebp)
fsin
fdivp

movl %ebp, %esp
popl %ebp
ret
