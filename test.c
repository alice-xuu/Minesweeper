#include<stdio.h>
#include<string.h>

#define MAX_STRING_LEN 80

int main() {
     printf("1");

     struct cell {
         int mined;
         int selected;
         int num_adjacent;
         struct cell * adjacent[1000];
         int coords[5];
         int hint;
     };

     static struct cell game[10000];

     int dim = 6;
     int dim_sizes[2000] = {2, 2, 3, 3, 5,8};
     //int num_mines = 2;
     //int mined_cells[50][50] = {{1,3,4},{2,2,5}};

     int num_cells;
     if (dim == 0) {
          num_cells = 0;
     }
     else {
          num_cells = 1;
     }

     for (int a = 0; a < dim; a++) {
          num_cells *= dim_sizes[a];
     }

     for (int b = 0; b < num_cells; b++) {
         game[b].selected = 0;
         game[b].mined = 0;
         game[b].num_adjacent = 0;
     }

     int multiple;

     for (int h = 0; h < dim; h++) {
          int game_i = 0;

          if (dim == 2 && h == 0) {
               multiple = 1;
               multiple = dim_sizes[h+1];
          }
          else if (h == dim - 1) {
               multiple = 1;
          }
          else {
               multiple = 1;
               for (int a = h+1; a < dim; a++) {
                         multiple *= dim_sizes[a];
               }
          }

          int adjust_multiple = num_cells / dim_sizes[h];
          int repeat = 0;

          while (repeat != adjust_multiple) {
               int j = 0;
               while (j < dim_sizes[h]) {
                    int dim_val = 0;
                    while (dim_val < multiple) {
                         game[game_i].coords[h] = j;
                         dim_val++;
                         game_i++;
                         }
                         j++;
               }
               if (game_i == num_cells) {
                    break;
               }
               repeat++;
          }
     }

/*
// {{1,3},{2,2}}; mined_cells
     for (int b = 0; b < num_mines; b++){
          int is_mined = 0;
          for (int a = 0; a < num_cells; a++){
               //printf("cell is %d, coord: %d %d\n", a, game[a].coords[0], game[a].coords[1]);

               for (int c = 0; c < dim; c++){
                    if (game[a].coords[c] == mined_cells[b][c]){
                         is_mined = 1;
                         //printf("       b,c %d %d mined\n", b, c);

                    }
                    else {
                         is_mined = 0;
                         break;
                         //printf("       %d %d not\n", b, c);
                    }
               }
               if (is_mined == 1){
                    game[a].mined = 1;
                    //printf("                      game[a] %d\n", a);
                    //printf("                      coords %d %d\n", game[a].coords[0], game[a].coords[1]);
               }
          }
     }
*/
/*
     for (int a = 0; a < num_cells; a++){
          for (int b = 0; b < dim; b++){
               printf("%d, ", game[a].coords[b]);
          }
          //printf("mined = %d", game[a].mined);
          printf("\n");
     }
*/
     int a = 1;
     int b = a;
     //b = a;
     a = 5;
     printf("a = %d, b = %d",a,b);


}
