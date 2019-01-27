
#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<conio.h>
#include <ctime>
#include<fstream>
using namespace std;
const int R = 20;
const int C = 40;
struct snake
{
	int x;
	int y;
	char value;
	snake *next;
};
snake *create(int x,int y,char v)
{
	snake *ptr=new snake;
	ptr->x=x;
	ptr->y=y;
	ptr->value=v;
	ptr->next=NULL;
	return ptr;
}
void insert(snake **t,int x,int y)
{
    snake *p=*t;
    snake *temp;
    temp=create(x,y,'=');
    if(*t==NULL)
    {
        *t=temp;
        (*t)->value='H';
    }
    else
    {
        p=(*t);
        while(p->next!=NULL)
        {
            p=p->next;
        }
        p->next=temp;
        if(p!=(*t))
            p->value='=';
        temp->value='T';
    }

}
void create_board(char *board)
{
    int i,j;
	for(i=0;i<R;i++)
    {
        for(j=0;j<C;j++)
        {
            if(i==0||i==R-1||j==0||j==C-1)
                board[i*C+j]='*';
            else
                board[i*C+j]=' ';
        }
    }
}
void display(char board[R][C])
{
	int i,j;
	for(i=0;i<R;i++)
	{
		for(j=0;j<C;j++)
		{
			printf("%c ",board[i][j]);
		}
		printf("\n");
	}
}
void put_snake(char *board,snake *t,int x,int y,int a,int b,int flag)
{
    while(t!=NULL)
    {
        board[(t->x)*C+(t->y)]=(t->value);
        t=t->next;
    }
    if(flag==0)
    {
    board[x*C+y]='+';
    }
    board[a*C+b]='-';
}
void right(snake **t)
{
    snake *p=(*t);
    snake *w=(*t);
    int x,y,temp;
    w=w->next;
    if(p->y+1!=w->y)
    {
    x=(p->x);
    y=(p->y)+1;
    if(y==C)
        y=1;
    while(p!=NULL)
    {
    	temp=(p->x);
    	p->x=x;
    	x=temp;
    	temp=(p->y);
    	p->y=y;
    	y=temp;
    	p=p->next;
	}
    }
}
void down(snake **t)
{
    snake *p=(*t);
    snake *w=(*t);
    int x,y,temp;
    w=w->next;
    if(p->x+1!=w->x)
    {
    x=(p->x)+1;
    y=(p->y);
    if(x==R)
        x=1;
    while(p!=NULL)
    {
    	temp=(p->x);
    	p->x=x;
    	x=temp;
    	temp=(p->y);
    	p->y=y;
    	y=temp;
    	p=p->next;
	}
    }
}
void up(snake **t)
{
    snake *p=(*t);
    snake *w=(*t);
    int x,y,temp;
    w=w->next;
    if(p->x-1!=w->x)
    {
    x=(p->x)-1;
    y=(p->y);
    if(x==0)
        x=R-2;
    while(p!=NULL)
    {
    	temp=(p->x);
    	p->x=x;
    	x=temp;
    	temp=(p->y);
    	p->y=y;
    	y=temp;
    	p=p->next;
	}
    }
}
void left(snake **t)
{

    snake *p=(*t);
    snake *w=(*t);
    int x,y,temp;
    w=w->next;
    if(p->y-1!=w->y)
    {
    x=(p->x);
    y=(p->y)-1;
    if(y==0)
        y=C-2;
    while(p!=NULL)
    {
    	temp=(p->x);
    	p->x=x;
    	x=temp;
    	temp=(p->y);
    	p->y=y;
    	y=temp;
    	p=p->next;
	}
    }
}
void food(int *x,int *y)
{
    *x = (1 + (rand() % (int)((R-1) - 1 + 1)));
    *y = (1 + (rand() % (int)((C-1) - 1 + 1)));
}
void poison(int *a,int *b)
{
    *a = (1 + (rand() % (int)((R-1) - 1 + 1)));
    *b = (1 + (rand() % (int)((C-1) - 1 + 1)));
}
void grow(snake **t,char c)
{
    snake *p,*temp;
    p=*t;
    if(c=='w'||c=='W')
    temp=create(p->x-1,p->y,'=');
    else if(c=='d'||c=='D')
    temp=create(p->x,p->y+1,'=');
    else if(c=='a'||c=='A')
    temp=create(p->x,p->y-1,'=');
    else if(c=='s'||c=='S')
    temp=create(p->x+1,p->y,'=');
    temp->next=*t;
    (*t)->value='=';
    *t=temp;
    (*t)->value='H';
}
int suicide(snake **t)
{
    snake *p,*temp;
    p=*t;
    temp=*t;
    p=p->next;
    while(p!=NULL)
    {
        if(p->x==temp->x&&p->y==temp->y)
            return 1;
        p=p->next;
    }
   return 0;
}
int menu()
{
    int n;
    system("cls");
    printf("-----------World of Snake-----------\n");
    printf("-----------Select  Option-----------\n");
    printf("1.New Game\n");
    printf("2.Load Save Game\n");
    scanf("%d",&n);
    return n;
}
int main()
{
    int choice=menu();
    int i,fx,fy,x,y,px,py,v,flag=0,points=0,count=0;
    char input;
	snake *head=NULL;
	snake *t;
	char board[R][C];
	fstream f;
    switch(choice)
    {
        case 1:for(i=4;i>0;i--)
               insert(&head,2,i);
               food(&fx,&fy);
               poison(&px,&py);
               break;
        case 2: f.open("Save1.txt",ios::in);
                f>>points;
                f>>count;
                f>>fx;
                f>>fy;
                f>>px;
                f>>py;
                while(!f.eof())
                {
                    f>>x;
                    f>>y;
                    insert(&head,x,y);
                }
                break;
        default: system("cls");
                 printf("Invalid choice !! Please Enter Again\n");
                 getch();
                 choice=menu();
    }
	create_board((char *)board);
    put_snake((char *)board,head,fx,fy,px,py,flag);
    system("cls");
    display(board);
    input=getch();
    while(input!='q'&&input!='Q')
    {
        count++;
        if(input=='d'||input=='D')
        {
            right(&head);
        }
        else if(input=='s'||input=='S')
        {
            down(&head);
        }
        else if(input=='w'||input=='W')
        {
            up(&head);
        }
        else if(input=='a'||input=='A')
        {
            left(&head);
        }
            create_board((char *)board);
            if(head->x==fx&&head->y==fy)
            {
                points++;
            flag=1;
            food(&fx,&fy);
            grow(&head,input);
            }
            if(head->x==px&&head->y==py)
            {
                count=0;
                poison(&px,&py);
                if(head->next==NULL)
                {
                    system("cls");
                    printf("Game Over\n");
                    printf("Too Much Poison is Injurious To Health......\n");
                    exit(1);
                }
                head=head->next;
                head->value='H';
            }
            if(suicide(&head))
            {
                system("cls");
                printf("Game Over\n");
                printf("Your Score is %d",points);
                getch();
             exit(1);
            }
            put_snake((char *)board,head,fx,fy,px,py,flag);
            flag=0;
            system("cls");
            display(board);
            input=getch();
            if(count==10)
            {
                poison(&px,&py);
                count=0;
            }
    }
    if(input=='Q'||input=='q')
    {
        f.open("Save1.txt",ios::out);
        f<<points;
        f<<'\n';
        f<<count;
        f<<'\n';
        f<<fx;
        f<<'\n';
        f<<fy;
        f<<'\n';
        f<<px;
        f<<'\n';
        f<<py;
        f<<'\n';
        t=head;
        while(t!=NULL)
        {
            f<<t->x;
            f<<'\n';
            f<<t->y;
            f<<'\n';
            t=t->next;
        }
        f.close();
    }
	return 0;
}
