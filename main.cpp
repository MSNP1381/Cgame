#include <SFML/Graphics.hpp>

#include<iostream>
#include<chrono>
#define delay_time 700
#define enemy_count 30
sf::Sprite build_bullet(sf::Sprite MyShip, sf::Sprite bullet, sf::Sprite empty_temp);
void fire(sf::Sprite bullet);
int allive_bullet = 0 ;
#define right_boundary 800-25-63
#define left_boundary 25
#define top_boundary 20
#define ship_movment_speed .3f
#define enemy_movment_speed .12f
#define enemy_width 64
#define enemy_height 192
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

void bullet_explode(sf::Sprite sp[enemy_count],int bullet_is_alive,sf::Sprite bullet,bool EnemyIsAlive[enemy_count])
{
    float bulletX=bullet.getPosition().x;
    float bulletY=bullet.getPosition().y;
    if(bullet_is_alive==1)
    {
        for (int i=0; i<enemy_count; i++)
        {
            float EnemyX=sp[i].getPosition().x;
            float EnemyY=sp[i].getPosition().y;
            if(EnemyIsAlive[i]&&(bulletX>EnemyX&&bulletX<EnemyX+enemy_width)&&(bulletY>EnemyY&&bulletY<EnemyY+enemy_height))
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

string title_init(bool enemy_is_alive[enemy_count],int bullet_count)
{
    int enemy_score=0;
    for(int i =0;i<enemy_count;i++)
        if (!enemy_is_alive[enemy_count])
        enemy_score++;
    char c[800/15];
    char scrtmp[]="Score : "
    char reloading="Reloading"
 char c=("%s",scrtmp);
}

int main()
{
    // Create the main window

    sf::RenderWindow window(sf::VideoMode(800,600),"my window");
    sf::Font vazir_font;
    sf::Text score;
    sf::Texture bullet_texture ;
    if(!bullet_texture.loadFromFile("images/bullet_main_3.png"))
        return -1;

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

    sf::Vector2f position_MyShip = spriteMyShip.getPosition();

    bullet_class bullet1(bullet_texture, position_MyShip);
    bullet_class bullet2(bullet_texture, position_MyShip);
    bullet_class bullet3(bullet_texture, position_MyShip);

    auto time_tmp=std::chrono::_V2::high_resolution_clock::now();
    auto time_now=std::chrono::_V2::high_resolution_clock::now();


    while (window.isOpen())
    {

        //receive new pos
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
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        time_now=std::chrono::_V2::high_resolution_clock::now();
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
        score.setString("salam");
        window.clear();

        if (bullet1.allive == 1)
        {
            window.draw(bullet1.bullet_sprite);
            bullet1.move_bullet(.1f);
        }
        if (bullet2.allive == 1)
        {
            window.draw(bullet2.bullet_sprite);
            //std::cout<<"hello !";
            bullet2.move_bullet(.2f);
        }
        if (bullet3.allive == 1)
        {
            window.draw(bullet3.bullet_sprite);
            bullet3.move_bullet(.3f);
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
