Core Concept: Virtual memory provides a layer of indirection between memory addresses programs use and actual physical RAM locations.

Components:

- Virtual Address Space: What programs see
- Physical Memory: Actual RAM
- MMU (Memory Management Unit): Hardware that handles translation
- Page Tables: Map virtual pages to physical frames

How Memory is Organized:

- Memory is divided into fixed-size pages (typically 4KB)
- Virtual pages map to physical frames
- Not all pages need to be in RAM (some can be on disk/swap)
- Pages have protection flags (read/write/execute)

```
Virtual Address Translation:
Program A                         Program B
Virtual: 0x0000                  Virtual: 0x0000
    ↓ MMU translates                 ↓ MMU translates
Physical: 0x54A71000             Physical: 0x76B82000
```

// Both programs use address 0x0000, but get different physical locations!

Why Programs Start at 0:

- Every program gets its own complete virtual address space
- Programs always start counting from 0 for simplicity
- Makes programming and pointer arithmetic predictable
- Compiler doesn't need to consider different base addresses
- Your code doesn't need to know its actual physical location

Why Page Alignment Matters:

- Memory can only be mapped at page boundaries
- Hardware memory protection works at page level
- Some CPU instructions require aligned addresses
- Memory operations are often more efficient when aligned
- That's why mmap() always returns page-aligned addresses, and we verify this with the modulo check

Benefits:

- Memory Isolation: Programs can't access each other's memory
- Memory Efficiency: Physical memory can be shared
- Memory Protection: Control over page permissions
- Larger Address Space: Use more memory than physically available
- Simplifies programming: Every program thinks it starts at 0
