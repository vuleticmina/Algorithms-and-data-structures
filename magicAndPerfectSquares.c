#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#include <math.h>

typedef struct node
{
    int ** info;
    struct node* left;
    struct node* right;

}Node;
typedef struct data{
    int i,j,k;
    Node * m;
}Data;
typedef struct node1
{
    Data info;
    struct node1* next;

}Node1;
typedef struct node2
{
    Node * info;
    struct node2* next;

}Node2;
typedef struct queue
{
    Node2* front;
    Node2* rear;
}Queue;
Queue * insertQ(Queue *q,Node* x)
{
    Node2 * p=malloc(sizeof(Node2));
    p->info=x;
    p->next=NULL;
    if(q->front==NULL)
    {
        q->front=p;
        q->rear=p;
    }
    else
    {
        q->rear->next=p;
    }
    q->rear=p;
    return q;
}
Node * deleteQ(Queue *q)
{
    Node * temp;
    if(q->front==NULL)return NULL;
    temp=q->front->info;
    q->front=q->front->next;
    return temp;
}
void push(Node1** s,  int n ,int i, int j, int k, Node * m)
{
    Node1* p=malloc(sizeof(Node1));
    p->info.m=m;
    p->info.k=k;
    p->info.j=j;
    p->info.i=i;
    p->next=*s;

    *s=p;
    return;
}
Data pop(Node1** s,int n)
{
    Data x;
    x.i=x.j=x.k=-1;
    x.m=NULL;
    if(s==NULL) return x;

    Node1* p=*s;
    *s=(*s)->next;
    x=p->info;
    free(p);
    return x;


}
void push2(Node2** s,  Node * m)
{
    Node2* p=malloc(sizeof(Node2));
    p->info=m;
    p->next=*s;
    *s=p;
    return;
}
Node* pop2(Node2** s)
{

    if(s==NULL) return NULL;

    Node2* p=*s;
    *s=(*s)->next;
    Node* x=p->info;
    free(p);
    return x;


}
int compare(const void* a,const void* b)
{
    return *(int* )a - *(int* )b;
}

int inputN()
{
    int n;
    do {
        printf("Unesite dimenzije kvadrata: ");
        scanf("%d",&n);
    }while(n<=0 || n>10);
    return n;
}
int inputVals(int vals[],int n)
{
    int i;
    int s=0;
    for(i=0;i<n*n;i++)
    {
        scanf("%d",&vals[i]);
        s+=vals[i];
    }
    return s/n;
}
int checkVals(int vals[],int n)
{
    int d;
    d=vals[1]-vals[0];
    for(int i=2;i<n*n;i++)
    {
        if((vals[i]-vals[i-1])!=d)
        {
            return 0;
        }
    }
    return 1;
}
int inputStart(int** start,int n,int vals[],int vals1[])
{
    for (int i = 0; i < n*n; i++)
    {
        vals1[i]=0;
    }
    int p=0;
    for(int i = 0;i<n;i++)
        for (int j = 0; j < n; j++)
        {
            scanf("%d",&start[i][j]);
            for(int k=0;k<n*n;k++)
            {
                if(vals[k]==start[i][j] && vals1[k]==0)
                {
                    vals1[k]=1;
                    break;
                }
                if(vals[k]==start[i][j] && vals1[k]!=0)
                {
                    p=1;
                    break;
                }


            }

            if(p) return 0;
        }
    return 1;
}
int checkSquare(int ** square, int n, int sum)
{
    int nOZ, curr;

    for(int i=0;i<n;i++)
    {
        nOZ=0;
        curr=0;
        for (int j = 0; j < n; ++j) {
            curr += square[i][j];
            if(square[i][j]==0) nOZ++;
        }
        if((nOZ==0 && curr!=sum)||(nOZ!=0 && curr>sum)) return 0;

    }
    for(int i=0;i<n;i++)
    {
        nOZ=0;
        curr=0;
        for (int j = 0; j < n; ++j) {
            curr += square[j][i];
            if(square[j][i]==0) nOZ++;
        }
        if((nOZ==0 && curr!=sum)||(nOZ!=0 && curr>sum)) return 0;

    }
    nOZ=0;
    curr=0;
    for (int i = 0; i < n; ++i)
    {
        curr+=square[i][i];
        if(square[i][i]==0) nOZ++;
    }
    if((nOZ==0 && curr!=sum)||(nOZ!=0 && curr>sum)) return 0;

    nOZ=0;
    curr=0;
    for (int i = 0; i < n; ++i)
    {
        curr+=square[i][n-1-i];
        if(square[i][n-1-i]==0) nOZ++;
    }
    if((nOZ==0 && curr!=sum)||(nOZ!=0 && curr>sum)) return 0;
    return 1;
}

