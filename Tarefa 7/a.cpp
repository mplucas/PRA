#include<bits/stdc++.h>

using namespace std;

class TableHash {

    public:

    vector<int> v;
    int m, slots;
    FILE *fp;

    TableHash( int newM, int newSlots ){

        m = newM;
        slots = newSlots;
        v = vector<int>( newM );

        createArq();

    }

    void createArq(){

        int max = INT_MAX;

        if ((fp = fopen("arquivo.bin", "w")) == NULL)
        {
            printf("Erro na criação do arquivo");
            exit(1);
        }

        if (fwrite( &max, sizeof(int), m * slots, fp ) != (unsigned)(m * slots)) {
            printf("Erro na escrita do arquivo\n");
        }

        fclose(fp);

    }

    int h( int k ){
        return k % m;
    }

    int signature( int k ){
        return k / m;
    }

    void insert( int value ){

        int bucket = h(value);
        int sign   = signature(value);
        int index  = bucket * slots;
        int change = -1;

        for(int i = index + slots - 1; i >= index; i--){
            if( signature(v[i]) < sign )
                break;
            change = i;
        }

        if(change != -1){

            for(int i = index + slots - 1; i > change; i--){
                v[i] = v[i - 1];
            }

            v[change] = value;

        }

    }

    // void printTable(){

    //     int auxSlots = 0;

    //     for( auto t:v ){

    //         if( t == INT_MAX )
    //             cout << "-\t";
    //         else
    //             cout << t << "\t";

    //         auxSlots++;
    //         if(auxSlots == slots){
    //             auxSlots = 0;
    //             cout << endl;
    //         }
    //     }
    // }

};

int main(int argc, char const *argv[])
{

    srand(time(NULL));

    TableHash table = TableHash( 5, 3 );

    for(int i = 0; i < 20; i++){

        table.insert( ((rand() % 100) + 1) * 7 );

    }

    cout << endl << "Tabela com m = 5:" << endl;
    //table.printTable();
    
    return 0;
}
