#include <SFML/Graphics.hpp>
#include<iostream>
#define enemy_count 30
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800,600),"my window");
    sf::Font vazir_font;
    sf::Text score;


            sf::Texture texture;
            sf::Texture textureMyShip;
        if (!texture.loadFromFile("enemy.png")||!vazir_font.loadFromFile("Vazir.ttf")||!textureMyShip.loadFromFile("images/small_ship_resized.png"))
            return -1;
        sf::Sprite spriteMyShip(textureMyShip);
        spriteMyShip.setPosition(375,500);
        sf::Sprite sprite[enemy_count];
        for(int n=0;n<enemy_count;n++){
        sprite[n].setTexture(texture);
          int i,j;
if (0<=n&&n<=enemy_count/3-1)
    j=20;
if (enemy_count/3<=n&&n<=2*enemy_count/3-1)
    j=20+64+28*2;
if (2*enemy_count/3<=n&&n<=enemy_count-1)
    j=20+64+28*2+64+28*2;
i=25+(n%10)*64+28*2;
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
    spriteMyShip.move(-.3f, 0.f);
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
{
    // left key is pressed: move our character
    spriteMyShip.move(+.3f, 0.f);
}

score.setString("salam");
        window.clear();
// Draw the textured sprite
for (int i=0;i<enemy_count;i++)
        window.draw(sprite[i]);
        window.draw(spriteMyShip);
        window.draw(score);
        window.display();
    }
    return EXIT_SUCCESS;
}

