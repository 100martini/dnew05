#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>


typedef struct {
    int rows;
    int cols;
    char empty;
    char obstacle;
    char full;
    char **map;
    int **dp;
} t_bsq;

void print_map_error(void) {
    fprintf(stderr, "map error\n");
}

int min3(int a, int b, int c) {
    int min_val = a;
    if (b < min_val)
        min_val = b;
    if (c < min_val)
        min_val = c;
    return min_val;
}

int allocate_map(t_bsq *bsq) {
    int i;
    
    bsq->map = malloc(sizeof(char *) * bsq->rows);
    if (!bsq->map)
        return 0;
    
    for (i = 0; i < bsq->rows; i++) {
        bsq->map[i] = malloc(sizeof(char) * (bsq->cols + 1));
        if (!bsq->map[i]) {
            while (--i >= 0)
                free(bsq->map[i]);
            free(bsq->map);
            return 0;
        }
    }
    
    bsq->dp = malloc(sizeof(int *) * bsq->rows);
    if (!bsq->dp) {
        for (i = 0; i < bsq->rows; i++)
            free(bsq->map[i]);
        free(bsq->map);
        return 0;
    }
    
    for (i = 0; i < bsq->rows; i++) {
        bsq->dp[i] = malloc(sizeof(int) * bsq->cols);
        if (!bsq->dp[i]) {
            while (--i >= 0)
                free(bsq->dp[i]);
            free(bsq->dp);
            for (i = 0; i < bsq->rows; i++)
                free(bsq->map[i]);
            free(bsq->map);
            return 0;
        }
    }
    
    return 1;
}

int parse_first_line(char *line, t_bsq *bsq) {
    int len = strlen(line);
    int i;
    
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
        len--;
    }
    if (len < 4)
        return 0;
    bsq->full = line[len - 1];
    bsq->obstacle = line[len - 2];
    bsq->empty = line[len - 3];
    if (bsq->empty == bsq->obstacle || bsq->empty == bsq->full || bsq->obstacle == bsq->full)
        return 0;
    bsq->rows = 0;
    for (i = 0; i < len - 3; i++) {
        if (line[i] < '0' || line[i] > '9')
            return 0;
        bsq->rows = bsq->rows * 10 + (line[i] - '0');
    }
    
    return bsq->rows > 0;
}

int validate_char(char c, t_bsq *bsq) {
    return (c == bsq->empty || c == bsq->obstacle || c == bsq->full);
}

int parse_map(FILE *fp, t_bsq *bsq) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int i, j;
    
    read = getline(&line, &len, fp);
    if (read == -1) {
        if (line) free(line);
        return 0;
    }
    if (!parse_first_line(line, bsq)) {
        free(line);
        return 0;
    }
    free(line);
    line = NULL;
    read = getline(&line, &len, fp);
    if (read == -1) {
        if (line) free(line);
        return 0;
    }
    bsq->cols = 0;
    while (line[bsq->cols] && line[bsq->cols] != '\n')
        bsq->cols++;
    
    if (bsq->cols == 0) {
        free(line);
        return 0;
    }
    if (!allocate_map(bsq)) {
        free(line);
        return 0;
    }
    for (j = 0; j < bsq->cols; j++) {
        if (!validate_char(line[j], bsq)) {
            free(line);
            return 0;
        }
        bsq->map[0][j] = line[j];
    }
    bsq->map[0][bsq->cols] = '\0';
    
    free(line);
    line = NULL;
    for (i = 1; i < bsq->rows; i++) {
        read = getline(&line, &len, fp);
        if (read == -1) {
            if (line) free(line);
            return 0;
        }
        
        int line_len = 0;
        while (line[line_len] && line[line_len] != '\n')
            line_len++;
        
        if (line_len != bsq->cols) {
            free(line);
            return 0;
        }
        
        for (j = 0; j < bsq->cols; j++) {
            if (!validate_char(line[j], bsq)) {
                free(line);
                return 0;
            }
            bsq->map[i][j] = line[j];
        }
        bsq->map[i][bsq->cols] = '\0';
        
        free(line);
        line = NULL;
    }
    
    return 1;
}

int solve_bsq(t_bsq *bsq, int *max_i, int *max_j, int *max_size) {
    int i, j;
    
    *max_size = 0;
    *max_i = 0;
    *max_j = 0;
    
    for (i = 0; i < bsq->rows; i++) {
        for (j = 0; j < bsq->cols; j++) {
            if (bsq->map[i][j] != bsq->empty) {
                bsq->dp[i][j] = 0;
            } else if (i == 0 || j == 0) {
                bsq->dp[i][j] = 1;
            } else {
                bsq->dp[i][j] = min3(bsq->dp[i-1][j], bsq->dp[i][j-1], bsq->dp[i-1][j-1]) + 1;
            }
            if (bsq->dp[i][j] > *max_size || 
                (bsq->dp[i][j] == *max_size && i - bsq->dp[i][j] + 1 < *max_i - *max_size + 1) ||
                (bsq->dp[i][j] == *max_size && i - bsq->dp[i][j] + 1 == *max_i - *max_size + 1 && 
                 j - bsq->dp[i][j] + 1 < *max_j - *max_size + 1)) {
                *max_size = bsq->dp[i][j];
                *max_i = i;
                *max_j = j;
            }
        }
    }
    
    return 1;
}
void print_solution(t_bsq *bsq, int max_i, int max_j, int max_size) {
    int i, j;
    int start_i = max_i - max_size + 1;
    int start_j = max_j - max_size + 1;
    
    for (i = 0; i < bsq->rows; i++) {
        for (j = 0; j < bsq->cols; j++) {
            if (i >= start_i && i <= max_i && j >= start_j && j <= max_j) {
                printf("%c", bsq->full);
            } else {
                printf("%c", bsq->map[i][j]);
            }
        }
        printf("\n");
    }
}

void free_bsq(t_bsq *bsq) {
    int i;
    
    if (bsq->map) {
        for (i = 0; i < bsq->rows; i++) {
            if (bsq->map[i])
                free(bsq->map[i]);
        }
        free(bsq->map);
        bsq->map = NULL;
    }
    
    if (bsq->dp) {
        for (i = 0; i < bsq->rows; i++) {
            if (bsq->dp[i])
                free(bsq->dp[i]);
        }
        free(bsq->dp);
        bsq->dp = NULL;
    }
}

void process_map(FILE *fp) {
    t_bsq bsq = {0};
    int max_i, max_j, max_size;
    
    if (!parse_map(fp, &bsq)) {
        print_map_error();
        free_bsq(&bsq);
        return;
    }
    
    if (!solve_bsq(&bsq, &max_i, &max_j, &max_size)) {
        print_map_error();
        free_bsq(&bsq);
        return;
    }
    
    print_solution(&bsq, max_i, max_j, max_size);
    free_bsq(&bsq);
}

int main(int argc, char **argv) {
    FILE *fp;
    int i;
    
    if (argc == 1) {
        process_map(stdin);
    } else {
        for (i = 1; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (!fp) {
                print_map_error();
                continue;
            }
            
            process_map(fp);
            fclose(fp);
            if (i < argc - 1) {
                printf("\n");
            }
        }
    }
    return 0;
}