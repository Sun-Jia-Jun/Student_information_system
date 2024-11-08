#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ID_LENGTH 20
#define MAX_NAME_LENGTH 10
#define DATA_FILE "student.txt"

// ����ѧ����Ϣ�ṹ��
typedef struct info
{
    char ID[MAX_ID_LENGTH];
    char Name[MAX_NAME_LENGTH];
    float Score1, Score2, Score3, Score4; // Ӣ�� ��ѧ ���� ��˼
    float Total;                          // �ܷ�
    float Avg;                            // ƽ����
} Info;

// ��������ڵ�
typedef struct Node
{
    Info studentInfo;
    struct Node *next;
} Node;

Node *head = NULL; // ��������ͷָ��

// ��ʾ�˵�
int Menu(void)
{
    int choice;
    printf("------------------------------------------------------------------------------------------------\n");
    printf("��ӭʹ��ѧ����Ϣ����ϵͳ-by sjj\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("��ѡ��ϵͳ����\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("0. �˳�ϵͳ\n");
    printf("1. ¼��ѧ����Ϣ\n");
    printf("2. �޸�ѧ����Ϣ\n");
    printf("3. ɾ��ѧ����Ϣ\n");
    printf("4. ����ѧ����Ϣ\n");
    printf("5. ��ӡѧ����Ϣ\n");
    printf("6. ����ѧ����Ϣ\n");
    printf("7. ѧ���ɼ�����\n");
    printf("8. ����ѧ����Ϣ�ļ�\n");
    printf("9. ���ļ��е���ѧ����Ϣ\n");
    printf("10. ������Ʋ������ѧ����Ϣ\n");
    printf("11. ���������߷ֵ�ѧ����Ϣ\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("������ѡ�");
    scanf("%d", &choice);
    return choice;
}

// �����ֺܷ�ƽ����
void calculateScores(Node *student)
{
    student->studentInfo.Total = student->studentInfo.Score1 + student->studentInfo.Score2 + student->studentInfo.Score3 + student->studentInfo.Score4;
    student->studentInfo.Avg = student->studentInfo.Total / 4;
}

// ���������ļ�
void generateDataFile()
{
    FILE *file = fopen(DATA_FILE, "w");
    if (file == NULL)
    {
        printf("�ļ�����ʧ�ܣ�\n");
        return;
    }
    fclose(file);
    printf("ѧ����Ϣ�ļ����ɳɹ���\n");
}

// ���ļ��м�������
void loadData()
{
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL)
    {
        printf("�ļ������ڣ��볢������ѧ����Ϣ�ļ���\n");
        return;
    }

    while (!feof(file))
    {
        Node *newStudent = (Node *)malloc(sizeof(Node)); // Ϊ��ѧ�������ڴ�
        if (fscanf(file, "%s %s %f %f %f %f", newStudent->studentInfo.ID, newStudent->studentInfo.Name,
                   &newStudent->studentInfo.Score1, &newStudent->studentInfo.Score2,
                   &newStudent->studentInfo.Score3, &newStudent->studentInfo.Score4) == 6)
        // ע�⣺ID,Name�������飬�����ֱ���ָ�룬����&ȡ��ַ��
        {
            calculateScores(newStudent); // �����ֺܷ�ƽ����
            newStudent->next = head;     // newStudent��һ���ڵ�Ϊ���ڵ�head
            head = newStudent;           // ��headָ��ָ���²���ͷ���Ľڵ�
        }
        else
        {
            free(newStudent); // ��ȡʧ�����ͷ��ڴ�
        }
    }
    fclose(file);
}

// д�����ݵ��ļ�
void saveData()
{
    FILE *file = fopen(DATA_FILE, "w"); // w:����д��,����ļ��������򴴽�
    if (head == NULL)
    {
        printf("ѧ����ϢΪ�գ�\n");
        fclose(file);
        return;
    }
    Node *current = head;   // ʹ��currentָ���������
    while (current != NULL) // �������е����нڵ�д���ļ�
    {
        fprintf(file, "%s %s %.2f %.2f %.2f %.2f\n", current->studentInfo.ID, current->studentInfo.Name,
                current->studentInfo.Score1, current->studentInfo.Score2, current->studentInfo.Score3, current->studentInfo.Score4);
        current = current->next;
    }
    fclose(file);
}

// ���ѧ����Ϣ
void addStudent()
{
    Node *newStudent = (Node *)malloc(sizeof(Node)); // Ϊ��ѧ�������ڴ�
    if (newStudent == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    printf("������ѧ����Ϣ��\n");
    printf("������ѧ�ţ�");
    scanf("%s", newStudent->studentInfo.ID);
    printf("������������");
    scanf("%s", newStudent->studentInfo.Name);
    printf("������Ӣ��ɼ���");
    scanf("%f", &newStudent->studentInfo.Score1);
    printf("��������ѧ�ɼ���");
    scanf("%f", &newStudent->studentInfo.Score2);
    printf("���������ĳɼ���");
    scanf("%f", &newStudent->studentInfo.Score3);
    printf("�������˼�ɼ���");
    scanf("%f", &newStudent->studentInfo.Score4);

    // �����ֺܷ�ƽ����
    calculateScores(newStudent);

    newStudent->next = head; // ���½ڵ��������ͷ��
    head = newStudent;       // ����ͷָ��

    saveData(); // �������ݵ��ļ�
    printf("ѧ����Ϣ¼��ɹ���\n");
}

// �޸�ѧ����Ϣ
void updateStudent()
{
    char ID[MAX_ID_LENGTH];
    printf("������ѧ��ѧ�ţ�");
    scanf("%s", ID);
    Node *current = head;

    while (current != NULL)
    {
        if (strcmp(current->studentInfo.ID, ID) == 0) // �ҵ���ӦID��ѧ��
        {
            printf("������ѧ����Ϣ��\n");
            printf("������������");
            scanf("%s", current->studentInfo.Name);
            printf("������Ӣ��ɼ���");
            scanf("%f", &current->studentInfo.Score1);
            printf("��������ѧ�ɼ���");
            scanf("%f", &current->studentInfo.Score2);
            printf("���������ĳɼ���");
            scanf("%f", &current->studentInfo.Score3);
            printf("�������˼�ɼ���");
            scanf("%f", &current->studentInfo.Score4);

            calculateScores(current); // �����ֺܷ�ƽ����
            saveData();               // �������ݵ��ļ�
            printf("ѧ����Ϣ�޸ĳɹ���\n");
            return;
        }
        current = current->next; // �ƶ�����һ���ڵ�
    }
    printf("δ�ҵ���ѧ����\n");
}

// ɾ��ѧ����Ϣ
void deleteStudent()
{
    char ID[MAX_ID_LENGTH];
    printf("������ѧ��ѧ�ţ�");
    scanf("%s", ID);

    Node *current = head;
    Node *previous = NULL; // previous��ʼ��ΪNULL�����ڼ�¼��ǰ�ڵ��ǰһ���ڵ�

    while (current != NULL)
    {
        if (strcmp(current->studentInfo.ID, ID) == 0)
        {
            if (previous == NULL)
            {                         // �ж��Ƿ�Ϊͷ�ڵ�
                head = current->next; // ��ͷָ��ָ����һ���ڵ㣬��ɶ�ͷ�ڵ��ɾ��
            }
            else
            {                                   // ɾ����ͷ�ڵ�
                previous->next = current->next; // ���������Ƴ���ǰ�ڵ�
            }
            free(current); // �ͷ�current�ڵ�ռ�õ��ڴ�
            saveData();
            printf("ѧ����Ϣɾ���ɹ���\n");
            return;
        }
        previous = current;
        current = current->next; // �ƶ�����һ���ڵ�
    }
    printf("δ�ҵ���ѧ����\n");
}

// ��ӡ����ѧ����Ϣ
void printStudent()
{
    Node *current = head; // ������ͬ��
    if (current == NULL)
    {
        printf("ѧ����ϢΪ�գ�\n");
        return;
    }
    while (current != NULL)
    {
        printf("------------------------------------------------------------------------------------------------\n");
        printf("ѧ�ţ�%s\n", current->studentInfo.ID);
        printf("������%s\n", current->studentInfo.Name);
        printf("Ӣ��ɼ���%.2f\n", current->studentInfo.Score1);
        printf("��ѧ�ɼ���%.2f\n", current->studentInfo.Score2);
        printf("���ĳɼ���%.2f\n", current->studentInfo.Score3);
        printf("��˼�ɼ���%.2f\n", current->studentInfo.Score4);
        printf("�ܷ֣�%.2f\n", current->studentInfo.Total);
        printf("ƽ���֣�%.2f\n", current->studentInfo.Avg);
        current = current->next;
    }
    printf("------------------------------------------------------------------------------------------------\n");
}

// ����ѧ����Ϣ
void insertStudent()
{
    Node *newStudent = (Node *)malloc(sizeof(Node));
    char position[MAX_NAME_LENGTH];
    if (newStudent == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }
    printf("������ѧ����Ϣ��\n");
    printf("������ѧ�ţ�");
    scanf("%s", newStudent->studentInfo.ID);
    printf("������������");
    scanf("%s", newStudent->studentInfo.Name);
    printf("������Ӣ��ɼ���");
    scanf("%f", &newStudent->studentInfo.Score1);
    printf("��������ѧ�ɼ���");
    scanf("%f", &newStudent->studentInfo.Score2);
    printf("���������ĳɼ���");
    scanf("%f", &newStudent->studentInfo.Score3);
    printf("�������˼�ɼ���");
    scanf("%f", &newStudent->studentInfo.Score4);
    calculateScores(newStudent);

    printf("������ѧ��ѧ�ţ��Ա���뵽��ѧ�������λ�ã�\n");
    scanf("%s", position);

    Node *current = head;
    Node *previous = NULL;
    while (current != NULL)
    {
        if (strcmp(current->studentInfo.ID, position) == 0)
        {
            if (previous == NULL) // Ҫ����ͷ�ڵ�
            {
                newStudent->next = head;
                head = newStudent;
            }
            else
            {
                newStudent->next = current;
                previous->next = newStudent;
            }
            break;
        }
        previous = current;
        current = current->next;
    }
    if (current == NULL)
    {
        printf("δ�ҵ�ָ��ѧ�ŵ�ѧ�����޷����룡\n");
        free(newStudent);
        return;
    }
    saveData();
    printf("ѧ����Ϣ����ɹ���\n");
}

// ����ѧ����Ϣ
void searchStudent()
{
    char ID[MAX_ID_LENGTH] = "";
    char Name[MAX_NAME_LENGTH] = "";
    printf("��ѡ����ҷ�ʽ��\n");
    printf("1. ѧ��\n");
    printf("2. ����\n");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("������ѧ��ѧ�ţ�");
        scanf("%s", ID);
        break;
    case 2:
        printf("������ѧ��������");
        scanf("%s", Name);
        break;
    default:
        printf("����������������룡\n");
        return;
    }

    Node *current = head;

    while (current != NULL)
    {
        if (strcmp(current->studentInfo.ID, ID) == 0 || strcmp(current->studentInfo.Name, Name) == 0)
        {
            printf("ѧ�ţ�%s\n", current->studentInfo.ID);
            printf("������%s\n", current->studentInfo.Name);
            printf("Ӣ��ɼ���%.2f\n", current->studentInfo.Score1);
            printf("��ѧ�ɼ���%.2f\n", current->studentInfo.Score2);
            printf("���ĳɼ���%.2f\n", current->studentInfo.Score3);
            printf("��˼�ɼ���%.2f\n", current->studentInfo.Score4);
            printf("�ܷ֣�%.2f\n", current->studentInfo.Total);
            printf("ƽ���֣�%.2f\n", current->studentInfo.Avg);
            return;
        }
        current = current->next;
    }
    printf("δ�ҵ���ѧ����\n");
}

// ��������qsort�����ıȽϺ����������������ٸ�~
// int sort_compare(const void *a, const void *b)
// {
//     Node *s1 = (Node *)a;
//     Node *s2 = (Node *)b;

//     printf("��ѡ��������߽���\n");
//     printf("1. ����\n");
//     printf("2. ����\n");
//     int order;
//     scanf("%d", &order);
//     // ������ظ�ֵ�����ʾ��һ��Ԫ��Ӧ�����ڵڶ���Ԫ��ǰ��----������λ�á�
//     // ���������ֵ�����ʾ��һ��Ԫ��Ӧ�����ڵڶ���Ԫ�غ���---����λ�á�
//     switch (order)
//     {
//     case 1:
//         return s1->studentInfo.Total - s2->studentInfo.Total; // �ܷ��������s1->Total>s2->Total���򷵻���������s1,s2����λ�ã����s1->Total<s2->Total���򷵻ظ�������s2,s1����λ�ã����s1->Total=s2->Total���򷵻�0����s1,s2������λ��
//     case 2:
//         return s2->studentInfo.Total - s1->studentInfo.Total; // �ֽܷ��򣬷���case1���෴�����ɡ�
//     default:
//         printf("����������������룡\n");
//         return 0;
//     }
// }

// �������ĸ������������������ڵ������
void swapNodes(Node *a, Node *b)
{
    Info temp = a->studentInfo; // �����ṹ������
    a->studentInfo = b->studentInfo;
    b->studentInfo = temp;
}
// ѧ���ɼ�����
void sortStudent()
{
    if (head == NULL)
    {
        printf("ѧ����ϢΪ�գ���������\n");
        return;
    }

    Node *current = head;
    Node *index;

    // ѡ������
    while (current != NULL)
    {
        index = current->next;
        while (index != NULL)
        {
            if (current->studentInfo.Total > index->studentInfo.Total)
            {
                // �����ڵ�����
                swapNodes(current, index);
            }
            index = index->next;
        }
        current = current->next;
    }
    saveData();
    printf("ѧ���ɼ�����ɹ������浽�ļ���\n");
}

// ������Ʋ������ѧ����Ϣ
void outputFail()
{
    bool found = false;
    if (head == NULL)
    {
        printf("ѧ����ϢΪ�գ�\n");
        return;
    }

    Node *current = head;
    while (current != NULL)
    {
        if (current->studentInfo.Score1 < 60 || current->studentInfo.Score2 < 60 || current->studentInfo.Score3 < 60 || current->studentInfo.Score4 < 60)
        {
            found = true;
            printf("------------------------------------------------------------------------------------------------\n");
            printf("ѧ�ţ�%s\n", current->studentInfo.ID);
            printf("������%s\n", current->studentInfo.Name);
            printf("�ܷ֣�%.2f\n", current->studentInfo.Total);
            printf("ƽ���֣�%.2f\n", current->studentInfo.Avg);
            printf("�������Ŀ��\n");
            if (current->studentInfo.Score1 < 60)
            {
                printf("Ӣ��ɼ���%.2f,������\n", current->studentInfo.Score1);
            }
            if (current->studentInfo.Score2 < 60)
            {
                printf("��ѧ�ɼ���%.2f,������\n", current->studentInfo.Score2);
            }
            if (current->studentInfo.Score3 < 60)
            {
                printf("���ĳɼ���%.2f,������\n", current->studentInfo.Score3);
            }
            if (current->studentInfo.Score4 < 60)
            {
                printf("��˼�ɼ���%.2f,������\n", current->studentInfo.Score4);
            }
        }
        current = current->next; // �ƶ�����һ���ڵ�
    }
    if (!found)
    {
        printf("����ѧ�����п�Ŀ������\n");
    }
}

// ���������߷ֵ�ѧ����Ϣ
void outputMax()
{
    if (head == NULL)
    {
        printf("ѧ����ϢΪ�գ�\n");
        return;
    }

    float max1 = 0, max2 = 0, max3 = 0, max4 = 0;
    char name1[MAX_NAME_LENGTH] = "", name2[MAX_NAME_LENGTH] = "", name3[MAX_NAME_LENGTH] = "", name4[MAX_NAME_LENGTH] = "";
    Node *current = head;

    while (current != NULL)
    {
        if (current->studentInfo.Score1 > max1)
        {
            max1 = current->studentInfo.Score1;
            strcpy(name1, current->studentInfo.Name);
        }
        if (current->studentInfo.Score2 > max2)
        {
            max2 = current->studentInfo.Score2;
            strcpy(name2, current->studentInfo.Name);
        }
        if (current->studentInfo.Score3 > max3)
        {
            max3 = current->studentInfo.Score3;
            strcpy(name3, current->studentInfo.Name);
        }
        if (current->studentInfo.Score4 > max4)
        {
            max4 = current->studentInfo.Score4;
            strcpy(name4, current->studentInfo.Name);
        }
        current = current->next; // �ƶ�����һ���ڵ�
    }
    printf("Ӣ����߷֣�%.2f, ������%s\n", max1, name1);
    printf("��ѧ��߷֣�%.2f, ������%s\n", max2, name2);
    printf("������߷֣�%.2f, ������%s\n", max3, name3);
    printf("��˼��߷֣�%.2f, ������%s\n", max4, name4);
}

// ѡ����
void functionChoose(int choice)
{
    switch (choice)
    {
    case 0:
        printf("�˳�ϵͳ\n");
        exit(0);
        break;
    case 1:
        printf("¼��ѧ����Ϣ\n");
        addStudent();
        break;
    case 2:
        printf("�޸�ѧ����Ϣ\n");
        updateStudent();
        break;
    case 3:
        printf("ɾ��ѧ����Ϣ\n");
        deleteStudent();
        break;
    case 4:
        printf("����ѧ����Ϣ\n");
        insertStudent();
        break;
    case 5:
        printf("��ӡ����ѧ����Ϣ\n");
        printStudent();
        break;
    case 6:
        printf("����ѧ����Ϣ\n");
        searchStudent();
        break;
    case 7:
        printf("ѧ���ɼ�����\n");
        sortStudent();
        break;
    case 8:
        printf("����ѧ����Ϣ�ļ�\n");
        generateDataFile();
        break;
    case 9:
        printf("���ļ��е���ѧ����Ϣ\n");
        loadData();
        break;
    case 10:
        printf("������Ʋ������ѧ����Ϣ\n");
        outputFail();
        break;
    case 11:
        printf("���������߷ֵ�ѧ����Ϣ\n");
        outputMax();
        break;
    default:
        printf("����������������룡\n");
        break;
    }
    printf("ִ����ϣ�\n");
    system("pause");
    system("cls");
}

// ������
int main(void)
{
    while (1)
    {
        int choice = Menu();
        functionChoose(choice);
    }
    return 0;
}
