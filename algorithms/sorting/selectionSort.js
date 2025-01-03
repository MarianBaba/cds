const selectionSort = (array) => {
    for (let j = 0; j < array.length - 1; j++) {
        minIndex = j;
        for (let i = j + 1; i < array.length; i++) {
            if (array[i] < array[minIndex]) {
                minIndex = i;
            }
        }
        let tmp = array[j];
        array[j] = array[minIndex];
        array[minIndex] = tmp;
    }
    return array;
}