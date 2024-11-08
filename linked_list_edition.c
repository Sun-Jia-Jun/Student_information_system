#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ID_LENGTH 20
#define MAX_NAME_LENGTH 10
#define DATA_FILE "student.txt"

// 定义学生信息结构体
typedef struct info
{
    char ID[MAX_ID_LENGTH];
    char Name[MAX_NAME_LENGTH];
    float Score1, Score2, Score3, Score4; // 英语 数学 语文 计思
    float Total;                          // 总分
    float Avg;                            // 平均分
} Info;

// 定义链表节点
typedef struct Node
{
    Info studentInfo;
    struct Node *next;
} Node;

Node *head = NULL; // 定义链表头指针

// 显示菜单
int Menu(void)
{
    int choice;
    printf("------------------------------------------------------------------------------------------------\n");
    printf("欢迎使用学生信息管理系统-by sjj\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("请选择系统功能\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("0. 退出系统\n");
    printf("1. 录入学生信息\n");
    printf("2. 修改学生信息\n");
    printf("3. 删除学生信息\n");
    printf("4. 插入学生信息\n");
    printf("5. 打印学生信息\n");
    printf("6. 查找学生信息\n");
    printf("7. 学生成绩排序\n");
    printf("8. 生成学生信息文件\n");
    printf("9. 从文件中导入学生信息\n");
    printf("10. 输出各科不及格的学生信息\n");
    printf("11. 输出各科最高分的学生信息\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("请输入选项：");
    scanf("%d", &choice);
    return choice;
}

// 计算总分和平均分
void calculateScores(Node *student)
{
    student->studentInfo.Total = student->studentInfo.Score1 + student->studentInfo.Score2 + student->studentInfo.Score3 + student->studentInfo.Score4;
    student->studentInfo.Avg = student->studentInfo.Total / 4;
}

// 生成数据文件
void generateDataFile()
{
    FILE *file = fopen(DATA_FILE, "w");
    if (file == NULL)
    {
        printf("文件生成失败！\n");
        return;
    }
    fclose(file);
    printf("学生信息文件生成成功！\n");
}

// 从文件中加载数据
void loadData()
{
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL)
    {
        printf("文件不存在！请尝试生成学生信息文件！\n");
        return;
    }

    while (!feof(file))
    {
        Node *newStudent = (Node *)malloc(sizeof(Node)); // 为新学生分配内存
        if (fscanf(file, "%s %s %f %f %f %f", newStudent->studentInfo.ID, newStudent->studentInfo.Name,
                   &newStudent->studentInfo.Score1, &newStudent->studentInfo.Score2,
                   &newStudent->studentInfo.Score3, &newStudent->studentInfo.Score4) == 6)
        // 注意：ID,Name都是数组，其名字便是指针，无需&取地址。
        {
            calculateScores(newStudent); // 计算总分和平均分
            newStudent->next = head;     // newStudent下一个节点为现在的head
            head = newStudent;           // 把head指针指向新插入头部的节点
        }
        else
        {
            free(newStudent); // 读取失败则释放内存
        }
    }
    fclose(file);
}

// 写入数据到文件
void saveData()
{
    FILE *file = fopen(DATA_FILE, "w"); // w:覆盖写入,如果文件不存在则创建
    if (head == NULL)
    {
        printf("学生信息为空！\n");
        fclose(file);
        return;
    }
    Node *current = head;   // 使用current指针遍历链表
    while (current != NULL) // 把链表中的所有节点写入文件
    {
        fprintf(file, "%s %s %.2f %.2f %.2f %.2f\n", current->studentInfo.ID, current->studentInfo.Name,
                current->studentInfo.Score1, current->studentInfo.Score2, current->studentInfo.Score3, current->studentInfo.Score4);
        current = current->next;
    }
    fclose(file);
}

// 添加学生信息
void addStudent()
{
    Node *newStudent = (Node *)malloc(sizeof(Node)); // 为新学生分配内存
    if (newStudent == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    printf("请输入学生信息：\n");
    printf("请输入学号：");
    scanf("%s", newStudent->studentInfo.ID);
    printf("请输入姓名：");
    scanf("%s", newStudent->studentInfo.Name);
    printf("请输入英语成绩：");
    scanf("%f", &newStudent->studentInfo.Score1);
    printf("请输入数学成绩：");
    scanf("%f", &newStudent->studentInfo.Score2);
    printf("请输入语文成绩：");
    scanf("%f", &newStudent->studentInfo.Score3);
    printf("请输入计思成绩：");
    scanf("%f", &newStudent->studentInfo.Score4);

    // 计算总分和平均分
    calculateScores(newStudent);

    newStudent->next = head; // 将新节点插入链表头部
    head = newStudent;       // 更新头指针

    saveData(); // 保存数据到文件
    printf("学生信息录入成功！\n");
}

// 修改学生信息
void updateStudent()
{
    char ID[MAX_ID_LENGTH];
    printf("请输入学生学号：");
    scanf("%s", ID);
    Node *current = head;

    while (current != NULL)
    {
        if (strcmp(current->studentInfo.ID, ID) == 0) // 找到对应ID的学生
        {
            printf("请输入学生信息：\n");
            printf("请输入姓名：");
            scanf("%s", current->studentInfo.Name);
            printf("请输入英语成绩：");
            scanf("%f", &current->studentInfo.Score1);
            printf("请输入数学成绩：");
            scanf("%f", &current->studentInfo.Score2);
            printf("请输入语文成绩：");
            scanf("%f", &current->studentInfo.Score3);
            printf("请输入计思成绩：");
            scanf("%f", &current->studentInfo.Score4);

            calculateScores(current); // 计算总分和平均分
            saveData();               // 保存数据到文件
            printf("学生信息修改成功！\n");
            return;
        }
        current = current->next; // 移动到下一个节点
    }
    printf("未找到该学生！\n");
}

// 删除学生信息
void deleteStudent()
{
    char ID[MAX_ID_LENGTH];
    printf("请输入学生学号：");
    scanf("%s", ID);

    Node *current = head;
    Node *previous = NULL; // previous初始化为NULL，用于记录当前节点的前一个节点

    while (current != NULL)
    {
        if (strcmp(current->studentInfo.ID, ID) == 0)
        {
            if (previous == NULL)
            {                         // 判断是否为头节点
                head = current->next; // 将头指针指向下一个节点，完成对头节点的删除
            }
            else
            {                                   // 删除非头节点
                previous->next = current->next; // 从链表中移除当前节点
            }
            free(current); // 释放current节点占用的内存
            saveData();
            printf("学生信息删除成功！\n");
            return;
        }
        previous = current;
        current = current->next; // 移动到下一个节点
    }
    printf("未找到该学生！\n");
}

// 打印所有学生信息
void printStudent()
{
    Node *current = head; // 遍历，同上
    if (current == NULL)
    {
        printf("学生信息为空！\n");
        return;
    }
    while (current != NULL)
    {
        printf("------------------------------------------------------------------------------------------------\n");
        printf("学号：%s\n", current->studentInfo.ID);
        printf("姓名：%s\n", current->studentInfo.Name);
        printf("英语成绩：%.2f\n", current->studentInfo.Score1);
        printf("数学成绩：%.2f\n", current->studentInfo.Score2);
        printf("语文成绩：%.2f\n", current->studentInfo.Score3);
        printf("计思成绩：%.2f\n", current->studentInfo.Score4);
        printf("总分：%.2f\n", current->studentInfo.Total);
        printf("平均分：%.2f\n", current->studentInfo.Avg);
        current = current->next;
    }
    printf("------------------------------------------------------------------------------------------------\n");
}

// 插入学生信息
void insertStudent()
{
    Node *newStudent = (Node *)malloc(sizeof(Node));
    char position[MAX_NAME_LENGTH];
    if (newStudent == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }
    printf("请输入学生信息：\n");
    printf("请输入学号：");
    scanf("%s", newStudent->studentInfo.ID);
    printf("请输入姓名：");
    scanf("%s", newStudent->studentInfo.Name);
    printf("请输入英语成绩：");
    scanf("%f", &newStudent->studentInfo.Score1);
    printf("请输入数学成绩：");
    scanf("%f", &newStudent->studentInfo.Score2);
    printf("请输入语文成绩：");
    scanf("%f", &newStudent->studentInfo.Score3);
    printf("请输入计思成绩：");
    scanf("%f", &newStudent->studentInfo.Score4);
    calculateScores(newStudent);

    printf("请输入学生学号，以便插入到该学生后面的位置：\n");
    scanf("%s", position);

    Node *current = head;
    Node *previous = NULL;
    while (current != NULL)
    {
        if (strcmp(current->studentInfo.ID, position) == 0)
        {
            if (previous == NULL) // 要插入头节点
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
        printf("未找到指定学号的学生，无法插入！\n");
        free(newStudent);
        return;
    }
    saveData();
    printf("学生信息插入成功！\n");
}

// 查找学生信息
void searchStudent()
{
    char ID[MAX_ID_LENGTH] = "";
    char Name[MAX_NAME_LENGTH] = "";
    printf("请选择查找方式：\n");
    printf("1. 学号\n");
    printf("2. 姓名\n");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("请输入学生学号：");
        scanf("%s", ID);
        break;
    case 2:
        printf("请输入学生姓名：");
        scanf("%s", Name);
        break;
    default:
        printf("输入错误，请重新输入！\n");
        return;
    }

    Node *current = head;

    while (current != NULL)
    {
        if (strcmp(current->studentInfo.ID, ID) == 0 || strcmp(current->studentInfo.Name, Name) == 0)
        {
            printf("学号：%s\n", current->studentInfo.ID);
            printf("姓名：%s\n", current->studentInfo.Name);
            printf("英语成绩：%.2f\n", current->studentInfo.Score1);
            printf("数学成绩：%.2f\n", current->studentInfo.Score2);
            printf("语文成绩：%.2f\n", current->studentInfo.Score3);
            printf("计思成绩：%.2f\n", current->studentInfo.Score4);
            printf("总分：%.2f\n", current->studentInfo.Total);
            printf("平均分：%.2f\n", current->studentInfo.Avg);
            return;
        }
        current = current->next;
    }
    printf("未找到该学生！\n");
}

// 被废弃的qsort函数的比较函数，后续看心情再改~
// int sort_compare(const void *a, const void *b)
// {
//     Node *s1 = (Node *)a;
//     Node *s2 = (Node *)b;

//     printf("请选择升序或者降序\n");
//     printf("1. 升序\n");
//     printf("2. 降序\n");
//     int order;
//     scanf("%d", &order);
//     // 如果返回负值，则表示第一个元素应该排在第二个元素前面----不交换位置。
//     // 如果返回正值，则表示第一个元素应该排在第二个元素后面---交换位置。
//     switch (order)
//     {
//     case 1:
//         return s1->studentInfo.Total - s2->studentInfo.Total; // 总分升序：如果s1->Total>s2->Total，则返回正数，则s1,s2交换位置；如果s1->Total<s2->Total，则返回负数，则s2,s1交换位置；如果s1->Total=s2->Total，则返回0，则s1,s2不交换位置
//     case 2:
//         return s2->studentInfo.Total - s1->studentInfo.Total; // 总分降序，返回case1的相反数即可。
//     default:
//         printf("输入错误，请重新输入！\n");
//         return 0;
//     }
// }

// 排序函数的辅助函数，交换两个节点的内容
void swapNodes(Node *a, Node *b)
{
    Info temp = a->studentInfo; // 交换结构体内容
    a->studentInfo = b->studentInfo;
    b->studentInfo = temp;
}
// 学生成绩排序
void sortStudent()
{
    if (head == NULL)
    {
        printf("学生信息为空，无需排序！\n");
        return;
    }

    Node *current = head;
    Node *index;

    // 选择排序
    while (current != NULL)
    {
        index = current->next;
        while (index != NULL)
        {
            if (current->studentInfo.Total > index->studentInfo.Total)
            {
                // 交换节点内容
                swapNodes(current, index);
            }
            index = index->next;
        }
        current = current->next;
    }
    saveData();
    printf("学生成绩排序成功并保存到文件！\n");
}

// 输出各科不及格的学生信息
void outputFail()
{
    bool found = false;
    if (head == NULL)
    {
        printf("学生信息为空！\n");
        return;
    }

    Node *current = head;
    while (current != NULL)
    {
        if (current->studentInfo.Score1 < 60 || current->studentInfo.Score2 < 60 || current->studentInfo.Score3 < 60 || current->studentInfo.Score4 < 60)
        {
            found = true;
            printf("------------------------------------------------------------------------------------------------\n");
            printf("学号：%s\n", current->studentInfo.ID);
            printf("姓名：%s\n", current->studentInfo.Name);
            printf("总分：%.2f\n", current->studentInfo.Total);
            printf("平均分：%.2f\n", current->studentInfo.Avg);
            printf("不及格科目：\n");
            if (current->studentInfo.Score1 < 60)
            {
                printf("英语成绩：%.2f,不及格！\n", current->studentInfo.Score1);
            }
            if (current->studentInfo.Score2 < 60)
            {
                printf("数学成绩：%.2f,不及格！\n", current->studentInfo.Score2);
            }
            if (current->studentInfo.Score3 < 60)
            {
                printf("语文成绩：%.2f,不及格！\n", current->studentInfo.Score3);
            }
            if (current->studentInfo.Score4 < 60)
            {
                printf("计思成绩：%.2f,不及格！\n", current->studentInfo.Score4);
            }
        }
        current = current->next; // 移动到下一个节点
    }
    if (!found)
    {
        printf("所有学生所有科目均及格！\n");
    }
}

// 输出各科最高分的学生信息
void outputMax()
{
    if (head == NULL)
    {
        printf("学生信息为空！\n");
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
        current = current->next; // 移动到下一个节点
    }
    printf("英语最高分：%.2f, 姓名：%s\n", max1, name1);
    printf("数学最高分：%.2f, 姓名：%s\n", max2, name2);
    printf("语文最高分：%.2f, 姓名：%s\n", max3, name3);
    printf("计思最高分：%.2f, 姓名：%s\n", max4, name4);
}

// 选择功能
void functionChoose(int choice)
{
    switch (choice)
    {
    case 0:
        printf("退出系统\n");
        exit(0);
        break;
    case 1:
        printf("录入学生信息\n");
        addStudent();
        break;
    case 2:
        printf("修改学生信息\n");
        updateStudent();
        break;
    case 3:
        printf("删除学生信息\n");
        deleteStudent();
        break;
    case 4:
        printf("插入学生信息\n");
        insertStudent();
        break;
    case 5:
        printf("打印所有学生信息\n");
        printStudent();
        break;
    case 6:
        printf("查找学生信息\n");
        searchStudent();
        break;
    case 7:
        printf("学生成绩排序\n");
        sortStudent();
        break;
    case 8:
        printf("生成学生信息文件\n");
        generateDataFile();
        break;
    case 9:
        printf("从文件中导入学生信息\n");
        loadData();
        break;
    case 10:
        printf("输出各科不及格的学生信息\n");
        outputFail();
        break;
    case 11:
        printf("输出各科最高分的学生信息\n");
        outputMax();
        break;
    default:
        printf("输入错误，请重新输入！\n");
        break;
    }
    printf("执行完毕！\n");
    system("pause");
    system("cls");
}

// 主函数
int main(void)
{
    while (1)
    {
        int choice = Menu();
        functionChoose(choice);
    }
    return 0;
}
