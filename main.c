#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int x;
    struct Node* next;
}Node;

void insert_end(Node** root, int value){
    Node* new_node = malloc(sizeof(Node));
    if (new_node==NULL){
        exit(1);
    }
    new_node->next=NULL;
    new_node->x = value;

    if(*root == NULL){
        *root = new_node;
        return;
    }
    Node *curr = *root;
    while (curr->next !=NULL){
        curr = curr->next;
    }
    curr->next=new_node;
}

void insert_beginning(Node** root, int value){
    Node *new_node = malloc(sizeof(Node));
    if (new_node==NULL){
        exit(3);
    }
    new_node->x=value;
    new_node->next = *root;

    *root =new_node;
}

void insert_after(Node* node, int value){
    Node *new_node = malloc(sizeof(Node));
    if (new_node==NULL){
        exit(3);
    }

    new_node->x = value;
    new_node->next = node->next;
    node->next = new_node;

}

void deallocate(Node **root){
    Node* curr = *root;
    while( curr != NULL){
        Node* aux = curr;//usage of aux pointer in order to keep track of the other nodes
        // instead of releasing one place and other not accessible
        curr = curr->next;
        free(aux);
    }
    *root=NULL;
}

void insert_sorted(Node** root, int value){
    if (*root  == NULL || (*root)->x>=value){ //checking if the linked list is empty
        // or at other case if first element bigger than value
        insert_beginning(root, value);
        return;
    }
    //iterating over the list
    Node *curr = *root;
    while(curr->next != NULL){
        if (curr->next->x>=value){
            break;//inserting element in current position and in sorter way
        }
        curr = curr->next;
    }
    insert_after(curr,value); // inserting a bigger element

}

int main() {
    Node* root = NULL;
    insert_sorted(&root, 1);
    insert_sorted(&root,2);
    insert_sorted(&root,0);
    insert_sorted(&root,-1);


//    insert_beginning(&root, 13);
//    insert_beginning(&root, 15);
//    insert_beginning(&root, 19);
//    insert_after(root->next->next, 7);
//    insert_end(&root, -2);
//    insert_end(&root, 11);
//    insert_after(root->next->next->next->next, 2);

    for(Node* curr= root; curr !=NULL; curr= curr->next){
        printf("%d\n", curr->x);
    }
    deallocate(&root);



    return 0;
}
