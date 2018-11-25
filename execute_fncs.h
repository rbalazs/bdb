struct Statement_t {
  StatementType type;
  Row row_to_insert;
};
typedef struct Statement_t Statement;

void execute_statement(Statement* statement) {
  switch (statement->type) {
    case (STATEMENT_INSERT):
      printf("This is to do an insert.\n");
      break;
    case (STATEMENT_SELECT):
      printf("This is to do a select.\n");
      break;
  }
}
