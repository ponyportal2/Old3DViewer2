#define LINESIZE 16384

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dot_t {
  float x;
  float y;
  float z;
} dot;

typedef struct vector_t {
  int x;
  int y;
  int z;
} huector;

typedef struct line_t {
  dot a;
  dot b;
} line;

int add_line(line c_line, line *lines);
void zanulyator_dots(dot *dots, int rows);
void zanulyator_dot(dot *dot);
int dot_eq(dot a, dot b);
void zanulyator_vector(huector *vector);

int main() {
  int rows_dots = 2000000;
  dot *dots = calloc(rows_dots, sizeof(dot));
  // zanulyator_dots(dots, rows_dots);
  char current_line[LINESIZE] = {0};
  FILE *obj_file = fopen("minicooper.obj", "rb");
  float x = 0.0, y = 0.0, z = 0.0;
  int v_i = 0;
  while (fgets(current_line, LINESIZE, obj_file)) {
    if (current_line[0] == 'v' && current_line[1] == ' ') {
      sscanf(current_line, "v %f %f %f", &dots[v_i].x, &dots[v_i].y,
             &dots[v_i].z);
      ++v_i;
    }
  }
  fclose(obj_file);
  obj_file = fopen("teapot.obj", "rb");

  int rows_lines = 4000000;
  line *lines_to_draw = (line *)calloc(rows_lines, sizeof(line));

  huector co_dot;
  zanulyator_vector(&co_dot);

  huector dummy;
  zanulyator_vector(&dummy);

  int l_i = 0;
  int file_lines_count = 0;
  int lines_count_to_draw = 0;
  while (fgets(current_line, LINESIZE, obj_file)) {
    if (current_line[0] == 'f' && current_line[1] == ' ') {
      // sscanf(current_line, "f %d %d %d", &co_dot.x, &co_dot.y, &co_dot.z);
      // line temp_line1, temp_line2, temp_line3;
      // // printf("\n|%f|\n", dots[co_dot.x].x);
      // temp_line1.a = temp_line3.b = dots[co_dot.x - 1];
      // temp_line1.b = temp_line2.a = dots[co_dot.y - 1];
      // temp_line2.b = temp_line3.a = dots[co_dot.z - 1];
      // lines_count_to_draw = add_line(temp_line1, lines_to_draw);
      // lines_count_to_draw = add_line(temp_line2, lines_to_draw);
      // lines_count_to_draw = add_line(temp_line3, lines_to_draw);

      // f 881  // 881 882//882 883//883

      sscanf(current_line, "f %i//%i %i//%i %i//%i", &co_dot.x, &dummy.x,
             &co_dot.y, &dummy.y, &co_dot.z, &dummy.z);
      line temp_line1, temp_line2, temp_line3;
      temp_line1.a = temp_line3.b = dots[co_dot.x - 1];
      temp_line1.b = temp_line2.a = dots[co_dot.y - 1];
      temp_line2.b = temp_line3.a = dots[co_dot.z - 1];
      lines_count_to_draw = add_line(temp_line1, lines_to_draw);
      lines_count_to_draw = add_line(temp_line2, lines_to_draw);
      lines_count_to_draw = add_line(temp_line3, lines_to_draw);

      // sscanf(current_line, "f %d %d", &co_dot.x, &co_dot.y);
      // line temp_line1, temp_line2, temp_line3;
      // // printf("\n|%f|\n", dots[co_dot.x].x);
      // temp_line1.a = dots[co_dot.x - 1];
      // temp_line1.b = dots[co_dot.y - 1];
      // lines_count_to_draw = add_line(temp_line1, lines_to_draw);
      // // lines_count_to_draw = add_line(temp_line2, lines_to_draw);
      // // lines_count_to_draw = add_line(temp_line3, lines_to_draw);
      if (!(file_lines_count % 1000)) printf("\n%i\n", file_lines_count);
      ++file_lines_count;
    }
  }

  FILE *lines_output = fopen("lines.txt", "w");
  for (int i = 0; i < lines_count_to_draw; ++i) {
    fprintf(lines_output, "%f %f %f %f %f %f\n", lines_to_draw[i].a.x,
            lines_to_draw[i].a.y, lines_to_draw[i].a.z, lines_to_draw[i].b.x,
            lines_to_draw[i].b.y, lines_to_draw[i].b.z);
  }
  fclose(lines_output);

  fclose(obj_file);
  free(dots);
  free(lines_to_draw);
  return 0;
}

