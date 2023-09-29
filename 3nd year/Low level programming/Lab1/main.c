#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE_SIZE 256

typedef struct Node {
    char data[MAX_NODE_SIZE];
    struct Node* children;
    struct Node* sibling;
} Node;

Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->children = NULL;
    newNode->sibling = NULL;
    return newNode;
}

void insertChild(Node* parent, Node* child) {
    if (parent->children == NULL) {
        parent->children = child;
    } else {
        Node* sibling = parent->children;
        while (sibling->sibling != NULL) {
            sibling = sibling->sibling;
        }
        sibling->sibling = child;
    }
}

Node* findNode(Node* root, const char* data) {
    if (strcmp(root->data, data) == 0) {
        return root;
    }
    Node* node = root->children;
    while (node != NULL) {
        Node* result = findNode(node, data);
        if (result != NULL) {
            return result;
        }
        node = node->sibling;
    }
    return NULL;
}

void printTree(Node* root, int indent) {
    for (int i = 0; i < indent; i++) {
        printf("    ");
    }
    printf("%s\n", root->data);
    
    Node* node = root->children;
    while (node != NULL) {
        printTree(node, indent + 1);
        node = node->sibling;
    }
    return;
}

void saveTreeToFile(Node* root, FILE* file) {
    fwrite(root, sizeof(Node), 1, file);
    
    Node* node = root->children;
    while (node != NULL) {
        saveTreeToFile(node, file);
        node = node->sibling;
    }
}

Node* loadTreeFromFile(FILE* file) { 
    Node* root = (Node*)malloc(sizeof(Node)); 
    fread(root, sizeof(Node), 1, file); 
  
    Node* node = root->children; 
    Node* prevSibling = NULL;
    while (node != NULL) { 
        Node* loadedNode = loadTreeFromFile(file); 
        if(prevSibling == NULL){
            root->children = loadedNode;
        } else {
            prevSibling->sibling = loadedNode;
        }
        loadedNode->sibling = NULL;
        prevSibling = loadedNode;
        node = node->sibling; 
    } 
    
    return root; 
}

int main() {
    Node* root = createNode("Root");
    
    Node* node1 = createNode("Node 1");
    insertChild(root, node1);
    
    Node* node11 = createNode("Node 1.1");
    insertChild(node1, node11);
    
    Node* node12 = createNode("Node 1.2");
    insertChild(node1, node12);
    
    Node* node2 = createNode("Node 2");
    insertChild(root, node2);
    
    Node* node21 = createNode("Node 2.1");
    insertChild(node2, node21);
    
    printf("Original Tree:\n");
    printTree(root, 0);
    FILE* file = fopen("tree.dat", "wb");
    if (file != NULL) {
        saveTreeToFile(root, file);
        fclose(file);
    }
    
    file = fopen("tree.dat", "rb");
    if (file != NULL) {
        Node* loadedRoot = loadTreeFromFile(file);
        fclose(file);
        printf("\nLoaded Tree:\n");
        printTree(loadedRoot, 0);
    }
    
    return 0;
}