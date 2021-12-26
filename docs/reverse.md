## Reverse Each RGB Data
```c
void reverseWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]){
	for(int i = y0; i < y1; i++){
		for(int j = x0; j < x1; j++){
		arrB[getIndex(i,j)] = 255 - arrB[getIndex(i,j)];
		arrG[getIndex(i,j)] = 255 - arrG[getIndex(i,j)];
		arrR[getIndex(i,j)] = 255 - arrR[getIndex(i,j)];
		}
	}
}
```
