```
High Address    +------------------+
                |       Stack      |  ↓ Stack grows down
                |        ↓        |
                |                 |
                |        ↑        |
                |       Heap      |  ↑ Heap grows up
                |                 |
                |   Uninitialized |
                |  Data (BSS)     |  Static/global uninitialized variables
                |                 |
                |   Initialized   |
                |      Data       |  Static/global initialized variables
                |                 |
                |      Text       |  Program code
Low Address     +------------------+
```

TEXT Segment:

- Contains executable instructions
- Read-only to prevent accidental modification
- Shareable so multiple instances of a program share same code
- Size fixed at compile time


Initialized Data Segment (DATA):

- Contains explicitly initialized global/static variables
- Takes actual memory in executable file
- Loaded into RAM when program starts
- Example: static int x = 5;


Uninitialized Data Segment (BSS - Block Started by Symbol):

- Contains uninitialized global/static variables
- Doesn't take space in executable file
- Automatically initialized to zero/null at program start
- Example: static int x;


Heap Segment:

- Dynamic memory allocation
- Managed by malloc/free (C) or new/delete (C++)
- Can grow/shrink during runtime
- No automatic cleanup - must be managed manually
- Can become fragmented
- Slower access than stack


Stack Segment:

- LIFO (Last In First Out) data structure
- Automatic allocation/deallocation
- Contains:
 - Local variables
 - Function parameters
 - Return addresses
 - Saved registers
- Fixed maximum size (stack overflow if exceeded)
- Very fast access
- Each thread gets its own stack



Output:

=== Memory Layout ===

DATA Segment:
  global_init:  0x5c7f173be010
  static_init:  0x5c7f173be014

BSS Segment:
  global_uninit: 0x5c7f173be01c
  static_uninit: 0x5c7f173be020

Stack Segment:
  stack_var:     0x7fffc08d7c64

Stack Growth:
Stack variable at depth 3: 0x7fffc08d7c44
Stack variable at depth 2: 0x7fffc08d7c14
Stack variable at depth 1: 0x7fffc08d7be4
Stack variable at depth 0: 0x7fffc08d7bb4

Heap Segment:
  heap_var1:     0x5c7f178916b0
  heap_var2:     0x5c7f178916d0



Key Observations:

- Stack and heap grow toward each other
- Stack addresses are much higher than heap/data (7fff vs 5c7f)
- Sequential heap allocations are contiguous in this case
- Stack frames have consistent size in the recursive calls
