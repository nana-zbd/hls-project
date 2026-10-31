# Vitis HLS Automated Testing Project

## Project Overview
This project provides an automated Python + Tcl framework to run Vitis HLS workflows (C Simulation and C Synthesis) and automatically determine if the C++ code passes or fails.

## Directory Structure
```text
├── docs/               # Authorization documents
├── scripts/            # Automation scripts
│   ├── run_test.py     # Python automation entry point
│   └── run_hls.tcl     # Tcl script to control Vitis HLS
├── src/                # Source code and testbenches
│   ├── fir.cpp         # Correct FIR implementation
│   ├── fir_error_logic.cpp   # Logic error test case
│   ├── fir_error_syntax.cpp  # Syntax error test case
│   ├── fir_tb.cpp      # Testbench file
│   └── fir.h           # Header file
└── README.md