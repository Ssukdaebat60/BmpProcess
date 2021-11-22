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


//추가할 기능: 범위 지정, 범위 리셋, row와 column구현 

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

void multipleBGR(float Bf, float Gf, float Rf, bool overwrite = false){
	if (not overwrite){
		for (int i = y0; i < y1; i++){
			for(int j = x0; j < x1; j++){
				B[getIndex(i,j)] = (int)(rawB[getIndex(i,j)]*Bf);
				G[getIndex(i,j)] = (int)(rawG[getIndex(i,j)]*Gf);
				R[getIndex(i,j)] = (int)(rawR[getIndex(i,j)]*Rf);
			}
		}
	}
	else{
		for (int i = y0; i < y1; i++){
			for(int j = x0; j < x1; j++){
				B[getIndex(i,j)] = (int)(B[getIndex(i,j)]*Bf);
				G[getIndex(i,j)] = (int)(G[getIndex(i,j)]*Gf);
				R[getIndex(i,j)] = (int)(R[getIndex(i,j)]*Rf);
			}
		}
	}
}

void sumBGR(float Bf, float Gf, float Rf,  bool overwrite = false){
	if (not overwrite){
		for(int i = y0; i < y1; i++){
			for(int j = x0; j < x1; j++){
				if (rawB[getIndex(i,j)]+Bf>255 || rawB[getIndex(i,j)]+Bf<0){
					B[getIndex(i,j)] = (rawB[getIndex(i,j)]+Bf>255) ? 255 : 0;
				}
				else{
					B[getIndex(i,j)] = int(rawB[getIndex(i,j)]+Bf);
				}
				if (rawG[getIndex(i,j)]+Gf>255 || rawG[getIndex(i,j)]+Gf<0){
					G[getIndex(i,j)] = (rawG[getIndex(i,j)]+Gf>255) ? 255 : 0;
				}
				else{
					G[getIndex(i,j)] = int(rawG[getIndex(i,j)]+Gf);
				}
				if (rawR[getIndex(i,j)]+Rf>255 || rawR[getIndex(i,j)]+Rf<0){
					R[getIndex(i,j)] = (rawR[getIndex(i,j)]+Rf>255) ? 255 : 0;
				}
				else{
					R[getIndex(i,j)] = int(rawR[getIndex(i,j)]+Rf);
				}
			}
		}
	}
	else{
		for(int i = y0; i < y1; i++){
			for(int j = x0; j < x1; j++){
				if (B[getIndex(i,j)]+Bf>255 || B[getIndex(i,j)]+Bf<0){
					B[getIndex(i,j)] = (B[getIndex(i,j)]+Bf>255) ? 255 : 0;
				}
				else{
					B[getIndex(i,j)] = int(B[getIndex(i,j)]+Bf);
				}
				if (G[getIndex(i,j)]+Gf>255 || G[getIndex(i,j)]+Gf<0){
					G[getIndex(i,j)] = (G[getIndex(i,j)]+Gf>255) ? 255 : 0;
				}
				else{
					G[getIndex(i,j)] = int(G[getIndex(i,j)]+Gf);
				}
				if (R[getIndex(i,j)]+Rf>255 || R[getIndex(i,j)]+Rf<0){
					R[getIndex(i,j)] = (R[getIndex(i,j)]+Rf>255) ? 255 : 0;
				}
				else{
					R[getIndex(i,j)] = int(R[getIndex(i,j)]+Rf);
				}
			}
		}
	}
}

void mosaic(bool overwrite = false){
	if (not overwrite){
		for(int i = y0; i < y1; i++){
			for(int j = x0; j < x1; j++){
				B[getIndex(i,j)]=rawB[getIndex(i/MOSAIC*MOSAIC,j/MOSAIC*MOSAIC)];
				G[getIndex(i,j)]=rawG[getIndex(i/MOSAIC*MOSAIC,j/MOSAIC*MOSAIC)];
				R[getIndex(i,j)]=rawR[getIndex(i/MOSAIC*MOSAIC,j/MOSAIC*MOSAIC)];
			}
		}
	}
	else{
		for(int i = y0; i < y1; i++){
			for(int j = x0; j < x1; j++){
				B[getIndex(i,j)]=B[getIndex(i,j)/MOSAIC*MOSAIC];
				G[getIndex(i,j)]=G[getIndex(i,j)/MOSAIC*MOSAIC];
				R[getIndex(i,j)]=R[getIndex(i,j)/MOSAIC*MOSAIC];
			}
		}
	}
}

void drawline(bool overwrite = false){
	int x_gap;
	int y_gap;
	if (not overwrite){
		for(int i = y0; i < y1; i++){
			for(int j = x0; j < x1; j++){
				int sum = (rawB[getIndex(i,j)] + rawG[getIndex(i,j)] + rawR[getIndex(i,j)]);
				x_gap = (sum - (rawB[getIndex(i,j+1)] + rawG[getIndex(i,j+1)] + rawR[getIndex(i,j+1)])) / 3;
				y_gap = (sum - (rawB[getIndex(i+1,j)] + rawG[getIndex(i+1,j)] + rawR[getIndex(i+1,j)])) / 3;
				
				if(x_gap>GAP || x_gap<-GAP || y_gap>GAP || y_gap<-GAP)
					B[getIndex(i,j)] = G[getIndex(i,j)] = R[getIndex(i,j)] = 0;
				else
					B[getIndex(i,j)] = G[getIndex(i,j)] = R[getIndex(i,j)] = 255;
			}
		}
	}
	else{
		for(int i = y0; i < y1; i++){
			for(int j = x0; j < x1; j++){
				B[getIndex(i,j)]=B[getIndex(i,j)/MOSAIC*MOSAIC];
				G[getIndex(i,j)]=G[getIndex(i,j)/MOSAIC*MOSAIC];
				R[getIndex(i,j)]=R[getIndex(i,j)/MOSAIC*MOSAIC];
			}
		}
	}
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
