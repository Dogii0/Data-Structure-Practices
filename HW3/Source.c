#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define SIZE 50
#define upL 50
#define lowL -50

typedef struct _node {
    int val;
    struct _node* left;
    struct _node* right;
}Node;

Node* addNode(Node* curNode, int val) {
    if (curNode == NULL) {
        Node* newNode = malloc(sizeof(Node));
        newNode->val = val;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    else {
        if (curNode->val > val)
            curNode->left = addNode(curNode->left, val);
        else
            curNode->right = addNode(curNode->right, val);
    }
    return curNode;
}

Node* queue[SIZE];
int front, rear;
Node* deq() {
    return queue[front++];
}
void enq(Node* node) {
    if (rear == -1) front++;
    queue[++rear] = node;
}

int num, sum;

int BFT(Node* curNode) {
    front = rear = -1;
    enq(curNode);
    while (front <= rear) {
        Node* curNode = deq();
        printf("%d(%d)-> ", curNode->val, num);
        sum += curNode->val;
        num--;
        if (num <= 0) return sum;
        if (curNode->left != NULL)
            enq(curNode->left);
        if (curNode->right != NULL)
            enq(curNode->right);
    }
}

int DFT(Node* curNode) {
    if (curNode == NULL || num <= 0) return sum;
    printf("%d(%d)-> ", curNode->val, num);
    sum += curNode->val;
    num--;
    DFT(curNode->left);
    DFT(curNode->right);
}

int all;

int main() {
    freopen("C:\\Users\\Dell\\Downloads\\hw3_input.txt", "r", stdin);
    FILE* outFile = fopen("output.txt ", "w");
    scanf("%d\n", &all);
    int count = 0;
    while (count < all) {
        char type;
        sum = 0;
        scanf("%c", &type);
        scanf("FS: %d\n", &num);
        Node* tree = NULL;
        if (type == 'B' || type == 'D') {
        printf("type: %c, num: %d\n", type, num);
            int arr[SIZE];
            int i = 0;
            while (i < SIZE) {
                arr[i] = upL + 1;
                scanf("%d", &arr[i]);
                if (arr[i]<=upL && arr[i]>=lowL)
                    tree = addNode(tree, arr[i]);
                i++;
            }

            if (type == 'B')
                fprintf(outFile, "%d\n", BFT(tree));
            else if (type == 'D') {
                fprintf(outFile, "%d\n", DFT(tree));
            }

            printf("\n");
            count++;
        }
    }

    fclose(outFile);
    return 0;
}