#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

typedef struct node{ // 定义 data 存储结构
    char name[MAX]; // 姓名
    char sex; // 性别
    int generation;// 代目
}node;

typedef struct ft{ // 创建结构体
    struct node l; // 家谱中直系家属
    struct ft *lchild;// 用来指向兄弟
    struct ft *rchild;// 用来指向孩子
}ft;
ft *root; //root 是结构体 ft 的指针
ft *search(ft *p,char ch[]) //  搜索指针函数
{
    ft *q;
    if(p==NULL)
        return NULL;// 没有家谱，头指针下为空
    if(strcmp(p->l.name,ch)==0)
        return p;// 家谱不为空，头指针下有这个人
    if(p->lchild)
    {
        q=search(p->lchild,ch);// 在兄弟中找
        if(q)
            return q;// 找到
    }
    if(p->rchild)
    {
        q=search(p->rchild,ch); // 在孩子中找
        if(q!=NULL)
            return q;
    }
    return NULL;// 没有找到
}
ft *parent(ft *p,ft *q,int *flag) // 通过 parent 函数得到双亲结点。用 flag 标志， -1 为左孩子， 1 为右孩子
{
    if(p==NULL)
        return NULL; // 没有家谱，头指针下为空
    if(p->rchild==NULL)
    {
        *flag=0;
        return NULL;
    }
    else
    {
        if(p->lchild==q)
        {
            *flag=1;
            return p;
        }
        else
        {
            if(p->rchild==q)
            {
                *flag=-1;
                return p;
            }
            else
            {
                if(p->lchild!=NULL)
                {
                    parent(p->lchild,q,*&flag);
                }
                if(p->rchild!=NULL)
                {
                        parent(p->rchild,q,*&flag);
                }
            }
        }
    }
}
int generation(ft *p,char ch[]) //  获得搜索到的成员的代目的返回值
{
    ft *q;
    if(p==NULL)
        return NULL;
    if(strcmpi(p->l.name,ch)==0)
        return p->l.generation; // 家谱不为空，头指针下有这个人
    if(p->lchild)
    {
        q=search(p->lchild,ch); // 在兄弟中找
        if(q)
            return q->l.generation; // 找到
    }
    if(p->rchild)
    {
        q=search(p->rchild,ch); // 在孩子中找
        if(q!=NULL)
            return q->l.generation;
    }
    return NULL;
}
void saves(ft *p,char b[],char c,int d) // 建立家谱孩子结点   创建结点并对 l 赋值   保存
{
    for(int i=0;i<MAX;i++)
    p->l.name[i]=b[i];
    p->l.sex=c;
    p->l.generation=d;
}
void disp(ft *n) // 搜索到数据的输出
{
    ft *t=NULL;
    printf(" 此人姓名 :%s  性别 %c  为第 %d 代 \n",n->l.name,n->l.sex,n->l.generation);
    printf("\n");
    printf(" 此人的子女 :"); // 子女输出
    if(n->rchild==NULL)
    {
        printf(" 此人无子女 !");
    }
    else
    {
        if(n->rchild->lchild==NULL)
        {
            printf(" 姓名 :%s  性别 :%c\t",n->rchild->l.name,n->rchild->l.sex);
        }
        else
        {
            printf(" 姓名 :%s  性别 :%c\t",n->rchild->l.name,n->rchild->l.sex);
            t=n->rchild->lchild;
            while(t!=NULL)
            {
                printf(" 姓名 :%s  性别 :%c\t",t->l.name,t->l.sex);
                t=t->lchild;
            }
        }
    }
    printf("\n");
    printf("\n");
    printf(" 此人的同辈成员 :"); // 同辈输出
    if(n->lchild==NULL)
    {
        printf(" 此人无同辈成员 !");
    }
    else
    {
        if(n->lchild->lchild==NULL)
        {
            printf(" 姓名 :%s  性别 :%c\t",n->lchild->l.name,n->lchild->l.sex);
        }
        else
        {
            printf(" 姓名 :%s  性别 :%c\t",n->lchild->l.name,n->lchild->l.sex);
            t=n->lchild->lchild;
            while(t!=NULL)
            {
                printf(" 姓名 :%s  性别 :%c\t",t->l.name,t->l.sex);
                t=t->lchild;
            }
        }
    }
    printf("\n");
}
void InitTree() // 初始化
{

    char b[MAX],c;
    int a;
 printf("  请输入始祖的姓名   性别 :\n");
        printf(" 输入姓名 ( 不超过 10 个字符 )\n");
 printf(" 性别： [M/F （男 / 女 )] \n");
 printf(" 格式： XX M( 姓名为 XX 性别男 )\n");
 free(root); // 释放 root  （ ft ）   空间
 root=(ft *)malloc(sizeof(ft)); //  创建一个 ft 结构体大小的空间   然后强制转换为 ft * 类型的指针   然后赋值给 root , 这时  root 指向一个 struct dictree 结构体大小的新空间
 scanf("%s %c",&b,&c);a=1; // 输入姓名，性别
 root->rchild=NULL; // 清空左右孩子
 root->lchild=NULL;
 saves(root,b,c,a); // 存入结构
 printf(" 家谱重构成功 !\n");
}
void Manu()
{
     printf(" *********************************************\n");
     printf(" *****  请选择对家谱的操作 :  　　　　  *****\n");
     printf(" *****     0. 退出　                    *****\n");
     printf(" *****     1. 添加　                    *****\n");
     printf(" *****     2. 查找　                    *****\n");
     printf(" *****     3. 修改　                    *****\n");
     printf(" *****     4. 删除　                    *****\n");
     printf(" *****     5. 重构                      *****\n");
     printf(" *********************************************\n");
}
void Add() // 添加
{
    ft *n,*m,*t=NULL;
    char b[MAX],c,d[MAX];
    int i;
    printf(" 请输入要添加子女的上一辈的姓名 :\n"); // 判断是否有重名
    scanf("%s",&d);
    n=search(root,d);
    int a=generation(root,d);
    while(n==NULL)
    {
        printf(" 此人不在家谱内 , 请重新输入姓名 :\n");

        scanf("%s",&d);
        n=search(root,d);
    } // 孩子信息添加
    if(n->rchild==NULL)
    {
        printf(" 孩子姓名与性别输入 :\n");
        scanf("%s %c",&b,&c);
        a++;
        m=search(root,b);
        if(m!=NULL)
        {
            printf(" 出现重名，添加失败 !\n");
        }
        else
        {
            n->rchild=(ft *)malloc(sizeof(ft));
            n->rchild->lchild=NULL;
            n->rchild->rchild=NULL;
            saves(n->rchild,b,c,a);
            printf(" 添加成功 !\n");
        }

    }
    else
    {
        n=n->rchild;
        while(n->lchild!=NULL)
        n=n->lchild;

        printf(" 孩子姓名与性别输入 :\n");
        scanf("%s %c",&b,&c);
        a++;
        m=search(root,b);
        if(m!=NULL)
            printf(" 出现重名，添加失败 !\n");
        else
        {
            t=(ft *)malloc(sizeof(ft));
            saves(t,b,c,a);
            t->lchild=NULL;
            t->rchild=NULL;
            n->lchild=t;
            printf(" 添加成功 !\n");
        }

    }
}
void Search() // 查询
{
    ft *n;
    char d[MAX];

    printf(" 输入姓名，查找相关信息 :\n");
    scanf("%s",&d);
    n=search(root,d);
    while(n==NULL)
    {
        printf(" 此人不存在，请再次输入 :\n");
        scanf("%s",&d);
        n=search(root,d);
    }
    disp(n);
}
void Change() // 修改
{

    char a[MAX],r[MAX],c;
    ft *n;
    printf(" 请输入要修改人的姓名 :");
    scanf("%s",&a);
    n=search(root,a);
    while(n==NULL)
    {
        printf(" 此人不存在 , 请重新输入姓名 :\n");

        scanf("%s",&a);
        n=search(root,a);
    }
    printf(" 此人存在，请输入新信息 :");
    scanf("%s %c",&r,&c);
    for(int i=0;i<MAX;i++)
        n->l.name[i]=r[i];
    n->l.sex=c;
    printf(" 修改成功 !\n");
}
void Delete() // 删除
{
    ft *n,*m;
    int flag;
    char d[MAX],a[MAX];
    printf(" 请输入要删除人的姓名 :");
    scanf("%s",a);
    n=search(root,a);
    while(n==NULL)
    {
        printf(" 此人不存在 , 请重新输入姓名 :\n");
        scanf("%s",&a);
        n=search(root,a);
    }
    printf("\n");
    printf(" 此人已找到 !\n");
    printf("\n");
    m=parent(root,n,&flag);
    if(flag>0)
     {
         m->lchild=n->lchild;
        printf(" 删除成功 !\n");
     }
     else if(flag<0)
     {
         m->rchild=n->lchild;
        printf(" 删除成功 !\n");
    }
    else if (flag == 0)
    {
       root->l.generation = NULL;
       root->l.sex = NULL;
       strcpy(root->l.name, "");
       printf(" 删除成功 !\n");
    }
}
int main()
{
    system("color 5a");
    InitTree();
    for(;;)
    {
         system("pause");
         system("cls");
         Manu();
         int choice;
         scanf("%d",&choice);
         switch(choice)
         {
             case 0:exit(0); break;// 退出
             case 1:Add(); break;// 添加
             case 2:Search(); break;// 查找
             case 3:Change(); break;// 修改
             case 4:Delete(); break;// 删除
             case 5:InitTree(); break;// 初始化
        }
    }
    return 0;
}
