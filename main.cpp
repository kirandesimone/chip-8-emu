#include <cstdio>

#define KIBIBYTES(a) ((a) * 1024)
#define MEMORY_SIZE KIBIBYTES(4)
#define PROGRAM_ADDR 0x200 // byte 512

typedef struct chip8 {
    unsigned short i;  // index register
    unsigned short pc; // program counter
    unsigned short sp; // stack pointer

    unsigned char memory[MEMORY_SIZE];

    unsigned char delay_timer;
    unsigned char sound_timer;

    // registers
    unsigned char V0;
    unsigned char V1;
    unsigned char V2;
    unsigned char V3;
    unsigned char V4;
    unsigned char V5;
    unsigned char V6;
    unsigned char V7;
    unsigned char V8;
    unsigned char V9;
    unsigned char VA;
    unsigned char VB;
    unsigned char VC;
    unsigned char VD;
    unsigned char VE;
    unsigned char VF;
} Chip8;

int main() {
  printf("Hello, world\n");
  return 0;
}
