#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ASCII 128

int count[ASCII];
double value[ASCII];
double totalbits;

int main(int argc, char *argv[]) {
    int i;
    int n;
    char* bit;
    int c;

    for (i = 1; i < argc; ++i) {
        memset(count, 0, ASCII * sizeof(int));

        for (bit = argv[i]; *bit; ++bit) {
            count[*bit]++;
        }

        n = bit - argv[i];

        totalbits = 0;
        for (c = 0; c < ASCII; ++c) {
            if (count[c] > 0) {
                value[c] = log(n / (double)count[c]) / log(2);
                totalbits += count[c] * value[c];
                printf("%c %f %f\n", c, value[c], count[c] * value[c]);
            }
        }
        printf("%f\n", totalbits);
        printf("\n");
    }
}
