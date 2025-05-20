# Parallel Block Lattice Reduction (Para-BLR)

This repository implements a **parallel version** of the Block Lattice Reduction (BLR) algorithm, using **OpenMP** for multicore processing. It is based on my MSc research at **McGill University**, and is intended as an extension of the original [BLR project](https://github.com/yijinwang7/BLR).

---

## 🔍 Description

The parallel algorithm divides the lattice basis into multiple blocks and reduces them concurrently using OpenMP. The design accelerates lattice reduction while preserving the quality of output, especially in floating-point settings.

### ✨ Key Features
- Parallel execution via **OpenMP**
- Compatible with the **floating-point BLR framework**
- Demonstrated on **Compute Canada supercomputers**: Beluga, Narval

---

## 📁 Files

- `paraLLLHy.cpp` – Core implementation of the parallel block lattice reduction algorithm

---

## ⚙️ Usage

You can compile the program using any C++11-compatible compiler with OpenMP support.

