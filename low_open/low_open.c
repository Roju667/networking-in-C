#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys\stat.h>

int main() {

  // file descriptor
  int fd =
      _open("data.txt", _O_CREAT | _O_RDWR | O_APPEND, _S_IREAD | _S_IWRITE);
  char buffer[] = "new data to folder\n";

  printf("File descriptor : %d \n", fd);

  if (-1 == fd) {
    perror("Open failed ");
  } else {
    printf("Opening OK \n");
  }

  char read_buff[4096] = {0};
  if (-1 == _read(fd, read_buff, 4096)) {
    perror("Error reading");
  }

  printf("%s", read_buff);

  if (-1 == _write(fd, buffer, sizeof(buffer))) {
    perror("Error writing");
  }

  _close(fd);

  return 0;
}