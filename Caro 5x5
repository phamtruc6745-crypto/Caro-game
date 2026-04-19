#include <stdio.h>
#include <stdbool.h>

#define SIZE 5 // Kich thuoc ban co 5x5

// 1. Su dung enum de tranh "magic numbers" nhu mo ta
typedef enum {
    NA = 0,     // O trong
    BLACK = 1,  // Quan den (Nguoi choi 1)
    WHITE = 2   // Quan trang (Nguoi choi 2)
} Stone;

// Khai bao ham
void initBoard(Stone board[SIZE][SIZE]);
void displayBoard(Stone board[SIZE][SIZE]);
bool checkWinner(Stone board[SIZE][SIZE], int row, int col, Stone player);

int main() {
    // 2. Su dung mang 2 chieu de bieu dien trang thai ban co
    Stone board[SIZE][SIZE];
    
    initBoard(board);
    
    Stone currentPlayer = BLACK; // Den di truoc
    int moves = 0;
    int maxMoves = SIZE * SIZE;
    
    printf("--- GAME CO CARO CO BAN ---\n");
    
    while (moves < maxMoves) {
        displayBoard(board);
        
        int row, col;
        char playerChar = (currentPlayer == BLACK) ? 'X' : 'O';
        
        printf("Luot cua quan %s (%c) - Nhap toa do (hang cot): ", 
               (currentPlayer == BLACK) ? "DEN" : "TRANG", playerChar);
        scanf("%d %d", &row, &col);
        
        // Kiem tra tinh hop le
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            printf("Toa do khong hop le!\n\n");
            continue;
        }
        if (board[row][col] != NA) {
            printf("O nay da co quan co!\n\n");
            continue;
        }
        
        // Cap nhat trang thai ban co (Game State)
        board[row][col] = currentPlayer;
        moves++;
        
        // TODO: Viet them ham checkWinner() o day de kiem tra thang thua

        // Kiem tra thang
        if (checkWinner(board, row, col, currentPlayer)) {
            displayBoard(board);
            printf("Quan %s thang!\n", (currentPlayer == BLACK) ? "DEN" : "TRANG");
            return 0;
}
        
        // Doi luot
        currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
    }
    
    printf("Ban co da kin, Hoa!\n");
    return 0;
}

// Ham khoi tao trang thai ban dau: Tat ca la NA (trong)
void initBoard(Stone board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = NA;
        }
    }
}

// Ham hien thi ban co dua tren Game State
void displayBoard(Stone board[SIZE][SIZE]) {
    printf("\n  ");
    for (int j = 0; j < SIZE; j++) printf("%d ", j);
    printf("\n");
    
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == NA) {
                printf(". ");
            } else if (board[i][j] == BLACK) {
                printf("X "); // Den bieu dien la X
            } else if (board[i][j] == WHITE) {
                printf("O "); // Trang bieu dien la O
            }
        }
        printf("\n");
    }
    printf("\n");
}

//Ham kiem tra chien thang 
bool checkWinner(Stone board[SIZE][SIZE], int row, int col, Stone player) {
    int count;
    int WIN = 5;

    // Kiem tra hang
    count = 1;
    for (int j = col - 1; j >= 0 && board[row][j] == player; j--) count++;
    for (int j = col + 1; j < SIZE && board[row][j] == player; j++) count++;
    if (count >= WIN) return true;

    // Kiem tra cot
    count = 1;
    for (int i = row - 1; i >= 0 && board[i][col] == player; i--) count++;
    for (int i = row + 1; i < SIZE && board[i][col] == player; i++) count++;
    if (count >= WIN) return true;

    // Kiem tra duong cheo chinh (\)
    count = 1;
    for (int i = 1; row - i >= 0 && col - i >= 0 && board[row - i][col - i] == player; i++) count++;
    for (int i = 1; row + i < SIZE && col + i < SIZE && board[row + i][col + i] == player; i++) count++;
    if (count >= WIN) return true;

    // Kiem tra duong cheo phu (/)
    count = 1;
    for (int i = 1; row - i >= 0 && col + i < SIZE && board[row - i][col + i] == player; i++) count++;
    for (int i = 1; row + i < SIZE && col - i >= 0 && board[row + i][col - i] == player; i++) count++;
    if (count >= WIN) return true;

    return false;
}
