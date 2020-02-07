#include <stdlib.h>
#include <stdio.h>



void generateGrid(char **grid, int n, int m){
  int noOfMines = 1 + (n*m)/10;
  int minesCount =0;
  int x,y;
  while(minesCount < noOfMines){
    x = (rand()%n);
    y = (rand()%m);
    if(grid[x][y] != '*'){
      grid[x][y] = '*';
      minesCount ++;
    }
  }

}

void initGrid(char **grid, int n, int m){
  for(int i=0; i<n; i++){
    for(int j=0;j<m;j++){
      grid[i][j]='z';
    }
  }
}

void initView(char **view, int n, int m){
  for(int i=0; i<n; i++){
    for(int j=0;j<m;j++){
      view[i][j]='X';
    }
  }
}

void initOpen(int **open, int n, int m){
  for(int i=0; i<n; i++){
    for(int j=0;j<m;j++){
      open[i][j]=0;
    }
  }
}

void printView(char **view, int n, int m){
  printf("s ");
  for(int i=0; i<m; i++){
    printf("%d ",i);
  }
  printf("\n\n");
  for(int i=0; i<n; i++){
    printf ("%d ",i);
    for(int j=0;j<m;j++){
      printf("%c ", view[i][j]);
    }
    printf("\n");
  }
}

void printGrid(char **grid, int n, int m){
  for(int i=0; i<n; i++){
    for(int j=0;j<m;j++){
      printf("%c ", grid[i][j]);
    }
    printf("\n");
  }
}

char minesAt(char **grid, int n, int m, int x, int y){
  int mines = 0;
  if(y>0){
    if(grid[x][y-1] == '*')
      mines++;
    if(x>0){
      if(grid[x-1][y-1] == '*')
        mines++;
    }
    if(x+1 < n){
      if(grid[x+1][y-1] == '*')
        mines++;
    }
  }
  if(y+1 < m){
    if(grid[x][y+1] == '*')
      mines++;
    if(x > 0){
      if(grid[x-1][y+1] == '*')
        mines++;
    }
    if(x+1 < n){
      if(grid[x+1][y+1] == '*')
        mines++;
    }
  }
  if(x > 0){
    if(grid[x-1][y] == '*')
      mines++;
  }
  if(x+1 < n){
    if(grid[x+1][y] == '*')
      mines++;
  }
  if(mines == 0)
    return ' ';
  else if( mines == 1)
    return '1';
  else if( mines == 2)
    return '2';
  else if( mines == 3)
    return '3';
  else if( mines == 4)
    return '4';
  else if( mines == 5)
    return '5';
  else if( mines == 6)
    return '6';
  else if( mines == 7)
    return '7';
  else if( mines == 8)
    return '8';

}

void generateNumbers(char ** grid, int n, int m){
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      if(grid[i][j] != '*'){
        char m = minesAt(grid, n, m, i, j);
        grid[i][j] = m;

      }
    }
  }
}

void openSpace(char **grid, char **view, int n, int m, int x, int y){
  if(x<n && x>=0 && y<m && y>=0 && grid[x][y] == ' '){
    if(y>0){
      if(view[x][y-1] != grid[x][y-1]){
        view[x][y-1] = grid[x][y-1];
        openSpace(grid,view, n, m, x, y-1);
      }
      if(x>0){
        if(view[x-1][y-1] != grid[x-1][y-1]){
          view[x-1][y-1] = grid[x-1][y-1];
          openSpace(grid, view, n, m, x-1, y-1);

        }
      }
      if(x+1 < n){
        if(view[x+1][y-1] != grid[x+1][y-1]){
          view[x+1][y-1] = grid[x+1][y-1];
          openSpace(grid,view, n, m, x+1, y-1);
        }
      }
    }
    if(y+1 < m){
      if(view[x][y+1] != grid[x][y+1]){
        view[x][y+1] = grid[x][y+1];
        openSpace(grid,view, n, m, x, y+1);
      }
      if(x > 0){
        if(view[x-1][y+1] != grid[x-1][y+1]){
          view[x-1][y+1] = grid[x-1][y+1];
          openSpace(grid,view, n, m, x-1, y+1);
        }
      }
      if(x+1 < n){
        if(view[x+1][y+1] != grid[x+1][y+1]){
          view[x+1][y+1] = grid[x+1][y+1];
          openSpace(grid,view, n, m, x+1, y+1);
        }
      }
    }
    if(x > 0){
      if(view[x-1][y] != grid[x-1][y]){
        view[x-1][y] = grid[x-1][y];
        openSpace(grid,view, n, m, x-1, y);

      }
    }
    if(x+1 < n){
      if(view[x+1][y] != grid[x+1][y]){
        view[x+1][y] = grid[x+1][y];
        openSpace(grid,view, n, m, x+1, y);
      }
    }
    return;
  }
  else {
    return;
  }

}

