# CYB4551 Lab 5: Arrays, Globals, Strings, and a Mystery

## Introduction

The purpose of this lab is to practice recognizing arrays, strides, globals, and strings in compiled code with the tools you'll use throughout the semester, including `gcc`, `objdump`, `nm`, `gdb`, and Ghidra. The lab content is directly based on lecture (pointer arithmetic, array indexing, two-dimensional arrays, and globals and strings). 

This lab is done on the **REMnux VM**. Submit your answers in `ANSWERS.md`, following the same structure as this file. Do **NOT** write your answers in this `README.md` file. Cite your sources when using information other than what was covered in class.

For this lab, please **enable the Shared Clipboard** feature on the REMnux VM to allow pasting code or commands between the host machine and the virtual machine.

## Background and References

Recall from lecture:
- `p + 1` moves a pointer by one **element**, not one byte. The constant added to a pointer tells you the size of the type it points to.
- `a[i]` is `base + index × element size`. In a two-dimensional array, `&g[r][c] = base + r × (columns × element size) + c × element size`. The **row stride** is baked into the instruction; the outer dimension never appears.
- A parameter written `int g[][4]` is really `int (*g)[4]`, a pointer to a row of 4 ints. The right-left (spiral) rule reads such declarations.
- Initialized globals live in `.data`, zero-filled ones in `.bss`, constants and string literals in `.rodata`. A pointer to a string literal is itself a variable in `.data` (or `.bss`); the characters are in `.rodata`.
- A global is reached with RIP-relative addressing: `target = address of the next instruction (RIP) + displacement`. Programs are built as position-independent executables (PIE), so the base address changes from run to run (ASLR), but the distances between things do not.
- A C string ends with a `0x00` byte (the null terminator, `\0`).
- _**In `gdb`**_:
  - `p EXPR` evaluates a C expression, `p/x` prints it in hexadecimal.
  - `x/s ADDR` prints a string; `x/8xb ADDR` prints 8 bytes in hex; `x/dw ADDR` prints one 4-byte decimal value.
  - `set var NAME = VALUE` changes a variable while the program is stopped.
- Further reading: *Practical Malware Analysis*, Chapter 6 (recognizing C code constructs; its examples are 32-bit, ours are x64).

## Provided Files (`src/`)

| File | What it is |
|---|---|
| `steps.c` | Source for Part 1A. You compile it. |
| `grid.c` | Source for Part 1B. You compile it. |
| `grid_bin` | Stripped executable for Part 1C (no source given). Run it as `./grid_bin ROW COL`. |
| `globals.c`, `globals_bin` | Source and executable (with symbols) for Part 2A and 2B. |
| `strings.c`, `strings_bin` | Source and executable (with symbols) for Part 2C. Run it as `./strings_bin N`. |
| `mystery.c`, `mystery_bin` | Source and executable for Part 3. Run it as `./mystery_bin NAME`. Use the **executable** for Parts 3A to 3C and open the source only for Part 3D. |


If a provided executable won't run, make it executable first: `chmod +x <filename>`.

## Setup

Programs you compile yourself in this lab (`steps.c`, `grid.c`) use:
```
gcc -O0 -g -masm=intel -fno-stack-protector -o <name> <name>.c
```
and in `gdb`:
```
set disassembly-flavor intel
```

The provided executables are position-independent (PIE). Run `gdb` from the folder that contains the source files so it can show source lines.

---

## Part 1: Arrays, Strides, and Pointer Steps (32 points)

How far does a pointer move, and how does the compiler find the right element of a two-dimensional array? You will predict first, then check with the tools.

### 1A. How far does `p + 1` move? (10 points)

`steps.c` creates five pointers of different types. Read it, but do **not** run it yet.

**i. Predict (0 points; completeness only; not graded).** For each pointer type, how many bytes does `p + 1` move past `p`?

| Pointer type | Bytes moved by `p + 1` |
|---|---|
| `char *` | |
| `short *` | |
| `int *` | |
| `long *` | |
| `short (*)[5]` | |

**ii. Verify (4 points).** Compile and run `steps.c`. Paste its output.

**iii. (6 points).** In `gdb`, break at the first `printf` line (`break 19`), then `run`. Print `*(pr + 1)` and `*(pr + 2)`. Paste what `gdb` prints. In one sentence, what does `pr + 1` point to?

### 1B. One lookup in a two-dimensional array (12 points)

`grid.c` has a function `cell` that returns `t[r][c]` from a `short` array with 6 columns.

**i. Calculate (3 points).** Using the formula from lecture, how many bytes is one row, and how many bytes is `&t[2][3]` past `&t[0][0]`?

