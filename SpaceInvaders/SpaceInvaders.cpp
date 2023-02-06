// SpaceInvaders.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <fstream>

using namespace std; //przesten nazw std z c++
using namespace sf; //przestrzen nazw sf z c++

#define width 800 //zmienna globalna szerokosci okna gry
#define height 600 //zmmienna globalna wysokosci okna gry

#define kolumny 16//nieuzywane
#define wiersze 5 //nieuzywane
//obiekty gry


vector<CircleShape> projectiles; //kontener typu vektor  przechowujący pociski wystrzelone przez gracza znajdujace sie na planszy
vector<Sprite>przeciwnicy; //kontener typu vektor  przechowujacy przeciwnikow znajdujacych sie na planszy



void losowe(Sprite AlienSprite, float alien_width, float alien_height) //funkcja generujaca przeciwnikow w srodku parametry kolejno Sprite Przeciwnika, szerokość przeciwnika, wysokość przeciwnika
{   
    int kolumna = 0; //zmienna pomocnicza sluzaca do wygenerowania przeciwnikow w kolumnach
    int wiersz = 0; // zmienna pomocnicza sluzaca do wygenerowania przeciwnikow w wierszach

    //Petla rezerwujaca miejsce dla przeciwnikow w kontenerze
    for (int i = 0; i < 64; i++)
    {
        przeciwnicy.push_back(AlienSprite); 

    }
    //petla sluzaca do ustawienia pozycji przeciwnikow na planszy
    for(int i=0;i<64;i++)
    {
        if (i % 16 == 0)
        {
            kolumna++;
            wiersz = 0;
        }
  
        przeciwnicy[i].setPosition(20 + (wiersz * alien_width), -1*(10 + (kolumna * alien_height)));
        wiersz++;
        
    }
}

int main()
{
    RenderWindow window(VideoMode(width, height), "SpaceInvaders"); //parametry okna kolejno szerokosc wysokosc, tytul okna
    window.setFramerateLimit(60); //limit klatek dla okna
    ofstream outputFile; //definicja obiektu klasy ofstream sluzaca do zapisu wyniku
    Event event;
    CircleShape circle(5.f);
    CircleShape projectile;
    projectile.setFillColor(Color::White);
    projectile.setRadius(5.f);
    int shootTimer = 0;
    bool defeat=false;
  

    int points = 0; // zmienna przechowujaca punkty zdobyte przez gracza
    int x, y;
    x = 400; y = 500;
    circle.setFillColor(Color(100, 250, 250));
    circle.setPosition(x, y);//czy potrzebne?
    //===============================
    //Tekst wyswietlajacy sie w grze
    //===============================
    Font font;
    font.loadFromFile("fonts/ARCADECLASSIC.ttf");
    Text StartText;
    Text EnterText;
    Text StartText2;
    Text HighScore;
    Text LicznikFali;
    Text Lost;
    StartText.setFont(font);
    LicznikFali.setFont(font);
    EnterText.setFont(font);
    StartText2.setFont(font);
    HighScore.setFont(font);
    Lost.setFont(font);
    LicznikFali.setCharacterSize(24);
    HighScore.setCharacterSize(24);
    EnterText.setCharacterSize(24);
    StartText.setCharacterSize(24);
    StartText2.setCharacterSize(24);
    Lost.setCharacterSize(24);
    LicznikFali.setFillColor(Color::Red);
    Lost.setFillColor(Color::Red);
    HighScore.setFillColor(Color::White);
    StartText.setFillColor(Color::White);
    StartText2.setFillColor(Color::White);
    EnterText.setFillColor(Color::Green);
    HighScore.setPosition(20,540);
    LicznikFali.setPosition(700, 540);
    StartText.setPosition((width / 2) - 150, (height / 2));
    Lost.setPosition((width / 2) - 150, (height / 2));
    EnterText.setPosition((width / 2) - 40, height / 2);
    StartText2.setPosition((width / 2) + 50, height / 2);
    StartText.setString("Wcisnij ");
    HighScore.setString("Score  " + to_string(points));
    Lost.setString("Przegrales Twoj wynik to  " + to_string(points));
 
    EnterText.setString(" enter ");
    StartText2.setString(" aby rozpoczac");
    bool text_flag = true;
    //==================
    // Koniec komentarza
    //==================

//==========
//Przeciwnik
//==========
    Texture AlienTexture;
    Sprite AlienSprite;
    Sprite AlienSprite2;
    AlienTexture.loadFromFile("textures/Alien1.png");
    AlienSprite.setTexture(AlienTexture);
    AlienSprite2.setTexture(AlienTexture);
    AlienSprite.setScale(Vector2f(0.5f, 0.5f));
    AlienSprite2.setScale(Vector2f(0.5f, 0.5f));
    float alien_width = (AlienTexture.getSize().x * AlienSprite.getScale().x) + 5;
    float alien_height = AlienTexture.getSize().y * AlienSprite.getScale().y + 5;
    float alien_x = 20;
    float alien_y = 10;
    AlienSprite.setPosition(20, 10);
    AlienSprite2.setPosition(alien_width - 5, 10);


    //=================
    //Koniec komentarza
    //=================

    //=============
    //Gracz Zmienne
    //=============
    Texture PlayerTexture; 
    Sprite PlayerSprite;
    PlayerTexture.loadFromFile("textures/Player.png");
    PlayerSprite.setTexture(PlayerTexture);
    PlayerSprite.setScale(Vector2f(0.5f, 0.5f));
    float player_width = PlayerTexture.getSize().x; //zmienna przechowujaca szerokosc sprite'u gracza
    float player_height = PlayerTexture.getSize().y; //zmienna przechowująca wysokosc sprite'u gracza

    //=================
    //Koniec komentarza
    //=================






  
    losowe(AlienSprite, alien_width, alien_height); //wywolanie funkcji generujacej przeciwnikow

    Clock enemyClock; //zegar wykorzystywany przy poruszaniu przeciwnikow
    Clock newEnemyLineClock;

    int fala = 1;//zmienna przechowujaca numer aktualnej fali

    //petla glowna
    while (true)
    {

        window.clear(Color::Black);
        window.pollEvent(event);
        if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
        {
            window.close();
            break;
        }

        if (defeat == false) //główna część gry
        {
            PlayerSprite.setPosition(x, y);

            HighScore.setString("Score  " + to_string(points));
            LicznikFali.setString("Fala  " + to_string(fala));

         

            //===================================
            //Inicjalizacja sterowania
            //===================================
            if (Keyboard::isKeyPressed(Keyboard::Left) && x >= 10 && text_flag == false)
            {
                x = x - 10;

            }
            else if (Keyboard::isKeyPressed(Keyboard::Right) && x <= 780 && text_flag == false)
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
                window.draw(EnterText);
                window.draw(StartText2);
            }

            if ((Keyboard::isKeyPressed(Keyboard::Enter)) && text_flag == true)
            {
                text_flag = false;
            }
            //==================
            //Koniec komentarza
            //==================
            //===================================
            //Inicjzalizacja mechaniki strzelania
            //===================================

            if (shootTimer < 5) //timer wykorzystywany przy czasie odnowienia strzelania
            {
                shootTimer++;
            }


            if ((Keyboard::isKeyPressed(Keyboard::Space)) && (text_flag == false) && (shootTimer >= 5)) //Sterowanie wraz z parametrami dla strzelania
            {
                projectile.setPosition(x + 10, y + 5);
                projectiles.push_back(CircleShape(projectile));
                shootTimer = 0;

            }


            //Schemat generowania kolejnych fal aby uzyskać efekt nieskończonej gry
            if (points % 640 == 0 && przeciwnicy.empty())
            {
                losowe(AlienSprite, alien_width, alien_height);
                fala++;

            }

            //Nadanie dynamiki strzelaniu aby pociski mogły się poruszać w góre planszy po wystrzeleniu oraz zostały usuwane gdy wylecą poza ekran
            for (size_t i = 0; i < projectiles.size(); i++)
            {

             
                projectiles[i].move(0.f, -10.f);

                if (projectiles[i].getPosition().y < 0)
                    projectiles.erase(projectiles.begin() + i);

            }
            
            //=======================================
            //SYSTEM KOLIZJI PRZECIWNIKOW Z POCISKAMI
            //=======================================
            for (int i = 0; i < przeciwnicy.size(); i++)
            {
                for (int j = 0; j < projectiles.size(); j++)
                {

                    if (projectiles[j].getGlobalBounds().intersects(przeciwnicy[i].getGlobalBounds()))
                    {
                        projectiles.erase(projectiles.begin() + j);
                        przeciwnicy.erase(przeciwnicy.begin() + i);
                        points += 10;
                        
                     
                        break;

                    }

                }
            }
            //================
            //KONIEC KOMENTARZA
            //=================

            //Warunek w petli sprawdzajacy czy gracz przegral
            for (int i = 0; i < przeciwnicy.size(); i++)
            {
                if (przeciwnicy[i].getPosition().y >= 560)
                    defeat = true;
            }



            //Rysowanie przeciwnikow dopiero po wcisnieciu Klawisza Enter który zmienia text_flag na true
            if (text_flag == false)
            {
                for (size_t i = 0; i < przeciwnicy.size(); i++)
                {

                    window.draw(przeciwnicy[i]);


                }
            }

            //Inicjalizacja timera który pozwala przeciwnikom poruszać się w dół planszy co 1s
            if (enemyClock.getElapsedTime().asSeconds() >= 1.0f)
            {
                for (int j = 0; j < przeciwnicy.size(); j++)
                {
                    przeciwnicy[j].move(0.f, (fala * 0.5f) * 15); //Kazda fala zwieksza szybkosc poruszania sie przeciwnikow
                    
                }

                enemyClock.restart(); //zegar restartuje swoj licznik po osiagnieciu żądanej wartości
            }


   
            //Rysowanie pocisków na planszy
            for (size_t i = 0; i < projectiles.size(); i++)
            {
                window.draw(projectiles[i]);
            }
    

            window.draw(PlayerSprite);
            window.draw(HighScore);
            window.draw(LicznikFali);
            window.display();
        }
        else if (defeat == true) //sprawdza czy warunek porazki spelniony jezeli tak wypisuje wynik 
        {   
            Lost.setString("Przegrales Twoj wynik to  " + to_string(points));
            window.draw(HighScore);
            window.draw(Lost);
            
            window.display();
        }
    }
    outputFile.open("highscore.txt", ios::app);
    outputFile << to_string(points) << "\n";
    outputFile.close();
    return 0;


    //Co warto dodac
    //System zyc dla gracza zamiast natychmiastowej przegranej
    //Dzwieki
    //Tlo
    //poruszanie przeciwnikow w lewo i w prawo ale do granic planszy
    //system kolizji gracza z przeciwnikami w celu odebrania punktu zycia
    
    //Co nalezy dodac
    //System eksportu wyniku do pliku

}

