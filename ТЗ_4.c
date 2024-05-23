#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#define inputStudent printf("Enter the number of students: ");
#define SizeOfMas(arr) printf("%d", arr);
void push(Node **head, student data) {
    Node *tmp = (Node *) malloc(sizeof(Node));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}
void SortList(Node** pBegin)
{
    int NodesCount=0;
    Node** Nodes=NULL;
    int i,j;
    Node* temp;
    temp=*pBegin;
    while(temp!=NULL)
    {
        NodesCount=NodesCount+1;
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
}
void print_list(Node** nodes){
    Node *tmp;
    tmp = *nodes;
    while(tmp!=NULL){
        printf("%s %s %s %d", tmp->value.surname, tmp->value.name, tmp->value.patronymic, tmp->value.group);
        tmp = tmp->next;
    }
}
void* inputStudents(void** head, void* arg2) {
    int count = (int)arg2;
    student newStudent;
    for (int i = 0; i < count; i++) {
        printf("Enter the %d student's last name: ", i+1);
        scanf("%s", &newStudent.surname);
        printf("Enter the student's name: ");
        scanf("%s", &newStudent.name);
        printf("Enter the student's middle name: ");
        scanf("%s", &newStudent.patronymic);
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
    int size = 0;
    inputStudent;
    scanf("%d", &size);
    Node *head = NULL;
    SizeOfMas(size);
    inputStudents((void *)&head, (void *) size);
    SortList(&head);
    print_list(&head);
    return 0;
}
