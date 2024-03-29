/*
 * Nick Haliday
 * Parallel Computing 1
 * Torbert
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFSIZE 1000

typedef struct node node;
struct node {
    char ch;
    node *next[2];
};
node *head;

node *newnode() {
    return malloc(sizeof(node));
}

void deltrie(node *p) {
    if (p == NULL) {
        return;
    }
    deltrie(p->next[0]);
    deltrie(p->next[1]);
    free(p);
}

node *addedge(node *n, int b) {
    if (n->next[b] == NULL) {
        n->next[b] = newnode();
    }
    return n->next[b];
}

int main() {
    head = newnode();
    char buffer[BUFFSIZE];
    char *bit;
    int i, n;
    node *p;

    FILE *fin = fopen("decode.txt", "r");

    fscanf(fin, "%d", &n);

    for (i = 0; i < n; ++i) {
        fscanf(fin, "%s", buffer);
        p = head;
        for (bit = buffer + 1; *bit; ++bit) {
            p = addedge(p, *bit == '1');
        }
        p->ch = buffer[0];
    }

    fscanf(fin, "%s", buffer);
    p = head;
    for (bit = buffer; *bit; ++bit) {
        p = p->next[*bit == '1'];
        if (p->ch) {
            putchar(p->ch);
            p = head;
        }
    }

    putchar('\n');

    deltrie(head);

    return 0;
}
