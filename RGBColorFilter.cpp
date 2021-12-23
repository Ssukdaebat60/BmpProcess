#include "BmpProcess.h"

int main(){
	openBMP("sample1.bmp");
	setXY(0, 0, getWidth()/2, getHeight()/2);
	multipleBGR(1, 0, 0);
	setXY(getWidth()/2, getHeight()/2, getWidth(), getHeight());
	multipleBGR(0, 1, 0);
	setXY(0, getHeight()/2, getWidth()/2, getHeight());
	multipleBGR(0, 0, 1);
	writeBMP("output.bmp");
	closeBGR();
	return 0;
}
