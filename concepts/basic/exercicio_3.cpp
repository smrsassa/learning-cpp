/*

Solução do Exercício 3: Imprima os números ímpares entre 1 e 10 em ordem decrescente usando loop for.

*/

#include <iostream>
using namespace std;

int main()
{
    for (int count = 9; count >= 0; count -= 2)
        std::cout << count << ' ';

}
