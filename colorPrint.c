
#include <stdio.h>
#include <colorPrint.h>
#include <stdarg.h>

void clearScreen()
{
	printf("\e[1;1H\e[2J");
}

void colorPrint(fgColor fg, bgColor bg, attribute att, char* format,...)
{
	va_list args;
	if(bg != BG_Def)
		printf("\e[%d;%d;%dm",att,fg,bg);
	else
		printf("\e[%d;%dm",att,fg);

	va_start (args, format);
	vprintf(format, args);
	va_end (args);
	printf("\e[0m");
}
