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

void* get_page(Pager* pager, uint32_t page_num) {
  return NULL; // TODO
}
