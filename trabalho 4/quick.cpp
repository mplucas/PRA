#include <bits/stdc++.h>
#include <time.h>
using namespace std;
#define MAX 430000

void swap(char** a, char** b);
int partition (char** lista, int low, int high);
void quickSort(char ** lista, int low, int high);
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

void swap(char** a, char** b)  
{  
    char* t; 
    t = *a;  
    *a = *b;  
    *b = t;  
}  
  
/* This function takes last element as pivot, places  
the pivot element at its correct position in sorted  
array, and places all smaller (smaller than pivot)  
to left of pivot and all greater elements to right  
of pivot */
int partition (char** lista, int low, int high)  
{  
    char* pivot; 
    pivot = lista[high]; // pivot  
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (strcmp(lista[j],pivot) < 0)  
        {  
            i++; // increment index of smaller element  
            swap(&lista[i], &lista[j]);  
        }  
    }  
    swap(&lista[i + 1], &lista[high]);  
    return (i + 1);  
}  
  
/* The main function that implements QuickSort  
arr[] --> Array to be sorted,  
low --> Starting index,  
high --> Ending index */
void quickSort(char ** lista, int low, int high)  
{  
    if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partition(lista, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSort(lista, low, pi - 1);  
        quickSort(lista, pi + 1, high);  
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

  quickSort(lista,0,MAX);

  putchar('\n');
  return 0;
}
