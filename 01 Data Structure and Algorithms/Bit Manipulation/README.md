
# 🔧 Bit Manipulation Cheat Sheet

Quick reference guide for essential and practical bit manipulation tricks used in coding interviews and competitive programming.

---

## 📌 XOR Tricks

### ✅ `num ^ 0 = num`
- **Use Case**: Initialize a result variable for XOR operations.
- **Effect**: Doesn't change the number.
```cpp
int result = 0;
result ^= num; // same as result = num;
```

### ✅ `num ^ num = 0`
- **Use Case**: Pairs cancel out. If a number appears an **even number of times**, XOR will cancel it.
- **Common Pattern**: Finding the element that appears only once.
```cpp
int result = 0;
for (int num : arr) result ^= num;
// result now holds the unique number
```

---

## 📌 Bit Checking and Manipulation

### ✅ Check if a bit is **set**
```cpp
if (num & (1 << position)) {
    // Bit at 'position' is set
}
```

### ✅ Set a bit (make it 1)
```cpp
num |= (1 << position);
```

### ✅ Unset a bit (make it 0)
```cpp
num &= ~(1 << position);  // ❗ use bitwise NOT to unset
```

---

## 📌 Operator Precedence & Parentheses

### ✅ Always use parentheses when using bitwise operators in conditionals
```cpp
if ((b & c) == 0) {
    // Correct usage
}
```
> ⚠️ Bitwise `&`, `|`, `^` have **lower precedence** than `==`, `!=`, etc.

---

## 📌 Bit Comparison Details

### ❌ Don't compare `(num & (1 << pos)) == 1`
- That value is not necessarily `1`; it’s a power of 2 (like `4`, `8`, etc.)
```cpp
if (num & (1 << pos)) // ✅ correct
```

---

## 📌 Unsetting the Last Set Bit

### ✅ `n & (n - 1)`
- **Effect**: Unsets the **rightmost set bit** of `n`.

```cpp
n = n & (n - 1);
```

### 🧮 Count number of set bits in `n`
```cpp
int count = 0;
while (n) {
    n = n & (n - 1);
    count++;
}
```

### 🔍 Check if a number is a **power of 2**
```cpp
if (n && (n & (n - 1)) == 0) {
    // n is a power of 2
}
```

---

## 🧠 Pro Tips

- Use `1 << k` to isolate or target the `k-th` bit (0-based index).
- When unsetting bit, don't forget **bitwise NOT (`~`)** when unsetting. (I often do forget this!)
