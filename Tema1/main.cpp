#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define assetsFolder "./resources/" 


int main(int agrc, char *argv[])
{

    sf::SoundBuffer sb;

    /* Window initialization */

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

    /* Textures */
    sf::Texture txBackground;
    txBackground.loadFromFile(assetsFolder "graphics/background.png");
    sf::Texture txTree;
    txTree.loadFromFile(assetsFolder "graphics/tree.png");
    sf::Texture txBee;
    txBee.loadFromFile(assetsFolder "graphics/bee.png");
    sf::Texture txCloud;
    txCloud.loadFromFile(assetsFolder "graphics/cloud.png");

    /* Sprites */
    std::vector<sf::Sprite *> vectors; // Vector of sprites

    sf::Sprite sBackground;
    sBackground.setTexture(txBackground);
    sBackground.setPosition(0, 0);
    vectors.push_back(&sBackground);

    sf::Sprite sTree;
    sTree.setTexture(txTree);
    sTree.setPosition(window.getSize().x / 2 - txTree.getSize().x / 2, 0);
    vectors.push_back(&sTree);

    sf::Sprite sBee;
    sBee.setTexture(txBee);
    sBee.setPosition(500, 800);
    bool beeActive = false;
    // How fast can the bee fly
    float beeSpeed = 0.0f;

    vectors.push_back(&sBee);

    sf::Sprite sCloud;
    sCloud.setTexture(txCloud);
    sCloud.setPosition(0, 0);
    bool cloudActive = false;
    float cloudSpeed = 0.0f;
    vectors.push_back(&sCloud);

    sf::Sprite sCloud2;
    sCloud2.setTexture(txCloud);
    sCloud2.setPosition(0, 250);
    bool cloud2Active = false;
    float cloud2Speed = 0.0f;
    vectors.push_back(&sCloud2);

    sf::Sprite sCloud3;
    sCloud3.setTexture(txCloud);
    sCloud3.setPosition(0, 500);
    bool cloud3Active = false;
    float cloud3Speed = 0.0f;
    vectors.push_back(&sCloud3);

    /* Fonts loading */
    sf::Font font;
    font.loadFromFile(assetsFolder "fonts/BrassMono/regular.otf");

    /* Text part */
    sf::Text myText;
    int points = 0;

    sf::Text messageText;
    sf::Text scoreText;

    messageText.setFont(font);
    scoreText.setFont(font);

    // Assign the actual message
    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");

    // Make it really big
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    messageText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White); 

    // Position the text
    sf::FloatRect textRect = messageText.getLocalBounds();

    messageText.setOrigin(textRect.left +
    textRect.width / 2.0f,
    textRect.top +
    textRect.height / 2.0f);

    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

    scoreText.setPosition(20, 20); 


    /* Game variables*/
    sf::Clock clock;
    sf::Time* dt = new sf::Time();
    bool paused = false;

    // Time bar
    sf::RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    sf::Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining; 

    while (window.isOpen())
    {

        window.clear();

        // Clear everything from the last frame
        /*     
        ****************************************
        Handle the players input
        ****************************************
        */

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {   
                paused = !paused; 
            }               
        }


        /*     
        ****************************************     
        Update the scene
        ****************************************     
        */


       if (!paused) {
            *dt = clock.restart(); 

            /* TimeBar */
            // Subtract from the amount of time remaining   
            timeRemaining -= dt->asSeconds();
            // size up the time bar
            timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond *
                timeRemaining, timeBarHeight)); 

            if (timeRemaining <= 0.0f) 
            {   
            // Pause the game   
            paused = true;   

            // Change the message shown to the player   
            messageText.setString("Out of time!!");   

            //Reposition the text based on its new size   
            sf::FloatRect textRect = messageText.getLocalBounds();
            messageText.setOrigin(textRect.left +     
                textRect.width / 2.0f,     
                textRect.top +     
                textRect.height / 2.0f);   

            messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            } 

            /* Bee */
            // Set up the bee
            if (!beeActive)
            {

                // How fast is the bee
                srand((int)time(0));
                beeSpeed = (rand() % 300) + 1000;
                float height = (rand() % 200) + window.getSize().y/8;
                sBee.setPosition(2000, height);
                beeActive = true;
            }
            else
            // Move the bee
            {
                sBee.setPosition(
                    sBee.getPosition().x -
                        (beeSpeed * dt->asSeconds()*4),
                    sBee.getPosition().y);

                // Has the bee reached the right hand edge of the screen?
                if (sBee.getPosition().x < -100)
                {
                    // Set it up ready to be a whole new cloud next frame
                    beeActive = false;
                }
            }


            // Update the score text   
            scoreText.setString("Score = " + std::to_string(points)); 
       }

        // Draw our game scene here

        for (auto sprite : vectors)
        {
            window.draw(*sprite);
        }
        
        /* Draw the text */

        // Draw the score
        window.draw(scoreText);
        window.draw(timeBar);
        if (paused) {   
        // Draw our message   
        window.draw(messageText);
        } 

        // Show everything we just drew
        window.display();
    }

    return 0;
}
