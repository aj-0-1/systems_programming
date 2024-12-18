struct Example {
    char c;    // 1 byte
    int i;     // 4 bytes
    double d;  // 8 bytes
};


Why Memory Alignment Matters

Performance: Modern CPUs read memory in fixed-size chunks (usually 4 or 8 bytes). Misaligned data requires multiple memory reads.

If an int starts at address 0x01, the CPU needs two reads to get all 4 bytes
When properly aligned, it needs just one read


Hardware Requirements: Some architectures (like ARM) can crash on misaligned access

Memory Alignment Rules

Natural Alignment: Each data type has a natural alignment equal to its size

char: 1-byte alignment
short: 2-byte alignment
int: 4-byte alignment
double: 8-byte alignment


Struct Alignment: The compiler adds padding to ensure each member is properly aligned

In our example:

char takes 1 byte, but 3 bytes of padding are added
int starts at offset 4 (properly aligned)
double starts at offset 8 (properly aligned)

Total Size: The struct's total size is padded to be a multiple of its largest alignment requirement

Our struct is 16 bytes total, not 13 (1 + 3 padding + 4 + 8)


// Misaligned (13 bytes)
struct tag_misaligned {
    char a;     
    double b;   
    int c;      
};

// Aligned (16 bytes)
struct tag_aligned {
    double b;   
    int c;      
    char a;     
};

Performance Results
Sequential Access

Misaligned: 0.002743 seconds
Aligned: 0.002761 seconds
Difference: -0.65% (negligible)

Random Access

Misaligned: 0.004575 seconds
Aligned: 0.004361 seconds
Difference: 4.91% (aligned is faster)

Key Observations

Access Patterns Matter

Sequential access shows minimal performance difference
Random access demonstrates significant benefits of alignment
Memory alignment becomes more important with unpredictable access patterns


Modern CPU Optimizations

Hardware prefetching helps with sequential access
Cache utilization is more efficient with aligned data
Misaligned access penalties are partially mitigated by modern CPUs


Size vs. Alignment Trade-off

Aligned structs may be larger due to padding
Misaligned structs save memory but may have performance penalties
The choice depends on access patterns and requirements



Best Practices

Struct Member Ordering

Order members from largest to smallest
Group similarly-sized members together
Consider cache line boundaries for large structs


Alignment Controls

Use #pragma pack carefully and only when necessary
Be aware of platform-specific alignment requirements
Document any custom alignment decisions


Performance Considerations

Profile before optimizing
Consider access patterns in your specific use case
Balance memory usage vs. access speed



Compiler Support

Most compilers automatically handle alignment
offsetof() macro helps inspect member offsets
#pragma pack directives control alignment behavior
__attribute__((packed)) (GCC) forces tight packing

Common Pitfalls

Assuming all platforms have same alignment requirements
Forcing packed structures without considering performance impact
Ignoring alignment in dynamic memory allocation
Not considering cache line boundaries in data structures
