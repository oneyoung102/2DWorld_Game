//basic_input_h
#ifndef BASIC_INPUT_H
#define BASIC_INPUT_H

#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 
//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void CursorView();
void textcolor(int foreground, int background);
void Gotoxy(int x, int y);
void Write(int x, int y, int foreground, int background, const char text[10000]);
void Write_char(int x, int y, int foreground, int background, char *text);
void Write_int(int x, int y, int foreground, int background, int *text);
#endif