**ii. Verify (3 points).** Compile `grid.c`. In `gdb`: execute `break cell`, `run`, then `up` commands to move to `main`'s frame. Next, print the distance and the value of `t[2][3]` using the following GDB commands:
```
(gdb) p (long)&t[2][3] - (long)&t[0][0]
(gdb) p t[2][3]
```
Paste the outputs to `ANSWERS.md`.

**iii. (3 points).** Still in `gdb`, run `disassemble cell`. The instructions that compute `r × (row size)` use only `add` and `shl`. Starting with `rdx` holding `r = 2` and `rax` copied from it by the `mov rax, rdx` instruction, give the value of `rax` after each of the next three arithmetic instructions (the two `add`s and the `shl`), in order.

> [!NOTE]
> The disassembled code consists of approximately 20 lines of instructions. Please ensure GDB displays all of them.
> 
> When you see the prompt like `--Type <RET> for more, q to quit, c to continue without paging--p t[2][3]`, hit the Enter key to continue.
> 
> The `shl` (Shift Left) command is a bitwise instruction that moves all the bits of a binary number or register a specified number of positions to the left.

**iv. (3 points).** Which instruction tells you the element size? What is the size, and how does it connect to your answer in i?

### 1C. Recover a function from a stripped binary (10 points)

`grid_bin` is stripped (no function names). It contains one small function that takes a two-dimensional array plus two `int` values (a row and a column), and returns a number. Run it a few times to see its behavior, for example:
```
./grid_bin 1 1
```

**Setup in Ghidra:**
1. Create a new project and import `grid_bin`. Accept the defaults. Let auto-analysis run with its default options.
2. Open the function named `entry` in the Decompile window. It passes the address of `main` as the first argument of `__libc_start_main`. Double-click that name to open `main`.
3. In `main`, find the call that is given the array and the two integers from the command line, and double-click it to open the function you will study.

**i. (3 points).** Open that function in the Listing and Decompile windows. What is the **element size** and the **number of columns** of the array? Give the numbers and say which instructions or constants show them. (The row computation may use shifts and adds instead of one multiply; you traced one like it in 1B.)

**ii. (4 points).** Write the equivalent C function. Use a prototype with a first parameter of the form `TYPE g[][N]`, and fill in `TYPE` and `N` yourself. Name the function `puzzle_one`.

**iii. (3 points).** In the Decompile window, **right-click the first parameter and choose Retype Variable**. Give it a pointer-to-row type of your own answer (for example, a pointer to a row of 3 shorts is written `short[3] *`). Paste the decompiler output **before** and **after** the retype.

---

## Part 2: Globals and Strings (30 points) 

Where do globals live, how does the code find them, and how do strings differ from each other in memory?

### 2A. Which section? (12 points)

`globals.c` defines several globals. Read its declarations (not the functions yet).

**i. (6 points).** Which section holds each item: `.data`, `.rodata`, or `.bss`?

| Item | Section |
|---|---|
| `ticks` | |
| `buckets` | |
| `version` | |
| `calls` | |
| `motto` (the pointer variable) | |
| the characters of `"keep digging"` | |

**ii. Verify (3 points).** Run:
```
nm -n globals_bin | grep -E ' (ticks|buckets|version|calls|motto)$'
objdump -s -j .rodata globals_bin
objdump -s -j .data globals_bin
```
Paste the `nm` lines. From the `objdump` output, give the **address** where the characters of `"keep digging"` start. Say which of your predictions, if any, were wrong.

**iii. Verify (3 points).** Dump `.data` with `objdump -s -j .data globals_bin`. Find the 8 bytes of `motto`, and read them as one little-endian value. Give that value, and say whether it matches the address you found in ii.

### 2B. RIP-relative addressing and PIE (10 points)

Disassemble the function `touch` with:
```
objdump -d -M intel --no-show-raw-insn globals_bin
```
(it is near the top of the `.text` output). Do the arithmetic **by hand**, then compare with the `# address <name>` comment that `objdump` adds.

**i. (5 points).** Take the **first** instruction in `touch` that reads a global. Give: (a) the address of the instruction that follows it, (b) its displacement, and (c) the sum, and say which global the sum is.

**ii. (5 points).** Take the **last** instruction in `touch` that writes a global. Give the same three values and name the global.

### 2C. Two kinds of string (8 points)

`strings.c` has two strings: `char *msg` and `char name[]`.

**i. (2 points).** Dump `.rodata` and `.data` of `strings_bin` with `objdump -s -j .rodata -j .data strings_bin`. Which section holds the characters of `"hello, world"`, and which holds the characters of `"analyst"`?

**ii. Predict, then verify (3 points).** `./strings_bin 1` writes to `name[0]`; `./strings_bin 2` writes to `msg[0]`. Predict which of the two runs will crash, and why. Then run both. Give your prediction, what happened, and the explanation.

**iii. (3 points).** In `gdb`: `break show`, `run 0`, then `x/8xb name`. Record the 8 bytes. Now run `set var name[3] = 0`, then `continue`. What does the program print for `name`, and why?

