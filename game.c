#include <stdio.h>

#define ROWS 10
#define COLS 10

typedef enum {
    DEAD = 0,
    ALIVE = 1,
} Cell;

char cell_chars[2] = {'.', '#'};

typedef struct {
    Cell cells[ROWS][COLS];
} Board;

void draw_board(Board *board)
{
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            putc(cell_chars[board->cells[row][col]], stdout);
        }
        putc('\n', stdout);
    }
}

int count_nbors(Board *board, int crow, int ccol)
{
    // ###
    // #.#
    // ###
    int result = 0;
    for (int drow = -1; drow <= 1; ++drow) {
        for (int dcol = -1; dcol <= 1; ++dcol) {
            int nrow = crow + drow;
            int ncol = ccol + dcol;
            if (0 <= nrow && nrow < ROWS) {
                if (0 <= ncol && ncol < COLS) {
                    if (!(drow == 0 && dcol == 0)) {
                        if (board->cells[nrow][ncol] == ALIVE) {
                            result += 1;
                        }
                    }
                }
            }
        }
    }
    return result;
}

void next_board(Board *current, Board *next)
{
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            int nbors = count_nbors(current, row, col);
            switch (current->cells[row][col]) {
            case ALIVE:
                next->cells[row][col] = nbors == 2 || nbors == 3 ? ALIVE : DEAD;
                break;
            case DEAD:
                next->cells[row][col] = nbors == 3 ? ALIVE : DEAD;
                break;
            }
        }
    }
}

Board board[2] = {0};

int main()
{
    // .#.
    // ..#
    // ###
    board[0].cells[0][1] = ALIVE;
    board[0].cells[1][2] = ALIVE;
    board[0].cells[2][0] = ALIVE;
    board[0].cells[2][1] = ALIVE;
    board[0].cells[2][2] = ALIVE;

    int current = 0;
    for (int i = 0; i < 1000; ++i) {
        int next = !current;
        draw_board(&board[current]);
        printf("------------------------------\n");
        next_board(&board[current], &board[next]);
        current = next;
    }

    return 0;
}
