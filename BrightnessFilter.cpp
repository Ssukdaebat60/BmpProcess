#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "BmpProcess.h"

extern BITMAPINFOHEADER hInfo;

int main(){
	openBMP("sample1.bmp");
	setXY(0, 0, hInfo.biWidth, hInfo.biHeight/3);
	sumBGR(50, 50, 50, true);
	setXY(0, hInfo.biHeight*2/3, hInfo.biWidth, hInfo.biHeight);
	sumBGR(-50, -50, -50, true);
	writeBMP("output.bmp");
	closeBGR();
	return 0;
}
