enum ExecuteResult_t {
  EXECUTE_SUCCESS,
  EXECUTE_TABLE_FULL
};
typedef enum ExecuteResult_t ExecuteResult;

struct Statement_t {
  StatementType type;
  Row row_to_insert;
};
typedef struct Statement_t Statement;

ExecuteResult execute_insert(Statement* statement, Table* table) {
  if (table->num_rows >= TABLE_MAX_ROWS) {
    return EXECUTE_TABLE_FULL;
  }

  Row* row_to_insert = &(statement->row_to_insert);

  serialize_row(row_to_insert, row_slot(table, table->num_rows));
  table->num_rows += 1;

  return EXECUTE_SUCCESS;
}

ExecuteResult execute_select (Statement* statement, Table* table) {
  Row row;
  uint32_t i = 0;
  for (i = 0; i < table->num_rows; i++) {
    deserialize_row(row_slot(table, i), &row);
    print_row(&row);
  }

  return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement, Table* table) {
  switch (statement->type) {
    case (STATEMENT_INSERT):
      return execute_insert(statement, table);
      break;
    case (STATEMENT_SELECT):
      return execute_select(statement, table);
      break;
  }
}
