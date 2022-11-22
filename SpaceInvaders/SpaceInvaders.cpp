// SpaceInvaders.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

using namespace std;
using namespace sf;

#define width 800
#define height 600

#define kolumny 16
#define wiersze 5
//obiekty gry

vector<vector <Sprite>>enemies;
vector<CircleShape> projectiles;
void create_enemies_easy(Sprite AlienSprite,float alien_width,float alien_height)
{   
    float pozycja_x=20;
    float pozycja_y=10;
        
    for (size_t i = 0; i < kolumny; i++)
    {   
        vector<Sprite>temp;
        for (size_t j = 0; j < wiersze; j++)
        {
            temp.push_back(Sprite(AlienSprite));
        }
        enemies.push_back(temp);
        //enemies[i][j].setPosition(pozycja_x, pozycja_y);
       // pozycja_x += alien_width;
    }

    for (size_t i = 0; i < kolumny; i++)
    {
        for (size_t j = 0; j < wiersze; j++)
        {
            enemies[i][j].setPosition(20 + (i * alien_width),10+(j*alien_height));
        }

    }
    
}



int main()
{
    //std::cout << "Hello World!\n";
    RenderWindow window( VideoMode(width,height), "SpaceInvaders" );
    window.setFramerateLimit(60);
    Event event;
    CircleShape circle(5.f);
    CircleShape projectile;
    projectile.setFillColor(Color::White);
    projectile.setRadius(5.f);
    int shootTimer = 0;
  
    //projectiles.push_back(CircleShape(projectile));
    

    int x, y;
    x = 400; y = 500;
    circle.setFillColor(Color(100, 250, 250));
    circle.setPosition(x, y);
    //======================
    //działa - TEXT STARTOWY
    //======================
    Font font;
    font.loadFromFile("fonts/ARCADECLASSIC.ttf");
    Text StartText;
    Text EnterText;
    Text StartText2;
    StartText.setFont(font);
    EnterText.setFont(font);
    StartText2.setFont(font);
    EnterText.setCharacterSize(24);
    StartText.setCharacterSize(24);
    StartText2.setCharacterSize(24);
    StartText.setFillColor(Color::White);
    StartText2.setFillColor(Color::White);
    EnterText.setFillColor(Color::Green);
    StartText.setPosition((width/2)-150,(height/2));
    EnterText.setPosition((width / 2)-40, height / 2);
    StartText2.setPosition((width / 2) + 50, height / 2);
    StartText.setString("Wcisnij ");
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

//=====
//Gracz
//=====
Texture PlayerTexture;
Sprite PlayerSprite;
PlayerTexture.loadFromFile("textures/Player.png");
PlayerSprite.setTexture(PlayerTexture);
PlayerSprite.setScale(Vector2f(0.5f, 0.5f));
float player_width = PlayerTexture.getSize().x;
float player_height = PlayerTexture.getSize().y;

//=================
//Koniec komentarza
//=================


//
//
//

// float alien_width = Sprite.GetSize().x;
// float alien_height = Sprite.GetSize().y;
//  Sprite AlienSprite


create_enemies_easy(AlienSprite, alien_width, alien_height);
//enemies.push_back(Sprite(AlienSprite));
while (true)
{

    window.clear(Color::Black);
    window.pollEvent(event);
    PlayerSprite.setPosition(x, y);


    //  window.draw(AlienSprite);
    //  window.draw(AlienSprite2);
    if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
    {
        window.close();
        break;
    }

    //===================================
    //Poczatkowa inicjalizacja sterowania
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

    if (shootTimer < 5)
    {
        shootTimer++;
    }

    if ((Keyboard::isKeyPressed(Keyboard::Space)) && (text_flag == false) && (shootTimer >= 5))
    {   
        projectile.setPosition(x+10, y + 5);
        projectiles.push_back(CircleShape(projectile));
        shootTimer = 0;

     }

        for (size_t  i= 0; i < projectiles.size(); i++)
        {
        
           // window.draw(projectiles[i]);
            projectiles[i].move(0.f, -10.f);

            if (projectiles[i].getPosition().y < 0)
                projectiles.erase(projectiles.begin()+i);
        }


        for (size_t i = 0; i < enemies.size(); i++)
        {   
            for (size_t j = 0; j < enemies[i].size(); j++)
            {
                window.draw(enemies[i][j]);
            }
            
        }
        for (size_t i = 0; i < projectiles.size(); i++)
        {
            window.draw(projectiles[i]);
        }
        window.draw(PlayerSprite);
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
