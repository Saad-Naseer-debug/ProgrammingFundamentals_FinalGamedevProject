
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

int Level(sf::RenderWindow& window)
{
    sf::Texture texture;
    if (!texture.loadFromFile("Resource/Back_ground.jpg"))
    {
       
    }
    sf::Texture texture2;
    if (!texture2.loadFromFile("Resource/pie.PNG"))
    {
       
    }
    vector<sf::Sprite> pies;
    sf::Sprite player(texture2);
    player.setScale({ 0.1f, 0.1f });
    player.setPosition({0.f,window.getSize().y - player.getGlobalBounds().size.y});
    pies.push_back(player);

    sf::Sprite sprite(texture);
    sprite.setScale({800.f/texture.getSize().x,600.f/texture.getSize().y});

    bool moving = true;
    sf::Clock clock;
    while (window.isOpen())
    {
        float dt = clock.getElapsedTime().asSeconds();
        if (dt >= 1.f/60.f)
        {
            while (auto event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }
                if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mouse->button == sf::Mouse::Button::Left && moving)
                    {
                        moving = false;
                        if (pies.size() >= 2)
                        {
                            float bottomLeft = pies[pies.size() - 2].getPosition().x;
                            float bottomRight = bottomLeft + pies[pies.size() - 2].getGlobalBounds().size.x;
                            float currentLeft = pies.back().getPosition().x;
                            float currentRight = currentLeft + pies.back().getGlobalBounds().size.x;
                            float overlapLeft = max(bottomLeft, currentLeft);
                            float overlapRight = min(bottomRight, currentRight);
                            float overlapWidth = overlapRight - overlapLeft;
                            if (overlapWidth > 0)
                            {
                                pies.back().setTextureRect(sf::IntRect({static_cast<int>((overlapLeft - currentLeft) / 0.1f),0 },{static_cast<int>(overlapWidth / 0.1f),static_cast<int>(texture2.getSize().y)} ));

                                pies.back().setPosition({overlapLeft,pies.back().getPosition().y});

                                sf::Sprite newPie = pies.back();

                                float newY = pies.back().getPosition().y -pies.back().getGlobalBounds().size.y;

                                newPie.setPosition({pies.back().getPosition().x, newY});

                                pies.push_back(newPie);

                                moving = true;
                            }
                           
                        }
                        else
                        {
    
                            sf::Sprite newPie(texture2);
                            newPie.setScale({ 0.1f, 0.1f });

                            float newY = pies.back().getPosition().y -pies.back().getGlobalBounds().size.y;

                            newPie.setPosition({pies.back().getPosition().x,newY });

                            pies.push_back(newPie);

                            moving = true;
                        }
                    }
                }
            }

            if (moving)
            {
                float v = 300.f;
                float dx = v * dt;

                float x1 = pies.back().getPosition().x;
                float x2 = x1 + dx;

                if (x2 >= window.getSize().x)
                {
                    x2 = 0.f;
                }

                pies.back().setPosition({
                    x2,
                    pies.back().getPosition().y
                    });
            }

          
            window.clear(sf::Color(64, 64, 64));
            window.draw(sprite);
            for (int i = 0; i < pies.size(); i++)
            {
                window.draw(pies[i]);
            }
            window.display();
            clock.restart();
        }
    }

    return 0;
}
