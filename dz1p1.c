#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
int info;
struct node* next;
struct node* prev;
}Node;

Node* insert(Node* list, int x)
{
    Node* new=malloc(sizeof(Node));
    if(list==NULL)
    {
        new->info=x;
        new->next=NULL;
        new->prev=NULL;
        return new;
    }
    if(list->info>x)
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
        if(current->info==x)
        {
            return list;
        }
        if(current->info>x)
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
Node* makeList(Node* list)
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

Node* delete(Node* list, int x)
{
    Node* current=list;
    if(current->info==x && current->next==NULL)
    {
        free(current);
        list=NULL;
        return list;
    }
    if(current->info==x)
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
        if(current->next==NULL)
        {
            current->prev->next=NULL;
            free(current);
            return list;
        }
        else
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

int elementOfList(Node* list,int x)
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
int cardinality(Node* list)
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
Node* intersectionOfLists(Node* list1,Node* list2,Node* list3)
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
Node* unionOflists(Node* list1, Node* list2, Node* list3)
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
        printf("1. Enter new set.\n2. Add new element.\n3. Delete one element.\n4. Print set.\n5. Operations.\n6. Delete set.\n7. End of program.\nEnter option:\n");
        scanf("%d",&k);
        switch (k)
        {
        case 1:
            printf("Enter set which you want to create(1-5):\n");
            scanf("%d",&set);
            if(set<6 && set>0)
            {
              if(array[set-1]==NULL)
              {
                array[set-1]=makeList(array[set-1]);
              }
              else
              {
                printf("ERROR! The set already exists!\n");
              }
            }
            else
            {
              printf("ERROR! Invalid value!\n");
            }
            break;
        case 2:
            printf("Enter set and element you want to add:\n");
            scanf("%d%d",&set,&element);
            array[set-1]=insert(array[set-1],element);
            break;
        case 3:
            printf("Enter set and element you want to delete:\n");
            scanf("%d%d",&set,&element);
            array[set-1]=delete(array[set-1], element);
            break;
        case 4:
            printf("Enter set you want to print:\n");
            scanf("%d",&set);
            printList(array[set-1]);
            break; 
        case 5:
            printf("1. Check if element is in set.\n2. Find number of elements.\n3. Union.\n4. Intersection.\n5. Difference.\nEnter option:\n");
            scanf("%d",&k);
            switch (k)
            {
            case 1: /
                printf("Enter set and element you want to check\n");
                scanf("%d%d",&set,&element);
                if(elementOfList(array[set-1],element))
                {
                    printf("Element %d is element of set %d.\n",element,set);
                }
                else
                {
                    printf("Element %d is not element of set %d.\n",element,set);
                }
                break;
            case 2:
                printf("Enter set.\n");
                scanf("%d",&set);
                printf("Number of elements of set %d is %d.\n",set,cardinality(array[set-1]));
                break;
            case 3:
                printf("Enter sets on which you want to operate:\n");
                scanf("%d%d",&set,&set1);
                printf("Enter set where you want to save the result:\n");
                scanf("%d",&set2);
                if(array[set2-1]==NULL)
                {
                    array[set2-1]=unionOflists(array[set-1],array[set1-1],array[set2-1]);
                }
                else printf("ERROR! The set where you want to save the result is taken!\n");
                break;

            case 4:
                printf("Enter sets on which you want to operate:\n");
                scanf("%d%d",&set,&set1);
                printf("Enter set where you want to save the result:\n");
                scanf("%d",&set2);
                if(array[set2-1]==NULL)
                {
                    array[set2-1]=intersectionOfLists(array[set-1],array[set1-1],array[set2-1]);
                }
                else printf("ERROR! The set where you want to save the result is taken!\n");
                break;
            case 5:
                printf("Enter sets on which you want to operate:\n");
                scanf("%d%d",&set,&set1);
                printf("Enter set where you want to save the result:\n");
                scanf("%d",&set2);
                if(array[set2-1]==NULL)
                {
                    array[set2-1]=differenceOfLists(array[set-1],array[set1-1],array[set2-1]);
                }
                else printf("ERROR! The set where you want to save the result is taken!\n");
                break;

            default:
                printf("ERROR! Invalid option.\n");
                break;
            }
            break;
        case 6:
            printf("Enter set you want to delete:\n");
            scanf("%d",&set);
            array[set-1]=deleteList(array[set-1]);
            break;
        case 7:
            printf("End of program!\n");
            break;
        default:
            printf("ERROR! Invalid option.\n");
            break;
        }
    }

}















