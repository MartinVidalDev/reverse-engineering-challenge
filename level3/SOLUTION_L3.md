# Level 3: Ghost Alien - Solution

## Challenge Overview
- **Goal**: Defeat the Ghost Alien boss that moves outside the screen
- **Problem**: Boss coordinates are invalid (X/Y = -9999), making it unreachable
- **Problem 2**: Anti-debugging protection kills the program if a debugger is attached
- **Expected Technique**: Anti-Debug Bypass + Function Hooking
- **Tools**: Frida, GDB with patches, or Angr

## Solution Approaches

### Approach 1: Frida Hooking (Recommended)

1. **Install Frida**:
   ```bash
   pip install frida-tools
   ```

2. **Use the provided Frida script**:
   ```bash
   frida -l hook.js ./level3
   ```

3. **The script does two things**:
   - Bypasses the anti-debug check by intercepting `ptrace()`
   - Hooks `update_boss_position()` to move the boss to the center (400, 300)
   - Hooks `player_shoot()` to make every shot hit

4. **Enhanced Frida script** with proper memory manipulation:
   ```javascript
   var module = Process.getModuleByName('level3');
   var update_boss = module.findExportByName('update_boss_position');
   
   Interceptor.attach(update_boss, {
       onLeave: function(retval) {
           // Find boss struct in memory and modify x, y coordinates
           var boss_x_addr = ... // Calculate from ida/ghidra
           var boss_y_addr = ...
           
           Memory.writeInt(boss_x_addr, 400);  // Center X
           Memory.writeInt(boss_y_addr, 300);  // Center Y
       }
   });
   ```

### Approach 2: GDB with Anti-Debug Bypass

1. **Patch the anti-debug check at binary level**:
   ```bash
   objdump -d level3 | grep -A 10 'check_for_debugger'
   ```

2. **Find the function entry and identify the check**

3. **Use a hex editor to patch the binary**:
   - Change the `ptrace()` call to return 0 (success)
   - Or replace the entire check with NOPs

4. **Then debug normally**:
   ```bash
   gdb ./level3
   (gdb) break update_boss_position
   (gdb) run
   (gdb) print boss
   (gdb) set variable boss.x = 400
   (gdb) set variable boss.y = 300
   (gdb) continue
   ```

### Approach 3: Angr Symbolic Execution (Advanced)

```python
import angr

project = angr.Project('./level3')
state = project.factory.entry_state()

# Explore until we reach the boss defeat function
simgr = project.factory.simgr(state)
simgr.explore(find=lambda s: b'LEVEL 3 COMPLETE' in s.posix.dumps(1))

if simgr.found:
    found_state = simgr.found[0]
    print("[+] Flag found!")
    print(found_state.posix.dumps(1))
```

### Approach 4: Manual Patching with x64dbg

1. **Open level3 in x64dbg**

2. **Locate `check_for_debugger()`**:
   - Set breakpoint at entry
   - Look for the `ptrace()` call

3. **Patch the return value**:
   - After `ptrace()` returns, modify RAX to 0 (no debugger)

4. **Find the boss struct in memory**:
   - Set breakpoint at `spawn_boss()`
   - Watch memory as variables are initialized
   - Note the address of `boss.x` and `boss.y`

5. **Modify the coordinates**:
   - Memory dump: modify both x and y to valid screen coordinates
   - Or patch `update_boss_position()` to do this

6. **Shoot the boss**:
   - Let the program continue
   - Flag should appear

## Key Observations

- Boss struct: `x = -9999, y = -9999` (out of bounds)
- Anti-debug: `ptrace(PTRACE_TRACEME, ...)` check
- Function to hook: `update_boss_position()`
- Shoot condition: `boss.x >= 0 && boss.x <= 800 && boss.y >= 0 && boss.y <= 600`
- Flag part 3: `h4ck3d!}` (XOR key: `0x99`)

## Flag Part 3

```
h4ck3d!}
```

## Tools Needed

- **Frida** (recommended, easiest)
- GDB or x64dbg (with patches)
- Ghidra or IDA Pro (for analysis)
- Angr (for symbolic execution)
- Hex editor (for binary patching)

## Python Decoding Script

```python
flag_xor = bytes([0x68 ^ 0x99, 0x34 ^ 0x99, 0x63 ^ 0x99, 0x6B ^ 0x99,
                  0x33 ^ 0x99, 0x64 ^ 0x99, 0x21 ^ 0x99, 0x7D ^ 0x99])
flag = bytes([b ^ 0x99 for b in flag_xor])
print(flag.decode())
```

## Advanced: Understanding Anti-Debugging

### Common Anti-Debug Techniques:
1. **ptrace() check**: Linux only, can be bypassed by Frida
2. **IsDebuggerPresent()**: Windows API, check BeingDebugged flag
3. **INT 3 Breakpoint**: Detecting debugger breakpoints
4. **Parent process check**: Looking for known debuggers
5. **VM detection**: Looking for hypervisor signatures

### How Frida Bypasses:
- Intercepts system calls before they execute
- Modifies return values
- Replaces function bodies
- All without needing a traditional debugger attached

## Why This Level?

This level teaches:
- Anti-debugging techniques and how to bypass them
- Runtime function hooking
- Advanced memory manipulation
- Instrumentation with Frida
- Understanding the gap between source and runtime behavior
