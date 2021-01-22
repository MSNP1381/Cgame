#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#define enemy_count 30

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
short ship_direction = 1;

class bullet_class
{
public:
    int allive = 0 ;
    sf::Texture bullet_texture;
    sf::Sprite bullet_sprite;
    sf::Vector2f position ;

    bullet_class (sf::Texture texture, sf::Vector2f Ship_pos)
    {
        bullet_texture = texture;
        position = Ship_pos;
        bullet_sprite.setTexture(bullet_texture);
        bullet_sprite.setPosition(position);
    }
    void move_bullet(float x)
    {
        bullet_sprite.move(0.f, -x);
    }
    void get_pos(sf::Vector2f posShipNew)
    {
        bullet_sprite.setPosition(posShipNew);
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
                sp[i].setColor(sf::Color::Black);
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
    srand(time(NULL));
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800,600),"my window");
    sf::Font vazir_font;
    sf::Text score;
    sf::Texture bullet_texture , bullet_texture_enemy;
    if(!bullet_texture.loadFromFile("images/bullet_main_3.png") || !bullet_texture_enemy.loadFromFile("images/bullet_main_3_enemy.png"))
        printf("we don't have bullets !");
    //sf::Sprite bullet(bullet_texture);
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
    //from here set the bullet position
    sf::Vector2f position_MyShip = spriteMyShip.getPosition();
    //bullet.setPosition(position_MyShip);
    //sf::Vector2f position_MyBullet = bullet.getPosition();
    //std::cout<<bullet.getPosition().x<<bullet.getPosition().y<<"\n";
    // up here .




    //bullet create

    //bullet enemy
    bullet_class bulletEnemy1(bullet_texture_enemy , sprite[rand()%30].getPosition());
    bullet_class bulletEnemy2(bullet_texture_enemy , sprite[rand()%30].getPosition());
    bullet_class bulletEnemy3(bullet_texture_enemy , sprite[rand()%30].getPosition());
    bullet_class bulletEnemy4(bullet_texture_enemy , sprite[rand()%30].getPosition());
    bullet_class bulletEnemy5(bullet_texture_enemy , sprite[rand()%30].getPosition());
    bullet_class bulletEnemy6(bullet_texture_enemy , sprite[rand()%30].getPosition());
    bullet_class bulletEnemy7(bullet_texture_enemy , sprite[rand()%30].getPosition());
    bullet_class bulletEnemy8(bullet_texture_enemy , sprite[rand()%30].getPosition());
    bullet_class bulletEnemy9(bullet_texture_enemy , sprite[rand()%30].getPosition());
    bullet_class bulletEnemy10(bullet_texture_enemy , sprite[rand()%30].getPosition());
    //bullet MyShip
    bullet_class bullet1(bullet_texture, position_MyShip);
    bullet_class bullet2(bullet_texture, position_MyShip);
    bullet_class bullet3(bullet_texture, position_MyShip);
    while (window.isOpen())
    {
        // bullet enemy receive pos
        if (bulletEnemy1.allive == 0)
        {
            bulletEnemy1.get_pos(sprite[rand()%30].getPosition());
        }
        if (bulletEnemy2.allive == 0)
        {
            bulletEnemy2.get_pos(sprite[rand()%30].getPosition());
        }
        if (bulletEnemy3.allive == 0)
        {
            bulletEnemy3.get_pos(sprite[rand()%30].getPosition());
        }
        if (bulletEnemy4.allive == 0)
        {
            bulletEnemy4.get_pos(sprite[rand()%30].getPosition());
        }
        if (bulletEnemy5.allive == 0)
        {
            bulletEnemy5.get_pos(sprite[rand()%30].getPosition());
        }
        if (bulletEnemy6.allive == 0)
        {
            bulletEnemy6.get_pos(sprite[rand()%30].getPosition());
        }
        if (bulletEnemy7.allive == 0)
        {
            bulletEnemy7.get_pos(sprite[rand()%30].getPosition());
        }
        if (bulletEnemy8.allive == 0)
        {
            bulletEnemy8.get_pos(sprite[rand()%30].getPosition());
        }
        if (bulletEnemy9.allive == 0)
        {
            bulletEnemy9.get_pos(sprite[rand()%30].getPosition());
        }
        if (bulletEnemy10.allive == 0)
        {
            bulletEnemy10.get_pos(sprite[rand()%30].getPosition());
        }

        //receive new pos for myship bullets
        sf::Vector2f position_MyShip = spriteMyShip.getPosition();
        if (bullet1.allive == 0)
        {
            bullet1.get_pos(position_MyShip);
        }
        if (bullet2.allive == 0)
        {
            bullet2.get_pos(position_MyShip);
        }
        if (bullet3.allive == 0)
        {
            bullet3.get_pos(position_MyShip);
        }

        //clos window
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        //front
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
            if (bullet1.allive == 0)
            {
                bullet1.allive = 1 ;
            }
            else if (bullet2.allive == 0)
            {
                bullet2.allive = 1 ;
            }
            else if (bullet3.allive == 0)
            {
                bullet3.allive = 1 ;
            }
            //allive_bullet = 1 ;
            //bullet bullet1( bullet_texture, position_MyShip);
        }
        //creating enemy bullet
        bulletEnemy1.allive = 1;
        bulletEnemy2.allive = 1;
        bulletEnemy3.allive = 1;
        bulletEnemy4.allive = 1;
        bulletEnemy5.allive = 1;
        bulletEnemy6.allive = 1;
        bulletEnemy7.allive = 1;
        bulletEnemy8.allive = 1;
        bulletEnemy9.allive = 1;
        bulletEnemy10.allive = 1;

        score.setString("salam");
        window.clear();

        //draw enemy bullet
        if (bulletEnemy1.allive == 1)
        {
            window.draw(bulletEnemy1.bullet_sprite);
            bulletEnemy1.move_bullet(-.1f);
        }
        if (bulletEnemy2.allive == 1)
        {
            window.draw(bulletEnemy2.bullet_sprite);
            bulletEnemy2.move_bullet(-.2f);
        }
        if (bulletEnemy3.allive == 1)
        {
            window.draw(bulletEnemy3.bullet_sprite);
            bulletEnemy3.move_bullet(-.3f);
        }if (bulletEnemy4.allive == 1)
        {
            window.draw(bulletEnemy4.bullet_sprite);
            bulletEnemy4.move_bullet(-.1f);
        }
        if (bulletEnemy5.allive == 1)
        {
            window.draw(bulletEnemy5.bullet_sprite);
            bulletEnemy5.move_bullet(-.2f);
        }
        if (bulletEnemy6.allive == 1)
        {
            window.draw(bulletEnemy6.bullet_sprite);
            bulletEnemy6.move_bullet(-.3f);
        }if (bulletEnemy7.allive == 1)
        {
            window.draw(bulletEnemy7.bullet_sprite);
            bulletEnemy7.move_bullet(-.1f);
        }
        if (bulletEnemy8.allive == 1)
        {
            window.draw(bulletEnemy8.bullet_sprite);
            bulletEnemy8.move_bullet(-.2f);
        }
        if (bulletEnemy9.allive == 1)
        {
            window.draw(bulletEnemy9.bullet_sprite);
            bulletEnemy9.move_bullet(-.3f);
        }
        if (bulletEnemy10.allive == 1)
        {
            window.draw(bulletEnemy10.bullet_sprite);
            bulletEnemy10.move_bullet(-.3f);
        }
        //draw MyShip bullet
        if (bullet1.allive == 1)
        {
            window.draw(bullet1.bullet_sprite);
            bullet1.move_bullet(.1f);
        }
        if (bullet2.allive == 1)
        {
            window.draw(bullet2.bullet_sprite);
            bullet2.move_bullet(.2f);
        }
        if (bullet3.allive == 1)
        {
            window.draw(bullet3.bullet_sprite);
            bullet3.move_bullet(.3f);
        }

        //if (allive_bullet == 1)
        //{
        //  window.draw(bullet);
        //  bullet.move(0.f, -.1f);
        //}
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
