#include "BmpProcess.h"

int main(){
	
	openBMP("sample2.bmp");
	reverse();
	writeBMP("output.bmp");
	closeBGR();
	
	return 0;
}
