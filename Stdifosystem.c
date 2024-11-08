#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_STUDENTS 100
#define Data_file "student.txt"

typedef struct
{
    // 数据格式： s114514 syy 90 89 91 90 360 90
    char ID[20];
    char Name[10];
    float Score1, Score2, Score3, Score4; // 英语 数学 语文 计思
    float Total;                          // 总分
    float Avg;                            // 平均分
} _Student;

int student_count = 0;          // 学生数量
_Student Student[MAX_STUDENTS]; // 学生数组

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
    printf("------------------------------------------------------------------------------------------------\n");
    printf("请输入选项：");
    scanf("%d", &choice);
    return choice;
}

void generateDataFile() // 生成文件
{
    FILE *file = fopen(Data_file, "x");
    if (file == NULL)
    {
        printf("文件已创建！\n");
        return;
    }
    fclose(file);
    printf("学生信息文件生成成功！\n");
}

void loadData() // 读取文件
{
    // 打开文件
    FILE *file = fopen(Data_file, "r");
    if (file == NULL)
    {
        printf("文件不存在！请尝试生成学生信息文件！\n");
        return;
    }
    // 读取文件内容
    while (fscanf(file, "%s %s %f %f %f %f %f %f", Student[student_count].ID, Student[student_count].Name, Student[student_count].Score1, Student[student_count].Score2, Student[student_count].Score3, Student[student_count].Score4, Student[student_count].Total, Student[student_count].Avg) != EOF)
    {
        student_count++; // 学生数量计数
    }
    // 关闭文件
    fclose(file);
}

void saveData() // 写入文件
{
    FILE *file = fopen(Data_file, "w"); // w:覆盖写入,如果文件不存在则创建
    if (student_count == 0)
    {
        printf("学生信息为空！\n");
        return;
    }
    for (int i = 0; i < student_count; i++) // 把Student数组中的数据全部写入文件
    {
        fprintf(file, "%s %s %f %f %f %f %f %f\n", Student[i].ID, Student[i].Name, Student[i].Score1, Student[i].Score2, Student[i].Score3, Student[i].Score4, Student[i].Total, Student[i].Avg);
    }
    fclose(file);
}

void addStudent()
{
    if (student_count >= MAX_STUDENTS)
    {
        printf("学生数量已达上限！\n");
        return;
    }
    printf("请输入学生信息：\n");
    printf("请输入学号：");
    scanf("%s", Student[student_count].ID);
    printf("请输入姓名：");
    scanf("%s", Student[student_count].Name);
    printf("请输入英语成绩：");
    scanf("%f", &Student[student_count].Score1);
    printf("请输入数学成绩：");
    scanf("%f", &Student[student_count].Score2);
    printf("请输入语文成绩：");
    scanf("%f", &Student[student_count].Score3);
    printf("请输入计思成绩：");
    scanf("%f", &Student[student_count].Score4);
    // 计算总分
    Student[student_count].Total = Student[student_count].Score1 + Student[student_count].Score2 + Student[student_count].Score3 + Student[student_count].Score4;
    // 计算平均分
    Student[student_count].Avg = Student[student_count].Total / 4;
    student_count++;
    saveData();
    printf("学生信息录入成功！\n");
}

void updateStudent() // 修改学生信息
{
    char ID[20];
    printf("请输入学生学号：");
    scanf("%s", ID);
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(Student[i].ID, ID) == 0) // 对比ID找到学生
        {
            printf("请输入学生信息：\n");
            printf("请输入姓名：");
            scanf("%s", Student[i].Name);
            printf("请输入英语成绩：");
            scanf("%f", &Student[i].Score1);
            printf("请输入数学成绩：");
            scanf("%f", &Student[i].Score2);
            printf("请输入语文成绩：");
            scanf("%f", &Student[i].Score3);
            printf("请输入计思成绩：");
            scanf("%f", &Student[i].Score4);
            // 计算总分
            Student[i].Total = Student[i].Score1 + Student[i].Score2 + Student[i].Score3 + Student[i].Score4;
            // 计算平均分
            Student[i].Avg = Student[i].Total / 4;
            saveData();
            printf("学生信息修改成功！\n");
            return;
        }
    }
}

