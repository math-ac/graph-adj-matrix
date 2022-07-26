#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "adj-matrix.h"

struct Graph {
    int size;
    bool directed;
    int **edges;
};

Graph *new_graph(int size, bool directed)
{
    Graph *tmp = malloc(sizeof(Graph));
    assert(tmp);

    tmp->size = size;
    tmp->directed = directed;
    tmp->edges = calloc(sizeof(int *), size);
    assert(tmp->edges);

    for (int i = 0; i < size; i++) {
        tmp->edges[i] = calloc(sizeof(int), size);
        assert(tmp->edges[i]);
    }

    return tmp;
}

bool insert_edge(Graph *g, int from, int to)
{
    if (from > g->size || to > g->size || from < 1 || to < 1) {
        return false;
    } else {
        g->edges[from - 1][to - 1]++;
        if (!g->directed && from != to)
            g->edges[to - 1][from - 1]++;

        return true;
    }
}

void print_graph(Graph *g)
{
    for (int i = 0; i < g->size; i++) {
        printf("%d: ", i + 1);
        for (int j = 0; j < g->size; j++) {
            if (g->edges[i][j] > 0) {
                int flag = g->edges[i][j];
                while(flag > 0) {
                    printf("%d ", j + 1);
                    flag--;
                }
            }
        }
        printf("\n");
    }
}

int node_degree(Graph *g, int node)
{
    if (node > g->size || node < 1) {
        return -1;
    } else {
        int degree = 0;

        for (int i = 0; i < g->size; i++) {
            if (g->edges[node - 1][i] > 0) {
                if ((node - 1) == i)
                    degree += g->edges[node - 1][i];
                degree += g->edges[node - 1][i];
            }
        }

        return degree;
    }
}

void all_degrees(Graph *g)
{
    for (int i = 0; i < g->size; i++) {
        printf("Vértice %d tem grau %d\n", i + 1, node_degree(g, i + 1));
    }
}

void highest_degree(Graph *g)
{
    int highest = 0;

    for (int i = 0; i < g->size; i++) {
        if (node_degree(g, i + 1) > highest)
            highest = node_degree(g, i + 1);
    }

    printf("Grau máximo: %d\n", highest);
}

void lowest_degree(Graph *g)
{
    int lowest = 10;

    for (int i = 0; i < g->size; i++) {
        if (node_degree(g, i + 1) < lowest)
            lowest = node_degree(g, i + 1);
    }

    printf("Grau mínimo: %d\n", lowest);
}

bool has_loop(Graph *g, int node)
{
    if (node > g->size || node < 1) {
        return false;
    } else if (g->edges[node - 1][node - 1] > 0) {
        return true;
    } else {
        return false;
    }
}

void loop_check(Graph *g)
{
    int amount = 0;
    int occurrence[g->size];

    for (int i = 0; i < g->size; i++) {
        if (has_loop(g, i + 1)) {
            occurrence[amount] = i + 1;
            amount++;
        }
    }

    if (amount == 0) {
        printf("Não há loops\n");
    } else {
        printf("Há loop nos vértices abixo:\n");
        for (int i = 0; i < amount; i++) {
            printf("%d ", occurrence[i]);
        }
        printf("\nTotal: %d\n", amount);
    }
}

bool has_paralel(Graph *g, int node)
{
    if (node > g->size || node < 1) {
        return false;
    } else {
        for (int i = 0; i < g->size; i++) {
            if (g->edges[node - 1][i] > 1)
                return true;
        }

        return false;
    }
}

void paralel_check(Graph *g)
{
    int amount = 0;
    int occurrence[g->size];

    for (int i = 0; i < g->size; i++) {
        if (has_paralel(g, i + 1)) {
            occurrence[amount] = i + 1;
            amount++;
        }
    }

    if (amount == 0) {
        printf("Não há arestas paralelas\n");
    } else {
        printf("Entre os vértices abaixo há arestas paralelas:\n");
        for (int i = 0; i < amount; i++) {
            printf("%d ", occurrence[i]);
        }
        printf("\nTotal: %d\n", amount);
    }
}

bool has_isolated(Graph *g, int node)
{
    if (node > g->size || node < 1) {
        return false;
    } else {
        for (int i = 0; i < g->size; i++) {
            if (g->edges[node - 1][i] != 0)
                return false;
        }

        return true;
    }
}

