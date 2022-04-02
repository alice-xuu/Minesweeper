#include "minesweeper.h"
#include "params.h"

void init_game(struct cell * game, int dim, int * dim_sizes, int num_mines, int ** mined_cells) {
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
//sets coordinates of game through row-major order
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
               for (int a = h + 1; a < dim; a++) {
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
//sets mined of game cells from mined_cells
     if (num_cells >= num_mines) {
          for (int b = 0; b < num_mines; b++) {
               int is_mined = 0;
               for (int a = 0; a < num_cells; a++) {
                    for (int c = 0; c < dim; c++) {
                         if (game[a].coords[c] == mined_cells[b][c]) {
                              is_mined = 1;
                         }
                         else {
                              is_mined = 0;
                              break;
                         }
                    }
                    if (is_mined == 1) {
                         game[a].mined = 1;
                    }
               }
          }
     }
//sets adjacent and num_adjacent of game
     for (int a = 0; a < num_cells; a++) {
          for (int b = 0; b < num_cells; b++) {
               if (a == b) {
                    continue;
               }
               int is_adjacent = 0;
               for (int c = 0; c < dim; c++) {
                    int a_coord_c = game[a].coords[c];
                    int b_coord_c = game[b].coords[c];
                    if ((a_coord_c - b_coord_c >= -1)
                         && (a_coord_c - b_coord_c <= 1)) {

                         is_adjacent = 1;
                    }
                    else {
                         is_adjacent = 0;
                         break;
                    }
               }
               if (is_adjacent == 1) {
                    game[a].adjacent[game[a].num_adjacent] = &game[b];
                    game[a].num_adjacent++;
               }
          }
     }
     return;
}

void select_recursion(struct cell *cell) {
     int hint_counter = 0;
     for (int d = 0; d < cell->num_adjacent; d++) {
          if (cell->adjacent[d]->mined == 1) {
               hint_counter++;
          }
     }
     cell->hint = hint_counter;
     if (hint_counter == 0) {
          for (int a = 0; a < cell->num_adjacent; a++) {
               if (cell->adjacent[a]->selected != 1) {
                    cell->adjacent[a]->selected = 1;
                    select_recursion(cell->adjacent[a]);
               }
          }
     }
}

int select_cell(struct cell * game, int dim, int * dim_sizes, int * coords) {
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

//checks for out of bounds coords
     for (int a = 0; a < dim; a++) {
          if (coords[a] >= dim_sizes[a]){
               return 0;
          }
     }

     for (int a = 0; a < num_cells; a++) {
          int coords_match = 0;
          for (int c = 0; c < dim; c++) {
               if (game[a].coords[c] == coords[c]) {
                    coords_match = 1;
               }
               else {
                    coords_match = 0;
                    break;
               }
          }
          if (coords_match == 1) {
               if (game[a].mined == 1) {
                    game[a].selected = 1;
                    return 1;
               }
               else {
                    if (game[a].selected == 1){
                         return 0;
                    }
                    else {
                         game[a].selected = 1;
                         select_recursion(&game[a]);
                    }
               }
          }
     }
//checks if game has been won
     int selected_cells = 0;
     int num_mines = 0;
     for (int a = 0; a < num_cells; a++) {
          if (game[a].selected == 1) {
               selected_cells++;
          }
          if (game[a].mined == 1) {
               num_mines++;
          }
     }
     if (selected_cells == num_cells-num_mines) {
          return 2;
     }
     else {
          return 0;

     }
}
