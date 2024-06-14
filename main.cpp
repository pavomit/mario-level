#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    //++++++++++++++++++++ window +++++++++++++++++++++++++++++
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Mario Level");
    window.setFramerateLimit(60);

    //+++++++++++++++++++ mario +++++++++++++++++++++++++++++++++
    sf::Texture marioTexture;
    if (!marioTexture.loadFromFile("../assets/images/mario.png")) {
        std::cerr << "Error loading mario texture @assets/images\n";
    }

    sf::Sprite marioSprite(marioTexture);
    marioSprite.setScale(0.5, 0.5);
    marioSprite.setPosition(100, 500);

    //++++++++++++++++++++++ background ++++++++++++++++++++++++
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../assets/images/background.jpg")) {
        std::cerr << "Error loading background texture @assets/images\n";
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(2.1, 2.5);

    //+++++++++++++++++++++++ blocks ++++++++++++++++++++++++++
    const int numberOfBlocks{ 100 };

    sf::Texture blockTexture;
    if (!blockTexture.loadFromFile("../assets/images/block.png")) {
        std::cerr << "Error loading block texture @assets/images\n";
    }

    sf::Sprite blockSprites[numberOfBlocks];
    for (int i = 0; i < numberOfBlocks; i++) {
        blockSprites[i].setTexture(blockTexture);
        blockSprites[i].setPosition(i * 80, 620);
        blockSprites[i].setScale(0.4, 0.4);
    }

    // no blocks(holes)
    blockSprites[7].setScale(0, 0);

    //++++++++++++++ animation ++++++++++++++++++++++++++++++++
    int animation_state{ 0 };
    float timer{ 0 };

    while (window.isOpen())
    {
        timer += 0.1;
        marioSprite.setTextureRect(sf::IntRect(animation_state, 0, 91, 175));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            // moving mario
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                marioSprite.move(5, 0);
                marioSprite.setScale(0.5, 0.5);
                if (timer > 1) {
                    animation_state += 91;
                    timer = 0;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                marioSprite.move(-5, 0);
                marioSprite.setScale(-0.5, 0.5);
                if (timer > 1) {
                    animation_state += 91;
                    timer = 0;
                }
            }
        }

        if (animation_state > 182) {
            animation_state = 0;
        }

        window.clear();
        window.draw(backgroundSprite);
        for (int i = 0; i < numberOfBlocks; i++) {
            window.draw(blockSprites[i]);
        }
        window.draw(marioSprite);
        window.display();
    }

    return 0;
}