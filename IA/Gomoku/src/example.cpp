#include "../includes/pisqpipe.h"
#include<stdlib.h>
#include<cstdio>
const char *infotext="name=\"Random\", author=\"Petr Lastovicka\", version=\"3.2\", country=\"Czech Republic\", www=\"https://plastovicka.github.io\"";

#define MAX_BOARD 100
int board[MAX_BOARD][MAX_BOARD];
static unsigned seed;


void brain_init() 
{
  if(width>MAX_BOARD || height>MAX_BOARD){
    width = height = 0;
    pipeOut("ERROR Maximal board size is %d", MAX_BOARD);
    return;
  }
  seed=start_time;
  pipeOut("OK");
}

void brain_restart()
{
  int x,y;
  for(x=0; x<width; x++){
    for(y=0; y<height; y++){
      board[x][y]=0;
    }
  }
  pipeOut("OK");
}

int isFree(int x, int y)
{
  return x>=0 && y>=0 && x<width && y<height && board[x][y]==0;
}

void brain_my(int x,int y)
{
  if(isFree(x,y)){
    board[x][y]=1;
  }else{
    pipeOut("ERROR my move [%d,%d]",x,y);
  }
}

void brain_opponents(int x,int y) 
{
  if(isFree(x,y)){
    board[x][y]=2;
  }else{
    pipeOut("ERROR opponents's move [%d,%d]",x,y);
  }
}

void brain_block(int x,int y)
{
  if(isFree(x,y)){
    board[x][y]=3;
  }else{
    pipeOut("ERROR winning move [%d,%d]",x,y);
  }
}

int brain_takeback(int x,int y)
{
  if(x>=0 && y>=0 && x<width && y<height && board[x][y]!=0){
    board[x][y]=0;
    return 0;
  }
  return 2;
}

unsigned rnd(unsigned n)
{
  seed=seed*367413989+174680251;
  return rand() % n;
}

int brain_place(int *x, int *y,int which) {
    int count = 0;
    int maxcount = 0;
    for (int j = 0; j < width; j++) {
        for (int k = 0; k < height; k++) {
            if (board[j][k] == which) {
              for (count = 0;board[j][k + count + 1] == which;count++);
              if (isFree(j,k + count + 1) && count >= maxcount) {
                *x = j;
                *y = k + count + 1;
                while(board[j][k + count + 2] == which)
                  count++;
                maxcount = count;
              }
              for (count = 0;board[j][k - count - 1] == which;count++);
              if (isFree(j,k - count - 1) && count >= maxcount) {
                *x = j;
                *y = k - count - 1;
                while(board[j][k - count - 2] == which)
                  count++;
                maxcount = count;
              }
              for (count = 0;board[j + count + 1][k] == which;count++);
              if (isFree(j + count + 1,k)  && count >= maxcount) {
                *x = j + count + 1;
                *y = k;
                while(board[j + count + 2][k] == which)
                  count++;
                maxcount = count;
              }
              for (count = 0;board[j - count - 1][k] == which;count++);
                if (isFree(j - count - 1,k) && count >= maxcount) {
                  *x = j - count - 1;
                  *y = k;
                  while(board[j - count - 2][k] == which)
                    count++;
                  maxcount = count;
                }
              for (count = 0;board[j - count - 1][k - count - 1] == which;count++);
                if (isFree(j - count - 1,k - count - 1) && count >= maxcount) {
                  *x = j - count - 1;
                  *y = k - count - 1;
                  while(board[j - count - 2][k - count - 2] == which)
                    count++;
                  maxcount = count;
                }
                for (count = 0;board[j - count - 1][k + count + 1] == which;count++);
                if (isFree(j - count - 1,k + count + 1) && count >= maxcount) {
                  *x = j - count - 1;
                  *y = k + count + 1;
                  while(board[j - count - 2][k +  count + 2] == which)
                    count++;
                  maxcount = count;
                }
              for (count = 0;board[j + count + 1][k - count - 1] == which;count++);
                if (isFree(j + count + 1,k - count - 1) && count >= maxcount) {
                  *x = j + count + 1;
                  *y = k - count - 1;
                  while (board[j + count + 2][k - count - 2] == which)
                    count++;
                  maxcount = count;
                }
              for (count = 0;board[j + count + 1][k + count + 1] == which;count++);
                if (isFree(j + count + 1,k + count + 1) && count >= maxcount) {
                  *x = j + count + 1;
                  *y = k + count + 1;
                  while (board[j + count + 2][k + count + 2] == which)
                    count++;
                  maxcount = count;
                }
            }
        }
    }
    return maxcount;
}

void brain_turn()
{
  int x,y,i;
  int count = 0;
  while (!isFree(x,y))
  {
    x= rnd(width);
    y= rnd(height);
  }
  i=-1;
  int attack = brain_place(&x,&y,1);
  int defense = brain_place(&x,&y,2);
  if(attack > defense && defense < 3)
    brain_place(&x,&y,1);
  if(terminateAI) return;
  i++;
  if(i>1) pipeOut("DEBUG %d coordinates didn't hit an empty field",i);
  do_mymove(x,y);
}

void brain_end()
{
}
