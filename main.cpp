#include <SFML/Graphics.hpp>

#include<iostream>
#include<chrono>
#define delay_time 700

#include<stdlib.h>
#include<time.h>

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

#define ship_width 64
#define ship_height 192

#define bullet_height 20
#define bullet_width 38
#define enemy_layout_boundary 28

short ship_direction = 1;


bool is_pressed=false;

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

bool collision(sf::Sprite ship,sf::Sprite bullet)
{
    float X,Y,W=enemy_width,H=enemy_height,x,y,w=bullet_width,h=bullet_height;
    x=bullet.getPosition().x
      ;
    y=bullet.getPosition().y
      ;
    X=ship.getPosition().x
      ;
    Y=ship.getPosition().y
      ;
    if((x>=X&&x<=X+W)&&(y>=Y-H&&y<=Y))
        return true;
    x=x+w;
    if((x>=X&&x<=X+W)&&(y>=Y-H&&y<=Y))
        return true;
    y=y+w;
    if((x>=X&&x<=X+W)&&(y>=Y-H&&y<=Y))
        return true;
    x=x-w;
    if((x>=X&&x<=X+W)&&(y>=Y-H&&y<=Y))
        return true;
    return false;



}

void bullet_explode_enemy(sf::Sprite sp[enemy_count],int *bullet_is_alive,sf::Sprite bullet_in,bool EnemyIsAlive[enemy_count])
{
    if(*bullet_is_alive==1)
    {
        float bulletX=bullet_in.getPosition().x;
        float bulletY=bullet_in.getPosition().y;

        for (int i=0; i<enemy_count; i++)
        {
            float EnemyX=sp[i].getPosition().x;
            float EnemyY=sp[i].getPosition().y;
            // std::cout<<"bx: "<<bulletX<<" bY: "<<bulletY<<" eX: "<<EnemyX<<" EY: "<<EnemyY<<" a"<<i<<": "<<EnemyIsAlive[i]<<std::endl;
            if(EnemyIsAlive[i])
                if(collision(sp[i],bullet_in))
                {
                    EnemyIsAlive[i]=false;
                    *bullet_is_alive=0;
                }
        }
        if (bulletY<-60)
            *bullet_is_alive=0;

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

void  title_init ( char s[], bool enemy_is_alive1[],int bullet_count)
{
    int enemy_score=0;
    for(int i =0;i<enemy_count;i++)
 {

     if (enemy_is_alive1[i]==false)
        {enemy_score++;


        }

}

        std::cout<<enemy_score<<std::endl;
 sprintf(s,"Score : %d      shot : %d       lives : %d",enemy_score,bullet_count,45);
}

int main()
{
    srand(time(NULL));
    // Create the main window

    sf::RenderWindow window(sf::VideoMode(800,600),"my window");
    sf::Font vazir_font;
    sf::Text score;
    sf::Texture bullet_texture, bullet_texture_enemy;
    if(!bullet_texture.loadFromFile("images/bullet_main_3.png") || !bullet_texture_enemy.loadFromFile("images/bullet_main_3_enemy.png"))
        return -1;
    //sf::Sprite bullet(bullet_texture);
    sf::Texture texture;
    sf::Texture textureMyShip;
    if (!texture.loadFromFile("enemy.png")||!vazir_font.loadFromFile("Vazir.ttf")||!textureMyShip.loadFromFile("images/small_ship_resized.png"))
        return -1;
    sf::Sprite spriteMyShip(textureMyShip);
    spriteMyShip.setPosition(375,500);
    spriteMyShip.setOrigin(21.60,0);
    sf::Sprite sprite[enemy_count];

    bool Enemy_is_alive[enemy_count];

    for(int i=0; i<enemy_count; i++)
        Enemy_is_alive[i]= {true};
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
    bullet_class bulletEnemy1(bullet_texture_enemy, sprite[rand()%30].getPosition());
    bullet_class bulletEnemy2(bullet_texture_enemy, sprite[rand()%30].getPosition());
    bullet_class bulletEnemy3(bullet_texture_enemy, sprite[rand()%30].getPosition());
    bullet_class bulletEnemy4(bullet_texture_enemy, sprite[rand()%30].getPosition());
    bullet_class bulletEnemy5(bullet_texture_enemy, sprite[rand()%30].getPosition());
    bullet_class bulletEnemy6(bullet_texture_enemy, sprite[rand()%30].getPosition());
    bullet_class bulletEnemy7(bullet_texture_enemy, sprite[rand()%30].getPosition());
    bullet_class bulletEnemy8(bullet_texture_enemy, sprite[rand()%30].getPosition());
    bullet_class bulletEnemy9(bullet_texture_enemy, sprite[rand()%30].getPosition());
    bullet_class bulletEnemy10(bullet_texture_enemy, sprite[rand()%30].getPosition());

    //bullet MyShip
    bullet_class bullet1(bullet_texture, position_MyShip);
    bullet_class bullet2(bullet_texture, position_MyShip);
    bullet_class bullet3(bullet_texture, position_MyShip);

    auto time_tmp=std::chrono::_V2::high_resolution_clock::now();
    auto time_now=std::chrono::_V2::high_resolution_clock::now();
    auto time_tmp1=std::chrono::_V2::high_resolution_clock::now();


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
        //close window
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        time_now=std::chrono::_V2::high_resolution_clock::now();
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
            if (!is_pressed)
            {
                is_pressed=true;
                time_tmp=std::chrono::_V2::high_resolution_clock::now();

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
            }
            else if (is_pressed&&(std::chrono::duration<double,std::milli>(time_now-time_tmp).count()>=delay_time))
            {
                is_pressed=false;

            }
        }
        //creating enemy bullet
        time_now=std::chrono::_V2::high_resolution_clock::now();
        //std::cout<<std::chrono::duration<double,std::milli>(time_now-time_tmp1).count()<<"\n";
        if (bulletEnemy1.allive != 1&&std::chrono::duration<double,std::milli>(time_now-time_tmp1).count()>=delay_time)
        {
            bulletEnemy1.allive = 1;
            time_tmp1=std::chrono::_V2::high_resolution_clock::now();

        }
        if (bulletEnemy2.allive != 1&&std::chrono::duration<double,std::milli>(time_now-time_tmp1).count()>=delay_time)
        {
            bulletEnemy2.allive = 1;
            time_tmp1=std::chrono::_V2::high_resolution_clock::now();

        }
        if (bulletEnemy3.allive != 1&&std::chrono::duration<double,std::milli>(time_now-time_tmp1).count()>=delay_time)
        {
            bulletEnemy3.allive = 1;
            time_tmp1=std::chrono::_V2::high_resolution_clock::now();

        }
        if (bulletEnemy4.allive != 1&&std::chrono::duration<double,std::milli>(time_now-time_tmp1).count()>=delay_time)
        {
            bulletEnemy4.allive = 1;
            time_tmp1=std::chrono::_V2::high_resolution_clock::now();

        }
        if (bulletEnemy5.allive != 1&&std::chrono::duration<double,std::milli>(time_now-time_tmp1).count()>=delay_time)
        {
            bulletEnemy5.allive = 1;
            time_tmp1=std::chrono::_V2::high_resolution_clock::now();

        }
        if (bulletEnemy6.allive != 1&&std::chrono::duration<double,std::milli>(time_now-time_tmp1).count()>=delay_time)
        {
            bulletEnemy6.allive = 1;
            time_tmp1=std::chrono::_V2::high_resolution_clock::now();

        }
        if (bulletEnemy7.allive != 1&&std::chrono::duration<double,std::milli>(time_now-time_tmp1).count()>=delay_time)
        {
            bulletEnemy7.allive = 1;
            time_tmp1=std::chrono::_V2::high_resolution_clock::now();

        }
        if (bulletEnemy8.allive != 1&&std::chrono::duration<double,std::milli>(time_now-time_tmp1).count()>=delay_time)
        {
            bulletEnemy8.allive = 1;
            time_tmp1=std::chrono::_V2::high_resolution_clock::now();

        }
        if (bulletEnemy9.allive != 1&&std::chrono::duration<double,std::milli>(time_now-time_tmp1).count()>=delay_time)
        {
            bulletEnemy9.allive = 1;
            time_tmp1=std::chrono::_V2::high_resolution_clock::now();

        }
        if (bulletEnemy10.allive != 1&&std::chrono::duration<double,std::milli>(time_now-time_tmp1).count()>=delay_time)
        {
            bulletEnemy10.allive = 1;
            time_tmp1=std::chrono::_V2::high_resolution_clock::now();

        }
char title[500];
title_init(title,Enemy_is_alive,5);
        score.setString(title);

        bullet_explode_enemy(sprite,&bullet1.allive,bullet1.bullet_sprite,Enemy_is_alive);
        bullet_explode_enemy(sprite,&bullet2.allive,bullet2.bullet_sprite,Enemy_is_alive);
        bullet_explode_enemy(sprite,&bullet3.allive,bullet3.bullet_sprite,Enemy_is_alive);



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
        }
        if (bulletEnemy4.allive == 1)
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
        }
        if (bulletEnemy7.allive == 1)
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
            bullet1.move_bullet(1.5f);
        }
        if (bullet2.allive == 1)
        {
            window.draw(bullet2.bullet_sprite);
            bullet2.move_bullet(1.5f);
        }
        if (bullet3.allive == 1)
        {
            window.draw(bullet3.bullet_sprite);
            bullet3.move_bullet(1.5f);
        }

        move_enemies(sprite);
        // Draw the textured sprite
        for (int i=0; i<enemy_count; i++)
        {
            if (Enemy_is_alive[i])
                window.draw(sprite[i]);
        }

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
