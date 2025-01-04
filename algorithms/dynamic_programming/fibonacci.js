const fibonacci = (n, mem) => {
    if (mem[n] != -1) {
        return mem[n];
    }

    if (n <= 1) {
        return n;
    }

    mem[n] = fibonacci(n - 2, mem) + fibonacci(n - 1, mem);
    return mem[n];
}

let mem = [];
let n = 10;

for (i = 0; i <= n; i++) {
    mem.push(-1);
}

console.log(fibonacci(n, mem));

