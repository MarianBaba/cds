class PriorityQueue {
    constructor() {
        this.queue = [];
    }

    // Add an element to the queue
    enqueue(node, priority) {
        this.queue.push({ node, priority });
        this.queue.sort((a, b) => a.priority - b.priority); // Sort by priority
    }

    // Remove and return the element with the highest priority (lowest value)
    dequeue() {
        return this.queue.shift(); // Remove the first element (lowest priority)
    }

    isEmpty() {
        return this.queue.length === 0;
    }
}

function dijkstra(graph, source) {
    const distances = {}; // To store the shortest distance to each node
    const previous = {}; // To store the previous node for path reconstruction
    const pq = new PriorityQueue(); // Priority queue for finding the shortest edge
    const visited = new Set(); // To keep track of visited nodes

    // Initialize distances and previous
    for (let node in graph) {
        distances[node] = Infinity; // Start with "infinity" distance
        previous[node] = null; // No previous node initially
    }
    distances[source] = 0; // Distance to the source is 0
    pq.enqueue(source, 0); // Add the source node to the queue

    // Process the priority queue
    while (!pq.isEmpty()) {
        const { node: currentNode } = pq.dequeue();

        // Skip if we've already visited this node
        if (visited.has(currentNode)) continue;

        visited.add(currentNode);

        // Explore neighbors of the current node
        for (let [neighbor, weight] of graph[currentNode]) {
            const newDistance = distances[currentNode] + weight;

            // If the new distance is shorter, update it
            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                previous[neighbor] = currentNode;
                pq.enqueue(neighbor, newDistance); // Add neighbor to the queue
            }
        }
    }

    return { distances, previous };
}