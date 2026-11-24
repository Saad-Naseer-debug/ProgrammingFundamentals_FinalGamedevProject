
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
int Level(sf::RenderWindow& window);
int main()
{
 
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "STACK THE PIE", sf::State::Fullscreen);

   
    sf::Texture texture;
    if (!texture.loadFromFile("Resource/background.png")) 
    {
        return 0;
    }

 
    float screenWidth = static_cast<float>(window.getSize().x);
    float screenHeight = static_cast<float>(window.getSize().y);

    sf::Sprite sprite(texture);
    sprite.setScale({screenWidth / texture.getSize().x,screenHeight / texture.getSize().y});
    sf::RectangleShape button({ 200.f, 60.f });
    button.setPosition({screenWidth / 2.f - 100.f,screenHeight / 2.f - 30.f
        });
    button.setFillColor(sf::Color::Red);

    sf::Font font("C:/Windows/Fonts/arial.ttf");
    sf::Text buttonText(font, "Start New Game", 24);

    buttonText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = buttonText.getLocalBounds();

    buttonText.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,textBounds.position.y + textBounds.size.y / 2.f });

    sf::Font boldFont("C:/Windows/Fonts/arialbd.ttf");
    buttonText.setPosition({screenWidth / 2.f,screenHeight / 2.f
        });
    sf::Text buttonText2(boldFont, "STACK THE PIE", 50);
    sf::FloatRect titleBounds = buttonText2.getLocalBounds();

    buttonText2.setOrigin({ titleBounds.position.x + titleBounds.size.x / 2.f,titleBounds.position.y + titleBounds.size.y / 2.f });
    buttonText2.setPosition({screenWidth / 2.f, screenHeight * 0.12f
        });
    buttonText2.setFillColor(sf::Color::Black);

   
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i pixelPosition = mouse->position;

                    sf::Vector2f mousePosition =
                        window.mapPixelToCoords(pixelPosition);

                    if (button.getGlobalBounds().contains(mousePosition))
                    {
                        Level(window);
                        return 0;
                    }
                }
            }
        }

            window.clear(sf::Color(64, 64, 64));
            window.draw(sprite);
            window.draw(button);
            window.draw(buttonText);
            window.draw(buttonText2);
            window.display();
            
        

       
    }

    return 0;
}
