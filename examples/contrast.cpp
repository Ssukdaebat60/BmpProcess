#include "BmpProcess.h"

int main(){
	openBMP("sample2.bmp");
	contrast(1.2);
	writeBMP("output.bmp");
	closeBGR();
	return 0;
}

