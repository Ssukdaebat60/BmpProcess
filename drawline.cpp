#include "BmpProcess.h"

int main()
{
	openBMP("sample1.bmp");
	drawline();
	writeBMP("output.bmp");
	closeBGR();
	
	return 0;
}
