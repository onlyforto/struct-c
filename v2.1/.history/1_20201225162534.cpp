#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#define MAXSIZE 100
struct INF
{
    int tes;
    char name[MAXSIZE];
    char id[MAXSIZE];
    char passwd[MAXSIZE];
    char booknum[MAXSIZE][MAXSIZE];
    int bookn; //记录借的书的种数
    int booknu[MAXSIZE];
    int y[MAXSIZE];
    int m[MAXSIZE];
    int d[MAXSIZE];
};
typedef struct Node
{
    char num[MAXSIZE];
    char name[MAXSIZE];
    char author[MAXSIZE];
    int bookflag;
    int now;
    int all;

    struct Node *next;
} Node, *LinkList;
int logout = 0;
int fl = 0;
int main();
INF inf[MAXSIZE];
// typedef struct delete
// {
// 	char num[MAXSIZE];
//     char name[MAXSIZE];
//     char author[MAXSIZE];
//     int now;
//     int all;
// }deleted;
// void init(LinkList *);
// void in(LinkList *);
// void switchl(LinkList *);
// void switchr(LinkList *);
// int lend(LinkList ,char,int );
// int lend1(LinkList ,char ,int );
// int lend2(LinkList ,char ,int );
// int returnb(LinkList ,char ,int );
// int returnb1(LinkList ,char ,int );
// int returnb2(LinkList ,char ,int );
void color(short x) //改变字体颜色
{
    if (x >= 0 && x <= 15)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
int init(LinkList &L) //书籍信息初始化
{
    LinkList L0;
    L = (LinkList)malloc(sizeof(Node));
    L0 = (LinkList)malloc(sizeof(Node));
    L0->bookflag = 0;
    L->next = NULL;
    L0->next = L->next;
    L->next = L0;
    return 1;
}
void initinf() //添加5个用户
{
    strcpy(inf[0].id, "1"); //张三为超级管理员，可以添加书籍
    strcpy(inf[0].name, "张三");
    strcpy(inf[0].passwd, "1");
    strcpy(inf[1].id, "2");
    strcpy(inf[1].name, "李四");
    strcpy(inf[1].passwd, "2");
    strcpy(inf[2].id, "3");
    strcpy(inf[2].name, "王五");
    strcpy(inf[2].passwd, "3");
    strcpy(inf[3].id, "4");
    strcpy(inf[3].name, "赵六");
    strcpy(inf[3].passwd, "4");
    strcpy(inf[4].id, "5");
    strcpy(inf[4].name, "孙七");
    strcpy(inf[4].passwd, "5");
    inf[0].tes = 1; //查看是否有用户
    inf[0].bookn = 0;
    inf[1].bookn = 0;
    inf[2].bookn = 0;
    inf[3].bookn = 0;
    inf[4].bookn = 0;
    for (int s = 0; s < MAXSIZE; s++)
    {
        inf[0].booknu[s] = 0;
        inf[1].booknu[s] = 0;
        inf[2].booknu[s] = 0;
        inf[3].booknu[s] = 0;
        inf[4].booknu[s] = 0;
    }
}
int in(LinkList &L) //录入书籍信息
{
    LinkList s, pre;
    pre = L;
    int c3;
    int flag = 1;
    while (flag)
    {
        s = (LinkList)malloc(sizeof(Node));
        fflush(stdin);
        printf("请输入书籍书号:");
        scanf("%s", &s->num);
        fflush(stdin);
        fl++;
        s->bookflag = fl;
        while (pre->next != NULL && strcmp(pre->num, s->num))
        {
            pre = pre->next;
        }
        if (!strcmp(pre->num, s->num))
        {
            printf("已存在此书，请直接输入数量:");
            scanf("%d", &s->now);
            fflush(stdin);
            pre->now += s->now;
            pre->all = pre->now;
            printf("是否继续录入书籍，若继续录入书籍请回车，否则输入任意字符回车：");
            if (getchar() != '\n')
            {
                fflush(stdin);
                flag = 0;
            }
            else
            {
                flag = 1;
            }
            continue;
        }
        printf("请输入书籍书名:");
        scanf("%s", &s->name);
        fflush(stdin);
        printf("请输入书籍作者:");
        scanf("%s", &s->author);
        fflush(stdin);
        printf("请输入数量:");
        scanf("%d", &s->now);
        fflush(stdin);
        printf("是否继续录入书籍，若继续录入书籍请回车，否则输入任意字符回车：");

        // s->num=c;
        // s->name=c1;
        // s->author=c2;
        s->all = s->now;
        s->next = L->next;
        L->next = s;
        if (getchar() != '\n')
        {
            fflush(stdin);
            flag = 0;
        }
    }
    return 1;
}
int show(LinkList &L) //显示图书馆中所有书籍
{
    LinkList pre;
    int k = 0;
    pre = L;
    int a[MAXSIZE];
    printf("现有的的书籍信息如下:\n");
    printf("书号\t书名\t作者\t剩余量\t库存量\n");
    while (pre->next != NULL)
    {
        pre = pre->next;
        printf(" %s\t %s\t %s\t  %d\t  %d\n", pre->num, pre->name, pre->author, pre->now, pre->all);
        k++;
    }
    if (k == 0)
    {
        printf("图书馆里没有书，请采编书籍入库\n");
    }
    return 1;
}
int bookdataw(LinkList &L) //存储图书馆中所有书籍数据
{
    LinkList pre;
    int flag3 = 0;
    pre = L;
    remove("bookdata.txt");
    FILE *fp;
    // char fileName[MAXSIZE];
    // strcpy(fileName, ".\book.\bookdata.txt");
    fp = fopen("bookdata.txt", "w");
    while (pre->next != NULL)
    {
        if (flag3 != 0)
        {
            fprintf(fp, "\n");
        }
        pre = pre->next;
        fprintf(fp, "%d %s %s %s %d %d", pre->bookflag, pre->num, pre->name, pre->author, pre->now, pre->all);
        flag3++;
    }
    fclose(fp);
    return 1;
}
int bookdatar(LinkList &L) //读取存储图书馆中所有书籍的数据
{
    LinkList s, pre;
    pre = L;
    init(L);
    FILE *fp;
    // char fileName[MAXSIZE];
    // strcpy(fileName, ".\book.\bookdata.txt");
    fp = fopen("bookdata.txt", "r");
    if (fp == NULL)
    {
        return 0;
    }
    rewind(fp);
    while (!feof(fp))
    {
        s = (LinkList)malloc(sizeof(Node));
        fscanf(fp, "%d%s%s%s%d%d", &s->bookflag, s->num, s->name, s->author, &s->now, &s->all);
        s->next = L->next;
        L->next = s;
    }
    fclose(fp);
    return 1;
}
int userdataw(LinkList &L, int r3) //存储用户借阅所有书籍数据
{
    LinkList pre;
    pre = L;
    FILE *fp;
    char fileName[MAXSIZE];
    char str[MAXSIZE];
    itoa(r3, str, 10);
    strcpy(fileName, "user");
    strcat(fileName, str);
    strcat(fileName, ".txt");
    remove(fileName);
    fp = fopen(fileName, "w");
    while (pre != NULL)
    {
        while (pre->next != NULL && strcmp(pre->num, inf[r3].booknum[inf[r3].bookn]))
        {
            pre = pre->next;
        }
        if (!strcmp(pre->num, inf[r3].booknum[inf[r3].bookn]))
        {
            fprintf(fp, "%d %s %d %d %d %d\n", inf[r3].bookn, inf[r3].booknum[inf[r3].bookn], inf[r3].booknu[inf[r3].bookn], inf[r3].y[inf[r3].bookn], inf[r3].m[inf[r3].bookn], inf[r3].d[inf[r3].bookn]);
        }

        pre = pre->next;
    }
    fclose(fp);
    return 1;
}
int userdatar(int r3) //读取用户借阅所有书籍数据
{
    initinf();
    FILE *fp;
    char fileName[MAXSIZE];
    char str[MAXSIZE];
    itoa(r3, str, 10);
    strcpy(fileName, "user");
    strcat(fileName, str);
    strcat(fileName, ".txt");
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        return 0;
    }
    while (!feof(fp))
    {
        fscanf(fp, "%d%s%d%d%d%d", &inf[r3].bookn, inf[r3].booknum[inf[r3].bookn], &inf[r3].booknu[inf[r3].bookn], &inf[r3].y[inf[r3].bookn], &inf[r3].m[inf[r3].bookn], &inf[r3].d[inf[r3].bookn]);
    }
    fclose(fp);
    return 1;
}
int lend(LinkList &L, char nu[MAXSIZE], int i, int r4) //通过书号借阅书籍
{
    time_t timep;
    struct tm *p;
    time(&timep);
    timep = time(NULL) + 31 * 24 * 60 * 60;
    p = gmtime(&timep);
    LinkList pre;
    int k;
    pre = L;
    k = 0;
    while (pre->next != NULL && strcmp(pre->num, nu))
    {
        pre = pre->next;
    }
    if (strcmp(pre->num, nu))
    {
        color(4);
        printf("不存在此书!\n");
        color(16);
        return 0;
    }
    if (pre->now == 0)
    {
        printf("书号\t书名\t作者\t剩余量\t库存量\n");
        printf("%s\t%s\t%s\t%d\t%d\n", pre->num, pre->name, pre->author, pre->now, pre->all);
        color(4);
        printf("此书已被借完！\n");
        color(16);
        return 0;
    }
    if (pre->now < i)
    {
        printf("书号\t书名\t作者\t剩余量\t库存量\n");
        printf("%s\t%s\t%s\t%d\t%d\n", pre->num, pre->name, pre->author, pre->now, pre->all);
        color(4);
        printf("此书库存不足%d本！\n", i);
        color(16);
        return 0;
    }
    pre->now -= i;
    printf("借阅的书籍信息如下:\n");
    printf("书号\t书名\t作者\t借阅数量\t剩余量\t归还时间\n");
    printf(" %s\t %s\t %s\t  %d\t\t%d\t%d年%d月%d日\n", pre->num, pre->name, pre->author, i, pre->now, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday);
    printf("成功借出此书!\n");
    inf[r4].bookn = pre->bookflag;
    inf[r4].y[inf[r4].bookn] = 1900 + p->tm_year;
    inf[r4].m[inf[r4].bookn] = 1 + p->tm_mon;
    inf[r4].d[inf[r4].bookn] = p->tm_mday;
    strcpy(inf[r4].booknum[inf[r4].bookn], pre->num);
    inf[r4].booknu[inf[r4].bookn] += i;
    return 1;
}
int lend1(LinkList &L, char nam[MAXSIZE], int i, int r4) //通过书名借出书籍
{
    time_t timep;
    struct tm *p;
    time(&timep);
    timep = time(NULL) + 31 * 24 * 60 * 60;
    p = gmtime(&timep);
    LinkList pre;
    int k;
    pre = L;
    k = 0;
    while (pre->next != NULL && strcmp(pre->name, nam))
    {
        pre = pre->next;
    }
    if (strcmp(pre->num, nam))
    {
        color(4);
        printf("不存在此书!\n");
        color(16);
        return 0;
    }
    if (pre->now == 0)
    {
        printf("书号\t书名\t作者\t剩余量\t库存量\n");
        printf("%s\t%s\t%s\t%d\t%d\n", pre->num, pre->name, pre->author, pre->now, pre->all);
        color(4);
        printf("此书已被借完！\n");
        color(16);
        return 0;
    }
    if (pre->now < i)
    {
        printf("书号\t书名\t作者\t剩余量\t库存量\n");
        printf("%s\t%s\t%s\t%d\t%d\n", pre->num, pre->name, pre->author, pre->now, pre->all);
        color(4);
        printf("此书库存不足%d本！\n", i);
        color(16);
        return 0;
    }
    pre->now -= i;
    printf("借阅的书籍信息如下:\n");
    printf("书号\t书名\t作者\t借阅数量\t剩余量\t归还时间\n");
    printf(" %s\t %s\t %s\t  %d\t\t%d\t%d年%d月%d日\n", pre->num, pre->name, pre->author, i, pre->now, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday);
    printf("成功借出此书!\n");
    inf[r4].bookn = pre->bookflag;
    inf[r4].y[inf[r4].bookn] = 1900 + p->tm_year;
    inf[r4].m[inf[r4].bookn] = 1 + p->tm_mon;
    inf[r4].d[inf[r4].bookn] = p->tm_mday;
    strcpy(inf[r4].booknum[inf[r4].bookn], pre->num);
    inf[r4].booknu[inf[r4].bookn] += i;
    return 1;
}
// int lend2(LinkList L,char aut[MAXSIZE],int i) //通过作者借出书籍
// {
//     LinkList pre,pre2;
//     int k=0;
// 	int b,g=0;
// 	pre=L;
//     pre2=L;

