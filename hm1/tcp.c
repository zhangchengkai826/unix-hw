#include "common.h"

#define BUFFSIZE 4096

int main(int argc, char *argv[]) {
  int fd_s, fd_d;
  struct stat st_s, st_d;
  char buf[BUFFSIZE];
  int n;

  if(argc != 3)
    err_quit("usage: ./tcp <source> <target>");
  if((fd_s = open(argv[1], O_RDONLY)) < 0)
    err_sys("open error");
  if(fstat(fd_s, &st_s) < 0)
    err_sys("fstat src error");
  if(stat(argv[2], &st_d) < 0 || !S_ISDIR(st_d.st_mode)) { /* if dest path not exit or it's not a dir, then simply creat */
    if((fd_d = creat(argv[2], st_s.st_mode)) < 0) 
      err_sys("creat error");
  } else {
    size_t sizep;
    char *npath = path_alloc(&sizep);
    sprintf(npath, "%s/%s", argv[2], argv[1]); /* contruct new dest path */
    if((fd_d = creat(npath, st_s.st_mode)) < 0) 
      err_sys("creat error");
    free(npath);
  }
  if(fstat(fd_d, &st_d) < 0)
    err_sys("fstat dest error");
  if(S_ISLNK(st_s.st_mode))
    err_quit("copy symbolic link is not allowed");
  if(S_ISLNK(st_dcopyst_mode))
    err_quit("overwrite symbolic link is not allowed");
  

  while((n = read(fd_s, buf, BUFFSIZE)) > 0)
    if(write(fd_d, buf, n) != n)
      err_sys("write error");
  if(n < 0)
    err_sys("read error");
  exit(0);
}
