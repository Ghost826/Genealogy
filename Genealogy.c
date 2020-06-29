#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

typedef struct node{ // ���� data �洢�ṹ
    char name[MAX]; // ����
    char sex; // �Ա�
    int generation;// ��Ŀ
}node;

typedef struct ft{ // �����ṹ��
    struct node l; // ������ֱϵ����
    struct ft *lchild;// ����ָ���ֵ�
    struct ft *rchild;// ����ָ����
}ft;
ft *root; //root �ǽṹ�� ft ��ָ��
ft *search(ft *p,char ch[]) //  ����ָ�뺯��
{
    ft *q;
    if(p==NULL)
        return NULL;// û�м��ף�ͷָ����Ϊ��
    if(strcmp(p->l.name,ch)==0)
        return p;// ���ײ�Ϊ�գ�ͷָ�����������
    if(p->lchild)
    {
        q=search(p->lchild,ch);// ���ֵ�����
        if(q)
            return q;// �ҵ�
    }
    if(p->rchild)
    {
        q=search(p->rchild,ch); // �ں�������
        if(q!=NULL)
            return q;
    }
    return NULL;// û���ҵ�
}
ft *parent(ft *p,ft *q,int *flag) // ͨ�� parent �����õ�˫�׽�㡣�� flag ��־�� -1 Ϊ���ӣ� 1 Ϊ�Һ���
{
    if(p==NULL)
        return NULL; // û�м��ף�ͷָ����Ϊ��
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
int generation(ft *p,char ch[]) //  ����������ĳ�Ա�Ĵ�Ŀ�ķ���ֵ
{
    ft *q;
    if(p==NULL)
        return NULL;
    if(strcmpi(p->l.name,ch)==0)
        return p->l.generation; // ���ײ�Ϊ�գ�ͷָ�����������
    if(p->lchild)
    {
        q=search(p->lchild,ch); // ���ֵ�����
        if(q)
            return q->l.generation; // �ҵ�
    }
    if(p->rchild)
    {
        q=search(p->rchild,ch); // �ں�������
        if(q!=NULL)
            return q->l.generation;
    }
    return NULL;
}
void saves(ft *p,char b[],char c,int d) // �������׺��ӽ��   ������㲢�� l ��ֵ   ����
{
    for(int i=0;i<MAX;i++)
    p->l.name[i]=b[i];
    p->l.sex=c;
    p->l.generation=d;
}
void disp(ft *n) // ���������ݵ����
{
    ft *t=NULL;
    printf(" �������� :%s  �Ա� %c  Ϊ�� %d �� \n",n->l.name,n->l.sex,n->l.generation);
    printf("\n");
    printf(" ���˵���Ů :"); // ��Ů���
    if(n->rchild==NULL)
    {
        printf(" ��������Ů !");
    }
    else
    {
        if(n->rchild->lchild==NULL)
        {
            printf(" ���� :%s  �Ա� :%c\t",n->rchild->l.name,n->rchild->l.sex);
        }
        else
        {
            printf(" ���� :%s  �Ա� :%c\t",n->rchild->l.name,n->rchild->l.sex);
            t=n->rchild->lchild;
            while(t!=NULL)
            {
                printf(" ���� :%s  �Ա� :%c\t",t->l.name,t->l.sex);
                t=t->lchild;
            }
        }
    }
    printf("\n");
    printf("\n");
    printf(" ���˵�ͬ����Ա :"); // ͬ�����
    if(n->lchild==NULL)
    {
        printf(" ������ͬ����Ա !");
    }
    else
    {
        if(n->lchild->lchild==NULL)
        {
            printf(" ���� :%s  �Ա� :%c\t",n->lchild->l.name,n->lchild->l.sex);
        }
        else
        {
            printf(" ���� :%s  �Ա� :%c\t",n->lchild->l.name,n->lchild->l.sex);
            t=n->lchild->lchild;
            while(t!=NULL)
            {
                printf(" ���� :%s  �Ա� :%c\t",t->l.name,t->l.sex);
                t=t->lchild;
            }
        }
    }
    printf("\n");
}
void InitTree() // ��ʼ��
{

    char b[MAX],c;
    int a;
 printf("  ������ʼ�������   �Ա� :\n");
        printf(" �������� ( ������ 10 ���ַ� )\n");
 printf(" �Ա� [M/F ���� / Ů )] \n");
 printf(" ��ʽ�� XX M( ����Ϊ XX �Ա��� )\n");
 free(root); // �ͷ� root  �� ft ��   �ռ�
 root=(ft *)malloc(sizeof(ft)); //  ����һ�� ft �ṹ���С�Ŀռ�   Ȼ��ǿ��ת��Ϊ ft * ���͵�ָ��   Ȼ��ֵ�� root , ��ʱ  root ָ��һ�� struct dictree �ṹ���С���¿ռ�
 scanf("%s %c",&b,&c);a=1; // �����������Ա�
 root->rchild=NULL; // ������Һ���
 root->lchild=NULL;
 saves(root,b,c,a); // ����ṹ
 printf(" �����ع��ɹ� !\n");
}
void Manu()
{
     printf(" *********************************************\n");
     printf(" *****  ��ѡ��Լ��׵Ĳ��� :  ��������  *****\n");
     printf(" *****     0. �˳���                    *****\n");
     printf(" *****     1. ��ӡ�                    *****\n");
     printf(" *****     2. ���ҡ�                    *****\n");
     printf(" *****     3. �޸ġ�                    *****\n");
     printf(" *****     4. ɾ����                    *****\n");
     printf(" *****     5. �ع�                      *****\n");
     printf(" *********************************************\n");
}
void Add() // ���
{
    ft *n,*m,*t=NULL;
    char b[MAX],c,d[MAX];
    int i;
    printf(" ������Ҫ�����Ů����һ�������� :\n"); // �ж��Ƿ�������
    scanf("%s",&d);
    n=search(root,d);
    int a=generation(root,d);
    while(n==NULL)
    {
        printf(" ���˲��ڼ����� , �������������� :\n");

        scanf("%s",&d);
        n=search(root,d);
    } // ������Ϣ���
    if(n->rchild==NULL)
    {
        printf(" �����������Ա����� :\n");
        scanf("%s %c",&b,&c);
        a++;
        m=search(root,b);
        if(m!=NULL)
        {
            printf(" �������������ʧ�� !\n");
        }
        else
        {
            n->rchild=(ft *)malloc(sizeof(ft));
            n->rchild->lchild=NULL;
            n->rchild->rchild=NULL;
            saves(n->rchild,b,c,a);
            printf(" ��ӳɹ� !\n");
        }

    }
    else
    {
        n=n->rchild;
        while(n->lchild!=NULL)
        n=n->lchild;

        printf(" �����������Ա����� :\n");
        scanf("%s %c",&b,&c);
        a++;
        m=search(root,b);
        if(m!=NULL)
            printf(" �������������ʧ�� !\n");
        else
        {
            t=(ft *)malloc(sizeof(ft));
            saves(t,b,c,a);
            t->lchild=NULL;
            t->rchild=NULL;
            n->lchild=t;
            printf(" ��ӳɹ� !\n");
        }

    }
}
void Search() // ��ѯ
{
    ft *n;
    char d[MAX];

    printf(" �������������������Ϣ :\n");
    scanf("%s",&d);
    n=search(root,d);
    while(n==NULL)
    {
        printf(" ���˲����ڣ����ٴ����� :\n");
        scanf("%s",&d);
        n=search(root,d);
    }
    disp(n);
}
void Change() // �޸�
{

    char a[MAX],r[MAX],c;
    ft *n;
    printf(" ������Ҫ�޸��˵����� :");
    scanf("%s",&a);
    n=search(root,a);
    while(n==NULL)
    {
        printf(" ���˲����� , �������������� :\n");

        scanf("%s",&a);
        n=search(root,a);
    }
    printf(" ���˴��ڣ�����������Ϣ :");
    scanf("%s %c",&r,&c);
    for(int i=0;i<MAX;i++)
        n->l.name[i]=r[i];
    n->l.sex=c;
    printf(" �޸ĳɹ� !\n");
}
void Delete() // ɾ��
{
    ft *n,*m;
    int flag;
    char d[MAX],a[MAX];
    printf(" ������Ҫɾ���˵����� :");
    scanf("%s",a);
    n=search(root,a);
    while(n==NULL)
    {
        printf(" ���˲����� , �������������� :\n");
        scanf("%s",&a);
        n=search(root,a);
    }
    printf("\n");
    printf(" �������ҵ� !\n");
    printf("\n");
    m=parent(root,n,&flag);
    if(flag>0)
     {
         m->lchild=n->lchild;
        printf(" ɾ���ɹ� !\n");
     }
     else if(flag<0)
     {
         m->rchild=n->lchild;
        printf(" ɾ���ɹ� !\n");
    }
    else if (flag == 0)
    {
       root->l.generation = NULL;
       root->l.sex = NULL;
       strcpy(root->l.name, "");
       printf(" ɾ���ɹ� !\n");
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
             case 0:exit(0); break;// �˳�
             case 1:Add(); break;// ���
             case 2:Search(); break;// ����
             case 3:Change(); break;// �޸�
             case 4:Delete(); break;// ɾ��
             case 5:InitTree(); break;// ��ʼ��
        }
    }
    return 0;
}
