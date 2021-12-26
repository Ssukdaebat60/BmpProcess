## Calculate each RGB Gap between the right pixel and the lower pixel.
```c
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
```
## Draw Line with Black and Make Empty Space with White.
```c
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
```
