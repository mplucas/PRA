/*Dada uma tabela hash de tamanho m = 9, função hash h(k) = k % m, com
encadeamento separado, mostre a tabela após a inserção das chaves 4, 23,
29, 15, 21, 43, 11, 5 e 10. Mostre também como ficaria a tabela após as
inserções se seu tamanho fosse m = 11. */

#include<bits/stdc++.h>

using namespace std;

class TableHash {       
    
    public:             

    vector<vector<int>> v;
    int m;

    TableHash( int eme ){

        m = eme;
        v = vector<vector<int>>( eme );

    }

    int h( int k ){
        return k % m;
    }

    void insert( int i ){
        v[ h(i) ].push_back( i );
    }

};

int main(int argc, char const *argv[])
{
    
    TableHash table9 = TableHash( 9 );

    table9.insert( 4 );
    table9.insert( 23 );
    table9.insert( 29 );
    table9.insert( 15 );
    table9.insert( 21 );
    table9.insert( 43 );
    table9.insert( 11 );
    table9.insert( 5 );
    table9.insert( 10 );

    cout << "Tabela com m = 9:" << endl;

    for( int i = 0; i < table9.v.size(); i++ ){

        cout << "Pos " << i << ":";

        for( auto v:table9.v[i] ){
            cout << " " << v;
        }

        cout << endl;

    }

    TableHash table11 = TableHash( 11 );

    table11.insert( 4 );
    table11.insert( 23 );
    table11.insert( 29 );
    table11.insert( 15 );
    table11.insert( 21 );
    table11.insert( 43 );
    table11.insert( 11 );
    table11.insert( 5 );
    table11.insert( 10 );

    cout << endl << "Tabela com m = 11:" << endl;

    for( int i = 0; i < table11.v.size(); i++ ){

        cout << "Pos " << i << ":";

        for( auto v:table11.v[i] ){
            cout << " " << v;
        }

        cout << endl;

    }

    cout << endl;

    return 0;
}
