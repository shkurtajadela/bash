#ifndef S21_CAT_H
#define S21_CAT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void printWithLineNumber(char* line, int lineNumber);
void printWithNonEmptyLineNumber(char* line, int* lineNumber);
void printWithEndMarker(char* line);
void printWithTabs(char* line);
void printWithSqueezedEmptyLines(char* line, int* emptyLineCount);

#endif