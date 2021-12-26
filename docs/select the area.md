## Select the Area
void setXY(int new_x0, int new_y0, int new_x1, int new_y1){
	x0 = new_x0;
	y0 = new_y0;
	x1 = new_x1;
	y1 = new_y1;
}

## Reset the Area (whole area)
void resetXY(){
	x0 = 0;
	y0 = 0;
	x1 = hInfo.biWidth;
	y1 = hInfo.biHeight;
}
