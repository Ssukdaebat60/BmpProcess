## Read the Header
``` c
void openBMP(const char *filename){
	FILE *f;
	f = fopen(filename, "rb");

	if (f == NULL) return ;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, f);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, f);
```

## Load the Img Size
```c
	ImgSize = hInfo.biWidth * hInfo.biHeight;
	x1 = hInfo.biWidth;
	y1 = hInfo.biHeight;
```

## Dynamic Allocation (ArrSize = ImgSize)
```c  
	rawB = (unsigned char *)malloc(ImgSize);
	rawG = (unsigned char *)malloc(ImgSize);
	rawR = (unsigned char *)malloc(ImgSize);
	B = (unsigned char *)malloc(ImgSize);
	G = (unsigned char *)malloc(ImgSize);
	R = (unsigned char *)malloc(ImgSize);
```

## Load the RGB Data & Close the File
```c
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
```
