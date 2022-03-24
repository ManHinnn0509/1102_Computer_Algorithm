#include <stdio.h>
#include <math.h>

int max(int a, int b) {
		return (a > b ? a : b);
		
}

int findNearest(n) {
		double d = log2(n);
			int c = ceil(d);
				return (int) pow(2, c);
				
}

void main() {
	int r1 = 11;
	int c1 = 4;
	int r2 = 4;
	int c2 = 28;
	
	int maxR = max(r1, r2);
	int maxC = max(c1, c2);
	int maxN = max(maxR, maxC);

	printf("maxN = %d\n", maxN);
	printf("Find Nearest = %d\n", findNearest(maxN));
}
