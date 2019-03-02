#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  printf("%d, %d, %d\n", STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
  printf("%d, %d, %d\n", stdin->_fileno, stdout->_fileno, stderr->_fileno);
}

