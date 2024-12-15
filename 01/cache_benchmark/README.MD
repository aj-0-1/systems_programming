```
graph TD
    subgraph CPU["CPU Processing"]
        C[CPU]
        L1[L1 Cache<br/>~64KB, ~1ns]
        L2[L2 Cache<br/>~256KB, ~4ns]
        L3[L3 Cache<br/>~8MB, ~10ns]
        M[Main Memory<br/>Many GB, ~100ns]
    end

    C --> L1
    L1 --> L2
    L2 --> L3
    L3 --> M

    subgraph Access["Memory Access Patterns"]
        G[Cache-Friendly<br/>Sequential Access]
        B[Cache-Unfriendly<br/>Random Access]
    end

    style C fill:#f96
    style L1 fill:#ff9
    style L2 fill:#9f9
    style L3 fill:#99f
    style M fill:#f99
    style G fill:#9f9
    style B fill:#f99
```  

Cache Lines:
- Fixed-size block (typically 64 bytes) of memory loaded into cache
- When you access one byte, entire cache line is loaded
- Sequential access = better cache utilization


Cache Misses:
- Occur when data isn't in cache and must be fetched from main memory
- ~100x slower than cache hits
- Common in random access patterns


Cache-Aware Sorting:
- Break data into cache-sized blocks
- Sort blocks individually (they fit in cache)
- Merge blocks efficiently using cache-friendly patterns

// Random access pattern
for (int i = 0; i < size; i += 64) {
    sum += array[i];  // Likely cache miss each time
}

// Sequential access within blocks
for (int block = 0; block < size; block += BLOCK_SIZE) {
    for (int i = block; i < block + BLOCK_SIZE; i++) {
        sum += array[i];  // Better cache utilization
    }
}

What Compilers Can Optimize:
- Loop transformations
- Data structure alignment
- Array padding
- Function inlining

What Compilers Cannot Optimize:
- Algorithm-level decisions
- Data structure layout changes
- Complex memory access patterns
- Cache-aware algorithm transformations

Best Practices:

Data Access:
- Access memory sequentially when possible
- Process data in cache-line-sized blocks
- Minimize random memory jumps


Data Structures:
- Keep related data together in memory
- Consider cache line size when designing structures
- Use array-based structures for better cache utilization


Algorithms:
- Break large problems into cache-sized blocks
- Sort or process blocks that fit in cache
- Merge results using cache-friendly patterns

Performance Impact:
- Cache-aware algorithms can be 2-3x faster
- Most significant for large datasets
- Critical for performance-sensitive applications