int add_line(line c_line, line *lines) {
  int loop_break = 0;
  static int current_lines_index = 0;
  for (int i = 0; i < current_lines_index && loop_break == 0; ++i) {
    if (dot_eq(c_line.a, lines[i].a) && dot_eq(c_line.b, lines[i].b)) {
      loop_break = 1;
    } else if (dot_eq(c_line.b, lines[i].a) && dot_eq(c_line.a, lines[i].b)) {
      loop_break = 1;
    }
  }
  if (loop_break == 0) {
    lines[current_lines_index] = c_line;
    ++current_lines_index;
  }
  return current_lines_index;
}

int dot_eq(dot a, dot b) {
  int equal = 0;
  if (a.x == b.x && a.y == b.y && a.z == b.z) {
    equal = 1;
  }
  return equal;
}

void zanulyator_vector(huector *vector) {
  vector->x = vector->y = vector->z = 0;
}

// void zanulyator_dots(dot *dots, int rows) {
//   for (int i = 0; i < rows - 1; ++i) {
//     zanulyator_dot(&dots[i]);
//   }
// }

// printf("\n|%f|\n", dots[co_dot.x].x);

// void zanulyator_dot(dot *dot) { dot->x = dot->y = dot->z = 0.0; }

// printf("\n{%f}\n", c_line.a.x);
// printf("\nx:[%f],y:[%f],z:[%f],%i\n", lines[current_lines_index].a.x,
//        lines[current_lines_index].a.y, lines[current_lines_index].a.z,
//        current_lines_index);
// printf("\nx:{%f},y:{%f},z:{%f},%i\n", lines[current_lines_index].b.x,
//        lines[current_lines_index].b.y, lines[current_lines_index].b.z,
//        current_lines_index);
// int add_line(line c_line, line * lines, int rows) {
//   int found_duplicate = 0, loop_break = 0;
//   for (int i = 0; i < rows && loop_break == 0; ++i) {
//     if (dot_eq(c_line.a, lines[i].a) && dot_eq(c_line.b, lines[i].b)) {
//       found_duplicate = 1;
//       loop_break = 1;
//     } else if (dot_eq(c_line.b, lines[i].a) && dot_eq(c_line.a,
//     lines[i].b)) {
//       found_duplicate = 1;
//       loop_break = 1;
//     }
//   }
//   return found_duplicate;
// }

// void zanulyator_int(int **matrix, int rows, int columns) {
//   for (int i; i < rows; ++i) {
//     for (int j; j < columns; ++j) {
//       matrix[i][j] = 0;
//       ++j;
//     }
//     ++i;
//   }
// }

// float **lines = (float **)calloc(lines, sizeof(float *));
// for (int i = 0; i < rows; i++) {
//   lines[i] = (float *)calloc(lines, sizeof(float));
// }
// zanulyator_float(dots, rows, cols);

// void zanulyator_float(float **matrix, int rows, int columns) {
//   for (int i; i < rows; ++i) {
//     for (int j; j < columns; ++j) {
//       matrix[i][j] = 0.0;
//       ++j;
//     }
//     ++i;
//   }
// }

// temp_line1.a = dots[co_dot.x];
// temp_line1.b = dots[co_dot.y];
// temp_line2.a = dots[co_dot.y];
// temp_line2.b = dots[co_dot.z];
// temp_line3.a = dots[co_dot.z];
// temp_line3.b = dots[co_dot.x];