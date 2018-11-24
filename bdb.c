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

typedef struct InputBuffer {
  char* buffer;
  size_t = buffer_length;
  ssize_t = input_length;
}

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void print_prompt() {
  printf("|Talktome|>");
}
