# Parallel Block Lattice Reduction (Para-BLR)

This repository implements a **parallel version** of the Block Lattice Reduction (BLR) algorithm, using **OpenMP** for multicore processing. It is based on my MSc research at McGill University and extends the original [BLR](https://github.com/yijinwang7/BLR) project.

---

## 🔍 Description

The parallel algorithm partitions the lattice basis into blocks and reduces each block concurrently. The goal is to accelerate lattice reduction while preserving high-quality output, especially in floating-point settings.

Key features:
- Parallelism via **OpenMP**
- Compatible with **floating-point BLR**
- Tested on **Compute Canada’s supercomputers** (Beluga, Narval)

---

## 📁 Files

- `paraLLLHy.cpp` — Core implementation of the parallel BLR algorithm

---

## ⚙️ Usage

You can compile the program using any C++11-compatible compiler with OpenMP enabled. For example:


