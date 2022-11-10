// SpaceInvaders.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

#define width 800
#define height 600

int main()
{
    //std::cout << "Hello World!\n";
    RenderWindow window( VideoMode(width,height), "SpaceInvaders" );
    window.setFramerateLimit(60);
    Event event;
    CircleShape circle(5.f);
    int x, y;
    x = 400; y = 500;
    circle.setFillColor(Color(100, 250, 250));
    circle.setPosition(x, y);
    //====================
    //Nie działa - TEXT
    //====================
    Font font;
    Text StartText;
    StartText.setFont(font);
    StartText.setCharacterSize(1);
    StartText.setString("Start");
    StartText.setFillColor(Color::White);
    StartText.setPosition(width / 2, height / 2);
    //==================
    // Koniec komentarza
    //==================
    while (true)
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
        if (Keyboard::isKeyPressed(Keyboard::Left) && x>=10)
        {
            x =x-10;
            
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right)&& x<=780)
        {
            x = x+10;
  
        }

        if (!(Keyboard::isKeyPressed(Keyboard::Enter)))
        {
            window.draw(StartText);
        }
        //===============================
        //Koniec inicjalizacji sterowania
        //===============================
        window.display();

    }
    return 0;

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
