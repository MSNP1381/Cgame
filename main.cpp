#include <SFML/Graphics.hpp>
#include<iostream>
#define enemy_count 30
#define right_boundary 800-25-63
#define left_boundary 25
#define top_boundary 20
#define ship_movment_speed .3f
#define enemy_movment_speed 1.f
#define enemy_width 64
#define enemy_layout_boundary 28

short ship_direction=1;


void move_enemies(sf::Sprite s[enemy_count])
{
    //int x=-1;
    if (s[9].getPosition().x<=(right_boundary)&&s[0].getPosition().x>=(left_boundary))
    {
        for (int i=0; i<enemy_count; i++)
        {
            s[i].move(ship_direction*enemy_movment_speed,0);
        }
        std::cout<<"direction : "<<ship_direction<<"pos : "<<s[0].getPosition().x <<std::endl;
    }
    else if (s[9].getPosition().x>(right_boundary)&&ship_direction==1)
    {
        ship_direction=-1;
        for (int i=0; i<enemy_count; i++)
        {
            s[i].move(ship_direction*enemy_movment_speed,0);
        }

        std::cout<<"direction : "<<ship_direction<<std::endl;
    }
    else if (s[9].getPosition().x<(left_boundary)||ship_direction==-1)
    {
        ship_direction=1;
        for (int i=0; i<enemy_count; i++)
        {
            s[i].move(enemy_movment_speed,0);
        }
        std::cout<<"direction : "<<ship_direction<<std::endl;
    }
}







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
    for(int n=0; n<enemy_count; n++)
    {
        sprite[n].setTexture(texture);
        int i,j;
        if (0<=n&&n<=enemy_count/3-1)
            j=top_boundary;
        if (enemy_count/3<=n&&n<=2*enemy_count/3-1)
            j=top_boundary+enemy_width+enemy_layout_boundary*2;
        if (2*enemy_count/3<=n&&n<=enemy_count-1)
            j=top_boundary+enemy_width*2+enemy_layout_boundary*4;
        i=left_boundary+(n%10)*enemy_width+enemy_layout_boundary*2;
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
        move_enemies(sprite);
// Draw the textured sprite
        for (int i=0; i<enemy_count; i++)
            window.draw(sprite[i]);
        window.draw(spriteMyShip);
        window.draw(score);
        window.display();
    }
    return EXIT_SUCCESS;
}
