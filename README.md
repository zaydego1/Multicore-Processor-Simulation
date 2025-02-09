# Multicore-Processor-Simulation

### How to Build ###

1. Install an IDE compatible with C++.
2. Install a C++ compiler (clang, Visual Studio(also install msys with mingwin32), g++).
3. Install CMake.
4. Add all of these downloads to path (as needed).
5. Clone repository.
6. Open repository in IDE and clone the easylogger library in the extern folder.
7. Run or Debug!

### Breakdown of Components:

1. **`cpu.cpp`**:
   - Initializes processors
   - Creates the instruction queue


2. **`processor.cpp`**:
   - Creates cores
   - Creates L2 Cache
   - Currently responsible for scheduling instructions (will be handled by task manager in the future) 

3. **`core.cpp`**:
   - Executes instructions in a thread safe manner
   - Creates L1 Caches and interfaces with L2 Caches and Memory
   - Collaborates with processor to schedule instructions (will be task manager)

4. **`cache.cpp`**:
   - Interface for creating L1 and L2 caches
   - Implemented as map, storing an address and a node in a doubly linked list
   - Handles MESI protocol and is implemented as a LRU Cache
   - Thread safe operations

5. **`memory.cpp`**:
   - Similar to cache except not implemented using LRU
   - Stores data in a map as an address and node with address and data (repurposes node class)
   - Thread safe operations
  
6. **`node.cpp`**:
   - Used a part of memory storage
   - Implemented as doubly linked list with pointers to address and data
   - Built in remove from end operation (used for LRU Cache)

7. **`main.cpp`**:
   - Responsible for initializing CPU and main memory
   - Will eventually take a file input to customize CPU settings such as number of processors/cores/cache sizes.
   - Will accept file input (same one) to feed instructions to CPU
  

