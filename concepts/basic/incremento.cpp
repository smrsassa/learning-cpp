#include <iostream>

int main() {
    int array[5] = {1, 2, 3, 4, 5};
    int i = 0;

    // Usando pós-incremento
    std::cout << "Usando pos-incremento:\n";
    while (i < 5) {
        std::cout << "Elemento " << i << ": " << array[i++] << std::endl;
    }

    std::cout << std::endl;

    i = 0; // Reiniciando i para 0

    // Usando pré-incremento
    std::cout << "Usando pre-incremento:\n";
    while (i < 5) {
        std::cout << "Elemento " << i << ": " << array[++i] << std::endl;
    }
    getchar();    return 0;
}
