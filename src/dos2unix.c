#include <stdio.h>

int main(int argc, char *argv[]) {
 FILE *fi = fopen(argv[1], "r");
 FILE *fo = fopen(argv[2], "w");
 
 char c;
 while((c=fgetc(fi)) != EOF) {
  if(c != '\r') fputc(c, fo);
 }
  
 fclose(fi);
 fclose(fo); 
}
