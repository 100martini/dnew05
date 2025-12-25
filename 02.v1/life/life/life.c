#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct pen
{
    int x;
    int y;
    int is_down;
} pen;

void print_board(char **borad, int w, int h)
{
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
           putchar(borad[i][j]);
        putchar('\n');
    }
}

char** creat_board(int w, int h)
{
    char** board = (char **)malloc(sizeof(char **) * h);
    for(int i = 0; i < h; i++)
    {
        board[i] = (char *)malloc(sizeof(char *) * w);
        for(int j = 0; j < w; j++)
        {
            board[i][j] = ' ';
        }
    }
    return(board);
}

void free_board(char **borad, int w, int h)
{
    for(int i = 0; i < h; i++)
    {
        free(borad[i]);
    }
    free(borad);
}

int count(char **borad, int w, int h, int x, int y)
{
    int c = 0;
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if (!(i == 0 && j == 0) && j + x >= 0 && j + x < w && i + y >= 0 && i + y < h && borad[i + y][j + x] == 'O')
                c++;
        }
    }
    return(c);
}

void iter_game(char **borad, int w, int h)
{
    char **clone = creat_board(w, h);
    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            int c = count(borad, w, h, x, y);
            if ((borad[y][x] == 'O' && (c == 2 || c == 3)) || (borad[y][x] != 'O' && c == 3))
                clone[y][x] = 'O';
            else
                clone[y][x] = ' ';
        }
    }
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            borad[i][j] = clone[i][j];
        }
    }
    free_board(clone, w, h);
}


int main(int ac, char **av)
{
    if (ac != 4)
        return (1);
    int w = atoi(av[1]), h = atoi(av[2]), iter = atoi(av[3]);
    char **board = creat_board(w, h);
    char c;
    pen pen = {0,0,0};

    while(read(0, &c, 1))
    {
        if(c == 'x')
            pen.is_down = !pen.is_down;
        if(c == 'w' && pen.y > 0)
            pen.y--;
        if(c == 's' && pen.y < h - 1)
            pen.y++;
        if(c == 'a' && pen.x > 0)
            pen.x--;
        if(c == 'd' && pen.x < w - 1)
            pen.x++;
        if(pen.is_down)
            board[pen.y][pen.x] = 'O';
    }
    for(int i = 0; i < iter; i++)
        iter_game(board, w, h);
    print_board(board, w, h);
    free_board(board, w, h);
}