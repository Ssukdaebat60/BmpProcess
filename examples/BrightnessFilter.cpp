#include "BmpProcess.h"

int main(){
	openBMP("sample1.bmp");
	setXY(0, 0, getWidth(), getHeight()/3);
	sumBGR(50, 50, 50);
	setXY(0, getHeight()*2/3, getWidth(), getHeight());
	sumBGR(-50, -50, -50);
	writeBMP("output.bmp");
	closeBGR();
	return 0;
}