//     int a[MAXSIZE];
//     while(pre->next!=NULL)
//     {
//         while(!strcmp(pre->author,aut))
//         {
//             pre=pre->next;
//             ++k;
//         }
//         a[g]=k;
//         g++;
//         if(!(pre->next)&&g==0)
//         {
//           printf("不存在此书!");
//             return 0;
//         }
//         if(g==1)
//         {
//             printf("序号\t书号\t书名\t作者\t剩余量\t库存量\n");
//         }
//         if(pre->now==0)
//          {
//             g--;
//         }
//         printf("%d\t%s\t%s\t%s\t%d\t%d\n",g,pre->num,pre->name,pre->author,pre->now,pre->all);
//         pre=pre->next;
//     }
//     g=0;
// 	printf("请选择你要借阅的书籍:");
//     scanf("%d",&b);
//     while(g<a[b-1])
//         {
//             pre2=pre2->next;
//             g++;
//         }
// 	pre2->now-=i;
// 	printf("借阅的书籍信息如下:\n");
//     printf("书号\t书名\t作者\t借阅数量\t剩余量\n");
//     printf("%s\t%s\t%s\t%d\t%d\n",pre2->num,pre2->name,pre2->author,i,pre2->now);
// 	printf("成功借出此书!");
// 	return 1;

