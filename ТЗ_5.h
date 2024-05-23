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
