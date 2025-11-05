#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;


typedef struct LinkedList {
    Node* head;
    int size;
} LinkedList;

void initList(LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}


Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}
int insertElement(LinkedList* list, int i, int e) {
    if (i < 0 || i > list->size) {
        return -1;
    }
    Node* newNode = createNode(e);
    if (!newNode) {
        return -1;
    }

    if (i == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node* prev = list->head;
        for (int j = 0; j < i - 1; j++) {
            prev = prev->next;
        }
        newNode->next = prev->next;
        prev->next = newNode;
    }

    list->size++;
    return 0;
}

void printList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}


void freeList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->size = 0;
}
int main() {
    LinkedList list;
    initList(&list);

    insertElement(&list, 0, 1);  // 在位置0插入元素1
    insertElement(&list, 1, 3);  // 在位置1插入元素3
    insertElement(&list, 1, 2);  // 在位置1插入元素2

    printList(&list);  // 输出链表: 1 -> 2 -> 3 -> NULL

    freeList(&list);  // 释放链表内存

    return 0;
}
