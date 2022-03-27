#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*
	Link to Github: https://github.com/ManHinnn0509/1102_Computer_Algorithm/tree/main/1-Strassen
*/

// c[][] is the array that stores the result
void subtractMatrix(int n, int a[][n], int b[][n], int c[][n]);
void addMatrix(int n, int a[][n], int b[][n], int c[][n]);

// Print r * c size from N * N matrix
void printMatrixPart(int N, int M[][N], int r, int c);

// I / O
void printMatrix(int row, int col, int m[][col]);
void scanInput(int row, int col, int a[][col]);

// For matrix joining / spliting / expanding (?)
void setSubMatrix(int n1, int n2, int iy, int ix, int a[][n2], int r[][n1]);
void joinMatrix(int n1, int n2, int iy, int ix, int a[][n1], int r[][n2]);
void enlarge(int r, int c, int A[][c], int N, int C[][N]);

// -.-
int max(int a, int b) {
	return (a > b ? a : b);
}

// Find nearest number thats 2^n
int findNearest(n) {
	double d = log2(n);
	int c = ceil(d);
	return (int) pow(2, c);
}

// Should I free memory ?
void strassen(int n, int a[][n], int b[][n], int c[][n]) {
	// printf("\n--- strassen - n = %d ---\n", n);
	// Calc it directly
	if (n <= 2) {
		int m1 = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
		int m2 = (a[1][0] + a[1][1]) * b[0][0];
		int m3 = a[0][0] * (b[0][1] - b[1][1]);
		int m4 = a[1][1] * (b[1][0] - b[0][0]);
		int m5 = (a[0][0] + a[0][1]) * b[1][1];
		int m6 = (a[1][0] - a[0][0]) * (b[0][0] + b[0][1]);
		int m7 = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1]);
		
		c[0][0] = m1 + m4 - m5 + m7;
		c[0][1] = m3 + m5;
		c[1][0] = m2 + m4;
		c[1][1] = m1 + m3 - m2 + m6;
	}
	
	else {
		int half = n / 2;
		
		// ----- Matrix A
		
		int A11[half][half];
		setSubMatrix(half, n, 0, 0, a, A11);
		
		int A12[half][half];
		// setSubMatrix(half, n, 0, 2, a, A12);
		setSubMatrix(half, n, 0, half, a, A12);
		
		int A21[half][half];
		// setSubMatrix(half, n, 2, 0, a, A21);
		setSubMatrix(half, n, half, 0, a, A21);
		
		int A22[half][half];
		// setSubMatrix(half, n, 2, 2, a, A22);
		setSubMatrix(half, n, half, half, a, A22);
		
		// ----- Matrix B
		
		int B11[half][half];
		setSubMatrix(half, n, 0, 0, b, B11);
		
		int B12[half][half];
		// setSubMatrix(half, n, 0, 2, b, B12);
		setSubMatrix(half, n, 0, half, b, B12);
		
		int B21[half][half];
		// setSubMatrix(half, n, 2, 0, b, B21);
		setSubMatrix(half, n, half, 0, b, B21);
		
		int B22[half][half];
		// setSubMatrix(half, n, 2, 2, b, B22);
		setSubMatrix(half, n, half, half, b, B22);
		
		// -----
		
		int temp1[half][half];
		int temp2[half][half];
		
		int M1[half][half];
		addMatrix(half, A11, A22, temp1);
		addMatrix(half, B11, B22, temp2);
		strassen(half, temp1, temp2, M1);
		
		int M2[half][half];
		addMatrix(half, A21, A22, temp1);
		strassen(half, temp1, B11, M2);
		
		int M3[half][half];
		subtractMatrix(half, B12, B22, temp1);
		strassen(half, A11, temp1, M3);
		
		int M4[half][half];
		subtractMatrix(half, B21, B11, temp1);
		strassen(half, A22, temp1, M4);
		
		int M5[half][half];
		addMatrix(half, A11, A12, temp1);
		strassen(half, temp1, B22, M5);
		
		int M6[half][half];
		subtractMatrix(half, A21, A11, temp1);
		addMatrix(half, B11, B12, temp2);
		strassen(half, temp1, temp2, M6);
		
		int M7[half][half];
		subtractMatrix(half, A12, A22, temp1);
		addMatrix(half, B21, B22, temp2);
		strassen(half, temp1, temp2, M7);
		
		// ---- C
		
		int C11[half][half];
		addMatrix(half, M1, M4, temp1);
		subtractMatrix(half, temp1, M5, temp2);
		addMatrix(half, temp2, M7, C11);
		
		int C12[half][half];
		addMatrix(half, M3, M5, C12);
		
		int C21[half][half];
		addMatrix(half, M2, M4, C21);
		
		int C22[half][half];
		addMatrix(half, M1, M3, temp1);
		subtractMatrix(half, temp1, M2, temp2);
		addMatrix(half, temp2, M6, C22);
		
		// printf("\n HALF = %d \n", half);
		/*
		printf("\n---\n");
		printMatrix(half, half, C11);
		printf("\n---\n");
		printMatrix(half, half, C12);
		printf("\n---\n");
		printMatrix(half, half, C21);
		printf("\n---\n");
		printMatrix(half, half, C22);
		*/
		
		
		joinMatrix(half, n, 0, 0, C11, c);
		joinMatrix(half, n, 0, half, C12, c);
		joinMatrix(half, n, half, 0, C21, c);
		joinMatrix(half, n, half, half, C22, c);
		
		// printf("\n===\n");
		// printMatrix(n, n, c);
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
	
	// ---
	
	int maxR = max(r1, r2);
	int maxC = max(c1, c2);
	int maxN = max(maxR, maxC);
	
	int N;
	N = findNearest(maxN);
	
	// ---
	
	
	// This step can be simplified so that the 2nd enlarge() function call is unnecessary
	// Maybe this will make the code faster?
	// But im too lazy lol
	int a2[r2][c2];
	scanInput(r2, c2, a2);
	
	// Make 3 N * N arrays
	int result[N][N];
	
	int A[N][N];
	enlarge(r1, c1, a1, N, A);
	
	int B[N][N];
	enlarge(r2, c2, a2, N, B);
	
	/*
	printf("\n--A--\n");
	printMatrix(N, N, A);
	
	printf("\n--B--\n");
	printMatrix(N, N, B);
	*/
	
	// Print ans	
	if (signal == 0) {
		// strassen(r1, a1, a2, result);
		strassen(N, A, B, result);
		
		printf("%d %d \n\n", r1, c2);
		
		/*
		int C[r1][c2];
		for (y = 0; y < r1; y++) {
			for (x = 0; x < c2; x++) {
				C[y][x] = result[y][x];
			}
		}
		printMatrix(r1, c2, C);
		*/
		
		// WTF THIS DOESNT WORK AND WTF?
		// Something to do with pointer or etc????
		/*
		printf("\n--- N x N (N = %d)---\n", N);
		printMatrix(N, N, result);

		printf("\n--- r1=%d x c2=%d ---\n", r1, c2);
		printMatrix(r1, c2, result);
		*/
		
		printMatrixPart(N, result, r1, c2);
		
		
	}
	
	// Print time
	else {
		clock_t start, end;
		start = clock();
		
		// strassen(r1, a1, a2, result);
		strassen(N, A, B, result);
		
        end = clock();
        double diff = end - start; // ms
        printf(" %lf," , diff);
	}
	
	return 0;
}



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
	int x = 0;
	int y = 0;
	
	for (y = 0; y < row; y++) {
		// printf("y = %d | ", y);
		
		for (x = 0; x < col; x++) {
			// printf("M[%d][%d] | ", y, x);
			int n = m[y][x];
			printf("%d ", n);
			// puts("");
		}
		if (y != row - 1) {
			puts("");
		}
		
	}
}