void deleteStudent() // 删除学生信息
{
    char ID[20];
    printf("请输入学生学号：");
    scanf("%s", ID);
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(Student[i].ID, ID) == 0) // 对比ID找到学生
        {
            for (int j = i; j < student_count - 1; j++)
            {
                Student[j] = Student[j + 1]; // 向前移动进位
            }
            student_count--; // 学生数量减一
            saveData();
            printf("学生信息删除成功！\n");
            return;
        }
    }
    printf("未找到该学生！\n");
}

void insertStudent() // 插入学生信息
{
    printf("功能暂未开放！\n");
}
void searchStudent() // 查找学生信息
{
    char ID[20];
    printf("请输入学生学号：");
    scanf("%s", ID);
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(Student[i].ID, ID) == 0) // 对比ID找到学生
        {
            printf("学号：%s\n", Student[i].ID);
            printf("姓名：%s\n", Student[i].Name);
            printf("英语成绩：%.2f\n", Student[i].Score1);
            printf("数学成绩：%.2f\n", Student[i].Score2);
            printf("语文成绩：%.2f\n", Student[i].Score3);
            printf("计思成绩：%.2f\n", Student[i].Score4);
            printf("总分：%.2f\n", Student[i].Total);
            printf("平均分：%.2f\n", Student[i].Avg);
            return;
        }
    }
    printf("未找到该学生！\n");
}

int sort_compare(const void *a, const void *b) // sortStudent中qsort的比较函数
{
    _Student *s1 = (_Student *)a;
    _Student *s2 = (_Student *)b;
    if (s1->Total < s2->Total)
    {
        return -114514; //<0,则小在前大在后
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
void sortStudent() // 学生总成绩排序
{
    qsort(Student, student_count, sizeof(_Student), sort_compare);
    printf("学生成绩排序成功！\n");
}

void printStudent() // 打印所有学生信息
{
    if (student_count == 0)
    {
        printf("学生信息为空！\n");
        return;
    }
    for (int i = 0; i < student_count; i++)
    {
        printf("------------------------------------------------------------------------------------------------\n");
        printf("学号：%s\n", Student[i].ID);
        printf("姓名：%s\n", Student[i].Name);
        printf("英语成绩：%.2f\n", Student[i].Score1);
        printf("数学成绩：%.2f\n", Student[i].Score2);
        printf("语文成绩：%.2f\n", Student[i].Score3);
        printf("计思成绩：%.2f\n", Student[i].Score4);
        printf("总分：%.2f\n", Student[i].Total);
        printf("平均分：%.2f\n", Student[i].Avg);
    }
    printf("------------------------------------------------------------------------------------------------\n");
}

void outputFail() // 输出某科不及格的学生信息
{
    int count = 0;
    if (student_count == 0)
    {
        printf("学生信息为空！\n");
        return;
    }
    for (int i = 0; i < student_count; i++)
    {
        if (Student[i].Score1 < 60 || Student[i].Score2 < 60 || Student[i].Score3 < 60 || Student[i].Score4 < 60)
        {
            count++;
            printf("------------------------------------------------------------------------------------------------\n");
            printf("学号：%s\n", Student[i].ID);
            printf("姓名：%s\n", Student[i].Name);
            printf("总分：%.2f\n", Student[i].Total);
            printf("平均分：%.2f\n", Student[i].Avg);
            printf("不及格科目：\n");
            if (Student[i].Score1 < 60)
            {
                printf("英语成绩：%.2f,不及格！\n", Student[i].Score1);
            }
            if (Student[i].Score2 < 60)
            {
                printf("数学成绩：%.2f,不及格！\n", Student[i].Score2);
            }
            if (Student[i].Score3 < 60)
            {
                printf("语文成绩：%.2f,不及格！\n", Student[i].Score3);
            }
            if (Student[i].Score4 < 60)
            {
                printf("计思成绩：%.2f,不及格！\n", Student[i].Score4);
            }
        }
    }
    if (count == 0)
    {
        printf("所有学生所有科目均及格！\n");
    }
}

void outputMax() // 输出某科最高分的学生信息
{
    if (student_count == 0)
    {
        printf("学生信息为空！\n");
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
    printf("英语最高分：%.2f, 姓名：%s\n", max1, name1);
    printf("数学最高分：%.2f, 姓名：%s\n", max2, name2);
    printf("语文最高分：%.2f, 姓名：%s\n", max3, name3);
    printf("计思最高分：%.2f, 姓名：%s\n", max4, name4);
}

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
    printf("执行完毕！");
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