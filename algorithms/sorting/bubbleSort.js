const bubbleSort = (array) => {
    for (let i = 0; i < array.length - 1; i++) {
        swap = false;
        for (let j = i + 1; j < array.length; j++) {
            if (array[i] > array[j]) {
                swap = true;
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
        if (!swap) {
            break;
        }
    }
    return array;
}

console.log(bubbleSort([5, 4, 2, 1, 0, -1, -2, -3]));
