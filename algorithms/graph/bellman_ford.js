function bellmanFord(graph, source) {
    const distances = {};
    const predecessors = {};

    // Step 1: Initialize distances and predecessors
    for (let vertex in graph) {
        distances[vertex] = Infinity; // Set initial distance to all vertices as Infinity
        predecessors[vertex] = null; // No predecessor initially
    }
    distances[source] = 0; // Distance to the source is 0

    const vertices = Object.keys(graph);

    // Step 2: Relax edges repeatedly (V-1 times)
    for (let i = 0; i < vertices.length - 1; i++) {
        for (let vertex in graph) {
            for (let neighbor in graph[vertex]) {
                const weight = graph[vertex][neighbor];
                if (distances[vertex] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[vertex] + weight;
                    predecessors[neighbor] = vertex;
                }
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    for (let vertex in graph) {
        for (let neighbor in graph[vertex]) {
            const weight = graph[vertex][neighbor];
            if (distances[vertex] + weight < distances[neighbor]) {
                throw new Error("Graph contains a negative-weight cycle");
            }
        }
    }

    return { distances, predecessors };
}

const graph = {
    A: { B: 1, C: 4 },
    B: { C: 2, D: 2 },
    C: { D: 3 },
    D: { E: 1 },
    E: { B: -10 }
};

try {
    const { distances, predecessors } = bellmanFord(graph, 'A');
    console.log("Distances:", distances);
    console.log("Predecessors:", predecessors);
} catch (error) {
    console.error(error.message);
}