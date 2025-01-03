const quickSort = (array) => {
    if (array.length <= 1) {
        return array;
    }

    let less = [];
    let great = [];
    let pivot = array[array.length-1];

    for (let i = 0; i < array.length - 1; i++) {
        if (array[i] < pivot) {
            less.push(array[i]);
        } else {
            great.push(array[i]);
        }
    }

    return [...quickSort(less), pivot, ...quickSort(great)];
}

console.log(quickSort([5, 4, 3, 2, 1]));