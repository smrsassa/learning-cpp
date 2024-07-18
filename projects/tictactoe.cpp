#include <iostream>
#include <limits>

using namespace std;

struct Move {
    int row, col;
};

const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY = '-';
char computer, player, winner;

char board[3][3] = {{EMPTY, EMPTY, EMPTY}, {EMPTY, EMPTY, EMPTY}, {EMPTY, EMPTY, EMPTY}};
int position[9][2] = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};

void drawBoard() {
    cout << "----++---++----" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "| ";
            if (board[i][j] == EMPTY) {
                cout << " " << " |";
            } else {
                cout << board[i][j] << " |";
            }
        }
        cout << "\n----++---++----" << endl;
    }
}

bool checkWinner(char tempBoard[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (tempBoard[i][0] == tempBoard[i][1] && tempBoard[i][1] == tempBoard[i][2] && tempBoard[i][0] != EMPTY) {
            winner = tempBoard[i][0];
            return true;
        } else if (tempBoard[0][i] == tempBoard[1][i] && tempBoard[1][i] == tempBoard[2][i] && tempBoard[0][i] != EMPTY) {
            winner = tempBoard[0][i];
            return true;
        }
    }

    if (tempBoard[0][0] == tempBoard[1][1] && tempBoard[1][1] == tempBoard[2][2] && tempBoard[0][0] != EMPTY) {
        winner = tempBoard[0][0];
        return true;
    } else if (tempBoard[0][2] == tempBoard[1][1] && tempBoard[1][1] == tempBoard[2][0] && tempBoard[0][2] != EMPTY) {
        winner = tempBoard[0][2];
        return true;
    }

    return false;
}

bool isDraw(char tempBoard[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tempBoard[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

bool endGame() {
    if (checkWinner(board) || isDraw(board)) {
        return true;
    }
    return false;
}

int playerInput() {
    int play;
    do {
        cout << "Escolha a casa da jogada: " << endl;
        cin >> play;
    } while (play < 0 || play > 8 || board[position[play][0]][position[play][1]] != EMPTY);

    return play;
}

int minimax(char tempBoard[3][3], int depth, bool isMaximizing) {
    if (checkWinner(tempBoard)) {
        return (winner == computer) ? 1 : -1;
    }
    if (isDraw(tempBoard)) {
        return 0;
    }

    if (isMaximizing) {
        int bestScore = -numeric_limits<int>::infinity();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tempBoard[i][j] == EMPTY) {
                    tempBoard[i][j] = computer;
                    int score = minimax(tempBoard, depth + 1, false);
                    tempBoard[i][j] = EMPTY;
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::infinity();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tempBoard[i][j] == EMPTY) {
                    tempBoard[i][j] = player;
                    int score = minimax(tempBoard, depth + 1, true);
                    tempBoard[i][j] = EMPTY;
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

int computerInput() {
    int bestScore = -numeric_limits<int>::infinity();
    Move bestMove;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = computer;
                int score = minimax(board, 0, false);
                board[i][j] = EMPTY;
                if (score > bestScore) {
                    bestScore = score;
                    bestMove.row = i;
                    bestMove.col = j;
                }
            }
        }
    }
    return bestMove.row * 3 + bestMove.col;
}

void makePlay(int (*input)(), char playSimbol) {
    Move playPos;

    do {
        int posIndex = input();

        playPos.row = position[posIndex][0];
        playPos.col = position[posIndex][1];
    } while (board[playPos.row][playPos.col] != EMPTY);

    board[playPos.row][playPos.col] = playSimbol;
}

int main() {
    int startPlayer;
    do {
        cout << "Digite 1 para Jogar Primeiro ou Digite 2 Para o Computador Jogar Primeiro: " << endl;
        cin >> startPlayer;
    } while (startPlayer < 1 || startPlayer > 2);

    computer = PLAYER_O;
    player = PLAYER_X;
    if (startPlayer == 2) {
        computer = PLAYER_X;
        player = PLAYER_O;
        makePlay(computerInput, computer);
    }

    while (true) {
        drawBoard();

        makePlay(playerInput, player);

        if (endGame())
            break;

        makePlay(computerInput, computer);

        if (endGame())
            break;
    }

    drawBoard();
    if (checkWinner(board)) {
        cout << "Ganhador: " << winner << endl;
    } else {
        cout << "Empate!" << endl;
    }

    return 0;
}
