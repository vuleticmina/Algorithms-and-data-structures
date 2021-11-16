#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int info;
    struct node* next;

}Node;
typedef struct head
{
    int name;
    Node * list;
}Head;
typedef struct node2
{
    Node * info;
    struct node2* next;

}Node2;
typedef struct queue
{
    Node* front;
    Node* rear;
}Queue;
Queue * insertQ(Queue *q,int x)
{
    Node * p=malloc(sizeof(Node));
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
int deleteQ(Queue *q)
{
    int temp;
    if(q->front==NULL) return NULL;
    temp=q->front->info;
    q->front=q->front->next;
    return temp;
}
void push(Node** s, int x)
{
    Node* p=malloc(sizeof(Node));
    p->info=x;
    p->next=*s;
    *s=p;
    return;
}
int pop(Node** s)
{
    int x;

    if(s==NULL) return -1;
    Node* p=*s;
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
Head * createGraph(int n)
{
    Head * p=NULL;
    p=malloc(n*sizeof(Head));

    for(int i=0;i<n;i++)
    {
        p[i].list=NULL;
        p[i].name=i;
    }
    return p;

}
Head* addInGraph(Head * p,int *n, int name)
{
    *n=(*n)+1;
    p=realloc(p,*n*sizeof(Head));
    p[*n-1].list=NULL;
    p[*n-1].name=name;
    return p;

}
Node* delete(Node* list, int name)//brisanje elementa
{
    Node* current=list;
    Node* prev=list;
    if(current->info==name && current->next==NULL)
    {
        free(current);
        list=NULL;
        return list;
    }
    if(current->info==name)//potrebno je izbrisati prvi element
    {
        list=current->next;
        free(current);
        return list;
    }
    while(current->next!=NULL && current->info<name)
    {
        prev=current;
        current=current->next;
    }
    if(current->info==name)
    {
        if(current->next==NULL)//Treba obrisati poslednji element
        {
            prev->next=NULL;
            free(current);
            return list;
        }
        else//treba obrisati clan koji se ne nalazi ni na pocetku ni na kraju
        {

            prev->next=current->next;
            free(current);
            return list;
        }
    }
}
Node* insert(Node* list, int name)//dodavanje elementa
{
    Node* new=malloc(sizeof(Node));
    if(list==NULL)//ukoliko je lista prazna
    {
        new->info=name;
        new->next=NULL;
        printf("dodato1");
        return new;
    }
    if(list->info>name)//ukoliko element treba dodati na pocetak
    {
        new->info=name;
        new->next=list;
        return new;

    }
    Node* current=list;
    Node* prev=list;
    while(1)
    {
        if(current->info==name)//ukoliko x vec postoji u skupu
        {
            return list;
        }
        if(current->info>name)//treba dodati cvor ispred trenutnog
        {
            new->info=name;
            new->next=current;
            prev->next=new;
            return list;

        }
        if(current->next==NULL)
        {
            new->info=name;
            new->next=NULL;
            current->next=new;
            return list;
        }
        prev=current;
        current=current->next;
    }
}
Head* deleteFromGraph(Head * p, int *n,int name1)
{

    int j=0,m=(*n),k=0;
    for(int i=0;i<m;i++)
    {
        if(p[i].name!=name1)
        {
            p[j].list=p[i].list;
            p[j].name=p[i].name;
            j++;
        }
        else
        {
            Node* temp=p[i].list;
            while(temp!=NULL)
            {
                Node* f=temp;
                temp=temp->next;
                free(f);
            }
            p[i].list=NULL;
            k=1;
        }
    }

    if(k==1) {
        *n =(*n)-1;
        p = realloc(p, *n * sizeof(Head));
        for (int i = 0; i < (*n); i++) {
            if(p[i].list!=NULL){
                p[i].list = delete(p[i].list, name1);
            }
        }
    }
    else{
        printf("Takav element ne postoji u grafu.\n");
    }
    return p;
}
Head* addEdge(Head * p, int name1,int name2,int n)
{
    int i,j;
    for(i=0;i<n && p[i].name!=name1;i++);
    for(j=0;j<n && p[j].name!=name2;j++);
    if(p[i].name==name1 && p[j].name==name2)
    {
        p[i].list=insert(p[i].list,name2);
    }
    else{
        printf("Takvi cvorovi ne postoje u grafu\n");
    }
    return p;
}
Head* deleteEdge(Head * p, int name1,int name2,int n)
{
    int i,j;
    for(i=0;i<n && p[i].name!=name1;i++);
    for(j=0;j<n && p[j].name!=name2;j++);
    if(p[i].name==name1 && p[j].name==name2)
    {
        p[i].list=delete(p[i].list,name2);
    }
    else{
        printf("Takvi cvorovi ne postoje u grafu\n");
    }
    return p;
}
void printGraph(Head* p,int n)
{
    for(int i=0;i<n;i++)
    {
        Node* temp=p[i].list;
        printf("%d",p[i].name);
        while(temp!=NULL)
        {
            printf("->%d",temp->info);
            temp=temp->next;
        }
        putchar('\n');
    }
}
Head* freeGraph(Head *p, int n)
{
    for(int i=0;i<n;i++)
    {
        Node* temp=p[i].list;
        while(temp!=NULL)
        {
            Node * f=temp;
            temp=temp->next;
            free(f);
        }
        p[i].list=NULL;

    }

    free(p);
    p=NULL;
    return p;
}
int maja(Head *p,int start,int finish,int * number)
{
    int name;
    int ind=-1;
    *number=0;
    Queue* q1=malloc(sizeof(Queue));
    q1->front=NULL;
    q1->rear=NULL;
    int k1=0;
    q1 = insertQ(q1, start);
    q1 = insertQ(q1, -1);

    while(q1->front!=NULL)
    {
        name=deleteQ(q1);
        if(name==finish)
        {
            *number=(*number)+1;
            ind=1;
            //break;
        }
        if(name!=-1) {
            Node *temp = p[name].list;
            while (temp != NULL) {
                q1 = insertQ(q1, temp->info);
                temp = temp->next;
            }
        }
        else
        {
            if(ind!=-1) break;
            k1++;
            if(q1->front!=NULL) insertQ(q1,-1);
        }

    }
    if(ind==-1) k1=-1;
    return k1;

}
int sanja(Head* p,int start,int finish,int* number)
{
    int name;
    int ind=-1;
    *number=0;
    Queue* q1=malloc(sizeof(Queue));
    q1->front=NULL;
    q1->rear=NULL;
    int k1=0,num=1;
    q1 = insertQ(q1, start);
    q1 = insertQ(q1, -1);
    while(q1->front!=NULL)
    {
        if(num%2)
        {
            name=deleteQ(q1);
            if(name==finish)
            {
                *number=(*number)+1;
                ind=1;
                //break;
            }
            while(name!=-1)
            {
                Node* temp=p[name].list;
                while(temp!=NULL)
                {
                    q1=insertQ(q1,temp->info);
                    temp=temp->next;
                }
                name=deleteQ(q1);
                if(name==finish)
                {
                    ind=1;
                    *number=(*number)+1;
                    //break;
                }
            }
            if(q1->front!=NULL)
            {
                if(ind!=-1){
                    break;
                }
                q1=insertQ(q1,-1);
                k1++;
            }
            if(ind!=-1){
                break;
            }
            num++;
        }
        else
        {
            name=deleteQ(q1);
            if(name==finish)
            {
                *number=(*number)+1;
                ind=1;
                //break;
            }
            while(name!=-1)
            {
                Node* temp=p[name].list;
                while(temp!=NULL)
                {
                    q1=insertQ(q1,temp->info);
                    temp=temp->next;
                }
                name=deleteQ(q1);
                if(name==finish)
                {
                    ind=1;
                    *number=(*number)+1;
                    //break;
                }
            }
            if(q1->front!=NULL)
            {
                if(ind!=-1){
                    break;
                }
                q1=insertQ(q1,-1);
                k1++;
            }
            if(ind!=-1){
                break;
            }



            if(q1->front!=NULL)
            {
                name=deleteQ(q1);
                while(name!=-1)
                {
                    Node* temp=p[name].list;
                    while(temp!=NULL)
                    {
                        q1=insertQ(q1,temp->info);
                        temp=temp->next;
                    }
                    name=deleteQ(q1);

                }
                if(q1->front!=NULL)
                {
                    q1=insertQ(q1,-1);

                }
            }

            num++;
        }


    }
    if(ind==-1) k1=-1;
    return k1;
}
void printStackM(Node* s)
{
    Node* s1=NULL;
    while(s!=NULL)
    {
        int x=pop(&s);
        push(&s1,x);
    }
    while(s1!=NULL)
    {
        int x=pop(&s1);
        push(&s,x);
        printf("%d",x);
        if(s1!=NULL) printf("->");
        else putchar('\n');
   }
}
void printStackS(Node* s)
{
    Node* s1=NULL;
    int step=1, first=0,start=0;
    while(s!=NULL)
    {
        int x=pop(&s);
        push(&s1,x);
    }
    while(s1!=NULL)
    {
        int x=pop(&s1);
        printf("%d",x);
        push(&s,x);


        if(s1!=NULL)
        {
            if(start==0)
            {
                printf("->");
                start=1;
            }
            else if(step%2)
            {
                step++;
                printf("->(");
            }
            else if(first==0)
            {
                printf("->");
                first=1;
            }
            else {
                first=0;
                printf(")->");
                step++;
            }
        }
        else if(first==1) printf(")");

    }
    putchar('\n');
}
void print1Maja(Head * p, int start,int finish,int n,int m)
{
    Node* s1=NULL;
    Node2* s2=NULL;
    int size=0;
    int skinuto=0;
    push(&s1,start);
    //push2(&s2,p[start].list);
    while(!(size==m && s1->info==finish))
    {
        int name1;
        int name=pop(&s1);


        if (p[name].list == NULL || size==m || skinuto==1) {
            Node *temp = pop2(&s2)->next;
            size--;
            skinuto=1;
            if (temp != NULL) {
                push(&s1, temp->info);
                push2(&s2, temp);
                size++;
                skinuto=0;
            }

        } else {
            skinuto=0;
            push(&s1, name);
            name1 = p[name].list->info;
            push(&s1, name1);
            push2(&s2, p[name].list);
            size++;
        }




    }
    printStackM(s1);


}
void printAllMaja(Head * p, int start,int finish,int number,int m) {
    Node *s1 = NULL;
    Node2 *s2 = NULL;
    int size = 0;
    int num=0;
    int skinuto=0;
    push(&s1, start);
    //push2(&s2,p[start].list);
    while (num<number) {
        if(size == m && s1->info == finish)
        {
            printStackM(s1);
            num++;

        }
        int name1;
        int name = pop(&s1);


        if (p[name].list == NULL || size == m || skinuto==1) {
            Node *temp = pop2(&s2)->next;
            size--;
            skinuto=1;
            if (temp != NULL) {
                push(&s1, temp->info);
                push2(&s2, temp);
                size++;
                skinuto=0;
            }

        } else {
            skinuto=0;
            push(&s1, name);
            name1 = p[name].list->info;
            push(&s1, name1);
            push2(&s2, p[name].list);
            size++;
        }


    }
    //printStackM(s1);

}
void print1Sanja(Head * p, int start,int finish,int n,int m)
{

    Node* s1=NULL;
    Node2* s2=NULL;
    int size=0, step=1,first=0;
    int skinuto=0;
    push(&s1,start);
    //push2(&s2,p[start].list);
    while(!(size==m && s1->info==finish))
    {
        int name1;
        int name=pop(&s1);


        if (p[name].list == NULL || size==m || skinuto==1) {
            Node *temp = pop2(&s2)->next;
            size--;
            if (temp != NULL) {
                push(&s1, temp->info);
                push2(&s2, temp);
                skinuto=0;
                //size++;
            } else {
                skinuto=1;
                if(step%2) {
                    step--;
                    size--;
                    first=1;
                }
                else if(first==1)
                {
                    first=0;
                }
                else
                {
                    step--;
                    size--;
                }
        }

        } else {
            push(&s1, name);
            name1 = p[name].list->info;
            push(&s1, name1);
            push2(&s2, p[name].list);
            skinuto=0;
            if(step%2) {
                step++;
                size++;
            }
            else if(first==0){
                first=1;
            }
            else{
                step++;
                size++;
                first=0;
            }

        }
    }
    printStackS(s1);




}
void printAllSanja(Head * p, int start,int finish,int number,int m)
{

    Node* s1=NULL;
    Node2* s2=NULL;
    int size=0, step=1,first=0;
    int num=0;
    int skinuto=0;
    push(&s1,start);
    //push2(&s2,p[start].list);
    while(num<number)
    {
        if(size==m && s1->info==finish)
        {
            num++;
            printStackS(s1);
        }
        int name1;
        int name=pop(&s1);



        if (p[name].list == NULL || size==m || skinuto==1) {
            Node *temp = pop2(&s2)->next;
            //size--;
            if (temp != NULL) {
                push(&s1, temp->info);
                push2(&s2, temp);
                skinuto=0;
                //size++;
            } else {
                skinuto=1;
                if(step%2) {
                    step--;
                    size--;
                    first=1;
                }
                else if(first==1)
                {
                    first=0;
                }
                else
                {
                    step--;
                    size--;
                }
            }

        } else {
            push(&s1, name);
            name1 = p[name].list->info;
            push(&s1, name1);
            push2(&s2, p[name].list);
            skinuto=0;
            if(step%2) {
                step++;
                size++;
            }
            else if(first==0){
                first=1;
            }
            else{
                step++;
                size++;
                first=0;
            }
        }
    }


}
int main() {

    int k=-1;
    int n,name,name1;
    Head * p=NULL;
    while(k!=0)
    {
        printf("---MENI---\n0. Izlaz.\n1. Kreiranje prazne strukture podataka za graf.\n2. Dodaj cvor.\n3. Ukloni cvor.\n4. Dodaj granu.\n5. Ukloni granu.\n6. Ispisi reprezentaciju grafa.\n7. Izbrisi graf iz memorije.\n");
        scanf("%d",&k);
        switch(k){
            case 0:
                printf("Kraj programa.\n");
                break;
            case 1:
                printf("Unesite zeljenu dimenziju grafa\n");
                scanf("%d",&n);
                p=createGraph(n);
                break;
            case 2:
                printf("Unesite ime cvora koji zelite da dodate (tip int)\n");
                scanf("%d",&name);
                p=addInGraph(p,&n,name);
                printf("%d",n);
                break;
            case 3:
                printf("Unesite ime cvora kojji zelite da izbrisete (tip int)\n");
                scanf("%d",&name);
                p=deleteFromGraph(p,&n,name);
                break;
            case 4:
                printf("Unesite imena cvorova izmdju kojih zelite da dodate granu (tip int)\n");
                scanf("%d %d",&name,&name1);
                p=addEdge(p,name,name1,n);
                break;
            case 5:
                printf("Unesite imena cvorova izmdju kojih zelite da dodate granu (tip int)\n");
                scanf("%d%d",&name,&name1);
                p=deleteEdge(p,name,name1,n);
                break;
            case 6:
                if(p){
                    printGraph(p,n);
                }
                break;
            case 7:
                p=freeGraph(p,n);
                break;
            default:
                printf("Niste uneli odgovarajucu opciju.\n");
                break;

        }


    }
    k=-1;
    int m,s;
    int numberm,numbers;
    while(k!=0)
    {
        printf("---MENI---\n0. Kraj igre.\n1. Zapocni igru.\n2. Ko je pobenik? \n   (Ispisati najmanji potreban broj poteza Maji i Sanji posebno)\n3. Ispisi bar jedan put.\n4. Ispisi sve puteve.\n");
        scanf("%d",&k);
        switch(k){
            case 0:
                printf("Kraj igre.\n");
                break;
            case 1:
                printf("Unesite startno polje i ciljno polje (tip int)\n");
                int start,finish;
                scanf("%d %d",&start,&finish);
                int i,j;
                for(i=0;i<n && p[i].name!=start;i++);
                for(j=0;j<n && p[j].name!=finish;j++);
                if(p[i].name!=start || p[j].name!=finish)
                {
                    start=-1;
                    printf("Takvi cvorovi ne postoje!\n");
                }
                break;
            case 2:

                if(start!=-1)
                {

                    m=maja(p,start,finish,&numberm);
                    s=sanja(p,start,finish,&numbers);
                    if(m==-1)
                    {
                        printf("Maja ne moze da stigne do cilja\n");
                    }
                    else
                    {
                        printf("Maji je potrebno %d poteza da bi stigla do cilja\n",m);
                    }

                    if(s==-1)
                    {
                        printf("Sanja ne moze da stigne do cilja\n");
                    }
                    else
                    {
                        printf("Sanji je potrebno %d poteza da bi stigla do cilja\n",s);
                    }
                    if((m!=-1 && s==-1) || (m!=-1 && s!=-1 && m<s)) printf("Maja je pobednik.\n");
                    else if((s!=-1 && m==-1) || (m!=-1 && s!=-1 && s<m)) printf("Sanja je pobednik.\n");
                    else printf("Nema pobednika.\n");
                }
                else
                {
                    printf("Nije uneto startno i ciljno polje.\n");
                }
                break;
            case 3:
                printf("Maja: \n");
                print1Maja(p,start,finish,n,m);
                printf("Sanja: \n");
                print1Sanja(p,start,finish,n,s);
                printf("%d %d\n",numberm,numbers);
                break;
            case 4:
                printf("Maja: \n");
                printAllMaja(p,start,finish,numberm,m);
                printf("Sanja: \n");
                printAllSanja(p,start,finish,numbers,s);
                break;
        }
    }

    return 0;
}
