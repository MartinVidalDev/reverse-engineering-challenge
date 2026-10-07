# Level 2: Inferno Wave

## Challenge Description

You've made it to Level 2. Now you face the **Inferno Wave** - a deadly barrage of 9,999 projectiles heading straight at you.

Your ship has only **3 lives**. The projectiles all hit at once. There's no way to dodge them all through gameplay.

**Key Twist**: Unlike Level 1, the flag part for this level is NOT stored as a constant in the binary. It's decoded and printed **at runtime** only when you survive.

## Build & Run

```bash
cd level2
make
./level2
```

Or with debugging:

```bash
make debug
```

## Hints

- 🔍 Open this binary in a **debugger** (GDB or x64dbg)
- 🔍 Set a **breakpoint** at the `take_damage()` function
- 🔍 Modify the `player.lives` variable in memory
- 🔍 Or try **patching** the `DEC` instruction to `NOP`
- 🔍 The flag appears **dynamically** when you reach the end

## Expected Output

When you solve the challenge, you should see:

```
[*] Against all odds, you survived!

╔═══════════════════════════════════╗
║    === LEVEL 2 COMPLETE ===       ║
║   You survived the Inferno Wave!  ║
╚═══════════════════════════════════╝

👾 FLAG PART 2: m3m_
```

## Difficulty

⭐⭐ Medium - Dynamic Reverse Engineering

This level requires:
- Understanding binary debugging
- Memory inspection and modification
- Understanding the relationship between C source and compiled assembly
- Binary patching skills

## Challenge Mechanics

1. The game spawns 9,999 projectiles
2. Each one hits the player, calling `take_damage()`
3. `take_damage()` decrements `player.lives`
4. You need to patch this to survive
5. Once you survive, the flag is decoded and displayed
