// Frida hook script for Level 3
// Usage: frida -l hook.js ./level3

function bypass_antidebug() {
    console.log("[Frida] Attempting to bypass anti-debug...");
    
    // Bypass ptrace check on Linux
    var libc = Module.getBaseAddress('libc.so.6');
    if (libc) {
        var ptrace = Module.findExportByName('libc.so.6', 'ptrace');
        if (ptrace) {
            Interceptor.attach(ptrace, {
                onEnter: function(args) {
                    console.log("[Frida] ptrace called, returning success");
                },
                onLeave: function(retval) {
                    retval.replace(0);  // Always return success
                }
            });
        }
    }
}

function hook_boss_position() {
    console.log("[Frida] Hooking update_boss_position()...");
    
    // Get the base address of the loaded binary
    var module = Process.getModuleByName('level3');
    if (!module) {
        console.log("[!] Could not find module 'level3'");
        return;
    }
    
    console.log("[Frida] Module base: " + module.base);
    
    // Find and hook the update_boss_position function
    // You may need to adjust the offset based on your binary
    var update_boss = module.findExportByName('update_boss_position');
    
    if (!update_boss) {
        console.log("[Frida] Searching for update_boss_position by pattern...");
        // Alternative: search by pattern or use nm/objdump output
        return;
    }
    
    Interceptor.attach(update_boss, {
        onEnter: function(args) {
            console.log("[Frida] update_boss_position called!");
        },
        onLeave: function(retval) {
            console.log("[Frida] Modifying boss coordinates to center screen...");
            // The boss struct is typically at a known memory location
            // You need to find this address via gdb or reverse engineering
            // For now, this is a template
        }
    });
}

function hook_player_shoot() {
    console.log("[Frida] Hooking player_shoot()...");
    
    var module = Process.getModuleByName('level3');
    if (!module) return;
    
    var shoot = module.findExportByName('player_shoot');
    if (!shoot) return;
    
    Interceptor.attach(shoot, {
        onLeave: function(retval) {
            console.log("[Frida] Making shot always hit!");
            retval.replace(1);  // Always return 1 (hit)
        }
    });
}

// Main execution
console.log("[Frida] Level 3 Hook Script Loaded");
bypass_antidebug();
hook_boss_position();
hook_player_shoot();
