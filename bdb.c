#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "input_buffer.h"
#include "enums.h"
#include "row.h"
#include "table.h"
#include "execute_result.h"
#include "prepare_result.h"

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
  if (strcmp(input_buffer->buffer, ".die") == 0) {
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}

void print_prompt() { printf(">"); }

void read_input(InputBuffer* input_buffer) {
  /*
   * ssize_t getline(char **lineptr, size_t *n, FILE *stream);
   * lineptr : pointer to the variable which points to the
   *           buffer containing the read line.
   * n: a pointer to the variable to save the size of allocated buffer.
   * stream: the input stream to read from (stdin)
   * return value: the number of bytes read.
   */
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    printf("Faliora\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing newline
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}


///////////////////////MAIN///////////////////
int main(int argc, char* argv[]) {
  Table* table = new_table();
  InputBuffer* input_buffer = new_input_buffer();
  while (true) {
    print_prompt();
    read_input(input_buffer);

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
