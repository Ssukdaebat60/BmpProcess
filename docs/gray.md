## Find the Gray Value by Multiplying Con Cells Value
```c
void grayWith(unsigned char arrB[], unsigned char arrG[], unsigned char arrR[]){
	for(int i = y0; i < y1; i++){
		for(int j = x0; j < x1; j++){
			int index = getIndex(i, j);
```
## Change Each RGB Data to Gray Value
```c
			int g =  arrB[index]*0.114 + arrG[index]*0.587 + arrR[index]*0.299;
			arrB[index] = arrG[index] = arrR[index] = g;
		}
	}
}
```
