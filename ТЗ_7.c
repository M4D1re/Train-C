#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_STUDENT printf("Enter the number of students: ");
#define SIZE_OF_MAS(arr) printf("%d", (int) sizeof(arr));

typedef struct student {
    char surname[50];
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
        free(temp);
    }
}

void writeStudentsToFile(const char *filename, Node *head) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Node *current = head;
    while (current != NULL) {
        int surname_length = strlen(current->value.surname) + 1;
        if (fwrite(&surname_length, sizeof(int), 1, file) != 1 ||
            fwrite(current->value.surname, sizeof(char), surname_length, file) != surname_length ||
            fwrite(current->value.name, sizeof(char), 50, file) != 50 ||
            fwrite(current->value.patronymic, sizeof(char), 50, file) != 50 ||
            fwrite(&current->value.group, sizeof(int), 1, file) != 1 ||
            fwrite(&current->value.mathematics, sizeof(int), 1, file) != 1 ||
            fwrite(&current->value.physics, sizeof(int), 1, file) != 1 ||
            fwrite(&current->value.chemistry, sizeof(int), 1, file) != 1) {
            perror("Error writing to file");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        current = current->next;
    }
    fclose(file);
}

void outputFromFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (1) {
        int surname_length;
        if (fread(&surname_length, sizeof(int), 1, file) != 1) break;

        char surname[50];
        if (fread(surname, sizeof(char), surname_length, file) != surname_length) {
            perror("Error reading from file");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        surname[surname_length - 1] = '\0';

        student buf;
        if (fread(buf.name, sizeof(char), 50, file) != 50 ||
            fread(buf.patronymic, sizeof(char), 50, file) != 50 ||
            fread(&buf.group, sizeof(int), 1, file) != 1 ||
            fread(&buf.mathematics, sizeof(int), 1, file) != 1 ||
            fread(&buf.physics, sizeof(int), 1, file) != 1 ||
            fread(&buf.chemistry, sizeof(int), 1, file) != 1) {
            perror("Error reading from file");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        printf("%s %s %s %d %d %d %d\n", surname, buf.name, buf.patronymic, buf.group, buf.mathematics, buf.physics, buf.chemistry);
    }
    fclose(file);
}

void push(Node **head, student data) {
    Node *tmp = (Node *) malloc(sizeof(Node));
    if (tmp == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}

void SortList(Node** pBegin) {
    int NodesCount = 0;
    Node** Nodes = NULL;
    Node* temp = *pBegin;

    while (temp != NULL) {
        NodesCount++;
        temp = temp->next;
    }

    if (NodesCount > 0) {
        Nodes = malloc(NodesCount * sizeof(*Nodes));
        if (Nodes == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        int i = 0;
        temp = *pBegin;
        while (temp != NULL) {
            Nodes[i++] = temp;
            temp = temp->next;
        }

        for (int j = 0; j < NodesCount - 1; j++) {
            for (int i = 0; i < NodesCount - 1 - j; i++) {
                if (Nodes[i]->value.group > Nodes[i + 1]->value.group) {
                    Node* tempNode = Nodes[i];
                    Nodes[i] = Nodes[i + 1];
                    Nodes[i + 1] = tempNode;
                }
            }
        }

        for (i = 0; i < NodesCount - 1; i++) {
            Nodes[i]->next = Nodes[i + 1];
        }
        Nodes[NodesCount - 1]->next = NULL;
        *pBegin = Nodes[0];
        free(Nodes);
    }
}

void inputStudents(Node** head, int count) {
    student newStudent;
    for (int i = 0; i < count; i++) {
        printf("Enter the %d student's last name: ", i + 1);
        scanf("%49s", newStudent.surname);
        printf("Enter the student's name: ");
        scanf("%49s", newStudent.name);
        printf("Enter the student's middle name: ");
        scanf("%49s", newStudent.patronymic);
        printf("Enter the student's group: ");
        scanf("%d", &newStudent.group);
        printf("Enter the math score: ");
        scanf("%d", &newStudent.mathematics);
        printf("Enter a physics grade: ");
        scanf("%d", &newStudent.physics);
        printf("Enter a chemistry grade: ");
        scanf("%d", &newStudent.chemistry);
        push(head, newStudent);
    }
}

void print_list(Node* head) {
    Node *tmp = head;
    while (tmp != NULL) {
        printf("%s %s %s %d\n", tmp->value.surname, tmp->value.name, tmp->value.patronymic, tmp->value.group);
        tmp = tmp->next;
    }
}

int main() {
    int size = 0;
    INPUT_STUDENT;
    scanf("%d", &size);

    Node *head = NULL;
    SIZE_OF_MAS(head);

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
