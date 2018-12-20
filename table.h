/*
 * A structure for Table
 *  - points to pages of rows
 *  - keeps track of quantity of rows.
 */

#define PAGE_SIZE 4096

#define ROWS_PER_PAGE PAGE_SIZE / ROW_SIZE
#define TABLE_MAX_ROWS ROWS_PER_PAGE * TABLE_MAX_PAGES

struct Table_t {
  void* pages[TABLE_MAX_PAGES];
  Pager* pager;
  uint32_t num_rows;
};
typedef struct Table_t Table;

void* row_slot(Table* table, uint32_t row_num) {
  uint32_t page_num = row_num / ROWS_PER_PAGE;

  void* page = get_page(table->pager, page_num);

  uint32_t row_offset = row_num % ROWS_PER_PAGE;
  uint32_t byte_offset = row_offset % ROW_SIZE;

  return page + byte_offset;
}

/**
* - opening the database file
* - initializing a pager data structure
*  - initializing a table data structure
*/
Table* init(const char* filename) {
  Pager* pager = pager_open(filename);
  uint32_t num_rows = pager->file_length / ROW_SIZE;

  Table* table = malloc(sizeof(Table));
  table->pager = pager;
  table->num_rows = num_rows;

  return table;
}
