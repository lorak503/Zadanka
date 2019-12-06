#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

bool czy_spelnia(float x, float y) {
    if(y <= (4/(1+x*x))) {
        return true;
    }
    return false;
}

double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int main() {
    srand(time(NULL));
    int N = 100000000;
    int zliczanie = 0;
    //scanf("%d", &N);
	if(N <= 0){
		printf("Niepoprawne N(musi byc N>0) - zamykanie programu");
		return 0;
	}
	double start = omp_get_wtime();
    #pragma omp parallel for num_threads(4) reduction(+: zliczanie)
	for(int i = 0; i < N; i++) {
        double x = randfrom(0.0, 1.0);
        double y = randfrom(0.0, 4.0);
        if(czy_spelnia(x, y)) {
            zliczanie++;
        }
	}
	double wynik = (double)zliczanie / (double)N;
	printf("%d %d %lf", zliczanie, N, wynik);
	printf("(CZAS: %f)", omp_get_wtime() - start);
	return 0;

}
