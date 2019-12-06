//gcc -fopenmp -o program program.c

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




#include #include #include #include using namespace std; //******************************* //** Tutaj definiujemy funkcjÄ™ ** //******************************* double f(double x) { return sqrt(1-(x*x)); } //******************** //** Program gÅ‚Ã³wny ** //******************** int main() { int N; //liczba punktÃ³w/prostokÄ…tÃ³w podziaÅ‚owych double a,b,s,h; int i; cout << setprecision(3) // 3 cyfry po przecinku << fixed; // format staÅ‚oprzecinkowy cout << "Podaj liczbe prostokatow podzialowych\n\n" "N = "; cin >> N; if(N <= 0) { cout<< "Liczba prostokatow podzialowych musi byc wieksza od zera [N > 0],\nuruchom program ponownie i wprowadz poprawne dane\n"; return -1; } cout << "Podaj poczatek przedzialu calkowania\n\n" "a = "; cin >> a; cout << "\nPodaj koniec przedzialu calkowania\n\n" "b = "; cin >> b; if(a >= b) { cout << "Poczatek przedzialu musi byc mniejszy niz koniec [a < b],\nuruchom program ponownie i wprowadz poprawne dane\n"; return -1; } if(a > 1 || b > 1) { cout << "Wynik nie jest liczbÄ… rzeczywistÄ…, gdy [a,b > 1],\nuruchom program ponownie i wprowadz poprawne dane\n"; return -1; } cout << endl; #pragma omp parallel reduction (+:s) private(h) { s = 0; h = (b - a) / N; #pragma omp for nowait for(i = 1; i <= N; i++) { s += f(a + i * h); } s *= h; } cout << "Wartosc calki wynosi : " << setw(8) << s << endl << endl; return 0; }
