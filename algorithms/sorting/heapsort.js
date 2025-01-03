const heapSort = (array) => {
    const heapify = (arr, n, i) => {
        let largest = i; // Initialize largest as root
        let left = 2 * i + 1; // Left child index
        let right = 2 * i + 2; // Right child index
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        if (largest !== i) {
            [arr[i], arr[largest]] = [arr[largest], arr[i]];
            heapify(arr, n, largest);
        }
    };
    // Build a max heap
    const n = array.length;
    for (let i = Math.floor(n / 2) - 1; i >= 0; i--) {
        heapify(array, n, i);
    }
    for (let i = n - 1; i > 0; i--) {
        [array[0], array[i]] = [array[i], array[0]];
        heapify(array, i, 0);
    }

    return array;
};

// Example usage
console.log(heapSort([10, 7, 8, 9, 1, 5]));