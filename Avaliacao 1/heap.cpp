#include <bits/stdc++.h>
#include <time.h>
using namespace std;
#define MAX 430000

void heapsort(char** lista,int n);
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

void heapsort(char** lista, int n) {
   int i = n / 2, pai, filho;
   char* t;
   while(true) {
      if (i > 0) {
          i--;
          t = lista[i];
      } else {
          n--;
          if (n <= 0) return;
          t = lista[n];
          lista[n] = lista[0];
      }
      pai = i;
      filho = i * 2 + 1;
      while (filho < n) {
          if ((filho + 1 < n)  &&  (strcmp(lista[filho + 1],lista[filho])) > 0 )
              filho++;
          if (strcmp(lista[filho],t) > 0) {
             lista[pai] = lista[filho];
             pai = filho;
             filho = pai * 2 + 1;
          } else {
             break;
          }
      }
      lista[pai] = t;
   }
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
  //mergesort(lista, MAX);
  heapsort(lista,MAX);

  putchar('\n');
  return 0;
}
