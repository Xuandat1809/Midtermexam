#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Address {
    char name[50];
    char phone[15];
    char email[50];
}Address;
typedef struct Address Add;

void sort(Add add[], int n){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = i + 1; j < n; j++){
            if (strcmp(add[i].name, add[j].name) > 0){
                Add tmp = add[i];
                add[i] = add[j];
                add[j] = tmp;
            }
        }
    }
}

Add input(){
    Add add;
    printf("Nhap ten: ");
    scanf("%s", &add.name);
    printf("Nhap sdt: ");
    scanf("%s", &add.phone);
    printf("Nhap email: ");
    scanf("%s", &add.email);
    return add;
}

void inputs(Add add[], int n){
    int i = 0;
    for(i = 0; i < n; i++){
        Add a = input();
        add[i] = a;
        printf("===============\n");
    }
}

void output(Add add){
    printf("%s - %s - %s\n", add.name, add.phone, add.email);
}

void outputs(Add add[], int n){
    int i;
    for(i = 0; i < n; i++){
        output(add[i]);
    }
}

int bSearch(Add add[], int n){
    char keyword[50];
    printf("Nhap tu khoa can tim: ");
    scanf("%s", &keyword);
    int l = 0;
    int r = n - 1;
    while (l <= r){
        int mid = l + (r-l)/2;
        int result = strcmp(add[mid].name, keyword);
        if (result == 0){
            return mid;
        }else if (result < 0){
            l = mid + 1;
        }else {
            r = mid - 1;
        }
    }
    return -1;
}

/* Linked list */

struct LinkedList{
    Add data;
    struct LinkedList *next;
 };
 
typedef struct LinkedList *node; 
 
node CreateNode(Add value){
    node temp;
    temp = (node)malloc(sizeof(struct LinkedList));
    temp->next = NULL;
    temp->data = value;
    return temp;
}
 
node AddTail(node head, Add value){
    node temp,p;
    temp = CreateNode(value);
    if(head == NULL){
        head = temp;     
    }
    else{
        p  = head;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = temp;
    }
    return head;
}

int llSearch(node head){
    char keyword[50];
    printf("Nhap tu khoa can tim: ");
    scanf("%s", &keyword);
    for(node p = head; p != NULL; p = p->next){
        if(strcmp(p->data.name, keyword) == 0){
            // đổi chỗ về đầu
            Add tmp = p->data;
            p->data = head->data;
            head->data = tmp;
            return 1;
        }
    }
    return -1;
}

/* Queue */
void Enqueue(Add queue[], Add element, int* rear, int arraySize, int* count) {
    if(*count == arraySize)          // Queue is full
            printf("OverFlow\n");
    else {
        queue[*rear] = element;
        *rear = (*rear + 1)%arraySize;
        *count = *count + 1;
    }
}

Add Dequeue(Add queue[], int* front, int rear, int* count, int arraySize) {
    if(*count == 0)            // Queue is empty
        printf("UnderFlow\n");
    else {
        Add result = queue[*front];
        strcpy(queue[*front].name, "\0");        // Delete the front element
        strcpy(queue[*front].email, "\0");        // Delete the front element
        strcpy(queue[*front].phone, "\0");        // Delete the front element
        *front = ((*front) + 1)%arraySize;
        *count = *count - 1;
        return result;
    }
}

int main(){
    /* 1 */
    Add add[105];
    int n, i, r;
    printf("Nhap so luong n = ");
    scanf("%d", &n);
    inputs(add, n);
    outputs(add, n);
    sort(add, n);
    outputs(add, n);
    r = bSearch(add, n);
    if (r != -1){
        output(add[r]);
    }else {
        printf("Not found!\n");
    }
    /* 2 */
    node head = NULL;
    for (i = 0; i < n; i++){
        head = AddTail(head, add[i]);
    }
    r = llSearch(head);
    if (r != -1){
        output(head->data);
    }else {
        printf("Not found!\n");
    }

    /* 3 + 4 */
    int max_queue = 10;
    int count = 0, front = 0, rear = 0;
    Add queue[max_queue];
    printf("Nhap so luong n = ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        Add tmp = input();
        if (count < max_queue) {
            Enqueue(queue, tmp, &rear, max_queue, &count);
        }else {
            // nếu quá 10 thì xóa sau đó mới thêm
            Add result = Dequeue(queue, &front, rear, &count, max_queue);
            Enqueue(queue, tmp, &rear, max_queue, &count);
            output(result);
        }
    }
    // queue search
    char keyword[50];
    printf("Nhap tu khoa can tim: ");
    scanf("%s", &keyword);
    int found = 0;
    while (count > 0){
        Add tmp = Dequeue(queue, &front, rear, &count, max_queue);
        if (strcmp(keyword, tmp.name) == 0){
            output(tmp);
            found = 1;
            break;
        }
    }
    if (found == 0){
        printf("Not found!\n");
    }
}