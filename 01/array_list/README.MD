Output:

```
Adding integers...

Adding strings...

Adding person struct...

List contents:
Integer at index 0: 0
Integer at index 1: 10
Integer at index 2: 20
String at index 3: Hello
String at index 4: World
Person at index 5: John Doe, age 30

List freed successfully


```


Notes:

- size_t is an unsigned integer type in C that is used to represent sizes and counts. It's guaranteed to be large enough to hold the size of the largest possible object on your system.
- Used for array indexing and loop counting
- Used for sizing in memory allocation
- Result type of the sizeof operator

- On 32-bit systems: typically 32 bits (4 bytes)
- On 64-bit systems: typically 64 bits (8 bytes)

- Can never be negative
- Maximum value is platform-dependent (e.g., 2^32 - 1 or 2^64 - 1)

- void in the parameter list explicitly indicates that the function takes no parameters. It's different from an empty parameter list () because it's more explicit and prevents accidental parameter passing.

- In C, you can't directly assign strings using = because strings are arrays of characters, and in C you can't directly assign arrays. strncpy is a safer version of strcpy that lets you specify a maximum number of characters to copy, helping prevent buffer overflows.


