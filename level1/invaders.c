#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Level 1: Static Reverse Engineering - Find the score check
int score = 0;
int game_running = 1;
int aliens_destroyed = 0;
int difficulty_multiplier = 1;

const int REQUIRED_SCORE = 999999;  // 0xF423F in hex

// XOR encoded flag part 1
const unsigned char flag_part1_xor[] = {
    0x46 ^ 0xAA,  // F
    0x4C ^ 0xAA,  // L
    0x41 ^ 0xAA,  // A
    0x47 ^ 0xAA,  // G
    0x7B ^ 0xAA,  // {
    0x31 ^ 0xAA,  // 1
    0x6E ^ 0xAA,  // n
    0x76 ^ 0xAA,  // v
    0x34 ^ 0xAA,  // 4
    0x64 ^ 0xAA,  // d
    0x33 ^ 0xAA,  // 3
    0x72 ^ 0xAA,  // r
    0x73 ^ 0xAA,  // s
    0x5F ^ 0xAA,  // _
    0x00
};

void check_score() {
    if (score >= REQUIRED_SCORE) {
        printf("\n=== LEVEL 1 COMPLETE ===\n");
        printf("Congratulations! You've reached the impossible score!\n\n");
        
        // Decode and display flag part 1
        unsigned char flag_buffer[32];
        for (int i = 0; flag_part1_xor[i] != 0; i++) {
            flag_buffer[i] = flag_part1_xor[i] ^ 0xAA;
        }
        flag_buffer[14] = 0;
        
        printf("🚀 FLAG PART 1: %s\n\n", (char*)flag_buffer);
        game_running = 0;
    }
}

void simulate_game() {
    printf("\n=== LEVEL 1: Score Impossible ===\n");
    printf("Objective: Destroy aliens and reach a score of 999,999\n");
    printf("Current score: %d\n", score);
    printf("Each alien destroyed: 1 point\n");
    printf("Game speed increases exponentially...\n\n");
    
    srand(time(NULL));
    
    while (game_running) {
        // Simulate game ticks
        for (int i = 0; i < 1000000 && game_running; i++) {
            // Simulate destroying an alien every tick (very slow)
            if (i % 100000 == 0) {
                aliens_destroyed++;
                score += 1;  // Only 1 point per alien
                
                if (aliens_destroyed % 10000 == 0) {
                    printf("Aliens destroyed: %d | Score: %d\n", 
                           aliens_destroyed, score);
                    
                    // Check if we've reached the impossible score
                    check_score();
                }
            }
        }
        
        // Safety check - this would take forever
        if (aliens_destroyed > 50000) {
            printf("\n[!] This is taking way too long... Maybe there's another way?\n");
            printf("[!] Try analyzing this binary with a disassembler (Ghidra/IDA)\n");
            printf("[!] Look for the constant 999999 (0xF423F)\n");
            printf("[!] Or patch the JNE instruction at check_score()\n\n");
            break;
        }
    }
}

int main() {
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║  REVERSE ENGINEERING CTF - Space Invaders      ║\n");
    printf("║  Level 1: Static Analysis Challenge           ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    
    simulate_game();
    
    printf("\n[*] Level 1 ended. Flag part 1 was: FLAG{1nv4d3rs_\n");
    return 0;
}
