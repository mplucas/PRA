#include<bits/stdc++.h>

using namespace std;

class TableHash {

    public:

    vector<int> v;
    int m, slot;

    TableHash( int eme, int slots ){

        m = eme;
        slot = slots;
        v = vector<int>( eme * slots, INT_MAX );

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
        int index  = bucket * slot;
        int change = -1;

        for(int i = index + slot - 1; i >= index; i--){
            if( signature(v[i]) < sign )
                break;
            change = i;
        }

        if(change != -1){

            for(int i = index + slot - 1; i > change; i--){
                v[i] = v[i - 1];
            }

            v[change] = value;

        }

    }

    void printTable(){

        int slots = 0;

        for( auto t:v ){

            if( t == INT_MAX )
                cout << "-\t";
            else
                cout << t << "\t";

            slots++;
            if(slots == slot){
                slots = 0;
                cout << endl;
            }
        }
    }

};

int main(int argc, char const *argv[])
{

    srand(time(NULL));

    TableHash table = TableHash( 5, 3 );

    for(int i = 0; i < 20; i++){

        table.insert( ((rand() % 100) + 1) * 7 );

    }

    cout << endl << "Tabela com m = 5:" << endl;
    table.printTable();

    table = TableHash( 10, 3 );

    for(int i = 0; i < 20; i++){

        table.insert( ((rand() % 100) + 1) * 7 );

    }

    cout << endl << "Tabela com m = 10:" << endl;
    table.printTable();

    return 0;
}
