const insertionSort = (array) => {
    let i = 1;
    while (i < array.length) {
        let x = array[i];
        let j = i;
        while (j > 0 && array[j - 1] > x) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = x;
        i++;
    }
    return array;
}

console.log(insertionSort([5, 4, 2, 1, 0, -1, -2, -3]));