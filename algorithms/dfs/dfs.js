const graph = {
    0: [1, 2],
    1: [0, 3],
    2: [0],
    3: [1]
}

const dfs = (graph, root) => {
    let stack = [];
    let visited = new Set();
    stack.push(root);
    visited.add(root);
    while (stack.length > 0) {
        const visiting = stack.pop();
        for (const neighbour of graph[visiting]) {
            if (!visited.has(neighbour)) {
                stack.push(neighbour);
                visited.add(neighbour);
            }
        }
    }
}

