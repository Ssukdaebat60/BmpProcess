## Write the Header
```c
void writeBMP(const char *filename){
	FILE *f = NULL;
	f = fopen(filename, "wb"); 
	fwrite(&hf, sizeof(BITMAPFILEHEADER), 1, f);
	fwrite(&hInfo, sizeof(BITMAPINFOHEADER), 1, f);
```
## Write the RGB Data & Close the File
```c
	for (int i = 0; i < ImgSize+hInfo.biHeight; i++){
		fputc(B[i],f);
		fputc(G[i],f);
		fputc(R[i],f);
	}
	fclose(f);
}
```
## Release the Memory
```c
void closeBGR(){
	free(rawB);
	free(rawG);
	free(rawR); 
	free(B);
	free(G);
	free(R);
}
```
