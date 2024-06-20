#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    //++++++++++++++++++++ window +++++++++++++++++++++++++++++
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Mario Level");
    window.setFramerateLimit(120);

    //+++++++++++++++++++ mario +++++++++++++++++++++++++++++++++
    sf::Texture marioTexture;
    if (!marioTexture.loadFromFile("../assets/images/mario.png")) {
        std::cerr << "Error loading mario texture @assets/images\n";
    }

    sf::Sprite marioSprite(marioTexture);
    marioSprite.setScale(0.5, 0.5);
    marioSprite.setPosition(100, 533);

    //++++++++++++++++++++++ background ++++++++++++++++++++++++
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../assets/images/background.jpg")) {
        std::cerr << "Error loading background texture @assets/images\n";
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(2.1, 2.5);

    //++++++++++++++++++++++ house ++++++++++++++++++++++++
    sf::Texture houseTexture;
    if (!houseTexture.loadFromFile("../assets/images/house.png")) {
        std::cerr << "Error loading background texture @assets/images\n";
    }
    sf::Sprite houseSprite(houseTexture);
    houseSprite.setScale(1.3, 1.3);
    houseSprite.setPosition(5000, 310);

    //++++++++++++++++++++++ enemy ++++++++++++++++++++++++
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("../assets/images/m.png")) {
        std::cerr << "Error loading background texture @assets/images\n";
    }
    sf::Sprite enemySprite(enemyTexture);
    enemySprite.setScale(0.3, 0.3);
    enemySprite.setPosition(650, 570);

    bool emenyDirection = true; // true - > right | false <- left

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
    blockSprites[12].setScale(0, 0);
    blockSprites[21].setScale(0, 0);
    blockSprites[25].setScale(0, 0);
    blockSprites[33].setScale(0, 0);

    //++++++++++++++ animation realted variables ++++++++++++++++++++++++++++++++
    int animation_state{ 0 };
    float timer{ 0 };
    //++++++++++++++ gravity related varibles ++++++++++++++++++++++++++++++++
    float xForce{}, yForce{};

    //++++++++++++++ camera +++++++++++++++++++++++++++++++++++
    sf::View camera;
    camera.setSize(1200, 700);
    camera.setCenter(600, 350);

    //++++++++++++++ game phases +++++++++++++++++++++++++
    /*
    * 1- Mian Menu
    * 2- Play
    * 3- Win
    * 4- Lose 
    */
    int phase = 2;

    while (window.isOpen())
    {
        // play
        if (phase == 2) {
            // pahse:2 - start
            timer += 0.1;
            marioSprite.setTextureRect(sf::IntRect(animation_state, 0, 91, 175));
            sf::Event event;
            xForce = 0;

            // state conditions
            if (marioSprite.getGlobalBounds().intersects(houseSprite.getGlobalBounds())) {
                phase = 3;
                continue;
            }
            if (marioSprite.getGlobalBounds().intersects(enemySprite.getGlobalBounds())) {
                phase = 4;
                continue;
            }

            if (yForce <= 5) {
                yForce += 0.1;
            }

            //enemy movement
            if (enemySprite.getPosition().x <= 620) {
                emenyDirection = true;
            }
            else if (enemySprite.getPosition().x >= 940) {
                emenyDirection = false;
            }

            if (emenyDirection) {
                enemySprite.move(2, 0);
            }
            else {
                enemySprite.move(-2, 0);
            }

            //collision with blocks after jump
            for (int i = 0; i < numberOfBlocks; i++)
            {
                if (marioSprite.getGlobalBounds().intersects(blockSprites[i].getGlobalBounds())) {
                    yForce = 0;
                }
            }

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
            }

            // moving mario
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                xForce = 3;
                marioSprite.setScale(0.5, 0.5);
                if (timer > 1) {
                    animation_state += 91;
                    timer = 0;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && marioSprite.getPosition().x > 100) {
                xForce = -3;
                marioSprite.setScale(-0.5, 0.5);
                if (timer > 1) {
                    animation_state += 91;
                    timer = 0;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && yForce == 0) {
                yForce = -5;
            }

            marioSprite.move(xForce, yForce);

            if (animation_state > 182) {
                animation_state = 0;
            }

            //static background inside camera
            backgroundSprite.setPosition(marioSprite.getPosition().x - 100, 0);

            camera.setCenter(marioSprite.getPosition().x + 500, 350);
            window.setView(camera);

            window.clear();
            window.draw(backgroundSprite);
            window.draw(houseSprite);
            window.draw(enemySprite);
            for (int i = 0; i < numberOfBlocks; i++) {
                window.draw(blockSprites[i]);
            }
            window.draw(marioSprite);
            window.display();
            // pahse:2 - end
        }
        // win
        if (phase == 3) {
            window.clear(sf::Color::Green);
            window.display();
        }
        // lose
        if (phase == 4) {
            window.clear(sf::Color::Red);
            window.display();
        }
    }

    return 0;
}