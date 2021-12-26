## Define Mosaic Area
```c
#define MOSAIC 8
```
## change 8×8 pixel data to its first value.
```c
void mosaicWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]){
	for(int i = y0; i < y1; i++){
		for(int j = x0; j < x1; j++){
			B[getIndex(i,j)]=arrB[getIndex(i/MOSAIC*MOSAIC,j/MOSAIC*MOSAIC)];
			G[getIndex(i,j)]=arrG[getIndex(i/MOSAIC*MOSAIC,j/MOSAIC*MOSAIC)];
			R[getIndex(i,j)]=arrR[getIndex(i/MOSAIC*MOSAIC,j/MOSAIC*MOSAIC)];
		}
	}
}
```
