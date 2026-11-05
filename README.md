# Tay Nguyen Campaign Simulation (CO1027 - Assignment 1)

A C++ simulation program inspired by the historic **1975 Tay Nguyen Campaign**, developed as Assignment 1 for the **Programming Fundamentals (CO1027)** course at Ho Chi Minh City University of Technology (HCMUT - VNU-HCM), Spring 2025 (Semester 242).

## Overview

This project implements core programming concepts in C++11—including file I/O, string manipulation, 1D/2D arrays, and control structures—to simulate five key military operations during the Tay Nguyen Campaign:

- **Task 0 — Reading Input Data (`readFile`, `parseSoldierArray`):** Parses campaign configuration files containing troop counts across 17 military ranks (`LF1`, `LF2`), combat experience (`EXP1`, `EXP2`), supply resources (`T1`, `T2`), and historical event codes (`E`), clamping values to valid ranges.
- **Task 1 — Force Assembly (`gatherForces`):** Computes the combined military force strength of two army corps using rank-based weight coefficients.
- **Task 2 — Deception Strategy (`determineRightTarget`, `decodeTarget`):**
  - Identifies actual primary targets (*Buon Ma Thuot*, *Duc Lap*, *Dak Lak*, *National Route 21*, *National Route 14*) or decoy operations (*Kon Tum*, *Pleiku*, *Gia Lai*) by extracting embedded numerical IDs.
  - Decrypts classified target messages using either a **Caesar Cipher** or **String Reversal** depending on corps intelligence experience.
- **Task 3 — Logistics Management (`manageLogistics`):** Dynamically recalculates and redistributes supply units (`T1`, `T2`) based on force ratios, experience levels, and historical event codes (`E`).
- **Task 4 — Attack Planning (`planAttack`):** Evaluates remaining army strength after engaging enemy strongholds across a `10x10` battlefield matrix with alternating row formulas.
- **Task 5 — Supply Reinforcement (`resupply`):** Finds the optimal 5-cell combination from a `5x5` supply matrix that meets or exceeds a supply shortfall while minimizing total excess.

## Project Structure

```text
.
├── include/
│   ├── main.h                          # Allowed standard library includes
│   └── tay_nguyen_campaign.h           # Function declarations for Tasks 0-5
├── src/
│   ├── main.cpp                        # Entry point and test runner
│   └── tay_nguyen_campaign.cpp         # Implementation of Tasks 0-5
├── specs/
│   ├── 242_CO1027_Assignment_1_EN.pdf  # Assignment specification (English)
│   └── 242_CO1027_Assignment_1_VI.pdf  # Assignment specification (Vietnamese)
├── tests/
│   └── tnc_tc_01_input                 # Standard sample input testcase
├── .gitignore                          # Git ignore rules
├── LICENSE                             # MIT License
├── README.md                           # Documentation
└── run.sh                              # Build and run script
```

## Getting Started

### Prerequisites

- A C++ compiler supporting **C++11** (e.g., `g++` or `clang++`).

### Build & Run

Compile and run using `g++`:

```bash
g++ -o main src/main.cpp src/tay_nguyen_campaign.cpp -I include -std=c++11
./main
```

Or pass a specific test input file:

```bash
./main tests/tnc_tc_01_input
```

Or execute the provided shell script:

```bash
bash run.sh
```

## License

This project is licensed under the [MIT License](LICENSE).
