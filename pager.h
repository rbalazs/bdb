struct Pager_t {
  int file_descriptor;
  uint32_t file_length;
  void* pages[TABLE_MAX_PAGES];
};
typedef struct Pager_t Pager;

Pager* pager_open (const char* filename) {
  // Disk io.
  int fd = open(
      filename,
      O_RDWR | O_CREAT, // RW and creates if not exists.
      S_IWUSR | S_IRUSR // User read and user write perms.
  );

  if (fd == -1) {
    printf("Unable to open file\n");
    exit(EXIT_FAILURE);
  }

  // From sys/types.h the off_t is used for file sizes.
  off_t file_length = lseek(fd, 0, SEEK_END);

  // Init pager.
  Pager* pager = malloc(sizeof(Pager));
  pager->file_descriptor = fd;
  pager->file_length = file_length;

  // Invalidate cache.
  for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
    pager->pages[i] = NULL;
  }

  return pager;
}

// Page 0 at offset 0,
// page 1 at offset 4096
// page 2 at offset 8192, etc
void* get_page(Pager* pager, uint32_t page_num) {
  if (page_num > TABLE_MAX_PAGES) {
    printf("Page number out of bounds: %d > %d\n",
      page_num, TABLE_MAX_PAGES);
    exit(EXIT_FAILURE);
  }

  // Cache hit.
  if (pager->pages[page_num] != NULL) {
    return pager->pages[page_num];
  }

  // Cache miss.
  if (pager->pages[page_num] == NULL) {
    // Allocate memoriy and load from file.
    void* page = malloc(PAGE_SIZE);
    uint32_t num_pages = pages->file_length / PAGE_SIZE;

    // Increment nu,ber of pages, so if there is a
    // partial of the page, we can save it.
    if (pager->file_length % PAGE_SIZE) {
      num_pages += 1;
    }

    // Load persisted data to memory.
    if (page_num <= num_pages) {
      lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);
      ssize_t bytes_read = read(pager->file_descriptor, page, PAGE_SIZE);
      if (bytes_read == -1) {
        printf("Error reading file: %d\n", errno);
        exit(EXIT_FAILURE);
      }
    }
    pager->pages[page_num] = page;
    return pager->pages[page_num];
  }
}












}
