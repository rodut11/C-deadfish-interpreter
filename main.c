#include <stdio.h>
#include <stdint.h>

typedef enum {
    OP_INC = 0,
    OP_DEC,
    OP_SQR,
    OP_OUT,
    OP_END
} Operator;

typedef struct {
    Operator op;
} Instruction;

typedef enum {
    SUCCESS = 0,
    FAILURE
} Status;

#define PROGRAM_SIZE 4096

static Instruction PROGRAM[PROGRAM_SIZE];

size_t ip = 0;

int compile(FILE *pFile) {

    int c;
    int program_counter = 0;

    while ((c = getc(pFile)) != EOF && program_counter < PROGRAM_SIZE) {
        switch (c) {
            case 'i': PROGRAM[program_counter].op = OP_INC; break;
            case 'd': PROGRAM[program_counter].op = OP_DEC; break;
            case 's': PROGRAM[program_counter].op = OP_SQR; break;
            case 'o': PROGRAM[program_counter].op = OP_OUT; break;
            default: continue;
        }
        program_counter++;
    }
    PROGRAM[program_counter].op = OP_END;
    return SUCCESS;
}

int execute() {
    int accumulator = 0;

    while (PROGRAM[ip].op != OP_END) {
        switch (PROGRAM[ip].op) {
            case OP_INC: accumulator++; break;
            case OP_DEC: accumulator--; break;
            case OP_SQR: accumulator = accumulator * accumulator ; break;
            case OP_OUT: putchar(accumulator); break;
        }
        ip++;
    }
    return SUCCESS;
}

int main(int argc, char *argv[]) {

    if (argc != 2) { // check if the user provided exactly one argument
        fprintf(stderr, "Usage: %s [FILE]\n", argv[0]);
        return FAILURE;
    }

    FILE *pFile = fopen(argv[1], "r");
    if (pFile == NULL) {
        fprintf(stderr, "Can't open file.\n");
        return FAILURE;
    }

    Status status = compile(pFile);
    fclose(pFile);

    switch (status) {
        case SUCCESS: status = execute(); break;
        case FAILURE: fprintf(stderr, "Encountered error!\n"); break;
    }

    return status;
}