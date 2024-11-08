#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_STUDENTS 100
#define Data_file "student.txt"

typedef struct
{
    // ���ݸ�ʽ�� s114514 syy 90 89 91 90 360 90
    char ID[20];
    char Name[10];
    float Score1, Score2, Score3, Score4; // Ӣ�� ��ѧ ���� ��˼
    float Total;                          // �ܷ�
    float Avg;                            // ƽ����
} _Student;

int student_count = 0;          // ѧ������
_Student Student[MAX_STUDENTS]; // ѧ������

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
    printf("------------------------------------------------------------------------------------------------\n");
    printf("������ѡ�");
    scanf("%d", &choice);
    return choice;
}

void generateDataFile() // �����ļ�
{
    FILE *file = fopen(Data_file, "x");
    if (file == NULL)
    {
        printf("�ļ��Ѵ�����\n");
        return;
    }
    fclose(file);
    printf("ѧ����Ϣ�ļ����ɳɹ���\n");
}

void loadData() // ��ȡ�ļ�
{
    // ���ļ�
    FILE *file = fopen(Data_file, "r");
    if (file == NULL)
    {
        printf("�ļ������ڣ��볢������ѧ����Ϣ�ļ���\n");
        return;
    }
    // ��ȡ�ļ�����
    while (fscanf(file, "%s %s %f %f %f %f %f %f", Student[student_count].ID, Student[student_count].Name, Student[student_count].Score1, Student[student_count].Score2, Student[student_count].Score3, Student[student_count].Score4, Student[student_count].Total, Student[student_count].Avg) != EOF)
    {
        student_count++; // ѧ����������
    }
    // �ر��ļ�
    fclose(file);
}

void saveData() // д���ļ�
{
    FILE *file = fopen(Data_file, "w"); // w:����д��,����ļ��������򴴽�
    if (student_count == 0)
    {
        printf("ѧ����ϢΪ�գ�\n");
        return;
    }
    for (int i = 0; i < student_count; i++) // ��Student�����е�����ȫ��д���ļ�
    {
        fprintf(file, "%s %s %f %f %f %f %f %f\n", Student[i].ID, Student[i].Name, Student[i].Score1, Student[i].Score2, Student[i].Score3, Student[i].Score4, Student[i].Total, Student[i].Avg);
    }
    fclose(file);
}

void addStudent()
{
    if (student_count >= MAX_STUDENTS)
    {
        printf("ѧ�������Ѵ����ޣ�\n");
        return;
    }
    printf("������ѧ����Ϣ��\n");
    printf("������ѧ�ţ�");
    scanf("%s", Student[student_count].ID);
    printf("������������");
    scanf("%s", Student[student_count].Name);
    printf("������Ӣ��ɼ���");
    scanf("%f", &Student[student_count].Score1);
    printf("��������ѧ�ɼ���");
    scanf("%f", &Student[student_count].Score2);
    printf("���������ĳɼ���");
    scanf("%f", &Student[student_count].Score3);
    printf("�������˼�ɼ���");
    scanf("%f", &Student[student_count].Score4);
    // �����ܷ�
    Student[student_count].Total = Student[student_count].Score1 + Student[student_count].Score2 + Student[student_count].Score3 + Student[student_count].Score4;
    // ����ƽ����
    Student[student_count].Avg = Student[student_count].Total / 4;
    student_count++;
    saveData();
    printf("ѧ����Ϣ¼��ɹ���\n");
}

void updateStudent() // �޸�ѧ����Ϣ
{
    char ID[20];
    printf("������ѧ��ѧ�ţ�");
    scanf("%s", ID);
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(Student[i].ID, ID) == 0) // �Ա�ID�ҵ�ѧ��
        {
            printf("������ѧ����Ϣ��\n");
            printf("������������");
            scanf("%s", Student[i].Name);
            printf("������Ӣ��ɼ���");
            scanf("%f", &Student[i].Score1);
            printf("��������ѧ�ɼ���");
            scanf("%f", &Student[i].Score2);
            printf("���������ĳɼ���");
            scanf("%f", &Student[i].Score3);
            printf("�������˼�ɼ���");
            scanf("%f", &Student[i].Score4);
            // �����ܷ�
            Student[i].Total = Student[i].Score1 + Student[i].Score2 + Student[i].Score3 + Student[i].Score4;
            // ����ƽ����
            Student[i].Avg = Student[i].Total / 4;
            saveData();
            printf("ѧ����Ϣ�޸ĳɹ���\n");
            return;
        }
    }
}

void deleteStudent() // ɾ��ѧ����Ϣ
{
    char ID[20];
    printf("������ѧ��ѧ�ţ�");
    scanf("%s", ID);
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(Student[i].ID, ID) == 0) // �Ա�ID�ҵ�ѧ��
        {
            for (int j = i; j < student_count - 1; j++)
            {
                Student[j] = Student[j + 1]; // ��ǰ�ƶ���λ
            }
            student_count--; // ѧ��������һ
            saveData();
            printf("ѧ����Ϣɾ���ɹ���\n");
            return;
        }
    }
    printf("δ�ҵ���ѧ����\n");
}

