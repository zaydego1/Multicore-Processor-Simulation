# Multicore-Processor-Simulation

### Breakdown of Components:

1. **`processor.cpp`**:
   - This file simulates the behavior of each processor core.
   - It fetches instructions, executes them, and handles the interaction with the cache/memory system.
   - It can also include mechanisms for handling pipeline execution if you're simulating a pipelined processor.
   - Worked on by Isaiah (for ticket explanation)

2. **`cache.cpp`**:
   - Implements cache memory for each core.
   - Includes cache lookup, handling cache hits and misses, and cache replacement policies (e.g., LRU).
   - Interfaces with the **cache coherence protocol** to ensure consistency across cores.

3. **`memory.cpp`**:
   - Simulates main memory and manages how data is fetched when it's not found in the cache.
   - Models the memory hierarchy (L1, L2, L3 caches, main memory).
   - Handles memory requests from the processor.

4. **`coherence.cpp`**:
   - Implements the cache coherence protocol, such as MESI or MOESI.
   - Ensures consistency between caches on different cores.
   - Handles state transitions (e.g., "Modified", "Exclusive", "Shared", "Invalid" states in MESI) and broadcast communication between cores.

5. **`synchronization.cpp`**:
   - Implements mechanisms for synchronizing threads or processes, such as locks, barriers, and atomic operations.
   - Ensures that shared data is accessed correctly and without race conditions.

6. **`task_manager.cpp`**:
   - Manages the scheduling of tasks across multiple cores.
   - Assigns tasks to cores, simulates context switching if necessary, and handles workload distribution.
   - Optionally simulates different scheduling algorithms (e.g., round-robin, load-balancing).

7. **`thread.cpp`**:
   - Simulates individual threads that execute on the cores.
   - Manages thread state (running, blocked, waiting) and tracks progress through the instruction set.
   - Communicates with the task manager to be scheduled on the available cores.

8. **`logger.cpp`**:
   - Responsible for logging simulation events (e.g., cache hits/misses, memory accesses, thread context switches).
   - Can be used to analyze the performance of your simulation (e.g., throughput, cache efficiency).

### Key Features to Include:

- **Cache Coherence Simulation**: Implement a full cache coherence protocol (e.g., MESI or MOESI). Track and log state changes between caches and resolve conflicts.
  
- **Memory Hierarchy**: Model a multi-level cache system (L1, L2, and possibly L3) and the interactions between caches and main memory.

- **Thread Synchronization**: Ensure correct access to shared memory with locks or atomic operations.

- **Task Scheduling**: Implement a basic scheduler to manage the execution of multiple threads on different cores.

### Testing Strategy:
- **Unit Tests**: Test individual modules (processor, cache, memory, etc.) to ensure they behave as expected.
- **Integration Tests**: Simulate a full multi-core system with realistic workloads to verify correct interaction between components (e.g., cache coherence working with memory hierarchy).
- **Performance Testing**: Measure and analyze the performance of your multi-core simulation in terms of throughput, cache hit/miss ratios, and thread execution time.

### Additional Considerations:
- **Data Visualization**: You could optionally add a simple GUI or logging system to visualize the state of each core, the cache states, and memory access patterns in real-time.
  
- **Benchmarking**: Use synthetic or real-world benchmarks to evaluate your multi-core system's performance, such as comparing different cache sizes, memory access times, or coherence protocol efficiencies.

This project structure will help organize your code and allow for modular development and testing of each component in the multi-core processor simulation.
