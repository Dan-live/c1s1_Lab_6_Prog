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

char str[255];// розмір масива чисел першого завдання


HANDLE hConsole;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void gotoxy(int X, int Y)
{
    COORD coord = { X, Y };
    SetConsoleCursorPosition(hStdOut, coord);  //функція переміщення курсора по Х і У
}

void SetColor(int text, int background)
{
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text)); //атрибути для шрифта і кольору символів в консолі
}
short regim;

void frame (int x1, int y1, int x2, int y2)   //рамка
{
    int i;
    gotoxy(x1,y1);
    cout << '\311';;// верхній лівий куточок
    for (i=(x1+1); i<=(x2-1); i++) cout <<'\315';// подвійна горизонталь
    cout << '\273';// правий верхній куточок
    for (i=(y1+1); i<=(y2-1); i++)
    {
        gotoxy(x1,i);
        cout << '\272';// подвійна вертикальна
        gotoxy(x2,i);
        cout << '\272';
    }
    gotoxy(x1, y2);
    cout << '\310';

    for (i=(x1+1); i<=(x2-1); i++)
        cout << '\315';// подвійна горизонталь
    cout << '\274';// правий нижній куточок
    return ;
} //frame()

void zastavka ()
{
    system ("cls");
    frame (10,5,70,18);
    gotoxy(34,8);
    cout << "Лабораторна робота"<<endl;
    gotoxy(33, 10);
    cout << "  з програмування"<< endl;
    gotoxy(35, 12);
    cout << "  Варiант 5" << endl;
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

    cout << " За допомогою q та a виберiть режим та натиснiть enter"<< endl;
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
    int  V[255];// кількість символів ,по аскі коду є індексами,  в слові
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
                if(str[j] == (char)i/*не явне
                   перетворення типа
                    бо інт бвльший за чар*/)
                {
                    for ( int k = j; k <= strlen(str)-1; k++)
                    {
                        str[k]= str[k+1];
                    }
                    countRem++;
                    f--;//ззсув кінця
                    j--;//для того , щоб залишатися на тій же самій позіції

                }
            }


        }
        if(V[i] > 8)
        {

            int countRem = 0 ;//лічильник видалених символів
            for ( int j = f; j >= st&&countRem <3; j--)
            {
                if(str[j] == (char)i/*не явне
                   перетворення типа
                    бо інт бвльший за чар*/)
                {
                    for ( int k = j; k <= strlen(str)-1; k++)
                    {
                        str[k]= str[k+1];
                    }
                    countRem++;
                    f--;//ззсув кінця
                    //j++;//для того , щоб залишатися на тій же самій позіції

                }
            }

        }


    }
    return f;
}

void view_b ()
{
    printf("Введiть строку : ");
    gets(str);
    int st =0 ;//індекс початку слова
    int f =0;//індекс кінця слова
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

// Главный цикл приложения: выполняется, пока открыто окно
    while (window.isOpen())
    {
        // Обрабатываем очередь событий в цикле
        Event event;
        while (window.pollEvent(event))
        {
            // Пользователь нажал на «крестик» и хочет закрыть окно?
            if (event.type == Event::Closed)
                window.close(); // тогда закрываем его
        }
        // Установка цвета фона
        window.clear(Color(250, 220, 100, 0));

        // Создаем фигуру - круг радиусом 50
        //  CircleShape circle(50.f);
        RectangleShape rectangle(Vector2f(120, 10));

        // Закрашиваем наш круг
        rectangle.setFillColor(Color(82, 240, 50));
        rectangle.setPosition(50, 50);
        //rectangle.setRotation(90);


        // Отрисовка линии
        window.draw(rectangle);

        rectangle.setPosition(50, 160);
        window.draw(rectangle);

        rectangle.setRotation(-43.5);
        rectangle.setSize(Vector2f(155, 10));
        window.draw(rectangle);
        // Отрисовка окна
        window.display();
    }




    //system ("cls");
}

void d3_litera ()
{
    RenderWindow window(VideoMode(200, 200), "SFML Works!");

// Главный цикл приложения: выполняется, пока открыто окно
    while (window.isOpen())
    {
        // Обрабатываем очередь событий в цикле
        Event event;
        while (window.pollEvent(event))
        {
            // Пользователь нажал на «крестик» и хочет закрыть окно?
            if (event.type == Event::Closed)
                window.close(); // тогда закрываем его
        }
        // Установка цвета фона
        window.clear(Color(0, 0, 100, 0));



        // Создаем фигуру - круг радиусом 50
        //  CircleShape circle(50.f);

        RectangleShape rectangle(Vector2f(120, 10));

        // Закрашиваем наш круг
        rectangle.setFillColor(Color(82, 240, 50));
        rectangle.setPosition(50, 50);
        //rectangle.setRotation(90);


        // Отрисовка линии
        window.draw(rectangle);

        rectangle.setPosition(50, 160);
        window.draw(rectangle);

        rectangle.setRotation(-43.5);
        rectangle.setSize(Vector2f(155, 10));
        window.draw(rectangle);
        // Отрисовка окна


         // создаём пустую фигуру
        ConvexShape convex;

// изменяем размер на 5 вершин
        convex.setPointCount(4);
        convex.setFillColor(Color(25, 71, 7));
        // определяем вершины
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


    char* locale = setlocale(LC_ALL, "");// налаштувння кодування для кирилиці
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
