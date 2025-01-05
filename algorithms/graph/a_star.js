class PriorityQueue {
    constructor() {
        this.elements = [];
    }

    enqueue(element, priority) {
        this.elements.push({ element, priority });
        this.elements.sort((a, b) => a.priority - b.priority); // Sort by priority
    }

    dequeue() {
        return this.elements.shift().element; // Remove and return the element with the highest priority
    }

    isEmpty() {
        return this.elements.length === 0;
    }
}

function aStar(graph, start, goal, heuristic) {
    const openSet = new PriorityQueue(); // Nodes to explore
    openSet.enqueue(start, 0);

    const cameFrom = {}; // Tracks the best path
    const gScore = {}; // Cost from start to a given node
    const fScore = {}; // Estimated total cost (gScore + heuristic)

    for (let node in graph) {
        gScore[node] = Infinity;
        fScore[node] = Infinity;
    }
    gScore[start] = 0;
    fScore[start] = heuristic(start, goal);

    while (!openSet.isEmpty()) {
        const current = openSet.dequeue();

        // If we reached the goal
        if (current === goal) {
            return reconstructPath(cameFrom, current);
        }

        for (let neighbor in graph[current]) {
            const tentativeGScore = gScore[current] + graph[current][neighbor];

            if (tentativeGScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentativeGScore;
                fScore[neighbor] = tentativeGScore + heuristic(neighbor, goal);

                // Add the neighbor to the open set if not already there
                if (!openSet.elements.some(e => e.element === neighbor)) {
                    openSet.enqueue(neighbor, fScore[neighbor]);
                }
            }
        }
    }

    return null; // No path found
}

function reconstructPath(cameFrom, current) {
    const path = [current];
    while (cameFrom[current] !== undefined) {
        current = cameFrom[current];
        path.unshift(current);
    }
    return path;
}

// Example Heuristic (Manhattan Distance)
function heuristic(node, goal) {
    const [x1, y1] = node.split(",").map(Number);
    const [x2, y2] = goal.split(",").map(Number);
    return Math.abs(x1 - x2) + Math.abs(y1 - y2);
}

// Example Usage
const graph = {
    "0,0": { "0,1": 1, "1,0": 1 },
    "0,1": { "0,0": 1, "0,2": 1, "1,1": 1 },
    "0,2": { "0,1": 1, "1,2": 1 },
    "1,0": { "0,0": 1, "1,1": 1, "2,0": 1 },
    "1,1": { "0,1": 1, "1,0": 1, "1,2": 1, "2,1": 1 },
    "1,2": { "0,2": 1, "1,1": 1, "2,2": 1 },
    "2,0": { "1,0": 1, "2,1": 1 },
    "2,1": { "1,1": 1, "2,0": 1, "2,2": 1 },
    "2,2": { "1,2": 1, "2,1": 1 }
};

const start = "0,0";
const goal = "2,2";

const path = aStar(graph, start, goal, heuristic);

console.log("Shortest Path:", path);