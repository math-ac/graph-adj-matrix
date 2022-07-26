#include <stdio.h>

#include "adj-matrix.h"

int main(void)
{
    int path[PATH_SIZE] = {0};
    Graph *g = load_shell(path);

    print_graph(g);
    printf("\n");

    loop_check(g);
    printf("\n");

    paralel_check(g);
    printf("\n");

    isolated_check(g);
    printf("\n");

    all_degrees(g);
    printf("\n");

    highest_degree(g);

    lowest_degree(g);
    printf("\n");

    complete_check(g);

    regular_check(g);
    printf("\n");

    elementar_check(path);
    cycle_check(path);
    trajectory_check(path);

    return 0;
}
