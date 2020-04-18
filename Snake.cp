//
//  main.cpp
//  fgg
//
//  Created by mac on 13/02/19.
//  Copyright © 2019 macAAA. All rights reserved.
//
#include <iostream>
#include <thread>
#include <time.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fstream>

int getch(void) {
    
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return ch;
}

using namespace std;

int disp[20][20],head[2]={10,10};
int x[100],y[100],px=0,py=0,l=0,size =3,dir=3,score = 0,t = 0,sp=0,tm= 100000;
bool flag=false,rea=false;

char ch='d';

int fileexists(){
    FILE *file;
    if ((file = fopen("snake.txt", "r"))){
        fclose(file);
        return 1;
    }
    return 0;
}
void save()
{
    ofstream f;
    f.open("snake.txt",ios::beg);
    for(int i =0;i<20;i++)
    {
        for(int j =0;j<20;j++)
        {
            f<<disp[i][j] << "\n";
        }
    }
    f<<head[0]<<"\n"<<head[1]<<"\n"<<size<<"\n";
    for(int i =0;i<=size;i++)
        f<<x[i]<<"\n";
    for(int i =0;i<=size;i++)
        f<<y[i]<<"\n";
    f<<dir<<"\n"<<score<<"\n"<<sp<<"\n"<<tm<<"\n"<<flag<<"\n"<<EOF;
}

void read()
{
    ifstream f;
        f.open("snake.txt");
        for(int i =0;i<20;i++)
        {
            for(int j =0;j<20;j++)
            {
                f>>disp[i][j];
            }
        }
        f>>head[0]>>head[1]>>size;
        for(int i =0;i<=size;i++)
            f>>x[i];
        for(int i =0;i<=size;i++)
            f>>y[i];
        f>>dir>>score>>sp>>tm>>flag;
    }
int menu()
{
    int n = 0;
    cout << "\t\t\t\tSNAKE\n\n\n\n";
    cout << "1.New Game" << endl << "2.Speed" << endl << "Choose Option (1 or 2) : ";
    cin >> n;
    while((n!=1)&&(n!=2))
    {
        cout << "\nEnter a Correct Option (1,2) : ";
        cin >> n;
    }
    return n;
}
int menu2()
{int n = 0;
    cout << "\t\t\t\tSNAKE\n\n\n\n";
    cout << "1.New Game" << endl << "2.Speed" << endl<<"3.Continue"<<endl<<"Choose Option (1 or 2 or 3) : ";
    cin >> n;
    while(((n!=1)&&(n!=2))&&(n!=3))
    {
        cout << "\nEnter a Correct Option (1,2,3) : ";
        cin >> n;
    }

    return n;
}

void speed()
{
    cout << "Choose speed between 1 and 10 : ";
    cin >> sp;
    while((sp>10)||(sp<1))
    {
        cout << "Please choose speed between 1 and 10 : ";
        cin >> sp;
    }
}

void spch()
{
    switch(sp)
    {
        case 1:
            tm = 2000000;
            break;
        case 2:
            tm = 1900000;
            break;
        case 3:
            tm = 1800000;
            break;

        case 4:
            tm = 1700000;
            break;

        case 5:
            tm = 1600000;
            break;

        case 6:
            tm = 1500000;
            break;

        case 7:
            tm = 1400000;
            break;

        case 8:
            tm = 1300000;
            break;

        case 9:
            tm = 1200000;
            break;

        case 10:
            tm = 1000000;
            break;
    }
}

void clear()
{
    for(int i = 0;i<25;i++)
        cout << '\n';
}

void display1()
{
    t = 1;
    usleep(10000);
    ch ='a';
    for(int i =0; i<20; i++)
        cout << "\n";
    cout << "\t\tYour score :" <<score;
    for(int i =0; i<10; i++)
        cout << "\n";
    exit(0);
}

void die()
{
    for(;;)
    {
        for(int i=0;i<(size-4);i++)
        {
            if((head[0]==x[i])&&(head[1]==y[i]))
            {
                display1();
            }
        }
    }
}

void d1()
{
    for(int i = 0;i<22;i++)
        cout<<"#";
    cout <<endl;
}

void display()
{
    d1();
    for(int i =0; i<20;i++)
    {
        cout <<"#";
        for(int j=0;j<20;j++)
        {
            if(disp[i][j]==0)
            {
                cout << " ";
            }
            else if(disp[i][j]==2)
            {
                cout << "@";
            }
            else
                cout << "*";
        }
        cout <<"#" <<  endl;
    }
    d1();
}
int rno()
{
    srand((int)time(0));
    return rand()%20;
}

int rno1()
{
    srand(x[0]);
    return rand()%20;
}

int ch1(int px,int py)
{
    int r =0;
    for(int i = 0;i<=size;i++)
    {
        if((x[i]==px)&&(y[i]==py))
            r++;
    }
    return r;
}

