void print_prompt() { printf(">"); }

void read_input_from_prompt(InputBuffer* input_buffer) {
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
