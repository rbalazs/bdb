#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "enums.h"
#include "input_buffer.h"
#include "meta_command_result.h"
#include "row.h"
#include "table.h"
#include "execute_result.h"
#include "prepare_result.h"
#include "basic_io.h"

int main(int argc, char* argv[]) {
  Table* table = new_table();
  InputBuffer* input_buffer = new_input_buffer();

  // Main REPL.
  while (true) {
    print_prompt();
    read_input_from_prompt(input_buffer);

    if (input_buffer->buffer[0] == '.') {
      switch (do_meta_command(input_buffer)) {
        case (META_COMMAND_SUCCESS):
          continue;
        case (META_COMMAND_UNRECOGNIZED_COMMAND):
          printf("Command not found: '%s'\n", input_buffer->buffer);
          continue;
      }
    }

    Statement statement;
    switch (prepare_statement(input_buffer, &statement)) {
      case (PREPARE_SUCCESS):
        break;
      case(PREPARE_SYNTAX_ERROR):
        printf("Syntax error!\n");
        continue;
      case(PREPARE_STRING_TOO_LONG):
        printf("String is too long!\n");
        continue;
      case(PREPARE_NEGATIVE_ID):
        printf("ID must be positive.\n");
        continue;
      case (PREPARE_UNRECOGNIZED_STATEMENT):
        printf("Keyword not found at start if '%s'.\n", input_buffer->buffer);
        continue;
    }

    switch (execute_statement(&statement, table)) {
      case (EXECUTE_SUCCESS):
        printf(".\n");
        break;
      case (EXECUTE_TABLE_FULL):
        printf("No more space left in table.\n");
        break;
    }
  }
}
