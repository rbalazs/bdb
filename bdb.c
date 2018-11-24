/*
 * First step: lets create a simple read-execute-print loop (REPL).
 */
int main (int argc, char* argv[]) {
  InputBuffer* input_buffer = new_input_buffer();
  while (true) {
    print_prompt();
    read_input(input_buffer);

    if (strcmp(input_buffer->buffer, '.die') == 0) {
      exit(EXIT_SUCCESS);
    } else {
      printf("Command not found.\n", );
    }
  }
}
