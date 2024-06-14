#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Mario Level");

    sf::Texture marioTexture;
    if (!marioTexture.loadFromFile("../assets/images/mario.png")) {
        std::cerr << "Error loading mario texture @assets/images\n";
    }

    sf::Sprite marioSprite(marioTexture);
    marioSprite.setScale(0.5, 0.5);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            // moving mario
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                marioSprite.move(5, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                marioSprite.move(-5, 0);
            }
        }

        window.clear();
        window.draw(marioSprite);
        window.display();
    }

    return 0;
}