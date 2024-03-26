#include <stdio.h>

int is_prime(int n) {
    if (n <= 1) return 0; 
    if (n == 2) return 1; 
    if (n % 2 == 0) return 0; 
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    for (int i = 1; i <= 100; i++) {
        if (is_prime(i))
            printf("%d\n", i);
    }
    return 0;
}