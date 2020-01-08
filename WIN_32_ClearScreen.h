/**********************************************************************
* WIN_32_ClearScreen function clears the terminal screen when compiled
* with Windows OS compiler
* source: http://www.cplusplus.com/articles/4z18T05o/
**********************************************************************/
#ifndef WIN_32_ClearScreen_H 
#define WIN_32_ClearScreen_H 
#ifdef _WIN32
#include <windows.h>
void WIN_32_ClearScreen();
#endif // _WIN32
#endif // !WIN_32_ClearScreen_H
