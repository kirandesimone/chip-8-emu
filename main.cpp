
/*************************************
 * 0xFFF  ______________
 *       |              |
 *       |    STACK     | Grows down
 * 0xFE0 |              |
 *        -------------
 *       |              |
 *       |
 *       |    PROGRAM
 *       |
 * 0x200 |              |
 *        -------------
 * 0x09F |              |
 *       |     FONT
 * 0x050 |              |
 *        -------------
 * 0x000 |_____________ |
 ************************************/

// Windows Headers
#include <memory.h>
#include <Windows.h>
#include <profileapi.h>

#define KIBIBYTES(a) ((a) * 1024)
#define ASSERT(expr) (expr) ? 0 : *(int *)0 = 0;
#define ARRAY_LEN(a) sizeof((a)) / sizeof((a)[0])

#define MEMORY_SIZE KIBIBYTES(4)
#define PROGRAM_BASE 0x200 // byte 512
#define STACK_BASE 0xFFF
#define STACK_END 0xFE0
#define FONT_BASE 0x50
#define FONT_END 0x9F
#define CPU_CYCLES 1000000 / 60

constexpr unsigned char font[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

struct Chip8 {
    unsigned char memory[MEMORY_SIZE];

    unsigned char delay_timer; // time register 1
    unsigned char sound_timer; // time register 2

    unsigned short i;  // index register
    unsigned short pc; // program counter
    unsigned short sp; // stack pointer

    // General Purpose Registers
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
};

constexpr float target_seconds_per_frame = 1 / 60.0f;
static unsigned char g_running {};

static inline long long
get_ticks()
{
    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);
    return ticks.QuadPart;
}

int main()
{
    LARGE_INTEGER perf_freq;
    QueryPerformanceFrequency(&perf_freq);

    Chip8 chip_8 {};
    memcpy((void*)(chip_8.memory + FONT_BASE), (void*)font, ARRAY_LEN(font));

    while (g_running) {
        LARGE_INTEGER last_counts;
        QueryPerformanceCounter(&last_counts);

        // code


        LARGE_INTEGER end_counts;
        QueryPerformanceCounter(&end_counts);

        long long elapsed_counts = end_counts.QuadPart - last_counts.QuadPart;
        float elapsed_seconds = ((float)elapsed_counts) / perf_freq.QuadPart;

        while (elapsed_seconds < target_seconds_per_frame) {
            QueryPerformanceCounter(&end_counts);
            elapsed_counts = end_counts.QuadPart - last_counts.QuadPart;
            elapsed_seconds = ((float)elapsed_counts) / perf_freq.QuadPart;
        }
    }

    return 0;
}
