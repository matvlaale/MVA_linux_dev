#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void handle_error(const char *msg) {
  perror(msg);
  printf("Exit with errno =\n%d\n", errno);
  exit(errno);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: %s [infile] [outfile]\n", argv[0]);
    return 0;
  }
  const char *infile = argv[1];
  const char *outfile = argv[2];

  if (strcmp(infile, outfile) == 0) {
    errno = EINVAL;
    handle_error("Cannot rewrite the same file");
  }

  int inputF = open(infile, O_RDONLY);
  if (inputF < 0)
    handle_error("Error in opening infile");
  int outputF = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
  if (outputF < 0) {
    close(inputF);
    handle_error("Error in opening outfile");
  }

  char buffer[1024];
  int bytes_read, bytes_written;

  while ((bytes_read = read(inputF, buffer, sizeof(buffer))) > 0) {
    if (bytes_read < 0) {
      close(inputF);
      close(outputF);
      unlink(outfile);
      handle_error("Error in reading from infile");
    }

    bytes_written = write(outputF, buffer, bytes_read);

    if (bytes_written < 0 || bytes_written != bytes_read) {
      close(inputF);
      close(outputF);
      unlink(outfile);
      handle_error("Error in writing to outfile");
    }
  }

  if (close(inputF) < 0) {
    close(outputF);
    unlink(outfile);
    handle_error("Error in closing infile");
  }
  if (close(outputF) < 0) {
    handle_error("Error in closing outfile");
  }

  if (unlink(infile) < 0)
    handle_error("Error in deleting infile");

  return 0;
}
