# CYB4551 Lab 5 — Answers

**Total: 100 points**

**Name:**

**Section:**

## Instructions

- Answer every question directly in this file, in the order they appear in `README.md`.
- Write every answer, including short explanations, in the code block after **Answer:**. Keep lines under about 80 characters.
- For fillable tables, copy the table from `README.md` and fill in the blank cells (already copied below).
- Save and **rename** this file with your name in the filename (e.g. `ANSWERS_Zhonghao_Liao.md`) and submit it as-is.

---

## Part 1: Arrays, Strides, and Pointer Steps

### 1A. How far does `p + 1` move? (10 points)

**i. Predict (0 points; completeness only; not graded)**

```
| Pointer type | Bytes moved by p + 1 |
|--------------|----------------------|
| char *       | 1 |
| short *      | 2 |
| int *        | 4 |
| long *       | 8 |
| short (*)[5] | 10 |
```

**ii. Verify (4 points).** Paste the output of `steps`.

**Answer:**
```
char  *       : p+1 is 1 bytes past p
short *       : p+1 is 2 bytes past p
int   *       : p+1 is 4 bytes past p
long  *       : p+1 is 8 bytes past p
short (*)[5] : p+1 is 10 bytes past p
```

**iii. (6 points)** Output of `p *(pr + 1)` and `p *(pr + 2)`, and one sentence on what `pr + 1` points to.

**Answer:**
```
*(pr + 1): {21, 22, 23, 24, 25}
*(pr + 2): {31, 32, 33, 34, 35}
pr + 1 seems to point to an array of 5 elements of some sort of integer format.
```

### 1B. One lookup in a two-dimensional array (12 points)

**i. Predict (3 points)**

**Answer:**
```
bytes in one row: it is 2 * 6 bytes, aka 12
&t[2][3] - &t[0][0] (bytes): 30
```

**ii. Verify (3 points).** Paste your `gdb` output.

**Answer:**
```
(gdb) p (long)&t[2][3] - (long)&t[0][0]
$2 = 30
```

**iii. (3 points)** Value of `rax` after each of the three instructions.

**Answer:**
```
after the first add: 4
after the second add: 6
after the shl: 24
```

**iv. (3 points)**

**Answer:**
```
The scale factor in movzx eax, WORD PTR [rdx+rax*2]
```

### 1C. Recover a function from a stripped binary (10 points)

**i. (3 points)**

**Answer:**
```
element size (bytes): 4
number of columns: 5
evidence: For this we have to look not just in main, but the interior function within main that actually does the calculation. This takes in a pointer to the array, a row index, and a column index. First it multiples the row index by 5 then 4 (through shifts and adds as to avoid having to make actual mul calls). This tells us that each row is 5 elements long, and each element is 4 bytes long. We can assume that it isn't vice versa, as we can tell the array is made of up 4 byte units by how each element in the array is manually set with dwords.
```

**ii. (4 points)**

**Answer:**
```c
int puzzle_one(int ptr[][4], int row, int col) {
    return ptr[row][col] + ptr[row][0];
}
```

**iii. (3 points)** Decompiler output before and after the retype.

**Answer:**
```
before:
int FUN_00101189(long param_1,int param_2,int param_3)

{
  return *(int *)(param_1 + (long)param_2 * 0x14) +
         *(int *)((long)param_2 * 0x14 + param_1 + (long)param_3 * 4);
}

after:
int puzzle_one(int (*arr) [5],int row,int col)

{
  return arr[row][0] + arr[row][col];
}

```

---

## Part 2: Globals and Strings

### 2A. Which section? (12 points)

**i. Predict (6 points)**

```
| Item                               | Section |
|------------------------------------|---------|
| ticks                              |  .data   |
| buckets                            |  .bss |
| version                            |  .rodata   |
| calls                              |  .bss  |
| motto (the pointer variable)       |  .data   |
| the characters of "keep digging"   |  .rodata  |
```

**ii. Verify (3 points)**

