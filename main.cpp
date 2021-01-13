#include <SFML/Graphics.hpp>
#include<iostream>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800,600),"my window");
    sf::Font vazir_font;
    sf::Text score;

            sf::Texture texture;
        if (!texture.loadFromFile("cb.bmp")||!vazir_font.loadFromFile("Vazir.ttf"))
            return -1;
        sf::Sprite sprite(texture);
        sprite.setPosition(0100,10);
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


score.setString("salam");
        window.clear();
// Draw the textured sprite
        window.draw(sprite);
        window.draw(score);
        window.display();
    }
    return EXIT_SUCCESS;
}

