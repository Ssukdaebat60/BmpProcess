#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define MOSAIC 8 // lower -> more pixels
#define GAP 50 // lower -> more lines
#define THRESHOLDING 70 //lower -> whiter

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

void openBMP(const char *filename);
void writeBMP(const char *filename);
void closeBGR();
void multipleBGR(float Bf, float Gf, float Rf, bool overwrite);
void multipleWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[], float Bf, float Gf, float Rf);
void sumBGR(float Bf, float Gf, float Rf,  bool overwrite);
void sumWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[], float Bf, float Gf, float Rf);
void mosaic(bool overwrite);
void mosaicWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]);
void drawline(bool overwrite);
void drawlineWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]);
void gray(bool overwrite);
void grayWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]);
void binarization(bool overwrite);
void binarizationWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]);
void reverse(bool overwrite);
void reverseWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]);
void contrast(float num, bool overwrite);
void setXY(int new_x0, int new_y0, int new_x1, int new_y1);
void resetXY();
int getWidth();
int getHeight();
int getIndex(int row, int col);

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
		rawB[i] = fgetc(f);
		B[i] = rawB[i];
		rawG[i] = fgetc(f);
		G[i] = rawG[i];
		rawR[i] = fgetc(f);
		R[i] = rawR[i];
	}
	
	fclose(f);
}

void writeBMP(const char *filename){
	FILE *f = NULL;
	f = fopen(filename, "wb"); 
	fwrite(&hf, sizeof(BITMAPFILEHEADER), 1, f);
	fwrite(&hInfo, sizeof(BITMAPINFOHEADER), 1, f);
	for (int i = 0; i < ImgSize+hInfo.biHeight; i++){
		fputc(B[i],f);
		fputc(G[i],f);
		fputc(R[i],f);
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

void multipleBGR(float Bf, float Gf, float Rf, bool overwrite = true){
	if (overwrite)
		multipleWith(B, G, R, Bf, Gf, Rf);
	else
		multipleWith(rawB, rawG, rawR, Bf, Gf, Rf);
}

void multipleWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[], float Bf, float Gf, float Rf){
	for (int i = y0; i < y1; i++){
		for(int j = x0; j < x1; j++){
			if (arrB[getIndex(i,j)]*Bf>255 || arrB[getIndex(i,j)]*Bf<0)
				B[getIndex(i,j)] = (arrB[getIndex(i,j)]*Bf>255) ? 255 : 0;
			else
				B[getIndex(i,j)] = int(arrB[getIndex(i,j)]*Bf);
				
			if (arrG[getIndex(i,j)]*Gf>255 || arrG[getIndex(i,j)]*Gf<0)
				G[getIndex(i,j)] = (arrG[getIndex(i,j)]*Gf>255) ? 255 : 0;
			else
				G[getIndex(i,j)] = int(arrG[getIndex(i,j)]*Gf);
			
			if (arrR[getIndex(i,j)]*Rf>255 || arrR[getIndex(i,j)]*Rf<0)
				R[getIndex(i,j)] = (arrR[getIndex(i,j)]*Rf>255) ? 255 : 0;
			else
				R[getIndex(i,j)] = int(arrR[getIndex(i,j)]*Rf);
		}
	}
}

void sumBGR(float Bf, float Gf, float Rf,  bool overwrite = true){
	if (overwrite)
		sumWith(B, G, R, Bf, Gf, Rf);
	else
		sumWith(rawB, rawG, rawR, Bf, Gf, Rf);
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

void mosaic(bool overwrite = true){
	if (overwrite)
		mosaicWith(B, G, R);
	else
		mosaicWith(rawB, rawG, rawR);
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

void drawline(bool overwrite = true){
	if (overwrite)
		drawlineWith(B, G, R);
	else
		drawlineWith(rawB, rawG, rawR);
}

void drawlineWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]){
	int x_gap;
	int y_gap;
	for(int i = y0+1; i < y1-1; i++){
		for(int j = x0+1; j < x1-1; j++){
			int x_gap[3];
			int y_gap[3];
			x_gap[0] = arrB[getIndex(i,j)] - arrB[getIndex(i,j+1)];
			x_gap[1] = arrG[getIndex(i,j)] - arrG[getIndex(i,j+1)];
			x_gap[2] = arrR[getIndex(i,j)] - arrR[getIndex(i,j+1)];
			y_gap[0] = arrB[getIndex(i,j)] - arrB[getIndex(i+1,j)];
			y_gap[1] = arrG[getIndex(i,j)] - arrG[getIndex(i+1,j)];
			y_gap[2] = arrR[getIndex(i,j)] - arrR[getIndex(i+1,j)];
			
			for(int k = 0; k < 3; k++){
				if(abs(x_gap[k]) > GAP || abs(y_gap[k]) > GAP){
					B[getIndex(i,j)] = G[getIndex(i,j)] = R[getIndex(i,j)] = 0;
					break;
				}
				else if(k == 2)
					B[getIndex(i,j)] = G[getIndex(i,j)] = R[getIndex(i,j)] = 255;
			}
		}
	}
}

void gray(bool overwrite = true){
	if (overwrite)
	    grayWith(B, G, R);
	else
		grayWith(rawB, rawG, rawR);
} 

void grayWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]){
	for(int i = y0; i < y1; i++){
		for(int j = x0; j < x1; j++){
			int index = getIndex(i, j);
			int g =  arrB[index]*0.114 + arrG[index]*0.587 + arrR[index]*0.299;
			arrB[index] = arrG[index] = arrR[index] = g;
		}
	}
}

void binarization(bool overwrite = true){
	if (overwrite)
	    binarizationWith(B, G, R);
	else
		binarizationWith(rawB, rawG, rawR);
}

void binarizationWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]){
	for(int i = y0; i < y1; i++){
		for(int j = x0; j < x1; j++){
			arrB[getIndex(i,j)] = (arrB[getIndex(i,j)] > THRESHOLDING) ? 255 : 0 ;
			arrG[getIndex(i,j)] = (arrG[getIndex(i,j)] > THRESHOLDING) ? 255 : 0 ;
			arrR[getIndex(i,j)] = (arrR[getIndex(i,j)] > THRESHOLDING) ? 255 : 0 ;
		}
	}
}

void reverse(bool overwrite = true){
	if (overwrite)
		reverseWith(B, G, R);
	else
		reverseWith(rawB, rawG, rawR);
}

void reverseWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]){
	for(int i = y0; i < y1; i++){
		for(int j = x0; j < x1; j++){
		arrB[getIndex(i,j)] = 255 - arrB[getIndex(i,j)];
		arrG[getIndex(i,j)] = 255 - arrG[getIndex(i,j)];
		arrR[getIndex(i,j)] = 255 - arrR[getIndex(i,j)];
		}
	}
}

void contrast(float num, bool overwrite = true){
	if (overwrite)
		multipleWith(B, G, R, num, num, num);
	else
		multipleWith(rawB, rawG, rawR, num, num, num);
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

int getWidth(){
	return hInfo.biWidth;
}

int getHeight(){
	return hInfo.biHeight;
}

int getIndex(int row, int col){
	return row*(hInfo.biWidth) + col;
}
