#include <SFML/Graphics.hpp>
#include<iostream>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800,600),"my window");
    sf::Font vazir_font;
    sf::Text score;


            sf::Texture texture;
        if (!texture.loadFromFile("enemy.png")||!vazir_font.loadFromFile("Vazir.ttf"))
            return -1;

        sf::Sprite sprite[24];
        for(int n=0;n<24;n++){
        sprite[n].setTexture(texture);
          int i,j;
if (0<=n&&n<=7)
    j=20;
if (8<=n&&n<=15)
    j=20+64+28*2;
if (16<=n&&n<=23)
    j=20+64+28*2+64+28*2;
i=(n%8)*64+28*2;
sprite[n].setPosition(i,j);
        }
        score.setFont(vazir_font);
        score.setCharacterSize(15);



        //sprite.setTexture(texture);
    // Start the game loop


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
{
    // left key is pressed: move our character
   // sprite.move(-1.f, 0.f);
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
{
    // left key is pressed: move our character
//    sprite.move(+1.f, 0.f);
}

score.setString("salam");
        window.clear();
// Draw the textured sprite
for (int i=0;i<24;i++)
        window.draw(sprite[i]);
        window.draw(score);
        window.display();
    }
    return EXIT_SUCCESS;
}