/*
The parameters are little fucked up
Heres a note for myself:

n1 <- Length of NEW array
n2 <- Length of original array

iy <- Starting index (y dir)
ix <- Starting index (x dir)

a[][] <- Original array
r[][] <- Result array
*/
void setSubMatrix(int n1, int n2, int iy, int ix, int a[][n2], int r[][n1]) {
	/*
	r[0][0] = a[iy][ix];
	r[0][1] = a[iy][ix + 1];
	r[1][0] = a[iy + 1][ix];
	r[1][1] = a[iy + 1][ix + 1];
	*/
	
	int x, y;
	int i, j;
	for (y = iy, j = 0; y < n2 && j < n1; y++, j++) {
		for (x = ix, i = 0; x < n2 && i < n1; x++, i++) {
			r[j][i] = a[y][x];
		}
	}
	
	/*
	printf("\n-- Original Matrix --\n");
	printMatrix(n2, n2, a);
	
	printf("\n-- New Sub Matrix --\n");
	printMatrix(n1, n1, r);
	*/
}

// Matrix subtraction
void subtractMatrix(int n, int a[][n], int b[][n], int c[][n]) {
	int x, y;
	
	for (y = 0; y < n; y++) {
		for (x = 0; x < n; x++) {		
			c[y][x] = a[y][x] - b[y][x];
		}
	}
}

// Matrix addition
void addMatrix(int n, int a[][n], int b[][n], int c[][n]) {
	int x, y;
	
	for (y = 0; y < n; y++) {
		for (x = 0; x < n; x++) {		
			c[y][x] = a[y][x] + b[y][x];
		}
	}
}

void joinMatrix(int n1, int n2, int iy, int ix, int a[][n1], int r[][n2]) {
	int x1, y1;
	int x2, y2;
	
	for (y1 = 0, y2 = iy; y1 < n1; y1++, y2++) {
		for (x1 = 0, x2 = ix; x1 < n1; x1++, x2++) {
			r[y2][x2] = a[y1][x1];
		}
	}
}

void printMatrixPart(int N, int M[][N], int r, int c) {
	int x, y;
	for (y = 0; y < N; y++) {
		for (x = 0; x < N; x++) {
			if (y < r && x < c) {
				int n = M[y][x];
				printf("%d ", n);
			}
		}
		
		if (y < r) {
			if (y != r - 1) {
				puts("");
			}
		}
	}
}

// Make r * c matrix to N * N matrix, also pad zeros to it
void enlarge(int r, int c, int A[][c], int N, int C[][N]) {
	int x, y;
	for (y = 0; y < N; y++) {
		for (x = 0; x < N; x++) {
			if (y < r && x < c) {
				// printf("HI");
				C[y][x] = A[y][x];
			}
			else {
				C[y][x] = 0;
			}
		}
	}
}
