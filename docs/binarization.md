## Change RGB data to 0 or 255 by Thresholding
```c
void binarizationWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]){
	for(int i = y0; i < y1; i++){
		for(int j = x0; j < x1; j++){
			arrB[getIndex(i,j)] = (arrB[getIndex(i,j)] > THRESHOLDING) ? 255 : 0 ;
			arrG[getIndex(i,j)] = (arrG[getIndex(i,j)] > THRESHOLDING) ? 255 : 0 ;
			arrR[getIndex(i,j)] = (arrR[getIndex(i,j)] > THRESHOLDING) ? 255 : 0 ;
		}
	}
}
```
