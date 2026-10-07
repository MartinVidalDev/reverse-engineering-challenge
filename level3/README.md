# Level 3: Ghost Alien

## Challenge Description

You've reached the final level. The **Ghost Alien** boss awaits you, but there's a catch:

1. **The boss is invisible**: Its coordinates are set to invalid values (-9999, -9999), placing it outside the screen boundaries.
2. **Anti-debugging is active**: If you try to open a traditional debugger, the program terminates immediately.
3. **No static clues**: The flag is only revealed when you defeat the boss.

**Key Twist**: You need to use advanced instrumentation techniques to bypass the anti-debug and hook the boss positioning function.

## Build & Run

```bash
cd level3
make
./level3
```

## Hints

- 🔗 This challenge requires **hooking**, not traditional debugging
- 🔗 Try using **Frida** to instrument the running process
- 🔗 Look for the `update_boss_position()` function - you need to modify its behavior
- 🔗 The boss struct has `x` and `y` fields that need to be moved to screen center (400, 300)
- 🔗 The anti-debug check happens before the main game loop

## Using Frida

```bash
# Install Frida if you haven't
pip install frida-tools

# Run with Frida hook script
frida -l hook.js ./level3
```

## Expected Output

When you solve the challenge, you should see:

```
[*] Boss current position: X=400, Y=300
[*] Screen bounds: X=[0-800], Y=[0-600]
[*] Attempting to shoot the boss...
[*] Player shoots! HIT!

╔════════════════════════════════════╗
║    === LEVEL 3 COMPLETE ===       ║
║     You defeated the Ghost Alien!  ║
╚════════════════════════════════════╝

👾 FLAG PART 3: h4ck3d!}
```

## Difficulty

⭐⭐⭐ Hard - Anti-Debug & Advanced Hooking

This level requires:
- Understanding anti-debugging techniques
- Runtime instrumentation with Frida
- Memory inspection and modification
- Ability to modify function behavior without traditional debuggers
- Advanced reverse engineering skills

## Challenge Mechanics

1. The program checks for debuggers on startup
2. If a debugger is detected, it exits
3. The boss position is updated to invalid coordinates
4. You need to hook the update function to move the boss
5. Once the boss is in range, shooting it triggers the victory condition
6. The flag is printed when you win

## Alternative Approaches

- **Patch the binary** to remove anti-debug checks
- **Use GDB with breakpoints** on the anti-debug function and skip it
- **Use Angr** for symbolic execution
- **Reverse engineer** and rewrite key functions