// }

int returnb(LinkList &L, char nu[MAXSIZE], int i, int r4) //通过书号归还书籍
{
    LinkList pre;
    int k;
    pre = L;
    k = 0;

    while (pre->next != NULL && strcmp(pre->num, nu))
    {
        pre = pre->next;
    }
    if (strcmp(pre->num, nu))
    {
        color(4);
        printf("不存在此书!\n");
        color(16);
        return 0;
    }
    if (pre->all < i + pre->now)
    {
        printf("书号\t书名\t作者\t剩余量\t库存量\n");
        printf("%s\t%s\t%s\t", pre->num, pre->name, pre->author);
        color(4);
        printf("%d\t", pre->now + i);
        color(16);
        printf("%d\n", pre->all);
        color(4);
        printf("归还的数量超出应有库存量，请检查是否确认无误！\n");
        color(16);
        return 0;
    }
    pre->now += i;
    printf("归还的书籍信息如下:\n");
    printf("书号\t书名\t作者\t归还数量\t剩余量\n");
    printf(" %s\t %s\t %s\t  %d\t\t%d\n", pre->num, pre->name, pre->author, i, pre->now);
    printf("成功归还此书!\n");
    inf[r4].bookn = pre->bookflag;
    strcpy(inf[r4].booknum[inf[r4].bookn], "");
    inf[r4].booknu[inf[r4].bookn] -= i;
    inf[r4].bookn--;
    return 1;
}
int returnb1(LinkList &L, char nam[MAXSIZE], int i, int r4) //通过书名归还书籍
{
    LinkList pre;
    int k;
    pre = L;
    k = 0;

    while (pre->next != NULL && strcmp(pre->name, nam))
    {
        pre = pre->next;
    }
    if (strcmp(pre->num, nam))
    {
        color(4);
        printf("不存在此书!\n");
        color(16);
        return 0;
    }
    if (pre->all < i + pre->now)
    {
        printf("书号\t书名\t作者\t剩余量\t库存量\n");
        printf("%s\t%s\t%s\t", pre->num, pre->name, pre->author);
        color(4);
        printf("%d\t", pre->now + i);
        color(16);
        printf("%d\n", pre->all);
        color(4);
        printf("归还的数量超出应有库存量，请检查是否确认无误！\n");
        color(16);
        return 0;
    }
    pre->now += i;
    printf("归还的书籍信息如下:\n");
    printf("书号\t书名\t作者\t归还数量\t剩余量\n");
    printf("%s\t%s\t%s\t%d\t%d\n", pre->num, pre->name, pre->author, i, pre->now);
    printf("成功归还此书!\n");
    inf[r4].bookn = pre->bookflag;
    strcpy(inf[r4].booknum[inf[r4].bookn], "");
    inf[r4].booknu[inf[r4].bookn] -= i;
    inf[r4].bookn--;
    return 1;
}
// int returnb2(LinkList &L,char aut[MAXSIZE],int i) //通过作者归还书籍
// {
//     LinkList pre,pre2;
// 	int k,b,g;
// 	pre=L;
//     pre2=L;
// 	k=0;
//     g=0;
//     int a[MAXSIZE];
//     printf("序号\t书号\t书名\t作者\t剩余量\t库存量\n");
//     while(pre->next!=NULL)
//     {
//         while(pre->next!=NULL&&strcmp(pre->author,aut))
//         {
//             pre=pre->next;
//             k++;
//         }
//         if(!(pre->next))
//         {
//             printf("不存在此书!");
//             return 0;
//         }

