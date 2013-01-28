


//defines possible colors for the foreground color.
typedef enum
{
    FG_Def = 0,
    FG_Black = 30,
    FG_Red,
    FG_Green,
    FG_Yellow,
    FG_Blue,
    FG_Magenta,
    FG_Cyan,
    FG_White
}fgColor;

//defines possible colors for the background color.
//BG_Def prints with the default background color of the terminal.
typedef enum
{
    BG_Def = 0,
    BG_Black = 40,
    BG_Red,
    BG_Green,
    BG_Yellow,
    BG_Blue,
    BG_Magenta,
    BG_Cyan,
    BG_White
}bgColor;

//defines possible additional attributes for the color printing.
//normally, you would use ATT_Def.
typedef enum
{	
    ATT_Def = 0,
    ATT_Bright = 1,
    ATT_Underline = 4,
    ATT_Reverse = 7,
    ATT_Hidden = 8,
    ATT_Scratch = 9

}attribute;

//clears the screen completely.
void clearScreen();

//prints a format string with its arguments (like printf!),
//in the specified foreground color, background color, and attribute.
void colorPrint(fgColor fg, bgColor bg, attribute att, char* format,...);

