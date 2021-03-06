#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class CustomSprite : public sf::Sprite
 {
  public:

    void setSpeed(int xspeed, int yspeed)
     {
      m_speed_x = xspeed;
      m_speed_y = yspeed;
     }

    void setBounds(int left, int right, int top, int bottom)
     {
      bound_top = top;
      bound_bottom = bottom;
      bound_right = right;
      bound_left = left;
     }
    int counter = 0;


    bool Collision_T(sf::Sprite wall)
     {
      sf::FloatRect guy_bounds = getGlobalBounds();
      sf::FloatRect wall_bounds = wall.getGlobalBounds();

      if ((guy_bounds.top+guy_bounds.height >= wall_bounds.top-3) && (guy_bounds.top < wall_bounds.top)
      && (guy_bounds.left+guy_bounds.width > wall_bounds.left+3) && (guy_bounds.left < wall_bounds.left+wall_bounds.width-3))
     {
        return 1;
       }
      else{return 0;}
     }

    bool Collision_R(sf::Sprite wall)
     {
      sf::FloatRect guy_bounds = getGlobalBounds();
      sf::FloatRect wall_bounds = wall.getGlobalBounds();

      if ((guy_bounds.left <= wall_bounds.left+wall_bounds.width+3) && (guy_bounds.left+guy_bounds.width > wall_bounds.left+wall_bounds.width)
       && (guy_bounds.top+guy_bounds.height > wall_bounds.top+3) && (guy_bounds.top < wall_bounds.top+wall_bounds.height-3))
       {
        return 1;
       }
      else{return 0;}
     }

    bool Collision_B(sf::Sprite wall)
     {
      sf::FloatRect guy_bounds = getGlobalBounds();
      sf::FloatRect wall_bounds = wall.getGlobalBounds();

      if ((guy_bounds.top <= wall_bounds.top + wall_bounds.height+3) && (guy_bounds.top+guy_bounds.height > wall_bounds.top+wall_bounds.height)
       && (guy_bounds.left+guy_bounds.width > wall_bounds.left+3) && (guy_bounds.left < wall_bounds.left+wall_bounds.width-3))
       {
        return 1;
       }
      else{return 0;}
     }

    bool Collision_L(sf::Sprite wall)
     {
      sf::FloatRect guy_bounds = getGlobalBounds();
      sf::FloatRect wall_bounds = wall.getGlobalBounds();

      if ((guy_bounds.left+guy_bounds.width >= wall_bounds.left-3) && (guy_bounds.left < wall_bounds.left)
       && (guy_bounds.top+guy_bounds.height > wall_bounds.top+3) && (guy_bounds.top < wall_bounds.top+wall_bounds.height-3))
       {

        return 1;
       }
      else{return 0;}
     }



    void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key, const std::vector<sf::Sprite> &obstacles, std::vector<sf::Sprite> &hearts)
     {
      sf::FloatRect rectangle_bounds = getGlobalBounds();
      bool top=0, left=0, bottom=0, right=0;


      for(auto &obstacle : obstacles)
      {
       if(Collision_T(obstacle) == 1){top = 1; hearts.pop_back(); setPosition(0, 0);}
       if(Collision_L(obstacle) == 1){left = 1; hearts.pop_back(); setPosition(0, 0);}
       if(Collision_B(obstacle) == 1){bottom = 1; hearts.pop_back(); setPosition(0, 0);}
       if(Collision_R(obstacle) == 1){right = 1; hearts.pop_back(); setPosition(0, 0);}
      }


      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rectangle_bounds.top > bound_top && bottom != true)
       {
        move(0, -m_speed_y*elapsed.asSeconds());
       }

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rectangle_bounds.top+rectangle_bounds.height < bound_bottom && top != true)
       {
        move(0, m_speed_y*elapsed.asSeconds());
       }

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && rectangle_bounds.left + rectangle_bounds.width < bound_right && left != true)
       {
        move(m_speed_x*elapsed.asSeconds(), 0);
       }

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && rectangle_bounds.left > bound_left && right != true)
       {
        move(-m_speed_x*elapsed.asSeconds(), 0);
       }
     }




  private:
    int m_speed_x = 200;
    int m_speed_y = 200;
    int bound_top = 0;
    int bound_bottom = 0;
    int bound_left = 0;
    int bound_right = 0;
 };

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Clock clock;

    sf::Texture guy_tex;
    if (!guy_tex.loadFromFile("guy.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture home_tex;
    if (!home_tex.loadFromFile("home.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    home_tex.setRepeated(true);

    sf::Texture grass_tex;
    if (!grass_tex.loadFromFile("grass.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    grass_tex.setRepeated(true);

    sf::Texture wall_tex;
    if (!wall_tex.loadFromFile("wall.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    wall_tex.setRepeated(true);

    sf::Texture heart_tex;
    if (!heart_tex.loadFromFile("heart.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    heart_tex.setRepeated(true);

    sf::Texture over_tex;
    if (!over_tex.loadFromFile("over.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    over_tex.setRepeated(true);


    CustomSprite guy;
    guy.setTexture(guy_tex);

    sf::Sprite grass;
    grass.setTexture(grass_tex);
    grass.setScale(1, 1);
    grass.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

    std::vector<sf::Sprite> hearts;

    sf::Sprite heart;
    heart.setTexture(heart_tex);
    heart.setScale(1.4, 1.4);
    heart.setPosition (530, 0);
    hearts.emplace_back(heart);

    sf::Sprite heart2;
    heart2.setTexture(heart_tex);
    heart2.setScale(1.4, 1.4);
    heart2.setPosition (600, 0);
    hearts.emplace_back(heart2);

    sf::Sprite heart3;
    heart3.setTexture(heart_tex);
    heart3.setScale(1.4, 1.4);
    heart3.setPosition (670, 0);
    hearts.emplace_back(heart3);


    sf::Sprite home;
    home.setTexture(home_tex);
    home.setScale(0.1, 0.1);
    home.setPosition(700, 500);

    sf::Sprite over;
    over.setTexture(over_tex);
    over.setScale(1, 1);
    over.setPosition(400, 300);

    std::vector<sf::Sprite> walls;

    sf::Sprite wall1;
    wall1.setTexture(wall_tex);
    wall1.setScale(0.3, 0.3);
    wall1.setTextureRect(sf::IntRect(0, 0, 100, 900));
    wall1.setPosition(200, 100);
    walls.emplace_back(wall1);

    sf::Sprite wall2;
    wall2.setTexture(wall_tex);
    wall2.setScale(0.3, 0.3);
    wall2.setTextureRect(sf::IntRect(0, 0, 700, 100));
    wall2.setPosition(230, 250);
    walls.emplace_back(wall2);

    sf::Sprite wall3;
    wall3.setTexture(wall_tex);
    wall3.setScale(0.3, 0.3);
    wall3.setTextureRect(sf::IntRect(0, 0, 100, 1100));
    wall3.setPosition(440, 190);
    walls.emplace_back(wall3);

    sf::Sprite wall4;
    wall4.setTexture(wall_tex);
    wall4.setScale(0.3, 0.3);
    wall4.setTextureRect(sf::IntRect(0, 0, 100, 1000));
    wall4.setPosition(570, 110);
    walls.emplace_back(wall4);

    sf::Sprite wall5;
    wall5.setTexture(wall_tex);
    wall5.setScale(0.3, 0.3);
    wall5.setTextureRect(sf::IntRect(0, 0, 600, 100));
    wall5.setPosition(570, 410);
    walls.emplace_back(wall5);

    sf::Sprite wall6;
    wall6.setTexture(wall_tex);
    wall6.setScale(0.3, 0.3);
    wall6.setTextureRect(sf::IntRect(0, 0, 700, 100));
    wall6.setPosition(100, 460);
    walls.emplace_back(wall6);

    guy.setBounds(0, window.getSize().x, 0, window.getSize().y);


    while (window.isOpen())
     {
      sf::Time elapsed = clock.restart();

      sf::Event event;
      while (window.pollEvent(event))
       {

        if (event.type == sf::Event::Closed)
         {
          window.close();
         }


       }

      window.clear(sf::Color::Black);
      window.draw(grass);
      window.draw(guy);
      window.draw(home);
      window.draw(wall1);
      window.draw(wall2);
      window.draw(wall3);
      window.draw(wall4);
      window.draw(wall5);
      window.draw(wall6);

        for( auto heart : hearts){
            window.draw(heart);
        }

      guy.moveInDirection(elapsed, event.key.code, walls, hearts);


      window.display();
     }
    return 0;
}
