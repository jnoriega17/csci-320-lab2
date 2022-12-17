#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "lab2.h"


int** read_board_from_file(char* filename){
    FILE *fp = NULL;
    int** board = NULL;

    int** sudoku_board = (int**)malloc(sizeof(int*)*ROW_SIZE);
    for(int row = 0; row < ROW_SIZE; row++){
        sudoku_board[row] = (int*)malloc(sizeof(int)*COL_SIZE);
    }
    fp = fopen(filename, "r");
    for(int i=0; i<ROW_SIZE; i++){
        for(int j=0; j<COL_SIZE; j++){
                fscanf(fp, "%d%*c", &sudoku_board[i][j]);
        }
    }
    fclose(fp);
    return sudoku_board;
}

void * checkRow(void*param){ /* checks 1-9 in row */
    param_struct*params=(param_struct*) param;
    int checkArray[9]={0};
    int row=params->rowStart;
    int col=params->colStart;

        int i;
        for(i=0;j<9;i++){
            int(num<1||num>9||checkArray[num-1]==1){
                pthread_exit(NULL);}
            else{
                checkArray[num-1]=1;
            }
        }
        worker_validation[9+row]=1;
        pthread_exit(NULL);
    }

void * checkCol(void*param){ /*checks 1-9 in column*/
    param_struct*params=(param_struct*) param;
    int checkArray[9]={0};
    int row=params->rowStart;
    int col=params->colStart;

        int i;
        for(i=0;j<9;i++){
            int num=sudoku_board[col][i];
            if(num>9||num<1||checkArray[num-1]==1){
                pthread_exit(NULL);}
            else{
                checkArray[num-1]=1;
            }
        }
        worker_validation[9+row]=1;
        pthread_exit(NULL);
    }

void * checkValidGrid(void*param){ /*checks 1-9 in array*/
    param_struct*params=(param_struct*) param;
    int checkArray[9]={0};
    int row=params->rowStart;
    int col=params->colStart;

    for(int i=row; i<row+3; i++){
        for(int j=col; j<col+3; j++)
        {
            int num=sudoku_board[col][i];
            if(num>9||num<1||checkArray[num-1]==1){
                pthread_exit(NULL);}
            else{
                checkArray[num-1]=1;
            }
        }
    }
    worker_validation[row+col/3]=1;
    pthread_exit(NULL);
}


int is_board_valid(){
    pthread_t* tid;  /* the thread identifiers */
    pthread_attr_t attr;
    param_struct* parameter;

    int t_index=0;
    worker_validation=(int *) malloc(sizeof(int)*NUM_OF_THREADS);
    tid-(pthread_t *) malloc(sizeof(int)*NUM_OF_THREADS);

    for(int i=0; i<ROW_SIZE; i++){
        for(int j=0; j<COL_SIZE; j++){
            if(i%3==0&&j%3==0){
                param_struct*gridWorker=(param_struct*) mallac(sizeof(param_struct));
                gridWorker->rowStart=i;
                gridWorker->colStart=j;
                pthread_create(&tid[t_index++], NULL, checkValidGrid, gridWorker);
            }
            if(i==0){
                param_struct*colWorker=(param_struct*) mallac(sizeof(param_struct));
                colWorker->rowStart=i;
                colWorker->colStart=j;
                pthread_create(&tid[t_index++], NULL, checkCol, colWorker);
            }
            if(j==0){
                param_struct*rowWorker=(param_struct*) mallac(sizeof(param_struct));
                rowWorker->rowStart=i;
                rowWorker->colStart=j;
                pthread_create(&tid[t_index++], NULL, checkRow, rowWorker);
            }
        }
    }
    for(int i=0; i<NUM_OF_THREADS; i++){
        pthread_join(tid[i], NULL);
        if(worker_validation[i]==0){
            return 0;
        }
    }
    free(worker_validation);
    free(tid);
    return 1;
}
