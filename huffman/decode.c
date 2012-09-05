#include <stdio.h>
#include <string.h>

int n;

const int BUFFSIZE = 20, MAXENTRY = 1000;
int nentry = 1;

typedef struct node node;
struct node {
    char ch;
    node *next[2];
};
node entry[MAXENTRY];

node *newentry() {
    return (nentry < MAXENTRY) ? &entry[nentry++] : NULL;
}

node *head = &entry[0];

node *addedge(node *n, int b) {
    if (n->next[b] == NULL) {
        n->next[b] = newentry();
    }
    return n->next[b];
}

int main() {
    FILE *fin = fopen("decode.txt", "r");
    fscanf(fin, "%d", &n);
    char buffer[BUFFSIZE];
    char *bit;
    int i;
    for (i = 0; i < n; ++i) {
        fgets(buffer, BUFFSIZE, fin);
        node *n = head;
        for (bit = buffer + 1; *bit != '\n' && *bit != '\0'; ++bit) {
            n = addedge(n, *bit == '1');
        }
        n->ch = buffer[0];
    }

    fgets(buffer, BUFFSIZE, fin);
    node *n = head;
    for (bit = buffer; *bit != '\n' && *bit != '\0'; ++bit) {
        if (n->ch) {
            putchar(n->ch);
            n = head;
        }
        n = n->next[*bit == '1'];
    }

    putchar('\n');
}
