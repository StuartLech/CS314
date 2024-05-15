#include<stdio.h>
#include<stdlib.h>
void countFile(const char* filename, int* totalLines, int* totalWords,int* totalChars);
int main(int argc, char *argv[]){
  int totalLines = 0;
  int totalWords = 0;
  int totalChars = 0;

  if (argc < 2){
    printf("Usage: % <file1> [file2] [... fileN\n", argv[0]);
    return 1;
  }

  for (int i = 1; i < argc; ++i) {
    countFile(argv[i], &totalLines, &totalWords, &totalChars);
	      }
      if (argc > 2) {
	printf("%d %d %d total\n", totalLines, totalWords, totalChars);
      }
    return 0;
  }
void countFile(const char* filename, int* totalLines, int* totalWords, int* totalChars){
    FILE* file = fopen(filename, "r");
    if (!file) {
      perror(filename);
      return;
    }

    int lines = 0;
    int words = 0;
    int chars = 0;
    int c;
    int inWord = 0;

    while ((c = fgetc(file)) != EOF) {
      ++chars;

      if (c == '\n'){
	++lines;
      }

      if (c == ' ' || c == '\n' ||c ==  '\t'){
	inWord = 0;
      } else if (!inWord){
	inWord = 1;
	++words;
      }
    }
    fclose(file);

    printf("%d %d %d %s\n", lines, words, chars, filename);

    *totalLines += lines;
    *totalWords += words;
    *totalChars += chars;
  }
