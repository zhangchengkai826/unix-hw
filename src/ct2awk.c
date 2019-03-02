#include "apue.h"

int main(int argc, char *argv[]) {
 if(argc != 3) err_quit("usage: ct2awk <input> <output>\n");
 FILE *fi = fopen(argv[1], "r");
 FILE *fo = fopen(argv[2], "w");
 size_t n = 0;
 char *l = NULL;
 fprintf(fo, "BEGIN {\n");
 while(getline(&l, &n, fi) != -1) {
  if(l[0] == '^') {
   fprintf(fo, "printf(\"");
   char *p = l+1;
   while(1) {
    if(*p == '^') break;
    if(*p == '\\') fprintf(fo, "\\\\");
    else if(*p == '\"') fprintf(fo, "\\\"");
    else if(*p == '$') fputc('%', fo);
    else if(*p == '%') fprintf(fo, "%%%%");
    else fputc(*p, fo);
    p++;
   }
   fprintf(fo, "\\n\",");
   p++;
   while(*p != '\n') {
    fputc(*p, fo);
    p++;
   }
   fprintf(fo, ")\n");
  } else if(l[0] == '@') {
   char *p = l+1;
   while(*p != '\0') {
    fputc(*p, fo);
    p++;
   }
  } else {
   fprintf(fo, "printf(\"");
   char *p = l;
   while(*p != '\n') {
    if(*p == '\\') fprintf(fo, "\\\\");
    else if(*p == '\"') fprintf(fo, "\\\"");
    else if(*p == '%') fprintf(fo, "%%%%");
    else fputc(*p, fo);
    p++;
   }
   fprintf(fo, "\\n\")\n");
  }    
 }
 free(l);
 fprintf(fo, "}\n");
 fclose(fi);
 fclose(fo);
}
