#include <stdio.h>
#include <stdlib.h>
struct student {
    char surname[10];
    char name[10];
    char patronymic[10];
    int group;
    int mathematics;
    int physics;
    int chemistry;
};
struct Node {
    struct student value;
    struct Node *next;
    void (*SortListI)(struct Node**);
    void (*print_listI)(struct Node**);
    void (*inputStudentsI)(struct Node**, int);
};

void push(struct Node **head, struct student data) {
    struct Node *tmp = (struct Node*) malloc(sizeof(struct Node));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
    printf("OK");
}
void SortList(struct Node** pBegin) {
    int NodesCount=0;
    struct Node** Nodes=NULL;
    int i,j;
    struct Node* temp;
    temp=*pBegin;
    while(temp!=NULL)
    {
        NodesCount++;
        temp=temp->next;
    }
    if(NodesCount!=0)
    {
        Nodes=malloc(NodesCount*sizeof(*Nodes));
        i=0;
        temp=*pBegin;
        while(temp!=NULL)
        {
            Nodes[i]=temp;
            i=i+1;
            temp=temp->next;
        }
        for(j=0;j<NodesCount;j++)
        {
            for(i=0;i<NodesCount-1;i++)
            {
                if((Nodes[i]->value.group) > (Nodes[i+1]->value.group))
                {
                    temp=Nodes[i];
                    Nodes[i]=Nodes[i+1];
                    Nodes[i+1]=temp;
                }
            }
        }
        for(i=0;i<NodesCount-1;i++) Nodes[i]->next=Nodes[i+1];
        Nodes[NodesCount-1]->next=NULL;
        *pBegin=Nodes[0];
        free(Nodes);
    }
    printf("OKOK");
}
void print_list(struct Node** nodes){
    struct Node *tmp;
    tmp = *nodes;
    while(tmp!=NULL){
        printf("%s %s %s %d\n", tmp->value.surname, tmp->value.name, tmp->value.patronymic, tmp->value.group);
        tmp = tmp->next;
    }
}
void inputStudents(struct Node **head, int count) {
    struct student newStudent;
    for (int i = 0; i < count; i++) {
        printf("\nnum of student: %d\n", i);
        printf("Enter the student's last name: ");
        scanf("%s", newStudent.surname);
        printf("Enter the student's name: ");
        scanf("%s", newStudent.name);
        printf("Enter the student's middle name: ");
        scanf("%s", newStudent.patronymic);
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
int main() {
    int count = 0;
    printf("Enter the number of students: ");
    scanf("%d", &count);
    struct Node *head = (struct Node*) malloc(sizeof(struct Node));

    head->SortListI = &SortList;
    head->print_listI = &print_list;
    head->inputStudentsI = &inputStudents;

    head->inputStudentsI(head, count);
    head->SortListI(head);
    head->print_listI(head);
    return 0;
}
