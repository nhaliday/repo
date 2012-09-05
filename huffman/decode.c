#include <stdio.h>
#include <string.h>

#define BUFFSIZE 20
#define MAXENTRY 1000

typedef struct node node;
struct node {
    char ch;
    node *next[2];
};

node entry[MAXENTRY];

int nentry = 0;
node *head;

node *newentry() {
    return (nentry < MAXENTRY) ? &entry[nentry++] : NULL;
}

node *addedge(node *n, int b) {
    if (n->next[b] == NULL) {
        n->next[b] = newentry();
    }
    return n->next[b];
}

int main() {
    head = newentry();
    char buffer[BUFFSIZE];
    char *bit;
    int i, n;
    node *p;

    FILE *fin = fopen("decode.txt", "r");

    fscanf(fin, "%d", &n);

    for (i = 0; i < n; ++i) {
        fgets(buffer, BUFFSIZE, fin);
        p = head;
        for (bit = buffer + 1; *bit != '\n' && *bit != '\0'; ++bit) {
            p = addedge(p, *bit == '1');
        }
        p->ch = buffer[0];
    }

    fgets(buffer, BUFFSIZE, fin);
    p = head;
    for (bit = buffer; *bit != '\n' && *bit != '\0'; ++bit) {
        if (p->ch) {
            putchar(p->ch);
            p = head;
        }
        p = p->next[*bit == '1'];
    }

    putchar('\n');
}