//         a[i]=k;
//         g++;
//         printf("%d\t%s\t%s\t%s\t%d\t%d\n",k,pre->num,pre->name,pre->author,pre->now,pre->all);
//     }
//     g=0;
// 	printf("请输入你要归还的书籍：");
//     scanf("%d",&b);
//     while(g<a[b])
//         {
//             pre2=pre2->next;
//             g++;
//         }

// 	pre2->now+=i;
// 	printf("归还的书籍信息如下:\n");
//     printf("书号\t书名\t作者\t归还数量\t剩余量\n");
//     printf("%s\t%s\t%s\t%d\t%d\n",pre->num,pre->name,pre->author,i,pre->now);
// 	printf("成功归还此书!");
// 	return 1;
// }
int own(LinkList &L, int r3) //查看自己借的书籍以及归还时间
{
    LinkList pre;
    int k;
    pre = L;
    k = 0;
    while (pre != NULL)
    {
        inf[r3].bookn = pre->bookflag;
        while (pre->next != NULL && strcmp(pre->num, inf[r3].booknum[inf[r3].bookn]))
        {
            pre = pre->next;
            inf[r3].bookn = pre->bookflag;
            ++k;
        }

        if (!(pre))
        {
            printf("你还没有借书！");
            return 0;
        }
        if (k == 1)
        {
            printf("序号\t书号\t书名\t作者\t借阅数量\t图书馆剩余量\t归还日期\n");
        }
        if (!strcmp(pre->num, inf[r3].booknum[inf[r3].bookn]))
        {
            printf(" %d\t %s\t %s\t %s\t  %d\t\t       %d\t%d年%d月%d日\n", k, pre->num, pre->name, pre->author, inf[r3].booknu[inf[r3].bookn], pre->now, inf[r3].y[inf[r3].bookn], inf[r3].m[inf[r3].bookn], inf[r3].d[inf[r3].bookn]);
        }

        pre = pre->next;
    }
    return 1;
}
void switchl(LinkList &M, int r3) //选择借阅书籍方式
{
    int flag = 0;
    do
    {
        printf("借阅方式\n"
               "1.书号\n"
               "2.书名\n");
        int x, i, ii = 0; //ii为借书数量限定的标志
        char b[MAXSIZE];
        printf("请选择借阅方式:");
        scanf("%d", &x);
        fflush(stdin);
        switch (x)
        {
        case 1:
            printf("请输入借阅书籍书号:");
            gets(b);
            fflush(stdin);
            do
            {
                printf("请输入借阅数量:");
                scanf("%d", &i);
                fflush(stdin);
                if (i > 2)
                {
                    printf("一本书最多只能借2本！！");
                    ii = 1;
                }
                else
                    ii = 0;
            } while (ii);
            lend(M, b, i, r3);
            flag = 0;
            break;
        case 2:
            printf("请输入借阅书籍书名:");
            gets(b);
            fflush(stdin);
            do
            {
                printf("请输入借阅数量:");
                scanf("%d", &i);
                fflush(stdin);
                if (i > 2)
                {
                    printf("一本书最多只能借2本！！");
                    ii = 1;
                }
                else
                    ii = 0;
            } while (ii);
            lend1(M, b, i, r3);
            flag = 0;
            break;
        // case 3:  printf("请输入借阅书籍作者:");
        //         gets(b);
        //         fflush(stdin);
        //         printf("请输入借阅数量:");
        //         scanf("%d",&i);
        //         fflush(stdin);
        //         lend2(M,b,i);
        //         break;
        default:
            system("cls");
            color(4);
            printf("不存在此操作，请重新选择！！！\n");
            color(16);
            flag = 1;
            break;
        }
    } while (flag);
}
void switchr(LinkList &M, int r3) //选择归还书籍方式
{
    int flag = 0;
    do
    {
        printf("还书方式\n"
               "1.书号\n"
               "2.书名\n");
        int x, i;
        char b[MAXSIZE];
        printf("请选择还书方式:");
        scanf("%d", &x);
        fflush(stdin);
        switch (x)
        {
        case 1:
            printf("请输入归还书籍书号:");
            gets(b);
            fflush(stdin);
            printf("请输入归还数量:");
            scanf("%d", &i);
            fflush(stdin);
            returnb(M, b, i, r3);
            flag = 0;
            break;
        case 2:
            printf("请输入归还书籍书名:");
            gets(b);
            fflush(stdin);
            printf("请输入归还数量:");
            scanf("%d", &i);
            fflush(stdin);
            returnb1(M, b, i, r3);
            flag = 0;
            break;
        // case 3:  printf("请输入归还书籍作者:");
        //         gets(b);
        //         fflush(stdin);
        //         printf("请输入归还数量:");
        //         scanf("%d",&i);
        //         fflush(stdin);
        //         returnb2(M,b,i);
        //         break;
        default:
            system("cls");
            color(4);
            printf("不存在此操作，请重新选择！！！\n");
            color(16);
            flag = 1;
            break;
        }
    } while (flag);
}

