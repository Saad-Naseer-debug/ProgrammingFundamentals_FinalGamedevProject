#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
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

    sf::Font font("C:/Windows/Fonts/arialbd.ttf");
    sf::Text endText(font, "", 60);
    bool gameOver = false;

    int score = 0;
    int bestScore = 0;
    ifstream inFile("best_score.txt");
    if (inFile)
    {
        inFile >> bestScore;
    }
    inFile.close();
    sf::Text scoreText(font, "", 30);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setPosition({ 10.f, 10.f });

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

                                score++;
                                if (score > bestScore)
                                {
                                    bestScore = score;
                                    ofstream outFile("best_score.txt");
                                    outFile << bestScore;
                                    outFile.close();
                                }

                                if (newY <= 0.f)
                                {
                                    gameOver = true;
                                    endText.setString("GAME FINISHED");
                                    endText.setFillColor(sf::Color::Green);
                                }
                                else
                                {
                                    moving = true;
                                }
                            }
                            else
                            {
                                gameOver = true;
                                endText.setString("GAME OVER");
                                endText.setFillColor(sf::Color::Red);
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
            if (gameOver)
            {
                sf::FloatRect textBounds = endText.getLocalBounds();
                endText.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,textBounds.position.y + textBounds.size.y / 2.f });
                endText.setPosition({ 400.f, 300.f });
                window.draw(endText);
            }
            scoreText.setString("Score: " + to_string(score) + "\nBest: " + to_string(bestScore));
            window.draw(scoreText);
            window.display();
            clock.restart();
        }
    }

    return 0;
}
