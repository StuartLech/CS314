#include<stdio.h>

int main(int argc, char* argv[]){
  if (argc != 3){
    puts("Usage: source_file destination_file");
    return 1;
  }
FILE *inputFile, *outputFile;
inputFile = fopen(argv[1],"r");
outputFile = fopen(argv[2],"w");
if (!inputFile || !outputFile){
  puts("File error");
  return 1;
 }
char ch;
 while((ch = fgetc(inputFile)) != EOF) {
  fputc(ch, outputFile);
 }
fclose(inputFile);
fclose(outputFile);
return 0;
}
