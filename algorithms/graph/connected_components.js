function findConnectedComponents(graph) {
    const visited = new Array(graph.length).fill(false); // Track visited nodes
    const components = []; // Store all connected components

    // Helper function to perform DFS
    function dfs(node, component) {
        visited[node] = true;
        component.push(node);

        for (const neighbor of graph[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, component);
            }
        }
    }

    // Main loop: Visit all nodes and start a DFS for unvisited ones
    for (let i = 0; i < graph.length; i++) {
        if (!visited[i]) {
            const component = []; // New connected component
            dfs(i, component);
            components.push(component); // Add component to the result
        }
    }

    return components;
}

const graph = [
    [1, 2],    // Node 0 is connected to nodes 1 and 2
    [0, 3],    // Node 1 is connected to nodes 0 and 3
    [0],       // Node 2 is connected to node 0
    [1],       // Node 3 is connected to node 1
    [5],       // Node 4 is connected to node 5
    [4]        // Node 5 is connected to node 4
];

const connectedComponents = findConnectedComponents(graph);

console.log("Connected Components:", connectedComponents);