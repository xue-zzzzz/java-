#include <stdio.h>
#include <string.h>   // 使用 strcpy 需要

#define MAX_STUDENTS 5
#define NAME_LEN 20   // 姓名最大长度

/* ============ 结构体定义 ============ */
struct Student
{
    char name[NAME_LEN];  // 学生姓名
    int  score;           // 学生成绩
};

/* ============ 函数声明 ============ */
void inputStudents(struct Student* stus, int n);
void printStudents(struct Student stus[], int n);
float calculateAverage(struct Student* stus, int n);
struct Student findMax(struct Student* stus, int n);
struct Student findMin(struct Student* stus, int n);
void sortStudents(struct Student* stus, int n);
void printStudentInfo(struct Student* stu);   // 演示结构体指针传参

int main(void)
{
    struct Student stus[MAX_STUDENTS];   // 结构体数组
    int choice;
    int n = MAX_STUDENTS;

    printf("===== 学生成绩管理系统 V2（结构体版）=====\n");

    do {
        printf("\n1. 录入学生信息\n");
        printf("2. 显示学生信息\n");
        printf("3. 统计信息(平均分/最高分/最低分)\n");
        printf("4. 成绩排序(降序)\n");
        printf("0. 退出\n");
        printf("请选择: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            inputStudents(stus, n);
            break;
        case 2:
            printStudents(stus, n);
            break;
        case 3:
            printf("平均分: %.2f\n", calculateAverage(stus, n));
            printStudentInfo(&(findMax(stus, n)));   // 返回结构体
            printStudentInfo(&(findMin(stus, n)));
            break;
        case 4:
            sortStudents(stus, n);
            printf("排序完成!\n");
            printStudents(stus, n);
            break;
        case 0:
            printf("再见!\n");
            break;
        default:
            printf("无效选择，请重新输入!\n");
        }
    } while (choice != 0);

    return 0;
}

/* ============ 函数定义 ============ */

/* 录入信息：结构体指针遍历 */
void inputStudents(struct Student* stus, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("请输入第 %d 个学生的姓名: ", i + 1);
        scanf("%19s", (stus + i)->name);        // -> 访问成员（指针方式）
        printf("请输入第 %d 个学生的成绩: ", i + 1);
        scanf("%d", &(stus + i)->score);
    }
}

/* 显示全部：数组下标方式访问成员（. 运算符） */
void printStudents(struct Student stus[], int n)
{
    int i;
    printf("%-10s %s\n", "姓名", "成绩");
    printf("----------------\n");
    for (i = 0; i < n; i++)
    {
        printf("%-10s %d\n", stus[i].name, stus[i].score);  // . 访问成员
    }
}

/* 平均分 */
float calculateAverage(struct Student* stus, int n)
{
    int i, sum = 0;
    for (i = 0; i < n; i++)
    {
        sum += (stus + i)->score;
    }
    return (float)sum / n;
}

/* 返回最高分的结构体：函数返回类型为 struct */
struct Student findMax(struct Student* stus, int n)
{
    int i, maxIndex = 0;
    for (i = 1; i < n; i++)
    {
        if ((stus + i)->score > (stus + maxIndex)->score)
        {
            maxIndex = i;
        }
    }
    return stus[maxIndex];   // 返回整个结构体副本
}

struct Student findMin(struct Student* stus, int n)
{
    int i, minIndex = 0;
    for (i = 1; i < n; i++)
    {
        if ((stus + i)->score < (stus + minIndex)->score)
        {
            minIndex = i;
        }
    }
    return stus[minIndex];
}

/* 冒泡排序：交换整个结构体 */
void sortStudents(struct Student* stus, int n)
{
    int i, j;
    struct Student temp;   // 结构体变量做交换媒介
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if ((stus + j)->score < (stus + j + 1)->score)
            {
                temp = *(stus + j);            // 结构体整体赋值
                *(stus + j) = *(stus + j + 1);
                *(stus + j + 1) = temp;
            }
        }
    }
}

/* 打印单个学生：结构体指针作为参数，避免拷贝 */
void printStudentInfo(struct Student* stu)
{
    printf("学生: %s, 分数: %d\n", stu->name, stu->score);
}