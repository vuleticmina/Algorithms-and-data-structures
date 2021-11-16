#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
int info;
struct node* next;
struct node* prev;
}Node;

Node* insert(Node* list, int x)//dodavanje elementa
{
    Node* new=malloc(sizeof(Node));
    if(list==NULL)//ukoliko je lista prazna
    {
        new->info=x;
        new->next=NULL;
        new->prev=NULL;
        return new;
    }
    if(list->info>x)//ukoliko element treba dodati na pocetak
    {
        new->info=x;
        new->next=list;
        new->prev=NULL;
        list->prev=new;
        return new;

    }
    Node* current=list;
    while(1)
    {
        if(current->info==x)//ukoliko x vec postoji u skupu
        {
            return list;
        }
        if(current->info>x)//treba dodati cvor ispred trenutnog
        {
            new->info=x;
            new->next=current;
            new->prev=current->prev;
            (current->prev)->next=new;
            current->prev=new;
            return list;

        }
        if(current->next==NULL)
        {
            new->info=x;
            new->prev=current;
            new->next=NULL;
            current->next=new;
            return list;
        }
        current=current->next;
    }
}
Node* makeList(Node* list)//pravljenje skupa
{
    int x;
    scanf("%d",&x);
    while(x!=-1)
    {
        list=insert(list,x);
        scanf("%d",&x);
    }
    
    return list;
}

Node* delete(Node* list, int x)//brisanje elementa
{
    Node* current=list;
    if(current->info==x && current->next==NULL)
    {
        free(current);
        list=NULL;
        return list;
    }
    if(current->info==x)//potrebno je izbrisati prvi element
    {
        current->next->prev=NULL;
        list=current->next;
        free(current);
        return list;
    }
    while(current->next!=NULL && current->info<x)
    {
        current=current->next;
    }
    if(current->info==x)
    {
        if(current->next==NULL)//Treba obrisati poslednji element
        {
            current->prev->next=NULL;
            free(current);
            return list;
        }
        else//treba obrisati clan koji se ne nalazi ni na pocetku ni na kraju
        {
            current->prev->next=current->next;
            current->next->prev=current->prev;
            free(current);
            return list;
        }
    }
}

Node* deleteList(Node* list)
{
    while(list!=NULL)
    {
        list=delete(list,list->info);
    }
    return list;
}

void printList(Node *list)
{
    Node* current=list;
    while(current!=NULL)
    {
        printf("%d ",current->info);
        current=current->next;
    }
    printf("\n");
    return;
}

int elementOfList(Node* list,int x)//ispitivanje da li je x element skupa
{
    Node* current=list;
    while(current!=NULL)
    {
        if(current->info>x)
        {
            return 0;
        }
        if(current->info==x)
        {
            return 1;
        }
        current=current->next;
    }
    return 0;

}
int cardinality(Node* list)//izracunavanje kardinalnosti
{
    int c=0;
    Node* current=list;
    while(current!=NULL)
    {
        c++;
        current=current->next;
    }
    return c;
}
Node* intersectionOfLists(Node* list1,Node* list2,Node* list3) //operacija presek
{
    while(list1!=NULL && list2!=NULL)
    {
        if(list1->info==list2->info)
        {
            list3=insert(list3,list1->info);
            list1=list1->next;
            list2=list2->next;
        }
        else
        {
            if(list1->info<list2->info)
            {
                list1=list1->next;
            }
            else
            {
                list2=list2->next;
            }
        }
    }
    return list3;
}
Node* unionOflists(Node* list1, Node* list2, Node* list3) //operacija unija
{
    while(list1!=NULL || list2!=NULL)
    {
        if(list2==NULL)
        {
            list3=insert(list3,list1->info);
            list1=list1->next;
        }
        else
        {
            if(list1==NULL)
            {
                list3=insert(list3,list2->info);
                list2=list2->next;
            }
            else
            {
                if(list1->info==list2->info)
                {
                    list3=insert(list3,list1->info);
                    list1=list1->next;
                    list2=list2->next;
                }
                else
                {
                    if(list1->info<list2->info)
                    {
                        list3=insert(list3,list1->info);
                        list1=list1->next;
                    }
                    else
                    {
                        list3=insert(list3,list2->info);
                        list2=list2->next;
                    }
                }
            }
        }
        
    }
    return list3;
}
Node* differenceOfLists(Node* list1, Node* list2, Node* list3)
{
    while(list1!=NULL)
    {
        if(list2==NULL)
        {
            list3=insert(list3,list1->info);
            list1=list1->next;
        }
        else
        {
            if(list1->info<list2->info)
            {
                list3=insert(list3,list1->info);
                list1=list1->next;
            }
            else
            {
                if(list1->info==list2->info)
                {
                    list1=list1->next;
                    list2=list2->next;
                }
                else
                {
                    list2=list2->next;
                }
            }
        }
    }
    return list3;
}
int isSetOk(int k)
{
    return (k>0 && k<6);
}

