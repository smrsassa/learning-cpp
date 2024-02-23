/*

Solução do Exercício 2: Imprima os números de 1 a 5 usando do-while

*/

#include <iostream>
using namespace std;

int main()
{
    int contador = 1;

    // Loop
    do {
        cout << contador << "\n";
        ++contador;
    }
    while (contador <= 5);
}