void isolated_check(Graph *g)
{
    int amount = 0;
    int occurrence[g->size];

    for (int i = 0; i < g->size; i++) {
        if (has_isolated(g, i + 1)) {
            occurrence[amount] = i + 1;
            amount++;
        }
    }

    if (amount == 0) {
        printf("Não há vertices isolados\n");
    } else {
        printf("Os vértices abaixo são isolados:\n");
        for (int i = 0; i < amount; i++) {
            printf("%d ", occurrence[i]);
        }
        printf("\nTotal: %d\n", amount);
    }
}

bool is_elementar(int *path)
{
    for (int i = 0; i < PATH_SIZE; i++) {
        if (path[i] == 0) //Assuming the array ends when a 0 is found
            break;
        for (int j = i + 1; j < PATH_SIZE; j++) {
            if (path[i] == path[j]) { //In case a vertex appears again
                return false;
            }
        }
    }

    return true;
}

void elementar_check(int *path)
{
    if (is_elementar(path))
        printf("O caminho é elementar\n");
    else
        printf("O caminho não é elementar\n");
}

bool is_cycle(int *path)
{
    int start = path[0];
    int end;

    for (int i = 1; i < PATH_SIZE; i++) {
        if (path[i] == 0) //Assuming the array ends when a 0 is found
            break;
        end = path[i];
    }

    if (start == end)
        return true;
    else
        return false;
}

void cycle_check(int *path)
{
    if (is_cycle(path))
        printf("O caminho é um ciclo\n");
    else
        printf("O caminho não é um ciclo\n");
}

bool is_trajectory(int *path)
{
    int from;
    int to;

    for (int i = 0; i < PATH_SIZE; i++) {
        if (path[i + 2] == 0) //Assuming the array ends when a 0 is found
            break;

        from = path[i];
        to = path[i + 1];

        for (int j = i + 2; j < PATH_SIZE; j++) {
            if (from == j && to == j + 1) //If a pair of vertex (edge) repeats
                return false;
        }
    }
    return true;
}

void trajectory_check(int *path)
{
    if (is_trajectory(path))
        printf("O caminho é um trajeto\n");
    else
        printf("O caminho não é um trajeto\n");
}

bool is_complete(Graph *g)
{
    for (int i = 0; i < g->size; i++) {
        for (int j = 0; j < g->size; j++) {
            if (i == j)
                continue;
            else if (g->edges[i][j] == 0)
                return false;
        }
    }
    return true;
}

void complete_check(Graph *g)
{
    if (is_complete(g))
        printf("Grafo Completo\n");
    else
        printf("Grafo não completo\n");
}

bool is_regular(Graph *g)
{
    int degree = node_degree(g, 1);

    for (int i = 1; i < g->size; i++) {
        if (degree != node_degree(g, i + 1))
            return false;
    }

    return true;
}

void regular_check(Graph *g)
{
    if (is_regular(g))
        printf("Grafo regular\n");
    else
        printf("Grafo não regular\n");
}

Graph *load_shell(int *path)
{
    int vertex_size = 0;
    int edge_size = 0;
    int directed = 0;

    //Read first line
    scanf("%d", &vertex_size);
    scanf("%d", &edge_size);
    scanf("%d", &directed);

    while (1) { //Check for a newline or end of file (stdin in this case)
        char flag = '\0';
        flag = getc(stdin);
        if (flag == '\n' || feof(stdin)) {
            break;
        }
    }

    Graph *graph = new_graph(vertex_size, directed);

    //Read edges
    for (int i = 0; i < edge_size; i++) {
        int from;
        int to;

        if (feof(stdin))
            break;

        scanf("%d", &from);
        scanf("%d", &to);

        insert_edge(graph, from, to);

        while (1) { //Check for a newline or end of file (stdin in this case)
            char flag = '\0';
            flag = getc(stdin);
            if (flag == '\n' || feof(stdin)) {
                break;
            }
        }
    }

    //Read path
    int count = 0;

    while (1) { //Check for a newline or end of file (stdin in this case)
        char flag = '\0';
        scanf("%d", &path[count]);
        flag = getc(stdin);
        if (flag == '\n' || feof(stdin)) {
            break;
        }
        count++;
    }

    return graph;
}
