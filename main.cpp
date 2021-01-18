#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
sf::Sprite build_bullet(sf::Sprite MyShip, sf::Sprite bullet, sf::Sprite empty_temp);
void fire(sf::Sprite bullet);
int allive_bullet = 0 ;
#define enemy_count 30
#define right_boundary 800-25-63
#define left_boundary 25
#define top_boundary 20
#define ship_movment_speed .3f
#define enemy_movment_speed .12f
#define enemy_width 64
#define enemy_height 192
#define enemy_layout_boundary 28
#define bullet_height
short ship_direction=1;

class bullet_Class {
    public:
    int allive = 1 ;
    sf::Texture bullet_texture;
    sf::Sprite bullet_sprite;
    sf::Vector2f position ;

    bullet (sf::Texture texture , sf::Vector2f Ship_pos){
        bullet_texture = texture;
        position = Ship_pos;
        bullet_sprite.setTexture(bullet_texture);
        bullet_sprite.setPosition(position);
    }
};

void bullet_explode(sf::Sprite sp[enemy_count],int bullet_is_alive,sf::Sprite bullet_in,bool EnemyIsAlive[enemy_count])
{
    float bulletX=bullet_in.getPosition().x;
    float bulletY=bullet_in.getPosition().y;
    if(bullet_is_alive==1)
    {
        for (int i=0; i<enemy_count; i++)
        {
            float EnemyX=sp[i].getPosition().x;
            float EnemyY=sp[i].getPosition().y;
            if(bulletY>(600+76)||bEnemyIsAlive[i]&&(bulletX>EnemyX&&bulletX<EnemyX+enemy_width)&&(bulletY>EnemyY&&bulletY<EnemyY+enemy_height))
            {
                EnemyIsAlive[i]=false;
                bullet_is_alive=0;
                sp[i].setColor(sf::Color.Black);

            }
        }

    }


}

void move_enemies(sf::Sprite s[enemy_count])
{
    //int x=-1;
    if (s[9].getPosition().x<=(right_boundary)&&s[0].getPosition().x>=(left_boundary))
    {
        for (int i=0; i<enemy_count; i++)
        {
            s[i].move(ship_direction*enemy_movment_speed,0);
        }
        //std::cout<<"direction : "<<ship_direction<<"pos : "<<s[0].getPosition().x <<std::endl;
    }
    else if (s[9].getPosition().x>(right_boundary)&&ship_direction==1)
    {
        ship_direction=-1;
        for (int i=0; i<enemy_count; i++)
        {
            s[i].move(ship_direction*enemy_movment_speed,0);
        }

        //std::cout<<"direction : "<<ship_direction<<std::endl;
    }
    else if (s[9].getPosition().x<(left_boundary)||ship_direction==-1)
    {
        ship_direction=1;
        for (int i=0; i<enemy_count; i++)
        {
            s[i].move(enemy_movment_speed,0);
        }
        //std::cout<<"direction : "<<ship_direction<<std::endl;
    }
}
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
    bool Enemy_is_alive[enemy_count]= {true};
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
bullet.
    //from here set the bullet position
    sf::Vector2f position_MyShip = spriteMyShip.getPosition();
    bullet.setPosition(position_MyShip);
    //sf::Vector2f position_MyBullet = bullet.getPosition();
    //std::cout<<bullet.getPosition().x<<bullet.getPosition().y<<"\n";
    // up here .

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
            window.draw(bullet);
            bullet.move(0.f, -.1f);
        }
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
//sf::Sprite build_bullet(sf::Sprite MyShip, sf::Sprite bullet, sf::Sprite empty_temp)
//{
//  sf::Vector2f position_MyShip = MyShip.getPosition();
//  bullet.setPosition(position_MyShip);
//  sf::Vector2f position_MyBullet = bullet.getPosition();
//  std::cout<<position_MyBullet.x<<position_MyBullet.y<<"\n";
//  return bullet;
//}
