#include <stdio.h>

int main() {
    int vettore[10] = {5, 2, 7, 8, 0, -50, 10, 90, 20, -1};

    int max = vettore[0];
    int min = vettore[0];

    for(int i = 0; i < 10; i++) {
        if(vettore[i] > max) {
            max = vettore[i];
        }
        if(vettore[i] < min) {
            min = vettore[i];
        }
    }

    printf("MASSIMO: %d\n", max);
    printf("MINIMO: %d\n", min);
}