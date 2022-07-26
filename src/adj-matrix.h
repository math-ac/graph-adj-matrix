#include <stdbool.h>

#define PATH_SIZE 10

typedef struct Graph Graph;

Graph *new_graph(int size, bool directed);

bool insert_edge(Graph *g, int from, int to);

void print_graph(Graph *g);

void all_degrees(Graph *g);

void highest_degree(Graph *g);

void lowest_degree(Graph *g);

void loop_check(Graph *g);

void paralel_check(Graph *g);

void isolated_check(Graph *g);

void elementar_check(int *path);

void cycle_check(int *path);

void trajectory_check(int *path);

void complete_check(Graph *g);

void regular_check(Graph *g);

Graph *load_shell(int *path);
