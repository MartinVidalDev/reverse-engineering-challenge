# Level 2: Inferno Wave - Solution

## Challenge Overview
- **Goal**: Survive the Inferno Wave (Level 2) where 9,999 projectiles hit the player instantly
- **Problem**: Player has only 3 lives, dies in less than a second
- **Expected Technique**: Dynamic Reverse Engineering & Binary Patching
- **Key Insight**: The flag is decoded dynamically at runtime (not statically stored)

## Solution Approaches

### Approach 1: Debugger Memory Modification (Recommended)

1. **Load the binary in GDB or x64dbg**:
   ```bash
   gdb ./level2
   ```

2. **Set a breakpoint at `take_damage()`**:
   ```gdb
   (gdb) break take_damage
   (gdb) run
   ```

3. **Modify the `lives` variable in memory**:
   ```gdb
   (gdb) set variable player.lives = 999
   (gdb) continue
   ```

4. **The player survives, and the flag part 2 is printed**!

### Approach 2: Binary Patching with x64dbg

1. **Open the binary in x64dbg**:
   ```bash
   x64dbg level2
   ```

2. **Search for the `take_damage()` function** in the code section

3. **Find the instruction that decrements `player.lives`**:
   - Look for: `DEC [rbp-offset]` or `SUB [memory], 1`
   - This is typically something like: `DEC DWORD PTR [rbp-0x8]`

4. **Replace with NOPs (No Operation)**:
   - Right-click the instruction → Patch → Replace with NOPs
   - This makes the function do nothing (player never takes damage)

5. **Save the patched binary** and run it
   - The flag part 2 will be printed when the level ends

### Approach 3: Source Code Analysis with Strings

1. **Use `strings` to find encoded data**:
   ```bash
   strings level2 | grep -i flag
   ```

2. **Identify the XOR-encoded flag**:
   - Look for patterns in the binary that might be the encoded flag
   - The flag part 2 is `m3m_` (encoded with XOR key `0x55`)

3. **Write a small program to decode**:
   ```c
   unsigned char encoded[] = {0x6D ^ 0x55, 0x33 ^ 0x55, 0x6D ^ 0x55, 0x5F ^ 0x55};
   // XOR with 0x55 to get: "m3m_"
   ```

### Approach 4: Frida Instrumentation (Advanced)

```python
import frida
import sys

def on_message(message, data):
    print("[Frida]", message)

device = frida.get_local_device()
process = device.spawn(["./level2"])
session = device.attach(process)

script = session.create_script("""
var take_damage = Module.findExportByName(null, "take_damage");
interceptor.attach(take_damage, {
    onEnter: function(args) {
        console.log("[*] take_damage called, skipping...");
        this.context.rax = 0;  // Return without doing anything
    }
});
""")

script.on('message', on_message)
script.load()
device.resume(process)
```

## Key Observations

- `player.lives` is the critical variable (starts at 3)
- `take_damage()` function decrements lives
- Flag part 2 (`m3m_`) is decoded dynamically when level2_complete() runs
- XOR key for encoding: `0x55`
- The flag is NOT in the binary as plaintext, only encoded

## Flag Part 2

```
m3m_
```

## Tools Needed

- GDB or x64dbg (debugging)
- Ghidra or IDA Pro (optional, for understanding structure)
- Frida (optional, for advanced instrumentation)

## Python Decoding Script

```python
flag_xor = bytes([0x6D ^ 0x55, 0x33 ^ 0x55, 0x6D ^ 0x55, 0x5F ^ 0x55])
flag = bytes([b ^ 0x55 for b in flag_xor])
print(flag.decode())
```

## Debugging Commands

### GDB
```bash
gdb ./level2
(gdb) break take_damage
(gdb) run
(gdb) info local              # Show local variables
(gdb) print player            # Print player struct
(gdb) set variable player.lives = 100
(gdb) continue
```

### x64dbg
- Press Ctrl+G to go to address
- Right-click → Assemble to patch instructions
- Use Hex Dump to view memory
- Breakpoints on functions: break on `take_damage` entry

## Why This Level?

This level teaches:
- Dynamic memory inspection
- Runtime value modification
- Understanding the relationship between source code and assembly
- Binary patching techniques
