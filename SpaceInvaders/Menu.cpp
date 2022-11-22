#include <iostream>
#include "menu.h"


void menu()
{   
    RenderWindow window(VideoMode(800, 600), "SpaceInvaders");
    window.setFramerateLimit(60);
    Event event;
    CircleShape circle(5.f);
    int x, y;
    x = 400; y = 500;
    circle.setFillColor(Color(100, 250, 250));
    circle.setPosition(x, y);
    //====================
    //Nie dzia³a - TEXT
    //====================
    Font font;
    font.loadFromFile("fonts/ARCADECLASSIC.ttf");
    Text StartText;
    StartText.setFont(font);
    StartText.setCharacterSize(16);
    StartText.setString("Wcisnij Start aby rozpoczac");
    StartText.setFillColor(Color::White);
    StartText.setPosition(800 / 2, 600 / 2);
    bool text_flag = true;
    
    while (!(Keyboard::isKeyPressed(Keyboard::Enter)))
    {
        window.clear(Color::Black);
        window.pollEvent(event);
        circle.setPosition(x, y);
        window.draw(circle);
        if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
        {
            window.close();
            break;
        }

        //===================================
        //Poczatkowa inicjalizacja sterowania
        //===================================
        if (Keyboard::isKeyPressed(Keyboard::Left) && x >= 10)
        {
            x = x - 10;

        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) && x <= 780)
        {
            x = x + 10;

        }
        //===============================
        //Koniec inicjalizacji sterowania
        //===============================


        //================================================
        //Schemat dzialania przyciskow start w trakcie gry
        //================================================
        if (text_flag == true)
        {
            window.draw(StartText);
        }

        if ((Keyboard::isKeyPressed(Keyboard::Enter)) && text_flag == true)
        {
            text_flag = false;
        }
        window.display();

    }
   
}