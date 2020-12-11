#include <iostream>

using namespace std;

int main(){
    double tempo_total, aux;
    FILE *arquivo = fopen("Tempos.txt","r");

    while (!feof(arquivo))
    {
        fscanf(arquivo, "%lf", &aux);

        tempo_total += aux;
    }
    cout << "Tempo total de execução:" << tempo_total << " ms" << endl;    

    return 0;
}