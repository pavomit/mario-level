#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Mario Level");
    window.setFramerateLimit(60);

    sf::Texture marioTexture;
    if (!marioTexture.loadFromFile("../assets/images/mario.png")) {
        std::cerr << "Error loading mario texture @assets/images\n";
    }

    sf::Sprite marioSprite(marioTexture);
    marioSprite.setScale(0.5, 0.5);
    marioSprite.setPosition(100, 400);

    int animation_state{ 0 };

    while (window.isOpen())
    {
        marioSprite.setTextureRect(sf::IntRect(animation_state, 0, 92, 175));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            // moving mario
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                marioSprite.move(5, 0);
                marioSprite.setScale(0.5, 0.5);
                animation_state += 92;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                marioSprite.move(-5, 0);
                marioSprite.setScale(-0.5, 0.5);
                animation_state += 92;
            }
        }

        if (animation_state > 184) {
            animation_state = 0;
        }

        window.clear();
        window.draw(marioSprite);
        window.display();
    }

    return 0;
}