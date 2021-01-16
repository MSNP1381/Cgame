#include <SFML/Graphics.hpp>
#include<iostream>
#define enemy_count 30
sf::Sprite build_bullet(sf::Sprite MyShip, sf::Sprite bullet, sf::Sprite empty_temp);
void fire(sf::Sprite bullet);
int allive_bullet = 0 ;
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800,600),"my window");
    sf::Font vazir_font;
    sf::Text score;
    sf::Texture bullet_texture ;
    if(!bullet_texture.loadFromFile("images/bullet_main_3.png"))
        printf("we don't have bullets !");
    sf::Sprite bullet(bullet_texture);
    sf::Sprite empty_temp ;
    sf::Texture texture;
    sf::Texture textureMyShip;
    if (!texture.loadFromFile("enemy.png")||!vazir_font.loadFromFile("Vazir.ttf")||!textureMyShip.loadFromFile("images/small_ship_resized.png"))
        return -1;
    sf::Sprite spriteMyShip(textureMyShip);
    spriteMyShip.setPosition(375,500);
    spriteMyShip.setOrigin(21.60,0);
    sf::Sprite sprite[enemy_count];
    for(int n=0; n<enemy_count; n++)
    {
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

    build_bullet(spriteMyShip, bullet, empty_temp);
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            allive_bullet = 1 ;
        }
        score.setString("salam");
        window.clear();
        if (allive_bullet == 1)
        {
            bullet.move(0.f, -.1f);
            window.draw(bullet);
        }
        //Draw the textured sprite
        for (int i=0; i<enemy_count; i++)
            window.draw(sprite[i]);
        window.draw(spriteMyShip);
        window.draw(score);
        window.display();
    }
    return EXIT_SUCCESS;
}
sf::Sprite build_bullet(sf::Sprite MyShip, sf::Sprite bullet, sf::Sprite empty_temp)
{
    sf::Vector2f position_MyShip = MyShip.getPosition();
    std::cout<<position_MyShip.x<<position_MyShip.y<<"\n";
    bullet.setPosition(position_MyShip.x, position_MyShip.y);
    if(allive_bullet == 1)
        return bullet;
    return empty_temp;
}
