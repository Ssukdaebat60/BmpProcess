#include <stdio.h> 
#include <stdlib.h> 
#include <Windows.h> 

#define MOSAIC 8 
#define GAP 10

BITMAPFILEHEADER hf;
BITMAPINFOHEADER hInfo;

int ImgSize = 0;
int x0, y0, x1, y1 = 0; 

unsigned char * rawB;
unsigned char * rawG;
unsigned char * rawR;
unsigned char * B;
unsigned char * G;
unsigned char * R;

int getIndex(int row, int col){
	return row*(hInfo.biWidth) + col;
}

void openBMP(const char *filename){
	FILE *f;
	f = fopen(filename, "rb");
	if (f == NULL) return ;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, f);  
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, f);
	
	ImgSize = hInfo.biWidth * hInfo.biHeight;
	x1 = hInfo.biWidth;
	y1 = hInfo.biHeight;
	
	rawB = (unsigned char *)malloc(ImgSize);
	rawG = (unsigned char *)malloc(ImgSize);
	rawR = (unsigned char *)malloc(ImgSize);
	B = (unsigned char *)malloc(ImgSize);
	G = (unsigned char *)malloc(ImgSize);
	R = (unsigned char *)malloc(ImgSize);
	
	for (int i = 0; i < ImgSize; i++){
		rawB[i] = getc(f);
		B[i] = rawB[i];
		rawG[i] = getc(f);
		G[i] = rawG[i];
		rawR[i] = getc(f);
		R[i] = rawR[i];
	}
	
	fclose(f);
}

int getWidth(){
	return hInfo.biWidth;
}

int getHeight(){
	return hInfo.biHeight;
}

void multipleWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[], float Bf, float Gf, float Rf){
	for (int i = y0; i < y1; i++){
		for(int j = x0; j < x1; j++){
			B[getIndex(i,j)] = (int)(arrB[getIndex(i,j)]*Bf);
			G[getIndex(i,j)] = (int)(arrG[getIndex(i,j)]*Gf);
			R[getIndex(i,j)] = (int)(arrR[getIndex(i,j)]*Rf);
		}
	}
}

void multipleBGR(float Bf, float Gf, float Rf, bool overwrite = false){
	if (not overwrite)
		multipleWith(rawB, rawG, rawR, Bf, Gf, Rf);
	else
		multipleWith(B, G, R, Bf, Gf, Rf);
}

void sumWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[], float Bf, float Gf, float Rf){
	for(int i = y0; i < y1; i++){
		for(int j = x0; j < x1; j++){
			if (arrB[getIndex(i,j)]+Bf>255 || arrB[getIndex(i,j)]+Bf<0)
				B[getIndex(i,j)] = (arrB[getIndex(i,j)]+Bf>255) ? 255 : 0;
			else
				B[getIndex(i,j)] = int(arrB[getIndex(i,j)]+Bf);
				
			if (arrG[getIndex(i,j)]+Gf>255 || arrG[getIndex(i,j)]+Gf<0)
				G[getIndex(i,j)] = (arrG[getIndex(i,j)]+Gf>255) ? 255 : 0;
			else
				G[getIndex(i,j)] = int(arrG[getIndex(i,j)]+Gf);
			
			if (arrR[getIndex(i,j)]+Rf>255 || arrR[getIndex(i,j)]+Rf<0)
				R[getIndex(i,j)] = (arrR[getIndex(i,j)]+Rf>255) ? 255 : 0;
			else
				R[getIndex(i,j)] = int(arrR[getIndex(i,j)]+Rf);
		}
	}
}

void sumBGR(float Bf, float Gf, float Rf,  bool overwrite = false){
	if (not overwrite)
		sumWith(rawB, rawG, rawR, Bf, Gf, Rf);
	else
		sumWith(B, G, R, Bf, Gf, Rf);
}

void mosaicWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]){
	for(int i = y0; i < y1; i++){
		for(int j = x0; j < x1; j++){
			B[getIndex(i,j)]=arrB[getIndex(i/MOSAIC*MOSAIC,j/MOSAIC*MOSAIC)];
			G[getIndex(i,j)]=arrG[getIndex(i/MOSAIC*MOSAIC,j/MOSAIC*MOSAIC)];
			R[getIndex(i,j)]=arrR[getIndex(i/MOSAIC*MOSAIC,j/MOSAIC*MOSAIC)];
		}
	}
}

void mosaic(bool overwrite = false){
	if (not overwrite)
		mosaicWith(rawB, rawG, rawR);
	else
		mosaicWith(B, G, R);
}

void drawlineWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]){
	int x_gap;
	int y_gap;
	for(int i = y0+1; i < y1-1; i++){
		for(int j = x0+1; j < x1-1; j++){
			int sum = (arrB[getIndex(i,j)] + arrG[getIndex(i,j)] + arrR[getIndex(i,j)]);
			x_gap = (sum - (arrB[getIndex(i,j+1)] + arrG[getIndex(i,j+1)] + arrR[getIndex(i,j+1)])) / 3;
			y_gap = (sum - (rawB[getIndex(i+1,j)] + arrG[getIndex(i+1,j)] + arrR[getIndex(i+1,j)])) / 3;
			
			if(x_gap>GAP || x_gap<-GAP || y_gap>GAP || y_gap<-GAP)
				B[getIndex(i,j)] = G[getIndex(i,j)] = R[getIndex(i,j)] = 0;
			else
				B[getIndex(i,j)] = G[getIndex(i,j)] = R[getIndex(i,j)] = 255;
		}
	}
}

void drawline(bool overwrite = false){
	if (not overwrite)
		drawlineWith(rawB, rawG, rawR);
	else
		drawlineWith(B, G, R);
}

void writeBMP(const char *filename){
	FILE *f;
	f = fopen(filename, "wb"); 
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), f);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), f);
	for (int i = 0; i < ImgSize; i++){
		putc(B[i],f);
		putc(G[i],f);
		putc(R[i],f);
	}
	fclose(f);
}

void closeBGR(){
	free(rawB);
	free(rawG);
	free(rawR); 
	free(B);
	free(G);
	free(R);
}

void setXY(int new_x0, int new_y0, int new_x1, int new_y1){
	x0 = new_x0;
	y0 = new_y0;
	x1 = new_x1;
	y1 = new_y1;
}

void resetXY(){
	x0 = 0;
	y0 = 0;
	x1 = hInfo.biWidth;
	y1 = hInfo.biHeight;
}
