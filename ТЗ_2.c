#include <stdio.h>
#include <stdlib.h>
typedef struct student {
    char surname[50];
    char name[50];
    char patronymic[50];
    int group;
    int mathematics;
    int physics;
    int chemistry;
} student;
typedef struct TreeNode {
    student data;
    struct TreeNode *left;
    struct TreeNode *right;
    void (*PrintStudentI)(struct TreeNode*);
    void (*InputStudentsI)(struct TreeNode*, int)
} TreeNode;
TreeNode* insertNode(TreeNode *root, student newStudent) {
    if(root == NULL) {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        newNode->data = newStudent;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if(newStudent.group < root->data.group) {
        root->left = insertNode(root->left, newStudent);
    } else {
        root->right = insertNode(root->right, newStudent);
    }
    printf("OK\n");
    return root;
}
void PrintStudents(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    PrintStudents(root->left);
    printf("%s %s %s %d %d %d %d\n", root->data.surname, root->data.name, root->data.patronymic,
           root->data.group, root->data.mathematics, root->data.physics, root->data.chemistry);
    PrintStudents(root->right);
}
void InputStudents(TreeNode *root, int count){
    struct student students;
    for(int i = 0; i < count; i++) {
        printf("%d Enter the student's last name: ", i + 1);
        scanf("%s", students.surname);
        printf("%d Enter the student's name: ", i + 1);
        scanf("%s", students.name);
        printf("%d Enter the student's middle name: ", i + 1);
        scanf("%s", students.patronymic);
        printf("%d Enter the student's group: ", i + 1);
        scanf("%d", &students.group);
        printf("%d Enter the math score: ", i + 1);
        scanf("%d", &students.mathematics);
        printf("%d Enter a physics grade: ", i + 1);
        scanf("%d", &students.physics);
        printf("%d Enter a chemistry grade: ", i + 1);
        scanf("%d", &students.chemistry);
        root = insertNode(root, students);
    }
}
int main() {
    int count = 0;
    printf("Enter the number of students: ");
    scanf("%d", &count);
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    root->InputStudentsI = &InputStudents;
    root->PrintStudentI = &PrintStudents;
    root->InputStudentsI(root, count);
    root->PrintStudentI(root);
    return 0;
}
