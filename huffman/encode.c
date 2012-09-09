/*
 * Nick Haliday
 * Parallel Computing 1
 * Torbert
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII 256
#define BUFFSIZE 1000

/* trie */

typedef struct node node;
struct node
{
    char ch;
    node *next[2];
};

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

node *addedge(node *p, int b) {
    if (p->next[b] == NULL) {
        p->next[b] = newnode();
    }
    return p->next[b];
}

node *merge(node *p1, node *p2) {
    node *rv = newnode();
    rv->next[0] = p1;
    rv->next[1] = p2;
    return rv;
}

/* end trie */

/* huffman scheme */

typedef struct wrapper wrapper;
struct wrapper {
    node *p;
    int count;
};

int wrapper_compare(const void *a, const void *b) {
    return ((wrapper*)a)->count - ((wrapper*)b)->count;
}

node *make_scheme_trie(int count[ASCII]) {
    char c;
    int cnt = 0;
    for (c = 0; c < ASCII; ++c) {
        if (count[c] > 0) {
            ++cnt;
        }
    }

    wrapper *arr = malloc(cnt * sizeof(wrapper));
    int i = 0;
    for (c = 0; c < ASCII; ++c) {
        if (count[c] > 0) {
            arr[i].p = newnode();
            arr[i].p->ch = c;
            arr[i].count = count[c];
            ++i;
        }
    }

    qsort(arr, cnt, sizeof(wrapper), &wrapper_compare);

    for (i = 0; i < cnt - 1; ++cnt) {

    }
}

/* end huffman scheme */
