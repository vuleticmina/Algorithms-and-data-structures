#include <stdio.h>
#include <stdlib.h>
#define MAX 30


typedef struct student
{
    char name[MAX], surname[MAX], studyProgram[MAX] ;
    int index, year;

}Student;

typedef struct node
{
    Student info;
    struct node* next;
    struct node* prev;

}Node;
typedef struct queue
{
    Node* front;
    Node* rear;
}Queue;

Node* insertInList(Node* list, Student x)//dodavanje studenta u ulancanu listu
{
    Node* new=malloc(sizeof(Node));
    if(list==NULL)//ukoliko je lista prazna
    {
        new->info=x;
        new->next=NULL;
        new->prev=NULL;
        return new;
    }
    else //u suprotnom samo dodajemo element na pocetak liste (kako nije bitan poredak clanova najefikasnije je dodati ga na pocetak)
    {
        new->info=x;
        new->next=list;
        new->prev=NULL;
        list->prev=new;
        return new;

    }
    
}
Node* makeList(Node* list, int * counter)//pravljenje skupa
{
    Student x;
    printf("Studente unosite u formi (ime prezime index studijskiProgram godina).\nZa kraj ucitavanja uneti 0 0 0 0 0\n");
    scanf("%s %s %d %s %d", x.name, x.surname ,&x.index, x.studyProgram, &x.year);
    while(x.index!=0)
    {
      list=insertInList(list,x);
      scanf("%s %s %d %s %d", x.name, x.surname ,&x.index, x.studyProgram, &x.year);
      (*counter)++;
    }
    printf("%d\n", *counter);
    return list;
}
Node* deleteFromList(Node* list, Node* temp)//nema alokacije jer taj element kasnije uvezemo u red
{
    
    if(temp->prev==NULL)//ukoliko se brise prvi clan
    {
        if(temp->next==NULL)//ukoliko je to i jedini clan
        {
            return NULL;
        }
        temp->next->prev=NULL;
        list=temp->next;
        temp->next=NULL;
        return list;
    }
    else if(temp->next==NULL)//ukoliko se brise poslednji clan
    {
        temp->prev->next=NULL;
        temp->prev=NULL;
        return list;
    }
    else
    {
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        temp->next=NULL;
        temp->prev=NULL;
        return list;
    }

}
int empty(Queue* q)//da li je red prazan
{
    if(q->rear==NULL) return 1;
    else return 0;
}
int full(Queue* q, int n)
{
    Node* temp=q->front;
    int counter=0;
    while(temp!=NULL)
    {
        temp=temp->next;
        counter++;
    }
    if (counter==n) return 1;
    else return 0;
}
Student get(Queue* q)
{
    if(empty(q))
    {
        printf("Red je prazan!\n");
    }
    else
    {
        return q->front->info;
    }
}
Queue* insertInQueue(Queue* q, Node* temp)//dodavanje u red
{
    //temp.next i temp.prev su vec postavljeni na null prilikom brisanja iz liste
    if (empty(q))
    {
        q->front=temp;
    }
    else
    {
        temp->prev=q->rear;
        q->rear->next=temp;
    }
    q->rear=temp;
    return q;
}
Queue* addOne(Queue* q, Node* list, int n)
{
    Node* temp=list;
    int r=rand()%n;
    for (int j=0;j<r;j++)
    {
        temp=temp->next;
    }
    list=deleteFromList(list,temp);
    q=insertInQueue(q,temp);
    return q;
}
Queue* addAll(Queue* q, Node* list, int n)
{
    while(n>0)
    {
        q=addOne(q,list,n);
        n--;
    }
    return q;
}
Queue* deleteFromQueue(Queue* q)
{
    Node* p=q->front;
    q->front=p->next;
    if(q->front==NULL)
    {
        q->rear=NULL;
    }
    else
    {
        q->front->prev=NULL;
    }
    free(p);
    return q;

}
Queue* move(Queue* q)//premestanje na kraj reda
{
    //isto kao brisanje samo nema alokacije memorije jer nam je taj cvor potreban jos uvek
    Node* p=q->front;
    q->front=p->next;
    if(q->front==NULL)
    {
        q->rear=NULL;
    }
    else
    {
        q->front->prev=NULL;
    }
    p->next=NULL;
    q=insertInQueue(q,p);
    return q;
}
Queue* admit(Queue* q, double X)
{
    double r=(rand()%100)/100.0;
    if(r>X)
    {
        printf("%s %s %d\n",q->front->info.name, q->front->info.surname,q->front->info.year+1);
        q=deleteFromQueue(q);
    }
    else
    {
        q=move(q);
    }
    return q;


}

void admission(Queue* q, double X)
{
    int counter=0;
    while(empty(q)==0)
    {
        q=admit(q,X);
        counter++;

    }
    printf("Broj izvrsenih koraka simulacije je: %d\n",counter);
}


int main()
{
    int k=0;
    double X;
    Node* list=NULL;
    int counter=0;
    Queue* q=malloc(sizeof(Queue));
    q->front=NULL;
    q->rear=NULL;

    while(k!=4)
    {
        printf("\n---MENI---\n\n1. Ucitavanje studenata.\n2. Premestanje  studenata u red cekanja.\n3. Upis.\n4. Zavrsi program.\nUnesite zeljenu opciju:\n");
        scanf("%d",&k);
        switch (k)
        {
        case 1:
            list=makeList(list, &counter);
            break;
        case 2:
            if(list!=NULL)
            {
                q=addAll(q,list,counter);
                printf("Svi studenti su uspesno dodati u red cekanja\n");
            }
            else 
            {
                printf("ERROR! Studenti jos uvek nisu ucitani\n");
            }
            break;
        case 3:
            if (counter!=0 && full(q,counter))
            {
                printf("Unesite zadati prag:\n");
                if(X>=0 && X<=0.5)
                {
                    scanf("%lf",&X);
                    admission(q,X);
                }
                else printf("ERROR! Niste uneli odgovarajuc prag!\n");
            }
            else printf("ERROR! Studenti nisu ucitani ili studenti nisu prebaceni u red cekanja\n");
            break;
        case 4:
            printf("Kraj programa.\n");
            break;
        default:
            printf("ERROR! Niste uneli odgovarajucu vrednost.\n");
            break;
        }


    }

}


