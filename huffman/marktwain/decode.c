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

node *traverse(node *n, int b) {
    return n->next[b];
}

node *add(node *n, char ch, int len, int *bits) {
    int i;
    for (i = 0; i < len; ++i) {
        if (bits[i] != 0 && bits[i] != 1) {
            return NULL;
        }
    }

    for (i = 0; i < len; ++i) {
        n = addedge(n, bits[i]);
    }
    n->ch = ch;

    return n;
}

char buffer[BUFFSIZE];
int bits[BUFFSIZE];

node *scanschema(FILE *fin) {
    node *root = newnode();
    int n, i;
    while (!feof(fin)) {
        fgets(buffer, BUFFSIZE - 1, fin);
        for (n = 0; n < BUFFSIZE && buffer[n] != '\0' && buffer[n] != '\n'; ++n);
        for (i = 1; i < n; ++i) {
            bits[i - 1] = buffer[i] - '0';
        }
        add(root, buffer[0], n - 1, bits);
    }
    return root;
}

char *decode(node *trie, int len, int *code) {
    static char plain[BUFFSIZE];
    node *n = trie;
    int i, j = 0;
    for (i = 0; i < len; ++i) {
        n = traverse(n, code[i]);
        if (n->ch) {
            plain[j++] = n->ch;
            n = trie;
        }
    }
    plain[j] = '\0';
    return plain;
}

int main(int argc, char *argv[]) {
    if (argc % 2 != 1) {
        fprintf(stderr, "usage: %s [schemafile messagefile [schemafile messagefile ...]]\n", argv[0]);
        return 1;
    }

    int i;
    char *scheme, *message;
    FILE *sfile, *mfile;
    node *trie;
    char *bit;
    for (i = 1; i < argc; i += 2) {
        scheme = argv[i];
        message = argv[i + 1];

        sfile = fopen(scheme, "r");
        if (sfile == NULL) {
            fprintf(stderr, "could not open schema file: %s\n", scheme);
            return 1;
        }

        mfile = fopen(message, "r");
        if (mfile == NULL) {
            fprintf(stderr, "could not open message file: %s\n", message);
            return 1;
        }

        trie = scanschema(sfile);
        fscanf(mfile, "%s", buffer);
        for (bit = buffer; *bit; ++bit) {
            bits[bit - buffer] = *bit - '0';
        }
        printf("%s\n", decode(trie, strlen(buffer), bits));

        deltrie(trie);
    }

    return 0;
}
