#include <stdio.h>
#include <stdlib.h>

#define INPUT_STUDENT printf("Enter the number of students: ");
#define SIZE_OF_MAS(arr) printf("%d", arr);

typedef struct student {
    char* surname;
    char name[50];
    char patronymic[50];
    int group;
    int mathematics;
    int physics;
    int chemistry;
    void (*hello)(struct student* _student);
} student;

typedef struct Node {
    student value;
    struct Node *next;
} Node;

void student_hello(struct student* _student) {
    printf("Hello %s\n", _student->surname);
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->value.surname);
        free(temp);
    }
}
void writeStudentsToFile(const char *filename, Node *head) {
    FILE *file = fopen(filename, "ab+");
    if (file == NULL) {
        printf("Error opening file.");
        exit(1);
    }
    Node *current = head;
    while (current != NULL) {
        fwrite(&(current->value), sizeof(student), 1, file);
        current = current->next;
    }
    fclose(file);
}
void outputFromFile(char *filename) {
    student buf;
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file.");
        exit(1);
    }
    while (fread(&buf, sizeof(student), 1, file)) {
        printf("%s %s %s %d %d %d %d\n",
               buf.surname, buf.name, buf.patronymic,
               buf.group, buf.mathematics, buf.physics,
               buf.chemistry);
    }
    fclose(file);
}
void push(Node **head, student data) {
    Node *tmp = (Node *) malloc(sizeof(Node));
    if (tmp == NULL) {
        printf("Memory allocation failed.");
        exit(1);
    }
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}
void SortList(Node** pBegin) {
    int NodesCount = 0;
    Node** Nodes = NULL;
    int i, j;
    Node* temp;
    temp = *pBegin;
    while (temp != NULL) {
        NodesCount = NodesCount + 1;
        temp = temp->next;
    }
    if (NodesCount != 0) {
        Nodes = malloc(NodesCount * sizeof(*Nodes));
        if (Nodes == NULL) {
            printf("Memory allocation failed.");
            exit(1);
        }
        i = 0;
        temp = *pBegin;
        while (temp != NULL) {
            Nodes[i] = temp;
            i = i + 1;
            temp = temp->next;
        }
        for (j = 0; j < NodesCount; j++) {
            for (i = 0; i < NodesCount - 1; i++) {
                if ((Nodes[i]->value.group) > (Nodes[i + 1]->value.group)) {
                    temp = Nodes[i];
                    Nodes[i] = Nodes[i + 1];
                    Nodes[i + 1] = temp;
                }
            }
        }
        for (i = 0; i < NodesCount - 1; i++) Nodes[i]->next = Nodes[i + 1];
        Nodes[NodesCount - 1]->next = NULL;
        *pBegin = Nodes[0];
        free(Nodes);
    }
}
void inputStudents(Node** head, int count) {
    student newStudent;
    for (int i = 0; i < count; i++) {
        newStudent.surname = malloc(50*(sizeof(char)));
        if (newStudent.surname == NULL) {
            printf("Memory allocation failed.");
            exit(1);
        }
        scanf("%s", newStudent.surname);
        printf("Enter the student's name: ");
        scanf("%s", newStudent.name);
        printf("Enter the student's middle name: ");
        scanf("%s", newStudent.patronymic);
        printf("Enter the student's group: ");
        scanf("%d", &newStudent.group);
        if(newStudent.group == NULL){
            printf("error");
        }
        if(sizeof(newStudent.group != 16)){
            printf("error group not found");
        }
        printf("Enter the math score: ");
        scanf("%d", &newStudent.mathematics);
        if(newStudent.mathematics ==  NULL){
            printf("error score not found\n");
        }
        switch(newStudent.mathematics){
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            default:
                printf("error: кому ты пиздишь? у тебя не %d ", newStudent.mathematics);
                break;
        }
        printf("Enter a physics grade: ");
        scanf("%d", &newStudent.physics);
        if(newStudent.physics == NULL){
            printf("error score not found");
        }
        switch(newStudent.physics){
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            default:
                printf("error: кому ты пиздишь? у тебя не %d ", newStudent.physics);
                break;
        }
        printf("Enter a chemistry grade: ");
        scanf("%d", &newStudent.chemistry);
        if(newStudent.chemistry == NULL){
            printf("error score not found");
        }
        switch(newStudent.chemistry){
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            default:
                printf("error: кому ты пиздишь? у тебя не %d ", newStudent.chemistry);
                break;
        }
        push(head, newStudent);
    }
}
void print_list(Node* head) {
    Node *tmp = head;
    while(tmp != NULL) {
        printf("%s %s %s %d\n", tmp->value.surname, tmp->value.name, tmp->value.patronymic, tmp->value.group);
        tmp = tmp->next;
    }
}
int main() {
    int size = 0;
    INPUT_STUDENT;
    scanf("%d", &size);
    Node *head = NULL;
    SIZE_OF_MAS(size);
    inputStudents(&head, size);
    writeStudentsToFile("students.bin", head);
    head->value.hello = student_hello;
    head->value.hello(&head->value);
    SortList(&head);
    print_list(head);
    free_list(head);
    printf("output\n");
    outputFromFile("students.bin");
    return 0;
}
