#include<bits/stdc++.h>

using namespace std;

#define TAM 500000

int binSearch(int *v, int value){

    int first = 0, last = TAM, mid;

    while( first <= last ){

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

int seqSearch(int *v, int value){

    for(int i = 0; i < TAM; i++){
        if( value == v[i] )
            return i;
    }

    return -1;

}

int main(int argc, const char** argv) {
    
    int v[TAM];
    
    clock_t Ticks[2];
    Ticks[0] = clock();
    Ticks[1] = clock();
    double Tempo;

    for(int i = 0; i < 500000; i++)
        v[i] = i+1;

    // for(auto i:v)
    //     printf("%d\n",i);

    printf("Buscando primeiro elemento(1):\n");

    Ticks[0] = clock();
    seqSearch(v,1);
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Tempo gasto na busca sequencial: %g us.\n", Tempo);

    Ticks[0] = clock();
    binSearch(v,1);
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Tempo gasto na busca binária: %g us.\n", Tempo);

    printf("Buscando último elemento(500000):\n");

    Ticks[0] = clock();
    seqSearch(v,500000);
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Tempo gasto na busca sequencial: %g us.\n", Tempo);

    Ticks[0] = clock();
    binSearch(v,500000);
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Tempo gasto na busca binária: %g us.\n", Tempo);

    printf("Buscando elemento mediano(250000):\n");

    Ticks[0] = clock();
    seqSearch(v,250000);
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Tempo gasto na busca sequencial: %g us.\n", Tempo);

    Ticks[0] = clock();
    binSearch(v,250000);
    Ticks[1] = clock();
    Tempo = (double)((Ticks[1] - Ticks[0]) ) * 1000000.0/ CLOCKS_PER_SEC;
    printf("Tempo gasto na busca binária: %g us.\n", Tempo);

    //printf("%d %d\n", seqSearch(v,124999), binSearch(v,124999) );

    return 0;
}