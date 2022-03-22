#include <stdio.h>
#include <time.h>

/*
	This script is for checking if the error occurs because of the output format
	
	See my previous submitions for the Strassen method (Still working on it)
*/

void scanInput(int row, int col, int a[][col]) {
	int x, y;
	int temp;
	char ignored;

	for (y = 0; y < row; y++) {
		for (x = 0; x < col; x++) {
			scanf("%d%c", &temp, &ignored);
			
			a[y][x] = temp;
			if (ignored == '\n') {
				break;
			}
		}
	}
}

// For checking if the input is correct
void printMatrix(int row, int col, int m[][col]) {
	int x, y;
	
	for (y = 0; y < row; y++) {
		for (x = 0; x < col; x++) {
			printf("%d ", m[y][x]);
		}
		if (y != row - 1) {
			puts("");
		}
		
	}
}

void multiply(int r1, int c1, int r2, int c2, int a[][c1], int b[][c2], int c[][c2]) {
	int x, y, z;
	for (x = 0; x < r1; x++) {
		for (y = 0; y < c2; y++) {
			c[x][y] = 0;
			for (z = 0; z < c1; z++) {
				c[x][y] += a[x][z] * b[z][y];
			}
		}
	}
}

int main(void) {
	int x, y, z;
	int temp;
	char ignored;
	
	int signal;
	scanf("%d\n", &signal);
	
	// ---
	
	int r1, c1;
	scanf("%d %d\n", &r1, &c1);
	
	int a1[r1][c1];
	scanInput(r1, c1, a1);
	
	// ---
	
	int r2, c2;
	scanf("%d %d\n", &r2, &c2);
	
	int a2[r2][c2];
	scanInput(r2, c2, a2);
	
	int result[r1][c2];
	
	// Print ans
	if (signal == 0) {
		// strassen(r1, a1, a2, result);
		multiply(r1, c1, r2, c2, a1, a2, result);
		printf("%d %d \n\n", r1, c2);
		printMatrix(r1, c2, result);
	}
	
	// Print time
	else {
		clock_t start, end;
		start = clock();
		
		// strassen(r1, a1, a2, result);
		multiply(r1, c1, r2, c2, a1, a2, result);
		
        end = clock();
        double diff = end - start; // ms
        printf(" %lf," , diff);
	}
	
	return 0;
}
