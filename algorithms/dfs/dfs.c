struct node {
    int key;
    struct node *next;
};

struct graph {
    struct node **vertices;
    int size;
    int vertex_count;
    int edge_count;
};

void add_vertex(struct graph *graph, int key) {

}

void dfs(struct graph *graph, struct node *root) {
}