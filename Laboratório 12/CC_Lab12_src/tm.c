
// The Tiny Machine (TM) Simulator

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"

// ----------------------------------------------------------------------------
// Macros ---------------------------------------------------------------------

#define IADDR_SIZE  1024 /* increase for large programs */
#define DADDR_SIZE  1024 /* increase for large programs */
#define NO_REGS 64
#define PC 0

#define LINE_SIZE 80

// ----------------------------------------------------------------------------
// Structures -----------------------------------------------------------------

typedef enum {
    OKAY,
    HALTED,
    IMEM_ERR,
    DMEM_ERR,
    DIV_ZERO
} StepResult;

typedef struct {
    OpCode op;
    int i1;
    int i2;
    int i3;
} Instruction;

// ----------------------------------------------------------------------------
// Memory ---------------------------------------------------------------------

Instruction iMem[IADDR_SIZE];
int dMem[DADDR_SIZE];
int reg[NO_REGS];

// ----------------------------------------------------------------------------
// Init -----------------------------------------------------------------------

void init() {
    // Clear Instruction Memory
    for (int iAddr = 0; iAddr < IADDR_SIZE; iAddr++) {
        iMem[iAddr].op = HALT;
        iMem[iAddr].i1 = 0;
        iMem[iAddr].i2 = 0;
        iMem[iAddr].i3 = 0;
    }
    // Clear Data Memory
    for (int dAddr = 0; dAddr < DADDR_SIZE; dAddr++) {
        dMem[dAddr] = 0;
    }
    // Clear Registers
    for (int r = 0; r < NO_REGS; r++) {
        reg[r] = 0;
    }
}

// ----------------------------------------------------------------------------
// Read -----------------------------------------------------------------------

bool read_line(char *line) {
    return !fgets(line, LINE_SIZE, stdin);
}

bool is_empty(char *line) {
    return line[0] == ';' || line[0] == ' ' || line[0] == '\n';
}

#define OP_ERR "Undefined operation in ASM line above!"
#define ARG_ERR "Wrong number of operands or invalid syntax!"

void parse_error(char *line, char *msg) {
    fprintf(stderr, "ERROR in line: %s\n TM says: %s\n", line, msg);
    exit(1);
}

OpCode get_opcode(char *line) {
    if (line[0] == 'A') {
        if (line[1] == 'D' && line[2] == 'D') return ADD;
        else parse_error(line, OP_ERR);
    } else if (line[0] == 'D') {
        if (line[1] == 'I' && line[2] == 'V') return DIV;
        else parse_error(line, OP_ERR);
    } else if (line[0] == 'H') {
        if (line[1] == 'A' && line[2] == 'L' && line[3] == 'T') return HALT;
        else parse_error(line, OP_ERR);
    } else if (line[0] == 'I') {
        if (line[1] == 'N') return IN;
        else parse_error(line, OP_ERR);
    } else if (line[0] == 'J') {
        if (line[1] == 'M' && line[2] == 'P') return JMP;
        else if (line[1] == 'N' && line[2] == 'Z') return JNZ;
        else if (line[1] == 'O' && line[2] == 'N') return JON;
        else parse_error(line, OP_ERR);
    } else if (line[0] == 'L') {
        if (line[1] == 'D' && line[2] == 'A') return LDA;
        else if (line[1] == 'D' && line[2] == 'C') return LDC;
        else if (line[1] == 'D' && line[2] == ' ') return LD;
        else parse_error(line, OP_ERR);
    } else if (line[0] == 'M') {
        if (line[1] == 'U' && line[2] == 'L') return MUL;
        else parse_error(line, OP_ERR);
    } else if (line[0] == 'O') {
        if (line[1] == 'U' && line[2] == 'T') return OUT;
        else parse_error(line, OP_ERR);
    } else if (line[0] == 'S') {
        if (line[1] == 'U' && line[2] == 'B') return SUB;
        else if (line[1] == 'T') return ST;
        else parse_error(line, OP_ERR);
    } else parse_error(line, OP_ERR);
    return HALT; // Dummy return, should never be reached.
}

void read_params(char *line, OpCode op, int *i1, int *i2, int *i3) {
    line += 5;
    *i1 = 0;
    *i2 = 0;
    *i3 = 0;
    int n = OpCount[op];

    if (n == 0) return;

    if (op == IN || op == OUT) {
        sscanf(line, "r%d", i1);
    } else if (op == JMP) {
        sscanf(line, "%d", i1);
    } else if (op == LDC || op == JON || op == JNZ) {
        sscanf(line, "r%d, %d", i1, i2);
    } else if (op == LD || op == LDA || op == ST) {
        sscanf(line, "r%d, %d, r%d", i1, i2, i3);
    } else {
        sscanf(line, "r%d, r%d, r%d", i1, i2, i3);
    }
}

int ia = 0; // For program loading.

void parse_line(char *line) {
    OpCode op;
    int i1;
    int i2;
    int i3;

    if (is_empty(line)) return;

    op = get_opcode(line);
    read_params(line, op, &i1, &i2, &i3);

    // Store instruction
    iMem[ia].op = op;
    iMem[ia].i1 = i1;
    iMem[ia].i2 = i2;
    iMem[ia].i3 = i3;
    ia++;
}

 void read_program() {
    bool done;
    char line[LINE_SIZE];

    done = false;
    ia = 0;
    done = read_line(line);
    while (!done) {
        parse_line(line);
        done = read_line(line);
    }
}

