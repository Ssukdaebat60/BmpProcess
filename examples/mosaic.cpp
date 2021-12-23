#include "BmpProcess.h"

int main(){
	openBMP("sample1.bmp");
	mosaic();
	writeBMP("output.bmp");
	closeBGR();
	return 0;
}
