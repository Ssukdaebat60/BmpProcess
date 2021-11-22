#include <stdio.h> 
#include <stdlib.h> 
#include <Windows.h> 
#include "BmpProcess.h"

extern BITMAPINFOHEADER hInfo;

int main(){
	openBMP("sample1.bmp");
	setXY(0, 0, hInfo.biWidth/2, hInfo.biHeight/2);
	multipleBGR(1, 0, 0, true);
	setXY(hInfo.biWidth/2, hInfo.biHeight/2, hInfo.biWidth, hInfo.biHeight);
	multipleBGR(0, 1, 0, true);
	setXY(0, hInfo.biHeight/2, hInfo.biWidth/2, hInfo.biHeight);
	multipleBGR(0, 0, 1, true);
	writeBMP("output.bmp");
	closeBMP();
	return 0;
}

