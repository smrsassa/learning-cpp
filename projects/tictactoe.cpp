#include<iostream>
#include<stdlib.h>
#include <random>

using namespace std;

struct Move{ 
    int row, col; 
}; 
 
char computer, player, winner;

int position[9][2] = {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};

void drawBoard(char board[3][3]) {
    cout << "----++---++----" << endl;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++) {
            cout << "| ";
            if(board[i][j] == '-') {
                cout << " " << " |";
            }
            else{
                if(board[i][j]=='X') cout << "X |";
                else cout << "O |";
            }
        }
        cout << "\n----++---++----" << endl;
    }
}

int playerInput() {
    int play;
    do
    {
        cout << "Escolha a casa da jogada: " << endl;
        cin >> play;
    } while (play < 0 || play > 8);

    return play;
}

int computerInput() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribuicao(0, 8);

    return distribuicao(gen);
}

void makePlay(char board[3][3], int (*input)(), char playSimbol) {
    Move playPos;

    do
    {
        int posIndex = input();

        playPos.row = position[posIndex][0];
        playPos.col = position[posIndex][1];
    } while (board[playPos.row][playPos.col] != '-');

    board[playPos.row][playPos.col] = playSimbol;
}

bool endGame(char board[3][3]) {
    // Verificar linhas e colunas
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '-') {
            winner = board[i][0];
            return true;
        } else if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '-') {
            winner = board[0][i];
            return true;
        }
    }

    // Verificar diagonais
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '-') {
        winner = board[0][0];
        return true;
    } else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '-') {
        winner = board[0][2];
        return true;
    }

    // Empate
    int count = 0;
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board[row][col] != '-') count++;
        }
    }
    if (count == 9) return true;

    return false;
}

int main() {
    char board[3][3] = {{'-','-','-'},{'-','-','-'},{'-','-','-'}};

    int startPlayer;
    do
    {
        cout << "Digite 1 para Jogar Primeiro ou Digite 2 Para o Computador Jogar Primeiro: " << endl;
        cin >> startPlayer;
    } while (startPlayer < 1 || startPlayer > 2);
    computer = 'O';
    player = 'X';
    if (startPlayer == 2) {
        computer = 'X';
        player = 'O';

        makePlay(board, computerInput, computer);
    }

    while (true)
    {
        drawBoard(board);

        makePlay(board, playerInput, player);

        if (endGame(board))
            break;

        makePlay(board, computerInput, computer);

        if (endGame(board))
            break;
    }

    drawBoard(board);
    cout << "Ganhador: " << winner << endl;

    getchar();
    return 0;
}
