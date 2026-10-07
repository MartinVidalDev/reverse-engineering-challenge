#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#ifdef __linux__
#include <sys/ptrace.h>
#include <sys/types.h>
#endif

// Level 3: Anti-Debugging & Hooking - The Ghost Alien Boss

struct Boss {
    int x;
    int y;
    int hp;
    int visible;
    int is_ghost;  // Ghost mode = out of screen
};

Boss boss = {-9999, -9999, 100, 0, 1};  // Boss starts invisible/out of screen

int debug_detected = 0;
int game_running = 1;

// Anti-debugging function
int check_for_debugger() {
    #ifdef __linux__
    // Check for ptrace attach
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1) {
        return 1;  // Debugger detected
    }
    #endif
    
    // Check for GDB via /proc
    #ifdef __linux__
    FILE *fp = fopen("/proc/self/status", "r");
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, "TracerPid:") && strstr(line, " 0") == NULL) {
                fclose(fp);
                return 1;  // Debugger detected
            }
        }
        fclose(fp);
    }
    #endif
    
    return 0;
}

void anti_debug_exit() {
    printf("\n[!] ANTI-DEBUG PROTECTION ACTIVATED\n");
    printf("[!] Debugger detected! Exiting...\n");
    printf("[!] Try bypassing this check to continue...\n\n");
    exit(1);
}

void update_boss_position() {
    // CRITICAL FUNCTION TO HOOK
    // This function sets the boss position
    // Normally it's set to invalid/offscreen coordinates
    
    if (boss.is_ghost) {
        // Keep boss invisible
        boss.x = -9999;
        boss.y = -9999;
        boss.visible = 0;
    }
}

void spawn_boss() {
    printf("\n⚡⚡⚡ THE GHOST ALIEN APPEARS ⚡⚡⚡\n");
    printf("[!] The boss is moving in an impossible pattern!\n");
    printf("[!] Coordinates seem invalid: X=%d, Y=%d\n", boss.x, boss.y);
    printf("[!] You can't hit what you can't see...\n\n");
    
    boss.hp = 100;
    boss.visible = 0;
    boss.is_ghost = 1;
}

int player_shoot() {
    // Player attempts to shoot the boss
    printf("[*] Player shoots! ");
    
    // Check if boss is visible and within screen bounds
    if (boss.x < 0 || boss.x > 800 || boss.y < 0 || boss.y > 600) {
        printf("Miss! Boss is out of reach.\n");
        return 0;
    }
    
    if (boss.visible && !boss.is_ghost) {
        printf("HIT!\n");
        boss.hp -= 50;
        return 1;
    }
    
    printf("Miss!\n");
    return 0;
}

void boss_defeated() {
    printf("\n");
    printf("╔════════════════════════════════════╗\n");
    printf("║    === LEVEL 3 COMPLETE ===                  ║\n");
    printf("║     You defeated the Ghost Alien!          ║\n");
    printf("╚════════════════════════════════════╝\n\n");
    
    // Decode and display flag part 3
    const unsigned char flag_part3_xor[] = {
        0x68 ^ 0x99,  // h
        0x34 ^ 0x99,  // 4
        0x63 ^ 0x99,  // c
        0x6B ^ 0x99,  // k
        0x33 ^ 0x99,  // 3
        0x64 ^ 0x99,  // d
        0x21 ^ 0x99,  // !
        0x7D ^ 0x99,  // }
        0x00
    };
    
    unsigned char flag_buffer[16];
    for (int i = 0; flag_part3_xor[i] != 0; i++) {
        flag_buffer[i] = flag_part3_xor[i] ^ 0x99;
    }
    flag_buffer[8] = 0;
    
    printf("🚀 FLAG PART 3: %s\n\n", (char*)flag_buffer);
}

int main() {
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║  REVERSE ENGINEERING CTF - Space Invaders      ║\n");
    printf("║  Level 3: Anti-Debug & Hooking Challenge   ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    
    // Anti-debugging check
    if (check_for_debugger()) {
        anti_debug_exit();
    }
    
    printf("\n=== LEVEL 3: The Ghost Alien ===\n");
    printf("Objective: Defeat the Ghost Boss\n");
    printf("Warning: This boss cannot be touched!\n");
    printf("Warning: Opening a debugger will terminate the program!\n\n");
    
    // Spawn the boss
    spawn_boss();
    sleep(1);
    
    // Update boss position (keeps it out of screen)
    update_boss_position();
    printf("[*] Boss current position: X=%d, Y=%d\n", boss.x, boss.y);
    printf("[*] Screen bounds: X=[0-800], Y=[0-600]\n");
    printf("[!] The boss coordinates are invalid!\n");
    printf("[!] You need to hook the update_boss_position() function\n");
    printf("[!] Try moving the boss to the center of the screen: (400, 300)\n\n");
    
    sleep(1);
    
    // Try to shoot
    printf("[*] Attempting to shoot the boss...\n");
    if (player_shoot()) {
        boss_defeated();
    } else {
        printf("\n[!] You missed! The boss escaped!\n");
        printf("[*] Level 3 flag was: h4ck3d!}\n\n");
        return 1;
    }
    
    return 0;
}
