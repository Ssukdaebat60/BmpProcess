#include "BmpProcess.h"

int main(){
	openBMP("sample1.bmp");
	gray();
	writeBMP("output.bmp");
	closeBGR();
	return 0;
}
