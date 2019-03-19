/*
	Metodo de preenchimento Flood Fill
*/
void floodFill8(int x, int y, int fill, int old) {
	
	if (x < 0 || x >= dimx ) return;
	if (y < 0 || y >= dimy) return;

	if (matriz[x][y] == old){
		//cout << "x,y:" << x << "," << y << endl;
		matriz[x][y] = fill;
		floodFill8(x+1, y+0, fill, old);
		floodFill8(x+0, y+1, fill, old);
		floodFill8(x-1, y+0, fill, old);
		floodFill8(x+0, y-1, fill, old);
		floodFill8(x+1, y+1, fill, old);
		floodFill8(x-1, y+1, fill, old);
		floodFill8(x-1, y-1, fill, old);
		floodFill8(x+1, y-1, fill, old);
	}
}

void floodFill4(int x, int y, int fill, int old) {
	
	if (x < 0 || x >= dimx ) return;
	if (y < 0 || y >= dimy) return;

	if (matriz[x][y] == old){
		//cout << "x,y:" << x << "," << y << endl;
		matriz[x][y] = fill;
		floodFill8(x+1, y+0, fill, old);
		floodFill8(x+0, y+1, fill, old);
		floodFill8(x-1, y+0, fill, old);
		floodFill8(x+0, y-1, fill, old);
		
	}
}