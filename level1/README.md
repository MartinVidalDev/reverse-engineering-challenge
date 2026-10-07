# Level 1: Score Impossible

## Challenge Description

You're playing a space invaders game, and to unlock the next level, you need to reach an impossible score: **999,999 points**.

Each alien destroyed gives you only 1 point. The game's speed increases exponentially, making it humanly impossible to reach this score through normal gameplay.

## Build & Run

```bash
cd level1
make
./level1
```

Or with debugging symbols:

```bash
make debug
```

## Hints

- 💡 Try opening this binary in a disassembler like Ghidra or IDA Pro
- 💡 Search for the constant `999999` (or `0xF423F` in hex)
- 💡 Look at the `check_score()` function
- 💡 You might find encoded data nearby...
- 💡 Or try patching the JNE instruction with a debugger

## Expected Output

When you solve the challenge, you should see:

```
=== LEVEL 1 COMPLETE ===
Congratulations! You've reached the impossible score!

🚀 FLAG PART 1: FLAG{1nv4d3rs_
```

## Difficulty

⭐ Easy - Static Reverse Engineering

This is the entry-level challenge focusing on basic binary analysis skills.