void get_instruction_string(Instruction instr, char *s) {
    OpCode op = instr.op;
    s += sprintf(s, "%4s", OpStr[op]);

    if (op == HALT) return;

    if (op == IN || op == OUT) {
        sprintf(s, " r%d", instr.i1);
    } else if (op == JMP) {
        sprintf(s, " %d", instr.i1);
    } else if (op == LDC || op == JON || op == JNZ) {
        sprintf(s, " r%d, %d", instr.i1, instr.i2);
    } else if (op == LD || op == LDA || op == ST) {
        sprintf(s, " r%d, %d, r%d", instr.i1, instr.i2, instr.i3);
    } else {
        sprintf(s, " r%d, r%d, r%d", instr.i1, instr.i2, instr.i3);
    }
}

void write_instruction(int iAddr) {
    Instruction instr = iMem[iAddr];
    char instr_str[LINE_SIZE];
    get_instruction_string(instr, instr_str);
    printf("%5d: %s\n", iAddr, instr_str);
}

void dump_program() {
    printf("*** Instruction Memory:\n\n");
    for (int iAddr = 0; iAddr < ia; iAddr++) {
        write_instruction(iAddr);
    }
    printf("\n");
}

// ----------------------------------------------------------------------------
// Run ------------------------------------------------------------------------

#define inc_PC() reg[PC]++

StepResult run_halt(Instruction instr) {
    return HALTED;
}

StepResult run_in(Instruction instr) {
    int x;
    printf("IN: ");
    scanf("%d", &x);
    reg[instr.i1] = x;
    inc_PC();
    return OKAY;
}

StepResult run_out(Instruction instr) {
    printf("OUT: %d\n", reg[instr.i1]);
    inc_PC();
    return OKAY;
}

#define bin_op() \
    int l = reg[instr.i2];\
    int r = reg[instr.i3]

StepResult run_add(Instruction instr) {
    bin_op();
    reg[instr.i1] = l + r;
    inc_PC();
    return OKAY;
}

StepResult run_sub(Instruction instr) {
    bin_op();
    reg[instr.i1] = l - r;
    inc_PC();
    return OKAY;
}

StepResult run_mul(Instruction instr) {
    bin_op();
    reg[instr.i1] = l * r;
    inc_PC();
    return OKAY;
}

StepResult run_div(Instruction instr) {
    bin_op();
    if (r == 0) return DIV_ZERO;
    reg[instr.i1] = l / r;
    inc_PC();
    return OKAY;
}

#define compute_addr() \
    int addr = instr.i2 + reg[instr.i3]

StepResult run_ld(Instruction instr) {
    compute_addr();
    if (addr < 0 || addr >= DADDR_SIZE) return DMEM_ERR;
    reg[instr.i1] = dMem[addr];
    inc_PC();
    return OKAY;
}

StepResult run_lda(Instruction instr) {
    compute_addr();
    reg[instr.i1] = addr;
    inc_PC();
    return OKAY;
}

StepResult run_ldc(Instruction instr) {
    reg[instr.i1] = instr.i2;
    inc_PC();
    return OKAY;
}

StepResult run_st(Instruction instr) {
    compute_addr();
    if (addr < 0 || addr >= DADDR_SIZE) return DMEM_ERR;
    dMem[addr] = reg[instr.i1];
    inc_PC();
    return OKAY;
}

StepResult run_jon(Instruction instr) {
    if (reg[instr.i1] < 0) {
        reg[PC] += instr.i2;
    } else {
        inc_PC();
    }
    return OKAY;
}

StepResult run_jnz(Instruction instr) {
    if (reg[instr.i1] != 0) {
        reg[PC] += instr.i2;
    } else {
        inc_PC();
    }
    return OKAY;
}

StepResult run_jmp(Instruction instr) {
    reg[PC] = instr.i1;
    return OKAY;
}

#define TRACE

StepResult step() {
    if (reg[PC] < 0 || reg[PC] >= IADDR_SIZE) return IMEM_ERR;

    #ifdef TRACE
        printf("TRACE: Next instruction is - ");
        write_instruction(reg[PC]);
    #endif

    Instruction instr = iMem[reg[PC]];

    switch(instr.op) {
        case HALT:  return run_halt(instr);
        case IN:    return run_in(instr);
        case OUT:   return run_out(instr);
        case ADD:   return run_add(instr);
        case SUB:   return run_sub(instr);
        case MUL:   return run_mul(instr);
        case DIV:   return run_div(instr);
        case LD:    return run_ld(instr);
        case LDA:   return run_lda(instr);
        case LDC:   return run_ldc(instr);
        case ST:    return run_st(instr);
        case JON:   return run_jon(instr);
        case JNZ:   return run_jnz(instr);
        case JMP:   return run_jmp(instr);
        default:    return OKAY; // Dummy return, should not be reached.
    }
}

void run() {
    StepResult result;
    do {
        result = step();
    } while (result == OKAY);

    switch(result) {
        case HALTED:
            printf("SUCCESS: Execution finished!\n");
            break;
        case IMEM_ERR:
            printf("ERROR: Invalid access to Instruction Memory!\n");
            break;
        case DMEM_ERR:
            printf("ERROR: Invalid access to Data Memory!\n");
            break;
        case DIV_ZERO:
            printf("ERROR: Division by zero!\n");
            break;
        default:
            printf("ERROR: Fall-through in run..?\n");
    }
}

// ----------------------------------------------------------------------------
// Main -----------------------------------------------------------------------

#define DEBUG

int main(void) {
    init();
    read_program(); // From STDIN
    #ifdef DEBUG
        dump_program();
    #endif
    stdin = fopen(ctermid(NULL), "r"); // Reset STDIN so IN commands will work.
    run();
    return 0;
}
