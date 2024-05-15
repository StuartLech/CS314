#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[]){
  FILE* fp;
  char c;
  int line_number = 0;
  int print_line_number = 0;

  int start_arg = 1;
  int number_lines = 0;

  if (argc > 1 && strcmp(argv[1], "-b")==0){
    number_lines=1;
    start_arg=2;
  }
  for (int i = (argc == start_arg) ? 0 : start_arg; i < argc; i++){
    if (i >= start_arg + 5){
      break;
    }

    fp = (i == 0) ? stdin : fopen(argv[i],"r");
    if (!fp) {
      printf("Error: unable to open file %\n", argv[i]);
      continue;
    }
    while ((c = fgetc(fp)) != EOF) {
      if (print_line_number == 0 && c != '\n' && number_lines){
	printf("%d\t", ++line_number);
	print_line_number =1;
      }

      putchar(c);

      if (c == '\n'){
	print_line_number=0;
      }
    }
    if (fp != stdin){
      fclose(fp);
    }
  }
  return 0;
}
