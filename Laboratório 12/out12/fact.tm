; This program reads an integer and output its factorial.

IN   r1          ; r1 <- read from stdin
JON  r1, 6       ; Jump 6 instructions ahead if r1 < 0
LDC  r2, 1       ; r2 <- 1
LDC  r3, 1       ; r3 <- 1
MUL  r2, r2, r1  ; r2 <- r2 * r1
SUB  r1, r1, r3  ; r1 <- r1 - r3
JNZ  r1, -3      ; Jump 3 instructions back if r1 != 0
OUT  r2          ; r2 -> stdout
HALT