---

## Part 3: A Mystery Input (38 points)

`mystery_bin` takes one argument, a name, and prints either `access: denied` or `access: granted`:
```
./mystery_bin Alice
```
Something about it is odd. You will find out what, and why, using only `gdb` and the disassembly.

### 3A. Try some inputs (5 points)

Use a name made of repeated `A`s. For example, a 24-character name:
```
./mystery_bin $(python3 -c 'print("A"*24)')
```
**Do not use names longer than 31 characters in this lab;** next week's lab explains why.

Record what the program prints for each length:

| Length | Output |
|---|---|
| 4 | |
| 16 | |
| 24 | |
| 28 | |
| 30 | |
| 31 | |

### 3B. Find the layout (10 points)

Open the **executable file** (`mystery_bin`) in `gdb` and disassemble the function `check`.

**i. (5 points).** The function calls `strcpy`, whose first argument (in `rdi`) is the place the name is copied to. Find the stack slot (`[rbp-0x..]`) that holds that destination. Then find the stack slot whose value is returned from `check` (it is loaded into `eax` right before the function ends). Give both slots.

**ii. (5 points).** How many bytes lie between the start of the destination slot and the returned slot? Show how you confirmed this in `gdb`: set a breakpoint just after the `call` to `strcpy` (use `break *check+OFFSET`, with the offset taken from the disassembly), `run` with any short name, and print both addresses, for example `p $rbp-0x8`. Paste your commands and output.

### 3C. Predict the flip (10 points)

`strcpy` copies every character of the name **plus one extra byte**, the string terminator (a 0 byte).

**i. Predict (3 points).** Using your answer to 3A and 3B, what is the **smallest** name length (at most 31) for which the program prints `access: granted`?

**ii. Verify (7 points).** Run the program with your predicted length and with one less. Paste both outputs. Then, in `gdb`, stop just after `strcpy` for each of those two names and print the 4-byte value in the returned slot with `x/dw`. Paste both values.

### 3D. Now read the source (13 points)

Open `mystery.c`.

**i. (4 points).** The source declares the name array with 16 bytes. Your result in 3C is larger than 16. Explain the difference.

**ii. (4 points).** In one or two sentences, describe what is wrong with this function. (You do not need any special vocabulary; describe what the code does that it should not.)

**iii. (5 points).** Write **one line** of C to replace the `strcpy` line so that a long name can no longer reach the returned variable.

---

## Hints and Tips

- `p/x`, `p/d`, and `p/u` print a value as hexadecimal, signed decimal, and unsigned decimal. In gdb, `$eax` is the low 32 bits of `rax`.
- `break *ADDRESS` (with the asterisk) breaks at an exact instruction. Use the asterisk whenever you want to stop at a particular instruction rather than a source line. `break *function+offset` works too.
- Programs you compile yourself, and the provided executables, are position-independent, so their run-time addresses change every time (ASLR) outside `gdb`; inside `gdb` they are fixed at a base such as `0x555555554000`. Use `function+offset` in `gdb`, not absolute addresses. `nm`, `objdump`, and Ghidra show addresses **relative to the start of the program** (Ghidra adds a base of `0x100000`). 
- After `run`, the program stays loaded, and breakpoints remain until you `delete` them. Type `quit` to leave gdb.
- To run a program with an argument inside `gdb`, write `run ARG`.
- Ghidra names things generically (`FUN_00101234`, `param_1`, `local_c`, `undefined4`). The exact names and types can differ slightly between Ghidra versions; don't worry about matching anyone else's output character-for-character.
- If Ghidra's Decompile window is missing, open it from Window > Decompile.
- **Text too small in Ghidra?** Click inside the Listing (or Decompile) window and press **Ctrl-+** to make the text bigger, **Ctrl--** to make it smaller. This resets when you close Ghidra. To keep your size, open **Edit > Theme > Configure**, click **Save** (bottom of the window), and give the theme a new name. **Don't overdo it:** the Listing's columns have a fixed width, so the bigger the text, the more names, operands, and addresses get cut off with `...`. One or two steps is usually enough.
- **Something in the Listing shows as `...`** (an operand, a name, or an address)? **Hover the mouse over it**: Ghidra pops up the full text. If most lines are cut off, press **Ctrl--** once or twice to shrink the text. When you copy an address into gdb, always use the **full** address.

## Deliverables

- `ANSWERS.md`, completed, with all requested command output, pasted decompiler output, and answers for Parts 1-3.

## Grading Criteria

| Part | Points |
|---|---|
| Part 1: Arrays, Strides, and Pointer Steps | 32 |
| Part 2: Globals and Strings | 30 |
| Part 3: A Mystery Input | 38 |
| **Total** | **100** |
