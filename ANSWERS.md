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
| char *       |                      |
| short *      |                      |
| int *        |                      |
| long *       |                      |
| short (*)[5] |                      |
```

**ii. Verify (4 points).** Paste the output of `steps`.

**Answer:**
```
Please write your answer here and delete this sentence.
```

**iii. (6 points)** Output of `p *(pr + 1)` and `p *(pr + 2)`, and one sentence on what `pr + 1` points to.

**Answer:**
```
Please write your answer here and delete this sentence.
```

### 1B. One lookup in a two-dimensional array (12 points)

**i. Predict (3 points)**

**Answer:**
```
bytes in one row: ______
&t[2][3] - &t[0][0] (bytes): ______
```

**ii. Verify (3 points).** Paste your `gdb` output.

**Answer:**
```
Please write your answer here and delete this sentence.
```

**iii. (3 points)** Value of `rax` after each of the three instructions.

**Answer:**
```
after the first add: ______
after the second add: ______
after the shl: ______
```

**iv. (3 points)**

**Answer:**
```
Please write your answer here and delete this sentence.
```

### 1C. Recover a function from a stripped binary (10 points)

**i. (3 points)**

**Answer:**
```
element size (bytes): ______
number of columns: ______
evidence: Please write your explanation here and delete this sentence.
```

**ii. (4 points)**

**Answer:**
```c
Please write your answer here and delete this sentence and example code below.
int puzzle_one() {
  return 0;
}
```

**iii. (3 points)** Decompiler output before and after the retype.

**Answer:**
```
before:

after:

```

---

## Part 2: Globals and Strings

### 2A. Which section? (12 points)

**i. Predict (6 points)**

```
| Item                               | Section |
|------------------------------------|---------|
| ticks                              |         |
| buckets                            |         |
| version                            |         |
| calls                              |         |
| motto (the pointer variable)       |         |
| the characters of "keep digging"   |         |
```

**ii. Verify (3 points)**

**Answer:**
```
nm output:

address where "keep digging" starts: ______
predictions that were wrong: Please write your answer here and delete this sentence.
```

**iii. (3 points)**

**Answer:**
```
8 bytes of motto: Please write your answer here and delete this sentence.
value (little-endian): ______
matches the address in ii? ______
```

### 2B. RIP-relative addressing and PIE (10 points)

**i. (5 points)**

**Answer:**
```
(a) address of the next instruction: ______
(b) displacement: ______
(c) sum: ______   which global: ______
```

**ii. (5 points)**

**Answer:**
```
(a) address of the next instruction: ______
(b) displacement: ______
(c) sum: ______   which global: ______
```

### 2C. Two kinds of string (8 points)

**i. (2 points)**

**Answer:**
```
"hello, world" is in: ______
"analyst" is in: ______
```

**ii. Predict, then verify (3 points)**

**Answer:**
```
Prediction (which run crashes, and why): Please write your answer here and delete this sentence.
What happened with ./strings_bin 1: ______
What happened with ./strings_bin 2: ______
Explanation: Please write your explanation here and delete this sentence.
```

**iii. (3 points)**

**Answer:**
```
8 bytes of name: ______
Output for name after set var name[3] = 0: ______
Explanation: Please write your explanation here and delete this sentence.
```

---

## Part 3: A Mystery Input

### 3A. Try some inputs (5 points)

```
| Length | Output |
|--------|--------|
| 4      |        |
| 16     |        |
| 24     |        |
| 28     |        |
| 30     |        |
| 31     |        |
```

### 3B. Find the layout (10 points)

**i. (5 points)**

**Answer:**
```
destination slot of the copy: [rbp-0x__]
slot returned from check:     [rbp-0x__]
```

**ii. (5 points)**

**Answer:**
```
bytes between the two slots: ______
gdb commands and output:
```

### 3C. Predict the flip (10 points)

**i. Predict (3 points)**

**Answer:**
```
smallest length that prints granted: ______
```

**ii. Verify (7 points)**

**Answer:**
```
Run with the predicted length:
Run with one less:
x/dw of the returned slot (predicted length): ______
x/dw of the returned slot (one less): ______
```

### 3D. Now read the source (13 points)

**i. (4 points)**

**Answer:**
```
Please write your answer here and delete this sentence.
```

**ii. (4 points)**

**Answer:**
```
Please write your answer here and delete this sentence.
```

**iii. (5 points)**

**Answer:**
```c
Please write your answer here and delete this sentence and example code below.
strcpy(name, input);
```

---

## Feedback (optional)

Anything unclear, too hard, too easy, or broken in this lab? This section is not graded.

**Answer:**
```
```
