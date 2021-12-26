# BMP
- ## Uncompressed Format  


- ## Structure
> ### Header
> - BITMAPFILEHEADER(14bytes)
>```c
> typedef struct tagBITMAPFILEHEADER
> {
> WORD bfType; // file type(2bytes)
> DWORD bfSize; // size of img(4bytes)
> WORD bfReserved; // reserved variable(2bytes)
> WORD bfReserved;
> DWORD bfoffBits; // the starting point of bmp data(4bytes)
> } BITMAPFILEHEADER;
> ```
> - BITMAPINFOHEADER(40bytes)
> ```c
> typedef struct tagBITMAPINFOHEADER
> {
> DWORD biSize; // size of this struct(4bytes)
> LONG biWidth; // width of img(4bytes)
> LONG biHeight; // height of img(4bytes)
> WORD biplanes; // always 1(2bytes)
> WORD biBitCount; // bit a pixel (gray or color)(2bytes)
> DWORD biCompression; // compressed or uncompressed(4bytes)
> DWORD biSizeImage; // size of img(4bytes)
> LONG biXPelsPerMeter; // resolution of img width(4bytes)
> LONG biYPelsPerMeter; // resolution of img Height(4bytes)
> DWORD biClrUsed; // the number of colors used(4bytes)
> DWORD biClrImportant; // color index(4bytes)
> } BITMAPINFOHEADER;
> ```
> ### Body
> - store the RGB data
> - the order of colors data is B, G, R.
