#include <iostream>
#include <fstream>
#include <vector>


using namespace std;


//****************HEADER*******************
void RobertDowneyJr();
void ElementareWatson();
void merge(int* v, int start, int center, int end);
void mergesort(int* v, int start, int end);
int Max(int i, int j);
int NonTantoElementareWatson(int riga, int colonna, int contatore);

//***************VARIABILI*****************

int serate, momenti, travestimenti;
int** matrice;
int contaStampa;

// IL VALORE 1 CORRISPONDE A J
// IL VALORE 0 CORRISPONDE A H

//***************FUNZIONI******************
int main(){
	RobertDowneyJr();
	//ElementareWatson();
	int istanti = NonTantoElementareWatson(0,-1,0);

	cout<<"istanti:"<<istanti<<" con "<<contaStampa<<" travestimenti"<<endl;
	
	return 0;
}

//inizializza
void RobertDowneyJr(){
	
	ifstream in ("input.txt");
	in >> serate >> momenti >> travestimenti;

	matrice = new int*[serate];

	for(int i = 0; i < serate; i++){
		matrice[i] = new int[momenti];
	}

	for(int i = 0; i < serate; i++){
		for(int j = 0; j < momenti; j++){
			char s;
			in >> s;
			if(s == 'J') // la matrice contiene 1 se J e 0 se H
				matrice[i][j] = 1;
			else
				matrice[i][j] = 0;
		}
	}

	cout<<"N:"<<serate<<" m:"<<momenti<<" t:"<<travestimenti<<endl;
	cout<<"0:H 1:J"<<endl<<endl;

	cout<<"Matrice:"<<endl;
	for(int i = 0; i < serate; i++){
		for(int j = 0; j < momenti; j++){
			cout<<matrice[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

//caso base
void ElementareWatson(){
	vector<int> contaJ;
	vector<int> contaH;
	
	int coH =0; 
	int coJ = 0;

	for(int i = 0; i < serate; i++){
		for(int j = 0; j < momenti; j++){
			if(matrice[i][j] == 0)
				coH++;
			else
				coJ++;
			if(j == momenti-1){
				contaJ.push_back(coJ);
				contaH.push_back(coH);
			}
		}
		coH = 0;
		coJ = 0;
	}

	cout<<"stampo numero H"<<endl;
	for(int i = 0; i < contaH.size(); i++){
		cout<<contaH[i]<<" ";
	}

	cout<<endl<<"stampo numero J"<<endl;
	for(int i = 0; i < contaJ.size(); i++){
		cout<<contaJ[i]<<" ";
	}

	cout<<endl;

	//ordino vettore
	int* totali = new int[serate*2];

	for(int i = 0; i < serate*2; i+=2){
		totali[i] = 0;
	}

 int j = 0;
	for(int i = 0; i < serate*2; i+=2){
		totali[i] = contaH[j];
		totali[i+1] = contaJ[j];
		j++;
	}

	cout<<"totali:"<<endl;
	for(int i = 0; i < serate*2; i++){
		cout<<totali[i]<<" ";
	}
	cout<<endl;

	mergesort(totali,0,(serate*2)-1);

	cout<<"totali ordinati:"<<endl;
	for(int i = 0; i < serate*2; i++){
		cout<<totali[i]<<" ";
	}
	cout<<endl;

	//calcolo soluzione
	int soluzione=0;

	for(int i = 0; i < travestimenti; i++){
		soluzione+=totali[i];
	}

	cout<<"soluzione:"<<soluzione<<endl;

	ofstream out("output.txt");
	out<<soluzione;
}

//caso complicato:
/*
IDEA:
soluzione dinamica:
trovare il max(cambio vestito, non cambio vestito) tra tutte le serate tramite una funzione ricorsiva.
questo finchè non ho esaurito i travestimenti
*/
int NonTantoElementareWatson(int riga, int colonna, int contaTrav){
	//cout<<"riga:"<<riga<<" serate:"<<serate<<" colonna:"<<colonna<<" momenti:"<<momenti<<endl;
	if(riga == serate && colonna == momenti){
		contaStampa = contaTrav;
		return 1;
	}
	else{
		if(colonna<momenti)
			colonna++;
		else{
			riga++;
			colonna = 0;
		}
		//cout<<"contaTrav:"<<contaTrav<<" travestimenti:"<<travestimenti<<endl;
		if(contaTrav == travestimenti){
			contaStampa = contaTrav;
			return 1;
		}
		else{
			contaTrav++;		
			if(matrice[riga][colonna] == matrice[riga][colonna+1] && riga != 0 && colonna != 0)
				NonTantoElementareWatson(riga,colonna,contaTrav--)+1;
			else{
				Max(NonTantoElementareWatson(riga,colonna,contaTrav)+1,NonTantoElementareWatson(riga,colonna,contaTrav--));
			}
		}
	}
}

int Max(int i, int j){
	if(i>j)
		return i;
	else
		return j;
}


//ORDINAMENTO DECRESCENTE PER CASO BASE
void merge(int* v, int start, int center, int end){
  int s = start;
  int c = center+1;
  int supp[end-start];
  int i = 0;
  while(s<=center && c<=end){
    if(v[s] > v[c]){
      supp[i] = v[s];
      s++;
    }
    else{
      supp[i] = v[c];
      c++;
    }
    i++;
  }
  while(s<=center){
    supp[i] = v[s];
    s++;
    i++;
  }
  while(c<=end){
    supp[i] = v[c];
    c++;
    i++;
  }
  for(int i=start; i<=end; i++)
    v[i] = supp[i-start];
}
void mergesort(int* v, int start, int end){
  if(start<end){
    int center = (start+end)/2;
    mergesort(v,start,center);
    mergesort(v,center+1,end);
    merge(v,start,center,end);
  }
}