void insertStudent() // ����ѧ����Ϣ
{
    printf("������δ���ţ�\n");
}
void searchStudent() // ����ѧ����Ϣ
{
    char ID[20];
    printf("������ѧ��ѧ�ţ�");
    scanf("%s", ID);
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(Student[i].ID, ID) == 0) // �Ա�ID�ҵ�ѧ��
        {
            printf("ѧ�ţ�%s\n", Student[i].ID);
            printf("������%s\n", Student[i].Name);
            printf("Ӣ��ɼ���%.2f\n", Student[i].Score1);
            printf("��ѧ�ɼ���%.2f\n", Student[i].Score2);
            printf("���ĳɼ���%.2f\n", Student[i].Score3);
            printf("��˼�ɼ���%.2f\n", Student[i].Score4);
            printf("�ܷ֣�%.2f\n", Student[i].Total);
            printf("ƽ���֣�%.2f\n", Student[i].Avg);
            return;
        }
    }
    printf("δ�ҵ���ѧ����\n");
}

int sort_compare(const void *a, const void *b) // sortStudent��qsort�ıȽϺ���
{
    _Student *s1 = (_Student *)a;
    _Student *s2 = (_Student *)b;
    if (s1->Total < s2->Total)
    {
        return -114514; //<0,��С��ǰ���ں�
    }
    else if (s1->Total > s2->Total)
    {
        return 114514;
    }
    else
    {
        return 0;
    }
}
void sortStudent() // ѧ���ܳɼ�����
{
    qsort(Student, student_count, sizeof(_Student), sort_compare);
    printf("ѧ���ɼ�����ɹ���\n");
}

void printStudent() // ��ӡ����ѧ����Ϣ
{
    if (student_count == 0)
    {
        printf("ѧ����ϢΪ�գ�\n");
        return;
    }
    for (int i = 0; i < student_count; i++)
    {
        printf("------------------------------------------------------------------------------------------------\n");
        printf("ѧ�ţ�%s\n", Student[i].ID);
        printf("������%s\n", Student[i].Name);
        printf("Ӣ��ɼ���%.2f\n", Student[i].Score1);
        printf("��ѧ�ɼ���%.2f\n", Student[i].Score2);
        printf("���ĳɼ���%.2f\n", Student[i].Score3);
        printf("��˼�ɼ���%.2f\n", Student[i].Score4);
        printf("�ܷ֣�%.2f\n", Student[i].Total);
        printf("ƽ���֣�%.2f\n", Student[i].Avg);
    }
    printf("------------------------------------------------------------------------------------------------\n");
}

void outputFail() // ���ĳ�Ʋ������ѧ����Ϣ
{
    int count = 0;
    if (student_count == 0)
    {
        printf("ѧ����ϢΪ�գ�\n");
        return;
    }
    for (int i = 0; i < student_count; i++)
    {
        if (Student[i].Score1 < 60 || Student[i].Score2 < 60 || Student[i].Score3 < 60 || Student[i].Score4 < 60)
        {
            count++;
            printf("------------------------------------------------------------------------------------------------\n");
            printf("ѧ�ţ�%s\n", Student[i].ID);
            printf("������%s\n", Student[i].Name);
            printf("�ܷ֣�%.2f\n", Student[i].Total);
            printf("ƽ���֣�%.2f\n", Student[i].Avg);
            printf("�������Ŀ��\n");
            if (Student[i].Score1 < 60)
            {
                printf("Ӣ��ɼ���%.2f,������\n", Student[i].Score1);
            }
            if (Student[i].Score2 < 60)
            {
                printf("��ѧ�ɼ���%.2f,������\n", Student[i].Score2);
            }
            if (Student[i].Score3 < 60)
            {
                printf("���ĳɼ���%.2f,������\n", Student[i].Score3);
            }
            if (Student[i].Score4 < 60)
            {
                printf("��˼�ɼ���%.2f,������\n", Student[i].Score4);
            }
        }
    }
    if (count == 0)
    {
        printf("����ѧ�����п�Ŀ������\n");
    }
}

void outputMax() // ���ĳ����߷ֵ�ѧ����Ϣ
{
    if (student_count == 0)
    {
        printf("ѧ����ϢΪ�գ�\n");
        return;
    }
    float max1 = 0, max2 = 0, max3 = 0, max4 = 0;
    char name1[10] = "", name2[10] = "", name3[10] = "", name4[10] = "";
    for (int i = 0; i < student_count; i++)
    {
        if (Student[i].Score1 > max1)
        {
            max1 = Student[i].Score1;
            strcpy(name1, Student[i].Name);
        }
        if (Student[i].Score2 > max2)
        {
            max2 = Student[i].Score2;
            strcpy(name2, Student[i].Name);
        }
        if (Student[i].Score3 > max3)
        {
            max3 = Student[i].Score3;
            strcpy(name3, Student[i].Name);
        }
        if (Student[i].Score4 > max4)
        {
            max4 = Student[i].Score4;
            strcpy(name4, Student[i].Name);
        }
    }
    printf("Ӣ����߷֣�%.2f, ������%s\n", max1, name1);
    printf("��ѧ��߷֣�%.2f, ������%s\n", max2, name2);
    printf("������߷֣�%.2f, ������%s\n", max3, name3);
    printf("��˼��߷֣�%.2f, ������%s\n", max4, name4);
}

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
    printf("ִ����ϣ�");
    system("pause");
    system("cls");
}

int main(void)
{
    while (1)
    {
        int choice = Menu();
        functionChoose(choice);
    }
    return 0;
}