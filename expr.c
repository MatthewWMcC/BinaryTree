#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expr.h"

#define N 4

char* makeString(char* s1, char* s2, char* s3){
    
    int m = strlen(s1);
    int n = strlen(s2);
    int o = strlen(s3);
    char *ans = malloc((m + n + o + 1) * sizeof(char));
    if(ans == NULL){
        return NULL;
    }
    strcpy(ans, s1);
    strcat(ans, s2);
    strcat(ans, s3);
    return ans;
}

Node* createNode(char* s, double val){
    Node* ndeused;
    ndeused = malloc(sizeof(Node));
    if(ndeused == NULL){
        return NULL;
    }
    ndeused->left = NULL;
    ndeused->right = NULL;
    if(s != NULL){
        ndeused->expr_string = makeString(s, "","");
    }
    ndeused->num_parents = 0;
    ndeused->value = val;
    return ndeused;
}

Node* binop(Operation op, Node* a, Node* b){
    
    if(a->num_parents == 1 || b->num_parents == 1){
        return NULL;
    }
    
    Node* ndeused;
    ndeused = createNode(0,0);
    ndeused->left = a;
    
    ndeused->right = b;
    ndeused->operation = op;
    
    a->num_parents = 1;
    b->num_parents = 1;
    if(op == addop){
        ndeused->expr_string = makeString(a->expr_string,"+",b->expr_string);
    }
    if (op == subop)
    {
        ndeused->expr_string = makeString(a->expr_string,"-",b->expr_string);
    }
    if (op == mulop)
    {
        char *thing = makeString("(", a->expr_string, ")");
        char *thing2 = makeString("(", b->expr_string, ")");
        ndeused->expr_string = makeString(thing,"*", thing2);
        free(thing);
        free(thing2);
    }
    if (op == divop)
    {
        char *thing = makeString("(", a->expr_string, ")");
        char *thing2 = makeString("(", b->expr_string, ")");
        ndeused->expr_string = makeString(thing,"/", thing2);
        free(thing);
        free(thing2);
    }
    return ndeused;
}

double evalTree(Node* root){
    if(root == NULL){
        return 0;
    }
    if(root->left == NULL && root->right ==NULL){
        return root->value;
    }
    if(root->operation == addop){
        root->value = evalTree(root->left) + evalTree(root->right);
        return root->value;  
    }
    if(root->operation == subop){
        root->value = evalTree(root->left) - evalTree(root->right);
        return root->value;  
    }
    if(root->operation == mulop){
        root->value = evalTree(root->left) * evalTree(root->right);  
        return root->value; 
    }
    if(root->operation == divop){
        root->value = evalTree(root->left) / evalTree(root->right); 
        return root->value;
    }
    return root->value;
}

void freeTree(Node* root){
    if(root==NULL){
        return;
    } 
    free(root->expr_string);
    freeTree(root->left);
    freeTree(root->right);
    free(root);

    
}

Node *dupTreeHelp(Node *root, int parents) {
    if (root == NULL){
        return NULL;
    }

    Node *ndeused = malloc(sizeof(Node));
    ndeused->operation = root->operation;
    ndeused->value = root->value;
    ndeused->expr_string = makeString(root->expr_string, "", "");
    ndeused->num_parents = parents;
    ndeused->left = dupTreeHelp(root->left, 1);
    ndeused->right = dupTreeHelp(root->right, 1);

    return ndeused;
}

Node *duplicateTree(Node *root) {
    if (root == NULL){
        return NULL;
    }
    int parents = 0;
    return dupTreeHelp(root, parents);
}
void printTree(Node *root){
    if (root==NULL){
        return;
    }
    printf("Node\n");
    printf("    expr_string = %s\n",root->expr_string);
    printf("    value       = %g\n",root->value);
    printf("    num_parents = %d\n",root->num_parents);
    
    printTree(root->left);
    printTree(root->right);
    return;
}