void update()
{
    for(int i =0;i<20;i++)
    {
        for(int j =0;j<20;j++)
        {
            disp[i][j]=0;
        }
    }
    for(int i =0;i<=size;i++)
    {
        disp[x[i]][y[i]]=1;
    }
    if(l!=0)
        disp[px][py]=2;
}

void pellets()
{
    for(;;)
    {
        if (t==0)
        {
            if(l==0)
            {
                px = rno();
                py = rno1();
                if(ch1(px,py)>0)
                {
                    px = rno();
                    py = rno1();
                    continue;
                }
                disp[px][py]=2;
                display();
                l=1;
            }
        }
    }
}
void eat()
{
    for(;;)
    {
        if( t == 0)
        {
            if((head[0]==px)&&(head[1]==py))
            {
                l=0;
                update();
                display();
                size++;
                x[size]=x[size-1];
                y[size]=y[size-1];
                update();
                display();
                score += 8;
                usleep(1000);
            }
        }
    }
}


void generate2()
{
    for(int i =0; i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            disp[i][j]=0;
        }
    }
    size = 3;
    t=0;
    x[0]=7;
    x[1]=8;
    x[2]=9;
    x[3]=10;
    y[0]=10;
    y[1]=10;
    y[2]=10;
    y[3]=10;
    update();
}

void move()
{
    int w = 0;
    for(int i =1;i<=size;i++)
    {
        x[i-1]=x[i];
        y[i-1]=y[i];
        w++;
    }
    x[w]=head[0];
    y[w]=head[1];
    update();
    display();
}

void snake_move_auto()
{
    for(;;)
    {
        if( t==0)
        {
            ch = getch();
            if((ch == 'd')&&((dir==2)||(dir==5)))
            {
                disp[head[0]][head[1]] = 0;
                if((head[1]+1)>19)
                    head[1]=-1;
                disp[head[0]][(head[1]+1)]=1;
                head[1] +=1;
                dir =3;
                move();
            }
            else if((ch == 'a')&&((dir==2)||(dir==5)))
            {
                disp[head[0]][head[1]] = 0;
                if((head[1]-1)<0)
                    head[1]=20;
                disp[head[0]][(head[1]-1)]=1;
                head[1] -=1;
                dir =1;
                move();
            }
            else  if((ch=='w')&&((dir==1)||(dir ==3)))
            {
                disp[head[0]][head[1]] = 0;
                if((head[0]-1)<0)
                    head[0]=20;
                disp[(head[0]-1)][head[1]]=1;
                head[0] -=1;
                dir =5;
                move();
            }
            else  if((ch=='s')&&((dir==1)||(dir ==3)))
            {
                disp[head[0]][head[1]] = 0;
                if((head[0]+1)>19)
                    head[0]=-1;
                disp[(head[0]+1)][head[1]]=1;
                head[0] +=1;
                dir = 2;
                move();
            }
            display();
        }
    }
}

void move1()
{
    for(;;)
    {
        if(t == 0)
        {
            usleep(tm);
            if(dir == 3)
            {
                disp[head[0]][head[1]] = 0;
                if((head[1]+1)>19)
                    head[1]=-1;
                disp[head[0]][(head[1]+1)]=1;
                head[1] +=1;
                dir = 3;
                move();
            }
            else if(dir == 2)
            {
                disp[head[0]][head[1]] = 0;
                if((head[0]+1)>19)
                    head[0]=-1;
                disp[(head[0]+1)][head[1]]=1;
                head[0] +=1;
                dir =2;
                move();
            }
            else if(dir == 1)
            {
                disp[head[0]][head[1]] = 0;
                if((head[1]-1)<0)
                    head[1]=20;
                disp[head[0]][(head[1]-1)]=1;
                head[1] -=1;
                dir =1;
                move();
            }
            else if(dir == 5)
            {
                disp[head[0]][head[1]] = 0;
                if((head[0]-1)<0)
                    head[0]=20;
                disp[(head[0]-1)][head[1]]=1;
                head[0] -=1;
                dir = 5;
                move();
            }
            display();
        }
    }
}
void check()
{
    for(;;)
    {
        if(ch=='e')
        {
            save();
            display1();
            exit(30);
        }
    }
}

int main()
{
    cout << "hi";
    generate2();
    if(fileexists())
    {
        rea = true;
    }
    else
        rea = false;
    if(rea)
    {
        if(menu2()==2)
        {
        do
        {
            clear();
            speed();
            clear();
        }
            while(menu2()==2);}
        else if(menu2()==3)
            read();
    }
    else
    {
    while(menu()==2)
    {
        clear();
        speed();
        clear();
    }
    }
    
    thread t1(snake_move_auto);
    thread t2(move1);
    thread t5(eat);
    thread t6(die);
    thread t3(check);
    thread t4(pellets);
    t2.join();
    t1.join();
    t5.join();
    t6.join();
    t3.join();
    t4.join();
    return 0;
}
