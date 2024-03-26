# Operating Systems Lab Codes Repository

Welcome to our Operating Systems Lab Codes Repository! This collection has been meticulously compiled to serve as a practical resource for students, educators, and enthusiasts exploring the vast world of operating systems concepts. From process scheduling to memory management and synchronization, you'll find a variety of code examples to help illuminate complex OS theories with real-world applications.

## What's Inside

This repository contains implementations of fundamental and advanced operating systems concepts, including but not limited to:

- **Process Scheduling Algorithms:**
  - First-Come, First-Served (FCFS) (`lab5fcfs.c`)
  - Shortest Job First (SJF) (`lab5sjf.c`)
  - Round Robin (RR) (`rr.c`)
  - Priority Scheduling (`priority.c`)
  - Shortest Remaining Time First (SRTF) (`srtf.c`)
  - Multi-level Queue Scheduling (`multi.c`)
- **Memory Management:**
  - First Fit, Best Fit, Worst Fit allocation strategies (`first.c`, `best.c`, `worst.c`)
- **Page Replacement Algorithms:**
  - FIFO (`FIFO.c`)
  - Least Recently Used (LRU) (`LRU.c`)
  - Optimal Page Replacement (`OPR.c`)
- **Synchronization Problems:**
  - Producer-Consumer (`procon.c`)
  - Dining Philosophers (`dine.c`)
- **Other Concepts:**
  - Banker's Algorithm (`bankers.c`)
  - Peterson's Solution (`pete.c`)

... and many more examples covering various aspects of operating systems.

## How to Use

Each file in this repository is a standalone C program demonstrating a specific concept or algorithm related to operating systems. You can compile each program with a C compiler like GCC. For example:

```bash
gcc -o fifo FIFO.c
./fifo
```

Replace `FIFO.c` with the filename of the code example you wish to compile and run.

## Contributing

We welcome contributions from the community! Whether you'd like to add more examples, improve existing codes, or fix bugs, your input is valuable. Please feel free to fork the repository, make your changes, and submit a pull request.