**Answer:**
```
nm output:
0000000000002008 R version
0000000000004010 D ticks
0000000000004030 D motto
0000000000004044 b calls
0000000000004050 B buckets
address where "keep digging" starts: 200c
predictions that were wrong: N/A
```

**iii. (3 points)**

**Answer:**
```
8 bytes of motto: 
value (little-endian): 0c200000
matches the address in ii? Yes
```

### 2B. RIP-relative addressing and PIE (10 points)

**i. (5 points)**

**Answer:**
```
(a) address of the next instruction: 0x1158
(b) displacement: 0x2eb8
(c) sum: 4010   which global: ticks
```

**ii. (5 points)**

**Answer:**
```
(a) address of the next instruction: 1181
(b) displacement: 0x2ec3
(c) sum: 4044   which global: calls
```

### 2C. Two kinds of string (8 points)

**i. (2 points)**

**Answer:**
```
"hello, world" is in: .rodata
"analyst" is in: .data
```

**ii. Predict, then verify (3 points)**

**Answer:**
```
Prediction (which run crashes, and why): I think mode 2 will crash, as "hello_world" is stored in read-only memory, and trying to modify read only memory sounds like a great way to crash.
What happened with ./strings_bin 1: Printed the values of msg and Analyst
What happened with ./strings_bin 2: Crash with error 139 (SIGSEGV demanded by OS)
Explanation: When the program tries to overwrite part of the string pointed to by msg, it tries to change read only memory. This causes a seg fault, being forced to exit by the OS as opposed to the program willingly exiting (an error which forces it to exit as opposed to allowing the program to exit gracefully is 128 + the regular error code).
```

**iii. (3 points)**

**Answer:**
```
8 bytes of name: 0x616e616c79737400
Output for name after set var name[3] = 0: ana
Explanation: Since the null character (0x00) was set to an earlier point in the string, and the function used to print this string relies on null termination to know when the string is done, once it got to the 0x00 at byte 3, it thought it was the end of the string and stopped looking for more to print.
```

---

## Part 3: A Mystery Input

### 3A. Try some inputs (5 points)

```
| Length | Output |
|--------|--------|
| 4      | denied |
| 16     | denied |
| 24     | denied |
| 28     | denied |
| 30     | granted|
| 31     | granted|
```

### 3B. Find the layout (10 points)

**i. (5 points)**

**Answer:**
```
destination slot of the copy: [rbp-0x20]
slot returned from check:     [rbp-0x4]
```

**ii. (5 points)**

**Answer:**
```
bytes between the two slots: 28 (0x1c)
gdb commands and output: p (long long)((void*)$rbp - 0x4) - (long long)((void*)$rbp - 0x20)
$7 = 28
```

### 3C. Predict the flip (10 points)

**i. Predict (3 points)**

**Answer:**
```
smallest length that prints granted: 29
```

**ii. Verify (7 points)**

**Answer:**
```
Run with the predicted length:
src/mystery_bin $(python -c 'print("A"*29)')
hello, AAAAAAAAAAAAAAAAAAAAAAAAAAAAA
access: granted
Run with one less:
src/mystery_bin $(python -c 'print("A"*28)')
hello, AAAAAAAAAAAAAAAAAAAAAAAAAAAA
access: denied
x/dw of the returned slot (predicted length): 65
x/dw of the returned slot (one less): 0
```

### 3D. Now read the source (13 points)

**i. (4 points)**

**Answer:**
```
When the compiler is marking out space in the stack, it likes to make the stack frame aligned to a 16-byte boundary. With the other stack variables, the next highest 16-byte boundary is 48 bytes. This leaves a bunch of extra space after the declared end of the char array.
```

**ii. (4 points)**

**Answer:**
```
The code should make sure the string actually fits into the char array. Without that, a user could manipulate data in the program outside of what is meant to be changed. The classic thing that should be done here is switching to strncpy or snprintf.
```

**iii. (5 points)**

**Answer:**
```c
strcpy(name, input);
//change to 
snprintf(name,sizeof(name),"%s",input); 
```

---

## Feedback (optional)

Anything unclear, too hard, too easy, or broken in this lab? This section is not graded.

**Answer:**
```
```