int run(char **grid, char **view, int n, int m){
    initView(view, n,m);
    initGrid(grid, n, m);
    generateGrid(grid, n, m);
    generateNumbers(grid, n, m);
    printView(view, n, m);
    int x,y;
    printf("Enter X position to open\n");
    scanf("%d",&x);
    printf("Enter Y position to open\n");
    scanf("%d", &y);
    while(grid[x][y] == '*'){
      generateGrid(grid, n, m);
      generateNumbers(grid, n, m);
    }
    view[x][y] = grid[x][y];
    if(grid[x][y] == ' ')
      openSpace(grid, view, n, m, x, y);
    printGrid(grid, n, m);
    printView(view, n, m);
    int play = 1;
    while(play){
      int a;
      printf("Enter X position \n");
      scanf("%d",&x);
      printf("Enter Y position \n");
      scanf("%d", &y);
      printf("Choose action\n 1-open \t2-flag\t3-question\t4-unmark");
      scanf("%d",&a);
      if(a == 1){
        if(view[x][y] != grid[x][y]){
          view[x][y]=grid[x][y];
          if(grid[x][y] == '*'){
            printView(view,m,n);
            printf("GAME OVERRRRRRR!!!!!\n");
            play =0;
            break;
          }
          else if(grid[x][y] == ' '){
            openSpace(grid, view, n, m, x, y);
            printView(view, n, m);
          }
          else{
            view[x][y] = grid[x][y];
            printView(view, n, m);
          }
        }
        else{
          printf("can't open cell it's already open\n");
          printView(view, n, m);
        }



      }
      else if( a == 2){
        if(view[x][y]!=grid[x][y]){
          view[x][y] = 'F';
          printView(view,m,n);
        }
        else{
          printf("can't flag cell it's already opened\n");
        }

      }
      else if( a == 3){
        if(view[x][y]!=grid[x][y]){
          view[x][y] = '?';
          printView(view,m,n);
        }
        else{
          printf("can't question cell it's already opened\n");
        }
      }
      else if( a == 4){
        if(view[x][y] == 'F' || view[x][y] == '?'){
          view[x][y] = 'X';
          printView(view,m,n);
        }
        else{
          printf("can't unmark cell it wasn't marked\n");
        }
      }
      //TODO
      //calculate score and time in every move
      



      int minesCount =  1 + (n*m)/10;
      int cells = n*m - minesCount;
      int counter = 0;
      for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
          if(grid[i][j] == view[i][j])
            counter++;
        }
      }

      if(counter == cells){
        printf("CONGRATULATIONSSSSSS YOU WIN !!!!!!!  \n");
        play =0;
        break;
      }

    }
}

int main(int argc, char const *argv[]) {
  /* code */

    int n,m;
    printf("Enter number of rows\n" );
    scanf("%d",&n);
    printf("Enter number of columns\n" );
    scanf("%d",&m);
    char **grid;
    char **view;
    grid = (char **) malloc(n * sizeof(char*));
    for (int row = 0; row<n; row++) {
    grid[row] = (char *) malloc(m * sizeof(char));
    }
    view = (char **) malloc(n * sizeof(char*));
    for (int row = 0; row<n; row++) {
    view[row] = (char *) malloc(m * sizeof(char));
    }

    run(grid, view, n, m);
  return 0;
}
