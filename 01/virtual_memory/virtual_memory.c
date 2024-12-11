#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
  // Return the number of bytes in a page. This is the system's page size, which
  // is not necessarily the same as the hardware page size.
  int page_size = getpagesize();
  printf("System page size: %d bytes\n", page_size);

  long total_phys_pages = sysconf(_SC_PHYS_PAGES);
  long avail_phys_pages = sysconf(_SC_AVPHYS_PAGES);

  printf("\nPhysical Memory:\n");
  printf("Total pages: %ld\n", total_phys_pages);
  printf("Available pages: %ld\n", avail_phys_pages);
  printf("Total memory: %ld MB\n",
         (total_phys_pages * page_size) / (1024 * 1024));
  printf("Available memory: %ld MB\n",
         (avail_phys_pages * page_size) / (1024 * 1024));

  // Allocate a page-aligned chunk of memory
  void *aligned_mem = mmap(NULL,                   // Let system choose address
                           page_size,              // Size of allocation
                           PROT_READ | PROT_WRITE, // Permissions
                           MAP_PRIVATE | MAP_ANONYMOUS, // Flags
                           -1,                          // No file descriptor
                           0                            // No offset
  );

  if (aligned_mem == MAP_FAILED) {
    perror("mmap failed");
    return 1;
  }

  printf("\nPage-aligned memory:\n");
  printf("Allocated address: %p\n", aligned_mem);
  printf("Page alignment check: %s\n",
         ((unsigned long)aligned_mem % page_size == 0) ? "Aligned"
                                                       : "Not aligned");

  munmap(aligned_mem, page_size);

  return 0;
}
