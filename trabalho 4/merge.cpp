#include <bits/stdc++.h>
#include <time.h>
using namespace std;
#define MAX 430000

void mergesort(char** lista, int n);
void sort(char** lista, char **c, int i, int f);
void merge(char** lista, char **c, int i, int m, int f);
const vector<string> explode(const string& s, const char& c);

const vector<string> explode(const string& s, const char& c)
{
	string buff{""};
	vector<string> v;

	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);

	return v;
}

void mergesort(char** lista, int n) {
  char **c = (char**) malloc(sizeof(char*) * n);
  sort(lista, c, 0, n - 1);
  free(c);
}

/*
  Dado um vetor de inteiros v e dois inteiros i e f, ordena o vetor v[i..f] em ordem crescente.
  O vetor c é utilizado internamente durante a ordenação.
*/
void sort(char** lista, char **c, int i, int f) {
  if (i >= f) return;

  int m = (i + f) / 2;

  sort(lista, c, i, m);
  sort(lista, c, m + 1, f);

  /* Se v[m] <= v[m + 1], então v[i..f] já está ordenado. */
  if (strcmp(lista[m],lista[m + 1]) <= 0){
    return;
  }

  merge(lista, c, i, m, f);
}


/*
  Dado um vetor v e três inteiros i, m e f, sendo v[i..m] e v[m+1..f] vetores ordenados,
  coloca os elementos destes vetores, em ordem crescente, no vetor em v[i..f].
*/
void merge(char** lista, char **c, int i, int m, int f) {
  int z, iv = i, ic = m + 1;

  for (z = i; z <= f; z++) c[z] = lista[z];

  z = i;

  while (iv <= m && ic <= f) {
    /* Invariante: v[i..z] possui os valores de v[iv..m] e v[ic..f] em ordem crescente. */

    if (strcmp(c[iv],c[ic]) < 0) /*c[iv] < c[ic])*/ {
      lista[z++] = c[iv++];
    } else {
      lista[z++] = c[ic++];
    }
  }

  while (iv <= m) lista[z++] = c[iv++];

  while (ic <= f) lista[z++] = c[ic++];
}
  

int main () {
  string line;
  char* lista[MAX];
  int i = 0;
  ifstream myfile ("avaliacao1.DB.senhas.txt"); // ifstream = padrão ios:in
  if (myfile.is_open()) {
    while (! myfile.eof() ) {
      getline (myfile,line);

    	vector<string> v{explode(line, ' ')};
      lista[i] = (char*) malloc(sizeof(char*)*stoi(v[0]));
      strcpy(lista[i],v[2].c_str());
      i++;
    }
    myfile.close();
  } else {
    cout << "Unable to open file";
  }
  mergesort(lista, MAX);

  putchar('\n');
  return 0;
}
