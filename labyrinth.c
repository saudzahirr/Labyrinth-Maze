#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define and &&
#define or ||
#define not !

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
    struct Node* up;
    struct Node* down;
} Node;

typedef Node* NodePtr;

void computeNumberOfGates(NodePtr, int*);


int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    NodePtr topRowStart = NULL;         // Start of the very first row
    NodePtr prevRowStart = NULL;        // Start of the previous row
    NodePtr currentRowStart = NULL;     // Start of the current row

    while (fgets(buffer, sizeof(buffer), file)) {
        char* token = strtok(buffer, " \t\n");
        NodePtr prevNode = NULL;        // Track previous node in current row
        NodePtr upperNode = prevRowStart; // Start linking from the upper row
        currentRowStart = NULL;

        while (token != NULL) {
            NodePtr n = (NodePtr)malloc(sizeof(Node));
            if (!n) {
                perror("Node allocation failed");
                exit(EXIT_FAILURE);
            }

            n->value = atoi(token);
            n->left = n->right = n->up = n->down = NULL;

            if (!currentRowStart)
                currentRowStart = n;

            // Link to the previous node in the same row
            if (prevNode) {
                prevNode->right = n;
                n->left = prevNode;
            }

            // Link to the node above (if exists)
            if (upperNode) {
                n->up = upperNode;
                upperNode->down = n;
                upperNode = upperNode->right; // Move to next node in upper row
            }

            prevNode = n;
            token = strtok(NULL, " \t\n");
        }

        // After each row, set prevRowStart to currentRowStart for next iteration
        if (!topRowStart)
            topRowStart = currentRowStart;

        prevRowStart = currentRowStart;
    }

    fclose(file);

    printf("Grid values:\n");
    for (NodePtr row = topRowStart; row != NULL; row = row->down) {
        for (NodePtr col = row; col != NULL; col = col->right) {
            printf("%d ", col->value);
        }
        printf("\n");
    }

    int numberOfGates = 0;
    computeNumberOfGates(topRowStart, &numberOfGates);
    printf("Total number of gates: %d\n", numberOfGates);

    NodePtr row = topRowStart;
    while (row) {
        NodePtr nextRow = row->down;
        NodePtr col = row;
        while (col) {
            NodePtr nextCol = col->right;
            free(col);
            col = nextCol;
        }
        row = nextRow;
    }

    return 0;
}

void computeNumberOfGates(NodePtr topLeft, int* gates) {
    if (!topLeft) return;

    NodePtr ptr = topLeft;

    puts("Traversing the boundary ...");

    do {
        if (ptr->right and not ptr->up) {
            if (ptr->value % 2 == 0) {
                if (ptr->value == 0 and not ptr->left) {
                    *gates += 2;
                }
                else if (ptr->value == 2 and not ptr->right) {}
                else {
                    *gates += 1;
                }
            }
            else if (ptr->value == 1 and not ptr->left and not ptr->up) {
                *gates += 1;
            }
            ptr = ptr->right;
        }

        else if (not ptr->right and ptr->down) {
            if (ptr->value == 0) {
                *gates += 1;
            }
            ptr = ptr->down;
        }

        else if (ptr->left and not ptr->down) {
            if (ptr->value == 0 and ptr->right) {
                *gates += 1;
            }
            ptr = ptr->left;
        }

        else if (not ptr->left and ptr->up) {
            if (ptr->value == 0) {
                *gates += 1;
            }
            else if (ptr->value == 1 and ptr->down) {
                *gates += 1;
            }
            ptr = ptr->up;
        }

        else break;

    } while (ptr != topLeft);
}