Node * makeTree(Node* tree, int vals[],int vals1[],int n, int** start,int sum) {

    Node1 *s = NULL;
    Data x;
    if (!checkSquare(start, n, sum)) return NULL;
    Node *p = malloc(sizeof(Node));
    p->info = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) p->info[i] = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; ++j) {
            p->info[i][j] = start[i][j];
        }
    p->left = NULL;
    p->right = NULL;
    tree = p;

    int i, j, k, thereIsNoSquare = 0;
    int pu=1;
    while (pu|| s!= NULL) {
        pu=0;
        if (thereIsNoSquare) {
            thereIsNoSquare = 1;

            x = pop(&s, n);
            i = x.i;
            j = x.j;
            k = x.k;
            p = x.m;

            for (int r = 0; r < n; r++)
                for (int q = 0; q < n; ++q) {
                    start[r][q] = p->info[r][q];
                }
            start[i][j] = 0;
            vals1[k] = 0;

            for (k = k + 1; k < n * n; k++)
                if (vals1[k] == 0) {
                    start[i][j] = vals[k];
                    if (checkSquare(start, n, sum)) {
                        thereIsNoSquare = 0;
                        vals1[k] = 1;
                        Node *new = malloc(sizeof(Node));
                        new->info = (int **) malloc(n * sizeof(int *));
                        for (int r = 0; r < n; r++) new->info[r] = (int *) malloc(n * sizeof(int));
                        for (int r = 0; r < n; r++)
                            for (int q = 0; q < n; ++q) {
                                new->info[r][q] = start[r][q];
                            }
                        p->right = new;
                        new->left = NULL;
                        new->right = NULL;
                        p = new;
                        push(&s, n, i, j, k, new);
                        break;
                    }

                }



        } else {
            thereIsNoSquare = 1;
            for (j = 0; j < n * n && (p->info[j / n][j % n] != 0); ++j);
            if (j<n*n && (p->info[j / n][j % n] == 0)) {
                i = j / n;
                j = j % n;
                for (k = 0; k < n * n; k++)
                    if (vals1[k] == 0) {
                        start[i][j] = vals[k];
                        if (checkSquare(start, n, sum)) {
                            thereIsNoSquare = 0;
                            vals1[k] = 1;
                            Node *new = malloc(sizeof(Node));
                            new->info = (int **) malloc(n * sizeof(int *));
                            for (int r = 0; r < n; r++) new->info[r] = (int *) malloc(n * sizeof(int));
                            for (int r = 0; r < n; r++)
                                for (int q = 0; q < n; ++q) {
                                    new->info[r][q] = start[r][q];
                                }
                            p->left = new;
                            new->left = NULL;
                            new->right = NULL;
                            p = new;
                            push(&s, n, i, j, k, new);
                            //if(k==n*n-2 && i==n-1 && j==n-1) return tree;

                            break;
                        }

                    }
            }

        }

    }

    return tree;
}
int isMagical(int ** m, int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if(m[i][j]==0) return 0;
    return 1;

}
void printSquare(int **m,int n)
{
    for (int i = 0; i <n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ",m[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}
void onlyMagical(Node* tree, int n)
{
    Node2* s=NULL;
    Node *p = malloc(sizeof(Node));
    p->info = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) p->info[i] = (int *) malloc(n * sizeof(int));
    push2(&s,tree);
    while(s!=NULL)
    {
        p=pop2(&s);
        while(p!=NULL)
        {
            if(isMagical(p->info,n))
            {
                printSquare(p->info,n);
            }
            if(p->right!=NULL) push2(&s,p->right);
            p=p->left;
        }
    }


}
int isPerfect(int** m,int n,int sum)
{
    int s1=0,s2=0;
    if(isMagical(m,n)) {
        for (int k = 1; k < n ; ++k) {
            s1=s2=0;
            for (int i = 0; i < n; ++i) {
                s1 += m[i][(n + i - k) % n];
                s2 += m[i][n - 1 - (n + i - k) % n];
            }

            if (s1!=sum || s2!=sum) return 0;
        }


        return 1;
    }
    return 0;
}
void onlyPerfect(Node* tree, int n,int sum)
{
    Node2* s=NULL;
    Node *p = malloc(sizeof(Node));
    p->info = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) p->info[i] = (int *) malloc(n * sizeof(int));
    push2(&s,tree);
    while(s!=NULL)
    {
        p=pop2(&s);
        while(p!=NULL)
        {
            if(isPerfect(p->info,n,sum))
            {
                printSquare(p->info,n);
            }
            if(p->right!=NULL) push2(&s,p->right);
            p=p->left;
        }
    }

}
void printTree(Node* tree,int n)
{
    Queue* q1=malloc(sizeof(Queue));
    Queue* q2=malloc(sizeof(Queue));
    q1->front=NULL;
    q1->rear=NULL;
    q2->front=NULL;
    q2->rear=NULL;
    int prev=0;
    int curr=0;
    int curr1=0;
    Node* p=tree;
    q1=insertQ(q1,p);
    prev=1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d",p->info[i][j]);

        }
        printf("\n");

    }
    printf("\n");
    while(q1->front!=NULL)
    {
        for(int k=0;k<prev;k++)
        {
            p=deleteQ(q1);

            if(p->left!=NULL)
            {
                p=p->left;
                q2=insertQ(q2,p);
                q1=insertQ(q1,p);
                curr++;
                curr1++;
                while(p->right!=NULL)
                {
                    p=p->right;
                    q2=insertQ(q2,p);
                    q1=insertQ(q1,p);
                    curr++;
                    curr1++;
                }

            }

            if(k!=prev-1) {
                q2=insertQ(q2,NULL);
                curr1++;
            }

        }


        while(q2->front!=NULL)
        {
            for(int i=0; i<n;i++) {
                for (int l = 0; l < curr1; l++) {
                    p = deleteQ(q2);
                    if (p != NULL) {
                        for (int j = 0; j < n; j++)
                            printf("%d", p->info[i][j]);
                        printf(" ");
                    } else printf("|");
                    if (i != n - 1) q2 = insertQ(q2, p);

                }
                printf("\n");
            }


        }
        printf("\n");
        prev=curr;
        curr=curr1=0;
    }


}

