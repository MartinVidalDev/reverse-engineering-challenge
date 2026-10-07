#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Level 2: Dynamic Reverse Engineering - Patch the take_damage function
struct Player {
    int x;
    int y;
    int lives;
    int score;
    int level;
};

struct Projectile {
    int x;
    int y;
    int active;
};

Player player = {400, 300, 3, 0, 2};
const int MAX_PROJECTILES = 10000;
Projectile projectiles[10000];
int projectile_count = 0;

// Encoded flag part 2 - decoded at runtime
const unsigned char flag_part2_encoded[] = {
    0x6D ^ 0x55,  // m
    0x33 ^ 0x55,  // 3
    0x6D ^ 0x55,  // m
    0x5F ^ 0x55,  // _
    0x00
};

void take_damage() {
    // THIS IS THE FUNCTION TO PATCH!
    // Patch this function to make the player invincible
    // Either: replace DEC with NOP
    // Or: create a variable is_invincible = 1
    
    player.lives--;  // <-- Patch this line
    
    if (player.lives <= 0) {
        printf("[!] Player died! Game Over.\n");
        exit(1);
    }
}

void spawn_inferno_wave() {
    // Level 2: Inferno Wave - thousands of projectiles
    printf("\n⚡ INFERNO WAVE INCOMING! ⚡\n");
    printf("[!] Spawning 9999 projectiles directly at the player...\n\n");
    
    for (int i = 0; i < 9999; i++) {
        projectiles[i].x = player.x;
        projectiles[i].y = player.y;
        projectiles[i].active = 1;
    }
    projectile_count = 9999;
}

void update_projectiles() {
    // All projectiles hit the player at once
    if (projectile_count > 0) {
        printf("[*] %d projectiles are heading toward you!\n", projectile_count);
        
        // Each tick, take massive damage
        for (int i = 0; i < 10 && player.lives > 0; i++) {
            printf("[HIT] Player hit! Lives remaining: %d\n", player.lives);
            take_damage();  // <-- This function needs to be patched
        }
        
        if (player.lives > 0) {
            printf("[!] Against all odds, you survived!\n");
        }
    }
}

void level2_complete() {
    printf("\n");  
    printf("╔════════════════════════════════════╗\n");
    printf("║    === LEVEL 2 COMPLETE ===                  ║\n");
    printf("║   You survived the Inferno Wave!          ║\n");
    printf("╚════════════════════════════════════╝\n\n");
    
    // Decode flag part 2
    unsigned char flag_buffer[16];
    for (int i = 0; flag_part2_encoded[i] != 0; i++) {
        flag_buffer[i] = flag_part2_encoded[i] ^ 0x55;
    }
    flag_buffer[4] = 0;
    
    printf("🚀 FLAG PART 2: %s\n\n", (char*)flag_buffer);
}

int main() {
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║  REVERSE ENGINEERING CTF - Space Invaders      ║\n");
    printf("║  Level 2: Dynamic Analysis Challenge        ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    
    printf("\n=== LEVEL 2: The Invincible Ship ===\n");
    printf("Objective: Survive the Inferno Wave\n");
    printf("Player lives: %d\n", player.lives);
    printf("Position: (%d, %d)\n\n", player.x, player.y);
    
    // Start the impossible wave
    spawn_inferno_wave();
    
    // Process projectiles
    sleep(1);
    update_projectiles();
    
    // Check if player survived
    if (player.lives > 0) {
        level2_complete();
    } else {
        printf("\n[!] You died! Game Over.\n");
        printf("[*] Level 2 flag was: m3m_\n\n");
        return 1;
    }
    
    return 0;
}
