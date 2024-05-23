#include <stdio.h>
#include <malloc.h>
 typedef struct student {
    char surname[50];
    char name[50];
    char patronymic[50];
    int group;
    int mathematics;
    int physics;
    int chemistry;
}student;

typedef struct Node {
    student value;
    struct Node *next;
} Node;

struct LIST{
    Node** node;
    int count;
};

void push(Node **head, student data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}
void* SortList(void** pBegin)
{
    int NodesCount=0;
    Node** Nodes=NULL;
    int i,j;
    Node* temp;
    temp=(Node*)*pBegin;
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
void* print_list(void** nodes){
    Node *tmp;
    tmp = (Node*)*nodes;
    while(tmp!=NULL){
        printf("%s %s %s %d", tmp->value.surname, tmp->value.name, tmp->value.patronymic, tmp->value.group);
        tmp = tmp->next;
    }
}
void* inputStudents(void* arg) {
    struct LIST *tmp = (struct LIST*)arg;
    Node **head = tmp->node;
    int count = tmp->count;
    student students;
    for (int i = 0; i < count; i++) {
        printf("%d\n", count);
        printf("Enter the student's last name: ");
        scanf("%s", students.surname);
        printf("Enter the student's name: ");
        scanf("%s", students.name);
        printf("Enter the student's middle name: ");
        scanf("%s", students.patronymic);
        printf("Enter the student's group: ");
        scanf("%d", &students.group);
        printf("Enter the math score: ");
        scanf("%d", &students.mathematics);
        printf("Enter a physics grade: ");
        scanf("%d", &students.physics);
        printf("Enter a chemistry grade: ");
        scanf("%d", &students.chemistry);
        push(head, students);
    }
}
int main() {
    Node *head = NULL;
    int size = 0;
    printf("Enter the number of students: ");
    scanf("%d", &size);
    struct LIST tmp = {&head, size};
    inputStudents(&tmp);
    SortList(&head);
    print_list(&head);
    return 0;
}
