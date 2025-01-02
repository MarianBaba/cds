const graph = {
    0: [1, 2],
    1: [0, 3, 4],
    2: [0, 5],
    3: [1],
    4: [1],
    5: [2]
}

const bsf = (graph, first) => {
    let visited = new Set();
    let queue = [];

    queue.push(first);
    visited.add(first);

    while (queue.length > 0) {
        let visiting = queue.shift();
        for (const neighbour of graph[visiting]) {
            if (!visited.has(neighbour)) {
                queue.push(neighbour);
                visited.add(neighbour);
            }
        }
    }
}