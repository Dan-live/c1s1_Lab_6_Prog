#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
using namespace sf;
using namespace std;

char str[255];// ����� ������ ����� ������� ��������


HANDLE hConsole;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void gotoxy(int X, int Y)
{
    COORD coord = { X, Y };
    SetConsoleCursorPosition(hStdOut, coord);  //������� ���������� ������� �� � � �
}

void SetColor(int text, int background)
{
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text)); //�������� ��� ������ � ������� ������� � ������
}
short regim;

void frame (int x1, int y1, int x2, int y2)   //�����
{
    int i;
    gotoxy(x1,y1);
    cout << '\311';;// ������ ���� �������
    for (i=(x1+1); i<=(x2-1); i++) cout <<'\315';// ������� �����������
    cout << '\273';// ������ ������ �������
    for (i=(y1+1); i<=(y2-1); i++)
    {
        gotoxy(x1,i);
        cout << '\272';// ������� �����������
        gotoxy(x2,i);
        cout << '\272';
    }
    gotoxy(x1, y2);
    cout << '\310';

    for (i=(x1+1); i<=(x2-1); i++)
        cout << '\315';// ������� �����������
    cout << '\274';// ������ ����� �������
    return ;
} //frame()

void zastavka ()
{
    system ("cls");
    frame (10,5,70,18);
    gotoxy(34,8);
    cout << "����������� ������"<<endl;
    gotoxy(33, 10);
    cout << "  � �������������"<< endl;
    gotoxy(35, 12);
    cout << "  ���i��� 5" << endl;
    gotoxy(35, 17);
    cout << "  Kyiv 2021"<< endl;
    Sleep(500);
    system ("cls");
    return ;
} // zastavka()


int vert_menu (int k1, int k2, int kp)
{
    const int kilk=4;
    typedef   char punkt[17] ;
    punkt m [kilk]= {"1. View Base  ", "2. Add record ", "3. Delete record", "4. Exit"};

    char ch;
    int i;

    for ( i=0; i<kp; i++)
    {
        gotoxy(33,6+i);
        cout <<(m[i])<<endl;
    }

    cout << " �� ��������� q �� a �����i�� ����� �� ������i�� enter"<< endl;
    i=0;
    while (1)
    {
        ch=_getch();
        if (ch=='\15')
        {
            return i;
        }
        if (ch=='\161')
        {
            gotoxy(k1, k2+i+1);
            SetColor(7,0);
            cout << m[i];
            i++;
            if (i==kp)
            {
                i=0;
                SetColor(7,0);
                gotoxy (k1,k2+i+1);
                SetColor(0,7);
                cout << m[i];
            }// if
            gotoxy(k1, k2+i+1);
            SetColor(0,7);
            cout << m[i];
            SetColor(7,0);
        }
        if ( ch=='\141')
        {
            gotoxy(k1,k2+i+1);
            SetColor(7,0);
            cout << m[i];
            i--;
            if (i<0)
            {
                i=kp-1;
                SetColor(7,0);
                gotoxy (k1,k2+i+1);
                SetColor(0,7);
                cout << m[i];
            }

            gotoxy(k1, k2+i+1);
            SetColor(0,7);
            cout << m[i];
            SetColor(7,0);
        } // case 110
    }// while
    return i;
}// vert menu()

int zsuv( int st, int f)
{
    int  V[255];// ������� ������� ,�� ��� ���� � ���������,  � ����
    for (int i = 0; i <= 255; i++)
    {
        V[i] = 0;
    }
    for (int i = st; i <= f; i++)
    {
        V[str[i]]++;//
    }
    for (int i = 0; i <= 255; i++)
    {
        if (V[i] >= 4 && V[i] <=8)
        {
            int countRem = 0;
            for ( int j = st; j <= f&&countRem <3; j++)
            {
                if(str[j] == (char)i/*�� ����
                   ������������ ����
                    �� ��� ������� �� ���*/)
                {
                    for ( int k = j; k <= strlen(str)-1; k++)
                    {
                        str[k]= str[k+1];
                    }
                    countRem++;
                    f--;//����� ����
                    j--;//��� ���� , ��� ���������� �� �� �� ���� ������

                }
            }


        }
        if(V[i] > 8)
        {

            int countRem = 0 ;//�������� ��������� �������
            for ( int j = f; j >= st&&countRem <3; j--)
            {
                if(str[j] == (char)i/*�� ����
                   ������������ ����
                    �� ��� ������� �� ���*/)
                {
                    for ( int k = j; k <= strlen(str)-1; k++)
                    {
                        str[k]= str[k+1];
                    }
                    countRem++;
                    f--;//����� ����
                    //j++;//��� ���� , ��� ���������� �� �� �� ���� ������

                }
            }

        }


    }
    return f;
}