int main() {
    int k=-1,n=0,vals[MAX],vals1[MAX],sum=0;
    int** start;
    Node* tree=NULL;
    while(k!=0)
    {
        printf("--MENU--\n0. Exit.\n1. Enter dimensions of square.\n2. Enter values.\n3. Enter starting state.\n4. Print characteristic sum.\n5. Form tree.\n6. Print tree.\n7. Print magic squares.\n8. Print perfect squares.\n");
        scanf("%d",&k);
        switch (k) {
            case 0:
                printf("End of program.\n");
                break;
            case 1:
                n=inputN();
                break;
            case 2:
                if(!n)
                {
                    printf("Enter dimensions first.\n");
                    break;
                }
                sum=inputVals(vals,n);
                qsort(vals,n*n,sizeof(int),compare);
                if(!checkVals(vals,n))
                {
                    printf("It is not possible to form magic square from given values\n");
                    sum=0;
                }
                break;
            case 3:
                start= (int **)malloc(n * sizeof(int*));
                for(int i = 0; i < n; i++) start[i] = (int *)malloc(n * sizeof(int));
                k=inputStart(start,n,vals,vals1);
                if(!k)
                {
                    printf("Bad input!");
                }
                break;
            case 4:
                if(sum)
                {
                    printf("Characteristic sum is %d\n",sum);
                }
                else
                {
                    printf("Enter starting state first!\n");
                }
                break;
            case 5:
                tree=makeTree(tree,vals,vals1,n,start,sum);
                break;
            case 6:
                printTree(tree,n);
                break;
            case 7:
                onlyMagical(tree,n);
                break;
            case 8:
                onlyPerfect(tree,n,sum);
                break;
            default:
                printf("Invalid option\n");
                break;

        }



    }
    return 0;
}