int main()
{
    int k=0,i=0;
    int set,set1,set2,element;
    Node* array[5];
    for(i=0;i<5;i++)
    {
      array[i]=NULL;
    }
    while(k!=7)
    {
        printf("1. Ucitavanje novog skupa.\n2. Dodavanje clana skupa.\n3. Brisanje clana skupa.\n4. Ispis zadatog skupa.\n5. Operacija.\n6. Brisanje zadatog skupa.\n7. Kraj programa.\nUnesite broj zeljene opcije:\n");
        scanf("%d",&k);
        switch (k)
        {
        case 1: //novi skup
            printf("Unesite koji skup pravite(1-5):\n");
            scanf("%d",&set);
            if(set<6 && set>0)
            {
              if(array[set-1]==NULL)
              {
                array[set-1]=makeList(array[set-1]);
              }
              else
              {
                printf("ERROR! Dati skup je zauzet!\n");
              }
            }
            else
            {
              printf("ERROR! Uneli ste nedozvoljenu vrednost!\n");
            }
            break;
        case 2: //dodavanje el.
            printf("Unesite skup i element za dodavanje:\n");
            scanf("%d%d",&set,&element);
            array[set-1]=insert(array[set-1],element);
            break;
        case 3: //brisanje elementa
            printf("Unesite skup i element za brisanje");
            scanf("%d%d",&set,&element);
            array[set-1]=delete(array[set-1], element);
            break;
        case 4: //ispis skupa
            printf("Unesite skup koji zelite da ispisete:\n");
            scanf("%d",&set);
            printList(array[set-1]);
            break; 
        case 5: //operacije
            printf("1. Provera pripadnosti elementa.\n2. Odredjivanje kardinalnosti skupa.\n3. Unija.\n4. Presek.\n5. Razlika.\nUnesi zeljenu opciju:\n");
            scanf("%d",&k);
            switch (k)
            {
            case 1: //pripadnost
                printf("Unesite skup i element ciju pripadnost zelite da proverite\n");
                scanf("%d%d",&set,&element);
                if(elementOfList(array[set-1],element))
                {
                    printf("Element %d jeste element skupa %d.\n",element,set);
                }
                else
                {
                    printf("Element %d nije element skupa %d.\n",element,set);
                }
                break;
            case 2: //kardinalnost
                printf("Unesite skup ciju kardinalnost zelite da odredite.\n");
                scanf("%d",&set);
                printf("Kardinalnost skupa %d je %d.\n",set,cardinality(array[set-1]));
                break;
            case 3:
                printf("Unesite skupove nad kojima zelite da vrsite operaciju:\n");
                scanf("%d%d",&set,&set1);
                printf("Unesite skup u koji zelite da smestite rezultat:\n");
                scanf("%d",&set2);
                if(array[set2-1]==NULL)
                {
                    array[set2-1]=unionOflists(array[set-1],array[set1-1],array[set2-1]);
                }
                else printf("ERROR! Skup u koji zelite da smestite rezultat je zauzet!\n");
                break;

            case 4:
                printf("Unesite skupove nad kojima zelite da vrsite operaciju:\n");
                scanf("%d%d",&set,&set1);
                printf("Unesite skup u koji zelite da smestite rezultat:\n");
                scanf("%d",&set2);
                if(array[set2-1]==NULL)
                {
                    array[set2-1]=intersectionOfLists(array[set-1],array[set1-1],array[set2-1]);
                }
                else printf("ERROR! Skup u koji zelite da smestite rezultat je zauzet!\n");
                break;
            case 5:
                printf("Unesite skupove nad kojima zelite da vrsite operaciju:\n");
                scanf("%d%d",&set,&set1);
                printf("Unesite skup u koji zelite da smestite rezultat:\n");
                scanf("%d",&set2);
                if(array[set2-1]==NULL)
                {
                    array[set2-1]=differenceOfLists(array[set-1],array[set1-1],array[set2-1]);
                }
                else printf("ERROR! Skup u koji zelite da smestite rezultat je zauzet!\n");
                break;

            default:
                printf("ERROR! Niste uneli ponudjenu opciju.\n");
                break;
            }
            break;
        case 6:
            printf("Unesite koji skup zelite da izbrisete:\n");
            scanf("%d",&set);
            array[set-1]=deleteList(array[set-1]);
            break;
        case 7:
            printf("Kraj programa!\n");
            break;
        default:
            printf("ERROR! Niste uneli ponudjenu opciju.\n");
            break;
        }
    }

}















