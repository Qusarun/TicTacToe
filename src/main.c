/* don't bully me for my shitty code pls */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* input */
char* get_input() {
    char* s = malloc(sizeof(char) * 8);
    fgets(s, 8, stdin);
    s[strcspn(s, "\n")] = 0;
    return s;
}

int* get_coordinates() {
    char* in = get_input();
    int* arr = malloc(sizeof(int) * 2);

    if (strlen(in) < 3)
        return NULL;
    
    if (in[1] != ' ' && in[1] != ',')
        return NULL;
    
    arr[0] = in[0] - '1';
    arr[1] = in[2] - '1';

    if (arr[0] < 0 || arr[0] > 2 || arr[1] < 0 || arr[1] > 2)
        return NULL;
    
    return arr;
}

/* displaying */
void print_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        printf("-------------\n");
        char* row = board[i];
        for (int j = 0; j < 3; j++)
            printf("| %c ", row[j] == 0 ? ' ' : row[j] == 1 ? 'o' : 'x');
        printf("|\n");
    }

    printf("-------------\n");
}

/* winning */
bool check(char a, char b, char c) { return a == b && b == c && a != 0; }

bool check_win(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (check(board[i][0], board[i][1], board[i][2]))
            return true;
        
        if (check(board[0][i], board[1][i], board[2][i]))
            return true;
    }

    if (check(board[0][0], board[1][1], board[2][2]))
        return true;
    
    if (check(board[2][0], board[1][1], board[0][2]))
        return true;

    return false;
}

/* main */
void start() {
    /* initialize the board */
    char board[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            board[i][j] = 0;
    }

    /* game loop */
    bool turn = 1;
    for (;;) {
        /* print the board */
        print_board(board);

        /* ask for input */
        printf("row,column (%c): ", turn ? 'x' : 'o');
        int* coords = get_coordinates();

        /* check if the coordinates are valid */
        if (coords == NULL) {
            printf("Invalid input, expected ROW,COLUMN\n");
            continue;
        }

        const int row = coords[0], column = coords[1];
        if (board[row][column]) {
            printf("This position is already occupied\n");
            continue;
        }

        /* set the tile */
        board[row][column] = turn + 1;

        /* check if the player has won */
        if (check_win(board)) {
            print_board(board);
            printf("Player %c won!\n", turn ? 'x' : 'o');
            break;
        }
        
        /* switch players */
        turn = !turn;
    }

    /* exiting / continuing */
    printf("Do you want to continue playing (y/n): ");
    char* input = get_input();
    if (strcmp(input, "y"))
        exit(0);
}

/* entry */
int main() {
    for (;;)
        start();
}