void view_b ()
{
    printf("����i�� ������ : ");
    gets(str);
    int st =0 ;//������ ������� �����
    int f =0;//������ ���� �����
    for(int  i =1; i <= strlen(str); i++)
    {
        if ((str[i]==' ' || str[i]=='\0' )  && str[i-1]!=' ' )
        {
            f=i-1;
            f = zsuv(st, f);
            i = f+1;
        }
        if (str[i]!=' '  && str[i-1]==' '  )
        {
            st = i;

        }
    }
    puts(str);
    getch();
    system ("cls");

}






void d2_litera ()
{
    RenderWindow window(VideoMode(200, 200), "SFML Works!");

// ������� ���� ����������: �����������, ���� ������� ����
    while (window.isOpen())
    {
        // ������������ ������� ������� � �����
        Event event;
        while (window.pollEvent(event))
        {
            // ������������ ����� �� �������� � ����� ������� ����?
            if (event.type == Event::Closed)
                window.close(); // ����� ��������� ���
        }
        // ��������� ����� ����
        window.clear(Color(250, 220, 100, 0));

        // ������� ������ - ���� �������� 50
        //  CircleShape circle(50.f);
        RectangleShape rectangle(Vector2f(120, 10));

        // ����������� ��� ����
        rectangle.setFillColor(Color(82, 240, 50));
        rectangle.setPosition(50, 50);
        //rectangle.setRotation(90);


        // ��������� �����
        window.draw(rectangle);

        rectangle.setPosition(50, 160);
        window.draw(rectangle);

        rectangle.setRotation(-43.5);
        rectangle.setSize(Vector2f(155, 10));
        window.draw(rectangle);
        // ��������� ����
        window.display();
    }




    //system ("cls");
}

void d3_litera ()
{
    RenderWindow window(VideoMode(200, 200), "SFML Works!");

// ������� ���� ����������: �����������, ���� ������� ����
    while (window.isOpen())
    {
        // ������������ ������� ������� � �����
        Event event;
        while (window.pollEvent(event))
        {
            // ������������ ����� �� �������� � ����� ������� ����?
            if (event.type == Event::Closed)
                window.close(); // ����� ��������� ���
        }
        // ��������� ����� ����
        window.clear(Color(0, 0, 100, 0));



        // ������� ������ - ���� �������� 50
        //  CircleShape circle(50.f);

        RectangleShape rectangle(Vector2f(120, 10));

        // ����������� ��� ����
        rectangle.setFillColor(Color(82, 240, 50));
        rectangle.setPosition(50, 50);
        //rectangle.setRotation(90);


        // ��������� �����
        window.draw(rectangle);

        rectangle.setPosition(50, 160);
        window.draw(rectangle);

        rectangle.setRotation(-43.5);
        rectangle.setSize(Vector2f(155, 10));
        window.draw(rectangle);
        // ��������� ����


         // ������ ������ ������
        ConvexShape convex;

// �������� ������ �� 5 ������
        convex.setPointCount(4);
        convex.setFillColor(Color(25, 71, 7));
        // ���������� �������
        convex.setPoint(0, Vector2f(56, 50));
        convex.setPoint(1, Vector2f(75, 45));
        convex.setPoint(2, Vector2f(185, 45));
        convex.setPoint(3, Vector2f(169, 50));
//convex.setPoint(4, Vector2f(0, 50));


        convex.setOutlineColor(Color(60, 80, 60));
        convex.setOutlineThickness(1);
        window.draw(convex);

        convex.setPoint(0, Vector2f(170, 50));
        convex.setPoint(1, Vector2f(190, 45));
        convex.setPoint(2, Vector2f(190, 55));
        convex.setPoint(3, Vector2f(170, 60));
        window.draw(convex);


        convex.setPoint(0, Vector2f(170, 60));
        convex.setPoint(1, Vector2f(188, 57));
        convex.setPoint(2, Vector2f(84, 155));
        convex.setPoint(3, Vector2f(64 , 160));
        window.draw(convex);

        convex.setPoint(0, Vector2f(84, 155));
        convex.setPoint(1, Vector2f(64, 160));
        convex.setPoint(2, Vector2f(170, 160));
        convex.setPoint(3, Vector2f(184 , 155));
        window.draw(convex);


        convex.setPoint(0, Vector2f(170, 160));
        convex.setPoint(1, Vector2f(190, 155));
        convex.setPoint(2, Vector2f(190, 165));
        convex.setPoint(3, Vector2f(170 , 170));
        window.draw(convex);

        window.display();
    }




}

int main ()
{


    char* locale = setlocale(LC_ALL, "");// ����������� ��������� ��� ��������
    int n;
//d3_litera();

    zastavka();
    system ("cls");
    while (1)
    {
        system ("cls");
        gotoxy(35,4);
        cout << "MAIN MENU";
        regim=vert_menu(33,5,4);
        switch (regim)
        {
        case 0:
            system ("cls");
            view_b();
            break;
        case 1:
            d2_litera();
            break;
        case 2:
            d3_litera();
            break;
        case 3:
        {
            system ("cls");
            return 0;
        }
        } //switch
    } // while;
    return 0;
} // main ()
