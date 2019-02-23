
#ifndef BDB_CURSORS_H

#define BDB_CURSORS_H

struct Cursor_t {
    Table* table;
    uint32_t row_num;
    bool end_of_table;
};
typedef struct Cursor_t Cursor;

#endif //BDB_CURSORS_H
