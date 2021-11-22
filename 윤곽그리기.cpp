#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "BmpProcess.h"

int main()
{
	openBMP("sample1.bmp");
	drawline();
	writeBMP("output.bmp");
	closeBGR();
	
	return 0;
}

