#include<bits/stdc++.h>

using namespace std;

#define TAM 500000

int binSearch(int *v, int value, int &numIterations){

    int first = 0, last = TAM, mid;
    numIterations = 0;

    while( first <= last ){

        numIterations++;

        mid = first + ((last - first) / 2);

        if( value == v[mid] ){
            return mid;
        }
        else if( value < v[mid] ){
            last = mid - 1;
        }else{
            first = mid + 1;
        }

    }

    return -1;

}

int seqSearch(int *v, int value, int &numIterations){

    numIterations = 0;
    
    for(int i = 0; i < TAM; i++){
        numIterations++;
        if( value == v[i] )
            return i;
    }

    return -1;

}

int main(int argc, const char** argv) {
    
    int v[TAM];
    
    clock_t Ticks[2];
    double Tempo;
    int numIterations;

    for(int i = 0; i < 500000; i++)
        v[i] = i+1;

    printf("\nBuscando primeiro elemento(1):\n");

    Ticks[0] = clock();
    seqSearch(v,1,numIterations);
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Busca sequencial:\nTempo gasto = %g us\tNumero de iteracoes = %i.\n", Tempo, numIterations);

    Ticks[0] = clock();
    binSearch(v,1,numIterations);
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Busca Binaria:\nTempo gasto = %g us\tNumero de iteracoes = %i.\n", Tempo, numIterations);

    printf("\nBuscando último elemento(500000):\n");

    Ticks[0] = clock();
    seqSearch(v,500000,numIterations);
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Busca sequencial:\nTempo gasto = %g us\tNumero de iteracoes = %i.\n", Tempo, numIterations);

    Ticks[0] = clock();
    binSearch(v,500000,numIterations);
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Busca Binaria:\nTempo gasto = %g us\tNumero de iteracoes = %i.\n", Tempo, numIterations);

    printf("\nBuscando elemento mediano(250000):\n");

    Ticks[0] = clock();
    seqSearch(v,250000,numIterations);
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Busca sequencial:\nTempo gasto = %g us\tNumero de iteracoes = %i.\n", Tempo, numIterations);

    Ticks[0] = clock();
    binSearch(v,250000,numIterations);
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Busca Binaria:\nTempo gasto = %g us\tNumero de iteracoes = %i.\n", Tempo, numIterations);

    printf("\nBuscando 200 elementos aleatorios:\n");
    srand(time(NULL));
    int acumIterations = 0;

    Ticks[0] = clock();
    for(int i = 0; i < 200; i++){
        seqSearch(v, (rand() % 500000) + 1,numIterations);
        acumIterations += numIterations;
    }
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Busca sequencial:\nTempo gasto = %g us\tNumero de iteracoes = %i.\n", Tempo, acumIterations);
    acumIterations = 0;
    
    Ticks[0] = clock();
    for(int i = 0; i < 200; i++){
        binSearch(v, (rand() % 500000) + 1,numIterations);
        acumIterations += numIterations;
    }
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Busca Binaria:\nTempo gasto = %g us\tNumero de iteracoes = %i.\n", Tempo, acumIterations);

    return 0;
}