# Level 1: Score Impossible - Solution

## Challenge Overview
- **Goal**: Reach a score of 999,999 to unlock the first part of the flag
- **Problem**: Each alien destroyed gives only 1 point, game runs extremely slow
- **Expected Technique**: Static Reverse Engineering

## Solution Approaches

### Approach 1: Disassembler Analysis (Recommended)

1. **Open the binary in Ghidra or IDA Pro**:
   ```bash
   ghidra level1
   ```

2. **Search for the constant 999999**:
   - In Ghidra: `Search > Search Constant` → enter `999999`
   - In IDA: `Search > Search Text` → enter `F423F` (hex value)

3. **Locate the `check_score()` function**:
   - The constant comparison will lead you to:
   ```c
   if (score >= 999999) {
       // Print flag here
   }
   ```

4. **Find the flag data**:
   - Near `check_score()`, you'll find the XOR-encoded flag: `flag_part1_xor[]`
   - Decode it by XORing each byte with `0xAA`
   - Result: `FLAG{1nv4d3rs_`

### Approach 2: Binary Patching (Faster)

1. **Patch the conditional jump**:
   ```bash
   x64dbg level1
   ```

2. **Find the JNE (Jump Not Equal) instruction in `check_score()`**:
   - This instruction jumps if score is NOT equal to 999999
   - Change `JNE` to `JZ` (or modify the comparison)
   - Or simply set a breakpoint and modify `score` to 999999 in memory

3. **Continue execution**:
   - The game will believe the score is reached
   - Flag part 1 will be printed immediately

### Approach 3: GDB Dynamic Analysis

```bash
gdb ./level1
(gdb) break check_score
(gdb) run
(gdb) set variable score = 999999
(gdb) continue
```

## Key Observations

- `REQUIRED_SCORE = 999999` (0xF423F)
- `flag_part1_xor[]` contains the encoded flag
- XOR key: `0xAA`
- The function is called frequently, making it easy to patch

## Flag Part 1

```
FLAG{1nv4d3rs_
```

## Tools Needed

- Ghidra or IDA Pro (disassembly)
- x64dbg or GDB (debugging/patching)
- Python (optional, for XOR decoding)

## Python Decoding Script

```python
flag_xor = bytes([0x46 ^ 0xAA, 0x4C ^ 0xAA, 0x41 ^ 0xAA, 0x47 ^ 0xAA,
                  0x7B ^ 0xAA, 0x31 ^ 0xAA, 0x6E ^ 0xAA, 0x76 ^ 0xAA,
                  0x34 ^ 0xAA, 0x64 ^ 0xAA, 0x33 ^ 0xAA, 0x72 ^ 0xAA,
                  0x73 ^ 0xAA, 0x5F ^ 0xAA])

flag = bytes([b ^ 0xAA for b in flag_xor])
print(flag.decode())
```
