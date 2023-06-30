#include "s21_cat.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s [flags] filename\n", argv[0]);
    return 1;
  }

  FILE* file = fopen(argv[argc - 1], "r");
  if (file == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  int printLineNumber = 0;
  int printEndMarker = 0;
  int printTabs = 0;
  int printNonEmptyLineNumber = 0;
  int printSqueezedEmptyLines = 0;

  for (int i = 1; i < argc - 1; i++) {
    if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
      printLineNumber = 1;
    } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "-E") == 0) {
      printEndMarker = 1;
    } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-T") == 0) {
      printTabs = 1;
    } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--number-nonblank") == 0) {
      printNonEmptyLineNumber = 1;
    } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--squeeze-blank") == 0) {
      printSqueezedEmptyLines = 1;
    } else {
      printf("Unknown flag: %s\n", argv[i]);
      return 1;
    }
  }

  char line[MAX_LINE_LENGTH];
  int lineNumber = 1;

  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    if (printLineNumber) {
      printWithLineNumber(line, lineNumber);
      lineNumber++;
    } else if (printEndMarker) {
      printWithEndMarker(line);
    } else if (printTabs) {
      printWithTabs(line);
    } else if (printNonEmptyLineNumber) {
      printWithNonEmptyLineNumber(line, &lineNumber);
    } else if (printSqueezedEmptyLines) {
      printWithSqueezedEmptyLines(line, &lineNumber);

    } else {
      printf("%s", line);
    }
  }

  fclose(file);
  return 0;
}


void printWithLineNumber(char* line, int lineNumber) {
  printf("%6d	%s", lineNumber, line);
}

void printWithNonEmptyLineNumber(char* line, int* lineNumber) {
  if (strlen(line) > 1) {
    printf("%6d	%s", *lineNumber, line);
    (*lineNumber)++;
  } else {
    printf("\n");
  }
}

void printWithEndMarker(char* line) {
  int lineLength = strlen(line);
  if (line[lineLength - 1] == '\n') {
    line[lineLength - 2] = '$';
    // line[lineLength] = '\n';
    // line[lineLength + 1] = '\0';
  } else {
    line[lineLength -1] = '$';
    // line[lineLength + 1] = '\n';
    // line[lineLength + 2] = '\0';
  }
  printf("%s", line);
}

void printWithTabs(char* line) {
  int i;
  for (i = 0; line[i] != '\0'; i++) {
    if (line[i] == '\t') {
      printf("^I");
    } else {
      printf("%c", line[i]);
    }
  }
}

void printWithSqueezedEmptyLines(char* line, int* emptyLineCount) {
  if (strlen(line) > 1) {
    printf("%s", line);
    *emptyLineCount = 0;
  } else {
    (*emptyLineCount)++;
    if (*emptyLineCount == 1) {
      printf("%s", line);
    }
  }
}