void getpwd(char *pwd, int pwdlen) //密码转星号
{
    char ch = 0;
    int i = 0;
    while (i < pwdlen)
    {
        ch = getch();
        if (ch == '\r')
        {
            printf("\n");
            break;
        }

        if (ch == '\b' && i > 0)
        {
            i--;
            printf("\b \b");
        }
        else if (isprint(ch))
        {
            pwd[i] = ch;
            printf("*");
            i++;
        }
    }
    pwd[i] = 0;
}
int login(int r2) //登录系统
{
    int a;
    LinkList Ctr;
    bookdatar(Ctr);
    if (logout == 1)
        init(Ctr);
    logout = 0;
    while (1)
    {
        if (r2 == 0)
        {
            printf("\t\t\t\t\t%s,欢迎来到海南大学图书管理系统\n", inf[r2].name);
            printf("\t\t\t\t\t\t1.采编入库\n"
                   "\t\t\t\t\t\t2.借阅\n"
                   "\t\t\t\t\t\t3.归还\n"
                   "\t\t\t\t\t\t4.查看图书馆书籍\n"
                   "\t\t\t\t\t\t5.查看已借阅书籍\n"
                   "\t\t\t\t\t\t6.注销\n"
                   "\t\t\t\t\t按Ctrl+C结束运行\n");
            printf("\t\t\t\t\t请选择你的操作:");
            scanf("%d", &a);
            fflush(stdin);
            switch (a)
            {
            case 1:
                in(Ctr);
                bookdataw(Ctr);
                break;
            case 2:
                if (Ctr->next == NULL)
                {
                    printf("图书馆还未采购书籍，请采购\n");
                    break;
                }
                else
                {
                    switchl(Ctr, r2);
                    userdataw(Ctr, r2);
                    break;
                }
            case 3:
                if (Ctr->next == NULL)
                {
                    color(4);
                    printf("图书馆还未采购书籍，请采购！\n");
                    color(16);
                    break;
                }
                else
                {
                    switchr(Ctr, r2);
                    userdataw(Ctr, r2);
                    break;
                }
            case 4:
                if (Ctr->next == NULL)
                {
                    color(4);
                    printf("图书馆还未采购书籍，请采购！\n");
                    color(16);
                    break;
                }
                else
                {
                    show(Ctr);
                    break;
                }
            case 5:
                own(Ctr, r2);
                break;
            case 6:
                main();
                logout = 1;
                break;
            default:
                system("cls");
                color(4);
                printf("不存在此操作，请重新选择！！！\n");
                color(16);
                break;
            }
        }
        else
        {
            printf("\t\t\t\t\t%s,欢迎来到海南大学图书管理系统\n", inf[r2].name);
            printf("\t\t\t\t\t\t1.借阅\n"
                   "\t\t\t\t\t\t2.归还\n"
                   "\t\t\t\t\t\t3.查看书籍\n"
                   "\t\t\t\t\t\t4.查看已借阅书籍\n"
                   "\t\t\t\t\t\t5.注销\n"
                   "\t\t\t\t\t按Ctrl+C结束运行\n");
            printf("\t\t\t\t\t请选择你的操作:");
            scanf("%d", &a);
            fflush(stdin);
            switch (a)
            {
            case 1:
                if (Ctr->next == NULL)
                {
                    color(4);
                    printf("图书馆还未采购书籍，请等待几天再试！\n");
                    color(16);
                    break;
                }
                else
                {
                    switchl(Ctr, r2);
                    userdataw(Ctr, r2);
                    break;
                }
            case 2:
                if (Ctr->next == NULL)
                {
                    color(4);
                    printf("图书馆还未采购书籍，请等待几天再尝试！\n");
                    color(16);
                    break;
                }
                else
                {
                    switchr(Ctr, r2);
                    userdataw(Ctr, r2);
                    break;
                }
            case 3:
                if (Ctr->next == NULL)
                {
                    color(4);
                    printf("图书馆还未采购书籍，请等待几天再尝试！\n");
                    color(16);
                    break;
                }
                else
                {
                    show(Ctr);
                    break;
                }
            case 4:
                own(Ctr, r2);
                break;
            case 5:
                main();
                break;
            default:
                system("cls");
                color(4);
                printf("不存在此操作，请重新选择！！！\n");
                color(16);
                break;
            }
        }
    }
}
int main()
{
    int f0 = 0;
    do
    {
        char tell[MAXSIZE], pas[MAXSIZE];
        int r = 0, r1;
        int f = 0, ff = 0; //循环标志
        inf[0].tes = 0;
        initinf();
        printf("\t\t\t\t\t\t欢迎来到海南大学图书管理系统\n");
        do
        {
            printf("\t\t请输入你的账号:");
            scanf("%s", tell);
            fflush(stdin);
            if (inf[0].tes == 0)
            {
                color(4);
                printf("没有录入学生！\n");
                color(16);
                f0 = 1;
            }
            if (!strcmp(tell, "\r"))
                f = 1;
            while (strcmp(inf[r].id, tell) && strcmp(tell, "\r"))
            {

                if (r >= MAXSIZE)
                {
                    color(4);
                    printf("不存在此用户！！\n");
                    color(16);
                    f = 1;
                    break;
                }
                else
                {
                    f = 0;
                }
                r++;
            }
            r1 = r;
            if (!strcmp(inf[r].id, tell))
                f = 0;
            r = 0;
        } while (f);
        if (f0 == 1)
            break;
        do
        {
            printf("\t\t请输入你的密码:");
            getpwd(pas, MAXSIZE + 1);
            fflush(stdin);
            if (strcmp(inf[r1].passwd, pas))
            {
                color(4);
                printf("密码错误,请重新输入！\n");
                color(16);
                ff = 1;
            }
            else
            {
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //使用system("cls")出现bug，启用手动清屏
                ff = 0;
                login(r1);
            }
        } while (ff);

    } while (f0);
}