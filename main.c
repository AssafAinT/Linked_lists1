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

void remove_element(Node** root, int value){//only removes the first occurence of the element
    if (*root == NULL){
        return; // element not found
    }
    if((*root)->x == value){//edge cases
        Node* to_remove = *root;
        *root = (*root)->next;
        free(to_remove);
        return;
    }
    for(Node* curr = *root; curr->next!=NULL;curr=curr->next){
        if(curr->next->x == value){
            Node* to_remove = curr->next;
            curr->next = curr->next->next;
            free(to_remove);
            return;
        }
    }
}

void reverse(Node** root){
    Node* prev = NULL;
    Node* curr = *root;

    while(curr!=NULL){
        Node* next = curr->next;

        curr->next = prev;

        prev = curr;
        curr = next;

    }
    *root = prev;

}

int has_loops(Node* root){
    Node* slow = root;
    Node* fast = root;
    while (slow != NULL && fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        if(slow==fast){//checking if pointing to the same address which means there is a cycle/loop
            return 1;
        }
    }
    return 0;
}

int count(Node* root)
{
    int cnt = 0;
    for (Node* curr = root; curr !=NULL;curr= curr->next){
        cnt++;
    }
    return cnt;
}

int count_rec(Node* node){ // counting elements in recursive manner.
    if (node == NULL){
        return 0;
    }
    return 1 + count_rec(node->next);
}

int main() {
    Node* root = NULL;
//    insert_sorted(&root, 1);
//    insert_sorted(&root,2);
//    insert_sorted(&root,0);
//    insert_sorted(&root,-1);
    insert_end(&root,1);
    insert_end(&root,1);
    insert_end(&root,3);
    insert_end(&root,6);
    insert_end(&root,7);

//    root->next->next->next->next->next = root->next;

    if(has_loops(root) == 1){
        printf("linked list has a loop\n");
        return 1;
    }

//    reverse(&root);

//    remove_element(&root, 2);

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

//    printf("\nLinked list has %d elements\n", count(root));
    printf("\nLinked list has %d elements\n", count_rec(root));
    deallocate(&root);
    return 0;
}
