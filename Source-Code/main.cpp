//Beetle Boy
//2016
//7th Stand User 2
//7SU2 Demo
//define _WIN32_WINNT 0x0500
#include <windows.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <list>
#include <ctype.h>
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "AnimatedSprite.cpp"
#include "Animation.cpp"
#include "Entity.hpp"

using namespace std;

int textSpeed = 25;

sf::Clock frameClock;
sf::Text stx;
sf::Text wtx;
sf::Text otx;
sf::Time elapsedTime;
sf::RenderWindow window(sf::VideoMode(640, 480), "7th Stand User 2", sf::Style::Close);
std::list<sf::Sprite> sprites;
std::list<sf::Texture> textures;
std::list<sf::Text> texts;
std::list<AnimatedSprite> animatedSprites;
std::string quote[1];
std::string genA[] = {"Male", "Female"};
std::string appMA[] = {"Average", "Chubby", "Pretty Boy", "Punk", "Glasses", "Short"};
std::string appFA[] = {"Average", "Chubby", "Ganguro", "Sukeban", "Glasses", "Short"};
std::string appMA1[] = {"Average", "Chubby", "Pretty Boy", "Not any of these..."};
std::string appMA2[] = {"Punk", "Glasses", "Short", "Go back"};
std::string appFA1[] = {"Average", "Chubby", "Ganguro", "Not any of these..."};
std::string appFA2[] = {"Sukeban", "Glasses", "Short", "Go back"};
std::string ranA[] = {"Short", "Mid", "Long"};
std::string typA[] = {"Power", "Speed", "Control", "Special", "Support", "Swarm"};

class Stand
{
public:
    string nam; //Stand's name
    int ran; //Stand's range
    int typ; //Stand's type
    int lev; //Stand's level
    int hpc; //Stand's current HP
    int hpt; //Stand's total HP
    int spc; //Stand's current SP
    int spt; //Stand's total SP
    int pow; //Stand's Power
    int dur; //Stand's Durability
    int spi; //Stand's Spirit
    int spe; //Stand's Speed
    sf::Sprite staSprite;
    sf::Texture staTexture;
    //Non-Battle Stats
    string pow_s; //Destructive Power
    string spe_s; //Speed
    string ran_s; //Range
    string dur_s; //Durability
    string pre_s; //Precision
    string dev_s; //Development Potential

    void initStand(int);
    void showStand(void);
};

class Protagonist
{
    string nam; //Protagonist's name
    Stand sta; //Protagonist's Stand
    int gen; //Protagonist's gender (male or female)
    int app; //Protagonist's appearance (see above)
public:
    void sapq();
};

void redraw()
{
    window.clear(sf::Color::Black);
    std::list<sf::Sprite>::iterator sprite;
    std::list<sf::Texture>::iterator texture = textures.begin();
    std::list<sf::Text>::iterator text;
    std::list<AnimatedSprite>::iterator animatedSprite = animatedSprites.begin();
    while (window.isOpen())
    {
        for (sprite = sprites.begin(); sprite != sprites.end(); ++sprite)
        {
            sf::Sprite s = *sprite;
            s.setTexture(*texture);
            window.draw(s);
            ++texture;
        }
        for (text = texts.begin(); text != texts.end(); ++text)
        {
            window.draw(*text);
        }
        for (animatedSprite = animatedSprites.begin(); animatedSprite != animatedSprites.end(); ++animatedSprite)
        {
            window.draw(*animatedSprite);
        }
        window.display();
        return;
    }
    return;
}

void advance()
{
    window.setKeyRepeatEnabled(false);
    sf::Event event;
    while (window.waitEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
                return;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            {
                return;
            }
            break;

        default:
            break;
        }
    }
}

void Stand::showStand()
{
    window.clear(sf::Color::White);
    sf::Vector2u dimensions;
    dimensions = staTexture.getSize();
    int x = (window.getSize().x - dimensions.x)/2.0;
    int y = 50;
    staSprite.setPosition(x, y);
    textures.push_back(staTexture);
    sprites.push_back(staSprite);
    redraw();
    return;
}

void showApp(int gen, int app)
{
    window.clear(sf::Color::White);
    sf::Texture texture1, texture2, texture3;
    sf::Sprite sprite1, sprite2, sprite3;
    int x1, x2, x3;
    int y1, y2, y3;
    string filename = "Images/";
    switch (gen)
    {
    case 1:
        filename.append("m");
        break;
    case 2:
        filename.append("f");
        break;
    default:
        return;
        break;
    }
    switch (app)
    {
    case 1:
        filename.append("average.png");
        break;
    case 2:
        filename.append("chubby.png");
        break;
    case 3:
        filename.append("pretty.png");
        break;
    case 4:
        filename.append("punk.png");
        break;
    case 5:
        filename.append("glasses.png");
        break;
    case 6:
        filename.append("short.png");
        break;
    default:
        break;
    }
    if (app < 7)
    {
        if (!texture1.loadFromFile(filename))
        {
            //error
            return;
        }
        else
        {
            x1 = (window.getSize().x - texture1.getSize().x) / 2.0;
            y1 = (window.getSize().y - texture1.getSize().y) / 2.0;
            sprite1.setPosition(x1, y1);
            sprites.push_back(sprite1);
            textures.push_back(texture1);
            redraw();
            return;
        }
    }
    else if (app == 7)
    {
        string filename2 = filename;
        filename2.append("average.png");
        if(!texture1.loadFromFile(filename2))
        {
            //error
            return;
        }
        filename2 = filename;
        filename2.append("chubby.png");
        if (!texture2.loadFromFile(filename2))
        {
            //error
            return;
        }
        filename2 = filename;
        filename2.append("pretty.png");
        if (!texture3.loadFromFile(filename2))
        {
            //error
            return;
        }
    }
    else if (app == 8)
    {
        string filename2 = filename;
        filename2.append("punk.png");
        if(!texture1.loadFromFile(filename2))
        {
            //error
            return;
        }
        filename2 = filename;
        filename2.append("glasses.png");
        if(!texture2.loadFromFile(filename2))
        {
            //error
            return;
        }
        filename2 = filename;
        filename2.append("short.png");
        if(!texture3.loadFromFile(filename2))
        {
            //error
            return;
        }
    }
    else
    {
        return;
    }
    x1 = (window.getSize().x - (texture1.getSize().x + texture2.getSize().x + texture3.getSize().x)) / 2.0;
    x2 = x1 + texture1.getSize().x;
    x3 = x2 + texture2.getSize().x;
    y1 = (window.getSize().y) / 2.0 - texture1.getSize().y + 100;
    y2 = (window.getSize().y) / 2.0 - texture2.getSize().y + 100;
    y3 = (window.getSize().y) / 2.0 - texture3.getSize().y + 100;
    sprite1.setPosition(x1, y1);
    sprite2.setPosition(x2, y2);
    sprite3.setPosition(x3, y3);
    sprites.push_back(sprite1);
    sprites.push_back(sprite2);
    sprites.push_back(sprite3);
    textures.push_back(texture1);
    textures.push_back(texture2);
    textures.push_back(texture3);
    redraw();
    return;
}

void speech(string speaker, string words)
{
    texts.clear();
    sf::Event event;
    sf::Clock clock;
    string w;
    window.setKeyRepeatEnabled(true);
    stx.setPosition(35, 325);
    wtx.setPosition(50, 355);
    textSpeed = 25;
    if (speaker.length() != 0)
    {
        speaker.append(":");
        w = "\"";
        w.append(words);
        w.append("\"");
    }
    else
    {
        w.append(words);
        wtx.move(0, -30);
    }
    stx.setString(speaker);
    texts.push_back(stx);
    bool skip = false;
    for (unsigned int i = 0; i <= w.length(); i++)
    {
        if (w[i] == '*')
        {
            advance();
            w.erase(w.begin()+i);
            skip = false;
        }
        wtx.setString(w.substr(0, i));
        texts.push_back(wtx);
        bool animated = false;
        if (skip)
        {
            redraw();
            animated = true;
        }
        while (!animated)
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z)
                {
                    textSpeed = 10;
                }
                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Z)
                {
                    textSpeed = 25;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X)
                {
                    skip = true;
                }
            }
            elapsedTime = clock.getElapsedTime();
            if (elapsedTime.asMilliseconds() > textSpeed)
            {
                clock.restart();
                redraw();
                animated = true;
            }
        }
        texts.pop_back();
    }
    advance();
}

void speech(string speaker, string words, int speedPointer[])
{
    texts.clear();
    string w;
    window.setKeyRepeatEnabled(false);
    stx.setPosition(35, 325);
    wtx.setPosition(50, 355);

    if (speaker.length() != 0)
    {
        speaker.append(":");
        w = "\"";
        w.append(words);
        w.append("\"");
    }
    else
    {
        w.append(words);
        wtx.move(0, -30);
    }
    stx.setString(speaker);
    texts.push_back(stx);
    for (unsigned int i = 0; i <= w.length(); i++)
    {
        wtx.setString(w.substr(0, i));
        texts.push_back(wtx);
        Sleep(*speedPointer);
        redraw();
        texts.pop_back();
        speedPointer++;
    }
    advance();
}

int choices(string words[], int options)
{
    texts.clear();
    window.setKeyRepeatEnabled(false);
    int input = 0;
    wtx.setPosition(50, 325);
    otx.setPosition(35, 355);
    int i;
    for (i = 0; i < options; i++)
    {
        wtx.move(0, 30);
        wtx.setString(words[i]);
        texts.push_back(wtx);
    }
    texts.push_back(otx);
    redraw();
    sf::Event event;
    while (window.waitEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
            return 0;
            break;

        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
                return (input + 1);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            {
                if (words[1].compare("No") == 0)
                {
                    return 2;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if (input == 0)
                {
                    input = options - 1;
                    otx.move(0, 30*(options-1));
                }
                else
                {
                    input -= 1;
                    otx.move(0, -30);
                }
                texts.pop_back();
                texts.push_back(otx);
                redraw();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                if (input == (options - 1))
                {
                    input = 0;
                    otx.move(0, -30*(options-1));
                }
                else
                {
                    input += 1;
                    otx.move(0, 30);
                }
                texts.pop_back();
                texts.push_back(otx);
                redraw();
            }
            break;

        default:
            break;
        }
    }
    return 0;
}

void Protagonist::sapq()
{
    texts.clear();
    sprites.clear();
    textures.clear();
    srand(time(NULL));
    int A = 0;
    int B = 0;
    int C = 0;
    int D = 0;
    int E = 0;
    int F = 0;
    int G = 0;
    int H = 0;
    int I = 0;

    std::string quote = "Welcome to the 7SU2 Personality Evaluation \n*(Coding Demo Version)";

    std::string qst1 = "First off, picture yourself in everyday surroundings. \nWhere are you standing?";

    std::string qst2 = "How much trust do you place in new people?";

    std::string qstA[] = {  "Your boyfriend or girlfriend has left their phone behind at your \nhouse. Do you check their messages?",
                            "You're at a party and you spot someone drinking by the \nwindow on their own. They seem lonely. Do you try to make \nconversation?",
                            "You're working on something important, but your friend is \nswamped with assignments. Do you put your project on the \nbackburner to help them?",
                            "Do you think all the world's problems will be solved if people \nsimply learn to cooperate?"};

    std::string ans[3];

    std::string qstB[] = {  "Do you have trouble with social obligations?",
                            "When your family members get sloppy, do you chastise \nthem?",
                            "Do you like to give presents that can be kept as a memento, \nrather than practical gifts?",
                            "Do you put a high value on your individuality?"};

    std::string qstC[] = {  "Do you often go out of your way to attend to others' needs?",
                            "When something good happens, do you suspect that there's\n a \"catch\"?",
                            "Do you talk to yourself frequently?",
                            "Are you a good liar?"};

    std::string qstD[] = {  "Are you flexible enough in your stances if someone puts up \na persuasive counterargument?",
                            "When you're troubled, do you like to talk it out with others?",
                            "Are you fussy about how others view you?",
                            "Do you readily take positions of leadership?"};

    std::string qstE[] = {  "Do you like being the only person in a room?",
                            "Do you think there's no one that truly understands you?",
                            "Do you dislike inviting friends over?",
                            "Do you have a hard time saying 'no'?"};

    std::string qstF[] = {  "Are you a quiet person?",
                            "When something exciting is going on, do you immediately \nperk up and want to join the fun?",
                            "Are you uninterested in gambling?",
                            "Do you think that life is short, and therefore enjoying yourself \nis most important?"};

    std::string qstG[] = {  "Are you often quick to throw in the towel?",
                            "Do you think that people are fundamentally evil by nature?",
                            "Are there people you trust so much that you feel completely \nat ease with them?",
                            "Do you aspire to become rich?"};

    std::string qstH[] = {  "Do you often worry about standing out?",
                            "On your days off, do you prefer going out to relaxing at \nhome?",
                            "Do you find yourself thinking 'women are scary'?",
                            "Are you bad at keeping still?"};

    std::string qstI[] = {  "Do you think that the ends justify the means?",
                            "Do you believe in 'survival of the fittest' - that it's natural for \nthose who are weaker to get picked off?",
                            "Do you think that two against one is unfair?",
                            "Do you think putting high hopes in others will just lead to being \nlet down?"};

    std::string speaker = "Rohan";

    speech("", quote);
    speech(speaker, qst1);

    ans[0] = "Mingling with the group";
    ans[1] = "Right in the center";
    ans[2] = "Off in my own place";
    int input1 = choices(ans, 3);
    if (input1 == 0)
    {
        return;
    }
    speech(speaker, qst2);
    ans[0] = "I trust them from the outset";
    ans[1] = "I make them earn my trust";
    ans[2] = "Depends on the situation";
    int input2 = choices(ans, 3);
    if (input2 == 0)
    {
        return;
    }
    ans[0] = "Yes";
    ans[1] = "No";

    if (input1 == 1)
    {
        if (input2 == 1)
        {
            F = rand() % 3 + 1;

            goto qF;
        }
        else if (input2 == 2)
        {
            C = rand() % 3 + 1;

            goto qC;
        }
        else if (input2 == 3)
        {
            I = rand() % 3 + 1;

            goto qI;
        }
    }
    else if (input1 == 2)
    {
        if (input2 == 1)
        {
            B = rand() % 3 + 1;

            goto qB;
        }
        else if (input2 == 2)
        {
            H = rand() % 3 + 1;

            goto qH;
        }
        else if (input2 == 3)
        {
            E = rand() % 3 + 1;

            goto qE;
        }
    }
    else if (input1 == 3)
    {
        if (input2 == 1)
        {
            A = rand() % 3 + 1;

            goto qA;
        }
        else if (input2 == 2)
        {
            G = rand() % 3 + 1;

            goto qG;
        }
        else if (input2 == 3)
        {
            D = rand() % 3 + 1;

            goto qD;
        }
    }

    qA:
        input1 = 0;
        speech(speaker, qstA[A-1]);
        input1 = choices(ans, 2);
        if (input1 == 1)
        {
            B++;

            if (B == 5)
            {
                goto endQuiz;
            }
            else
            {
                goto qB;
            }
        }
        else if (input1 == 2)
        {
            I++;

            if (I == 5)
            {
                goto endQuiz;
            }
            else
            {
                goto qI;
            }
        }
        else
        {
            return;
        }

    qB:
        input1 = 0;
        speech(speaker, qstB[B-1]);
        input1 = choices(ans, 2);
        if (input1 == 1)
        {
            if (B == 1)
            {
                C++;

                if (C == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qC;
                }
            }
            else if (B > 1)
            {
                A++;

                if (A == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qA;
                }
            }
        }
        else if (input1 == 2)
        {
            if (B == 1)
            {
                A++;

                if (A == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qA;
                }
            }
            else if (B > 1)
            {
                C++;

                if (C == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qC;
                }
            }
        }
        else
        {
            return;
        }

    qC:
        input1 = 0;
        speech(speaker, qstC[C-1]);
        input1 = choices(ans, 2);
        if (input1 == 1)
        {
            if (C == 1 || C == 4)
            {
                B++;

                if (B == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qB;
                }
            }
            else if (C == 2 || C == 3)
            {
                D++;

                if (D == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qD;
                }
            }
        }
        else if (input1 == 2)
        {
            if (C == 1 || C == 4)
            {
                D++;

                if (D == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qD;
                }
            }
            else if (C == 2 || C == 3)
            {
                B++;

                if (B == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qB;
                }
            }
        }
        else
        {
            return;
        }
    qD:
        input1 = 0;
        speech(speaker, qstD[D-1]);
        input1 = choices(ans, 2);
        if (input1 == 1)
        {
            if (D == 1)
            {
                E++;

                if (E == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qE;
                }
            }
            else if (D > 1)
            {
                C++;

                if (C == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qC;
                }
            }
        }
        else if (input1 == 2)
        {
            if (D == 1)
            {
                C++;

                if (C == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qC;
                }
            }
            else if (D > 1)
            {
                E++;

                if (E == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qE;
                }
            }
        }
        else
        {
            return;
        }

    qE:
        input1 = 0;
        speech(speaker, qstE[E-1]);
        input1 = choices(ans, 2);
        if (input1 == 1)
        {
            D++;

            if (D == 5)
            {
                goto endQuiz;
            }
            else
            {
                goto qD;
            }
        }
        else if (input1 == 2)
        {
            F++;

            if (F == 5)
            {
                goto endQuiz;
            }
            else
            {
                goto qF;
            }
        }
        else
        {
            return;
        }

    qF:
        input1 = 0;
        speech(speaker, qstF[F-1]);
        input1 = choices(ans, 2);
        if (input1 == 1)
        {
            if (F == 2)
            {
                G++;

                if (G == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qG;
                }
            }
            else if (F != 2)
            {
                E++;

                if (E == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qE;
                }
            }
        }
        else if (input1 == 2)
        {
            if (F == 2)
            {
                E++;

                if (E == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qE;
                }
            }
            else if (F != 2)
            {
                G++;

                if (G == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qG;
                }
            }
        }
        else
        {
            return;
        }

    qG:
        input1 = 0;
        speech(speaker, qstG[G-1]);
        input1 = choices(ans, 2);
        if (input1 == 1)
        {
            if (G == 2)
            {
                H++;

                if (H == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qH;
                }
            }
            else if (G != 2)
            {
                F++;

                if (F == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qF;
                }
            }
        }
        else if (input1 == 2)
        {
            if (G == 2)
            {
                F++;

                if (F == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qF;
                }
            }
            else if (G != 2)
            {
                H++;

                if (H == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qH;
                }
            }
        }
        else
        {
            return;
        }

    qH:
        input1 = 0;
        speech(speaker, qstH[H-1]);
        input1 = choices(ans, 2);
        if (input1 == 1)
        {
            if (H == 1)
            {
                I++;

                if (I == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qI;
                }
            }
            else if (H > 1)
            {
                G++;

                if (G == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qG;
                }
            }
        }
        else if (input1 == 2)
        {
            if (H == 1)
            {
                G++;

                if (G == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qG;
                }
            }
            else if (H > 1)
            {
                I++;

                if (I == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qI;
                }
            }
        }
        else
        {
            return;
        }

    qI:
        input1 = 0;
        speech(speaker, qstI[I-1]);
        input1 = choices(ans, 2);
        if (input1 == 1)
        {
            if (I == 3)
            {
                A++;

                if (A == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qA;
                }
            }
            else if (I != 3)
            {
                H++;

                if (H == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qH;
                }
            }
        }
        else if (input1 == 2)
        {
            if (I == 3)
            {
                H++;

                if (H == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qH;
                }
            }
            else if (I != 3)
            {
                A++;

                if (A == 5)
                {
                    goto endQuiz;
                }
                else
                {
                    goto qA;
                }
            }
        }
        else
        {
            return;
        }

    endQuiz:
        int standIndex = 0;
        if (A == 5)
        {
            if (B >= I)
            {
                standIndex = 12; //Long Special
            }
            else if (B < I)
            {
                standIndex = 10; //Short Special
            }
        }
        else if (B == 5)
        {
            if (A >= C)
            {
                standIndex = 5; //Mid Speed
            }
            else if (A < C)
            {
                standIndex = 8; //Mid Control
            }
        }
        else if (C == 5)
        {
            if (B >= D)
            {
                standIndex = 15; //Long Support
            }
            else if (B < D)
            {
                standIndex = 16; //Short Swarm
            }
        }
        else if (D == 5)
        {
            if (C > E)
            {
                standIndex = 6; //Long Speed
            }
            else if (C < E)
            {
                standIndex = 9; //Long Control
            }
        }
        else if (E == 5)
        {
            if (D >= F)
            {
                standIndex = 13; //Short Support
            }
            else if (D < F)
            {
                standIndex = 2; //Mid Power
            }
        }
        else if (F == 5)
        {
            if (E >= G)
            {
                standIndex = 17; //Mid Swarm
            }
            else if (E < G)
            {
                standIndex = 4; //Short Speed
            }
        }
        else if (G == 5)
        {
            if (F >= H)
            {
                standIndex = 14; //Mid Support
            }
            else if (F < H)
            {
                standIndex = 3; //Long Power
            }
        }
        else if (H == 5)
        {
            if (G >= I)
            {
                standIndex = 11; //Mid Special
            }
            else if (G < I)
            {
                standIndex = 1; //Short Power
            }
        }
        else if (I == 5)
        {
            if (H >= A)
            {
                standIndex = 7; //Short Control
            }
            else if (H < A)
            {
                standIndex = 18; //Long Swarm
            }
        }
        sta.initStand(standIndex);
        int bonus1 = A + C + E + G + I;
        int bonus2 = B + D + F + H;
        sta.dur += bonus1;
        sta.spt += bonus1;
        sta.spc += bonus1;
        sta.pow += bonus2;
        sta.hpt += bonus2;
        sta.hpc += bonus2;
        quote = "I've got it! Your Stand's name is...\n";
        quote.append(sta.nam);
        quote.append("!");
        sta.showStand();
        speech(speaker, quote);
        quote = "Destructive Power: ";
        quote.append(sta.pow_s);
        quote.append("\nSpeed: ");
        quote.append(sta.spe_s);
        quote.append("\nRange: ");
        quote.append(sta.ran_s);
        quote.append("\nDurability: ");
        quote.append(sta.dur_s);
        quote.append("\nDevelopment Potential: ");
        quote.append(sta.dev_s);
        speech("", quote);
        sprites.pop_back();
        textures.pop_back();
        /*
        quote = "What is your name?";
        speech(speaker, quote);
        cin >> nam;
        */
        quote = "Are you male or female?";
        speech(speaker, quote);
        gen = choices(genA, 2);
        if (gen == 0)
        {
            return;
        }
        quote = "Which of the following descriptions best describes your \nappearance?";
        speech(speaker, quote);
        app = 8;
        while (app % 4 == 0)
        {
            if (gen == 1)
            {
                if (app == 8)
                {
                    showApp(1, 7);
                    app = choices(appMA1, 4);
                }
                else if (app == 4)
                {
                    showApp(1, 8);
                    app = choices(appMA2, 4) + 4;
                }
                else
                {
                    return;
                }
            }
            else if (gen == 2)
            {
                if (app == 8)
                {
                    showApp(2, 7);
                    app = choices(appFA1, 4);
                }
                else if (app == 4)
                {
                    showApp(2, 8);
                    app = choices(appFA2, 4) + 4;
                }
                else
                {
                    return;
                }
            }
            for (int i = 0; i < 3; i++)
            {
                sprites.pop_back();
                textures.pop_back();
            }
        }
        if (app > 3)
        {
            app--;
        }
        quote = "So, you're a ";
        quote.append(genA[gen-1]);
        quote.append(" and you look ");
        if (gen == 1)
        {
            quote.append(appMA[app-1]);
        }
        else
        {
            quote.append(appFA[app-1]);
        }
        quote.append(".");
        sta.showStand();
        showApp(gen, app);
        speech(speaker, quote);
        speech(speaker, "Try again?");
        input1 = choices(ans, 2);
        if (input1 == 1)
        {
            sapq();
        }
        else
        {
            window.close();
            return;
        }
        /*
        cout << "\nName: " << nam << "\n";
        cout << "Gender: " << genA[gen-1] << "\n";
        if (gen)
            cout << "Appearance: " << appMA[app-1] << "\n";
        else
            cout << "Appearance: " << appFA[app-1] << "\n";
        cout << "Stand: " << sta.nam << "\n";
        cout << "Range: " << ranA[sta.ran-1] << "\n";
        cout << "Type: " << typA[sta.typ-1] << "\n";
        cout << "Level: " << sta.lev << "\n";
        cout << "HP: " << sta.hpc << "/" << sta.hpt << "\n";
        cout << "SP: " << sta.spc << "/" << sta.spt << "\n";
        cout << "Power: " << sta.pow << "\n";
        cout << "Durability: " << sta.dur << "\n";
        cout << "Spirit: " << sta.spi << "\n";
        cout << "Speed: " << sta.spe << "\n";
        */
        return;
}

void Stand::initStand(int i)
{
    ran = (i-1) % 3 + 1;
    typ = (i-1) / 3 + 1;
    lev = 1;
    string filename = "Images/";
    if (typ == 1)
    {
        if (ran == 1)
        {
            nam = "Motorhead";
            hpc = 40;
            hpt = 40;
            spc = 20;
            spt = 20;
            pow = 17;
            dur = 13;
            spi = 18;
            spe = 15;
            pow_s = "A";
            spe_s = "A";
            ran_s = "E";
            dur_s = "B";
            pre_s = "D";
            dev_s = "A";
            filename.append("motorhead.png");
        }
        else if (ran == 2)
        {
            nam = "Tenacious D";
            hpc = 40;
            hpt = 40;
            spc = 29;
            spt = 29;
            pow = 18;
            dur = 12;
            spi = 20;
            spe = 16;
            pow_s = "A";
            spe_s = "D";
            ran_s = "C";
            dur_s = "B";
            pre_s = "B";
            dev_s = "A";
            filename.append("tenaciousd.png");
        }
        else if (ran == 3)
        {
            nam = "Ace of Spades";
            hpc = 40;
            hpt = 40;
            spc = 29;
            spt = 29;
            pow = 15;
            dur = 14;
            spi = 20;
            spe = 19;
            pow_s = "B";
            spe_s = "C";
            ran_s = "A";
            dur_s = "A";
            pre_s = "B";
            dev_s = "A";
            filename.append("aceofspades.png");
        }
    }
    else if (typ == 2)
    {
        if (ran == 1)
        {
            nam = "Slim Shady";
            hpc = 40;
            hpt = 40;
            spc = 33;
            spt = 33;
            pow = 13;
            dur = 16;
            spi = 26;
            spe = 32;
            pow_s = "C";
            spe_s = "A";
            ran_s = "D";
            dur_s = "A";
            pre_s = "B";
            dev_s = "A";
            filename.append("slimshady.png");
        }
        else if (ran == 2)
        {
            nam = "Helter Skelter";
            hpc = 40;
            hpt = 40;
            spc = 40;
            spt = 40;
            pow = 12;
            dur = 16;
            spi = 28;
            spe = 31;
            pow_s = "D/B/A";
            spe_s = "C/B/A";
            ran_s = "C/D/A";
            dur_s = "D/B/C";
            pre_s = "B/A/B";
            dev_s = "A/C/E";
            filename.append("helterskelteract1.png");
        }
        else if (ran == 3)
        {
            nam = "Light Up The Night";
            hpc = 40;
            hpt = 40;
            spc = 40;
            spt = 40;
            pow = 13;
            dur = 15;
            spi = 22;
            spe = 33;
            pow_s = "C";
            spe_s = "A";
            ran_s = "B";
            dur_s = "C";
            pre_s = "A";
            dev_s = "A";
            filename.append("lightupthenight.png");
        }
    }
    else if (typ == 3)
    {
        if (ran == 1)
        {
            nam = "Space Oddity";
            hpc = 40;
            hpt = 40;
            spc = 20;
            spt = 20;
            pow = 23;
            dur = 31;
            spi = 16;
            spe = 19;
            pow_s = "D";
            spe_s = "B";
            ran_s = "D";
            dur_s = "C";
            pre_s = "A";
            dev_s = "A";
            filename.append("spaceoddity.png");
        }
        else if (ran == 2)
        {
            nam = "Danger Zone";
            hpc = 40;
            hpt = 40;
            spc = 32;
            spt = 32;
            pow = 11;
            dur = 18;
            spi = 24;
            spe = 13;
            pow_s = "E";
            spe_s = "B";
            ran_s = "B";
            dur_s = "A";
            pre_s = "C";
            dev_s = "A";
            filename.append("dangerzone.png");
        }
        else if (ran == 3)
        {
            nam = "Velvet Revolver";
            hpc = 40;
            hpt = 40;
            spc = 37;
            spt = 37;
            pow = 12;
            dur = 17;
            spi = 23;
            spe = 19;
            pow_s = "B";
            spe_s = "A";
            ran_s = "A";
            dur_s = "C";
            pre_s = "A";
            dev_s = "A";
            filename.append("velvetrevolver.png");
        }
    }
    else if (typ == 4)
    {
        if (ran == 1)
        {
            nam = "The Stand";
            hpc = 40;
            hpt = 40;
            spc = 33;
            spt = 33;
            pow = 13;
            dur = 16;
            spi = 26;
            spe = 32;
            pow_s = "D";
            spe_s = "D";
            ran_s = "E";
            dur_s = "C";
            pre_s = "B";
            dev_s = "None";
            filename.append("thestand.png");
        }
        else if (ran == 2)
        {
            nam = "New York Minute";
            hpc = 40;
            hpt = 40;
            spc = 40;
            spt = 40;
            pow = 12;
            dur = 16;
            spi = 28;
            spe = 31;
            pow_s = "D/C/B";
            spe_s = "D/A/B";
            ran_s = "C/B/A";
            dur_s = "C/B/A";
            pre_s = "C/C/A";
            dev_s = "A/C/E";
            filename.append("newyorkminuteact1.png");
        }
        else if (ran == 3)
        {
            nam = "Hip To Be Square";
            hpc = 40;
            hpt = 40;
            spc = 40;
            spt = 40;
            pow = 13;
            dur = 15;
            spi = 22;
            spe = 33;
            pow_s = "D";
            spe_s = "A";
            ran_s = "A";
            dur_s = "D";
            pre_s = "A";
            dev_s = "A";
            filename.append("hiptobesquare.png");
        }
    }
    else if (typ == 5)
    {
        if (ran == 1)
        {
            nam = "The Wall";
            hpc = 40;
            hpt = 40;
            spc = 34;
            spt = 34;
            pow = 12;
            dur = 21;
            spi = 20;
            spe = 23;
            pow_s = "B";
            spe_s = "D";
            ran_s = "D";
            dur_s = "S";
            pre_s = "B";
            dev_s = "A";
            filename.append("thewall.png");
        }
        else if (ran == 2)
        {
            nam = "Red Light Special";
            hpc = 40;
            hpt = 40;
            spc = 36;
            spt = 36;
            pow = 14;
            dur = 22;
            spi = 24;
            spe = 20;
            pow_s = "B";
            spe_s = "D";
            ran_s = "C";
            dur_s = "C";
            pre_s = "B";
            dev_s = "A";
            filename.append("redlightspecial.png");
        }
        else if (ran == 3)
        {
            nam = "Take On Me";
            hpc = 40;
            hpt = 40;
            spc = 30;
            spt = 30;
            pow = 13;
            dur = 22;
            spi = 20;
            spe = 21;
            pow_s = "C";
            spe_s = "A";
            ran_s = "A";
            dur_s = "C";
            pre_s = "C";
            dev_s = "A";
            filename.append("takeonme.png");
        }
    }
    else if (typ == 6)
    {
        if (ran == 1)
        {
            nam = "Wrecking Crew";
            hpc = 40;
            hpt = 40;
            spc = 38;
            spt = 38;
            pow = 15;
            dur = 19;
            spi = 22;
            spe = 22;
            pow_s = "A";
            spe_s = "C";
            ran_s = "D";
            dur_s = "A";
            pre_s = "C";
            dev_s = "A";
            filename.append("wreckingcrew.png");
        }
        else if (ran == 2)
        {
            nam = "Danger! High Voltage";
            hpc = 40;
            hpt = 40;
            spc = 40;
            spt = 40;
            pow = 15;
            dur = 17;
            spi = 16;
            spe = 17;
            pow_s = "B";
            spe_s = "C";
            ran_s = "B";
            dur_s = "C";
            pre_s = "C";
            dev_s = "A";
            filename.append("danger!highvoltage.png");
        }
        else if (ran == 3)
        {
            nam = "Maneater";
            hpc = 40;
            hpt = 40;
            spc = 33;
            spt = 33;
            pow = 12;
            dur = 21;
            spi = 20;
            spe = 23;
            pow_s = "A";
            spe_s = "B";
            ran_s = "A";
            dur_s = "B";
            pre_s = "E";
            dev_s = "A";
            filename.append("maneater.png");
        }
    }
    if (!staTexture.loadFromFile(filename))
    {
        //error
        return;
    }
    return;
}

int locationChange(MapSprite &game_map, MovingSprite &mc_sprite)
{
    if (game_map.mapName.compare("Hirose Residence, 1F") == 0)
    {
        if (mc_sprite.getPosition().x == 576 && mc_sprite.getPosition().y == 384)
        {
            game_map = MapSprite();
            if (!game_map.load("Maps/hirosehouse2f.png", sf::Vector2u(32, 32), 22, 35))
                return 0;
            mc_sprite.currentAnimation = &mc_sprite.walkD;
            mc_sprite.setPosition(sf::Vector2f(576, 352));
            mc_sprite.moving[1] = true;
            mc_sprite.walking = true;
            mc_sprite.nextSpot = 384;
        }
    }
    else if (game_map.mapName.compare("Hirose Residence, 2F") == 0)
    {
        if (mc_sprite.getPosition().x == 576 && mc_sprite.getPosition().y == 352)
        {
            game_map = MapSprite();
            if (!game_map.load("Maps/hirosehouse1f.png", sf::Vector2u(32, 32), 34, 40))
                return 0;
            mc_sprite.currentAnimation = &mc_sprite.walkD;
            mc_sprite.setPosition(sf::Vector2f(576, 384));
            mc_sprite.moving[1] = true;
            mc_sprite.walking = true;
            mc_sprite.nextSpot = 416;
        }
        else if (mc_sprite.getPosition().x == 512 && mc_sprite.getPosition().y == 320)
        {
            game_map = MapSprite();
            if (!game_map.load("Maps/hirosehouse3f.png", sf::Vector2u(32, 32), 16, 15))
                return 0;
            mc_sprite.currentAnimation = &mc_sprite.walkD;
            mc_sprite.setPosition(sf::Vector2f(384, 96));
            mc_sprite.moving[1] = true;
            mc_sprite.walking = true;
            mc_sprite.nextSpot = 128;
        }
    }
    else if (game_map.mapName.compare("Hirose Residence, 3F") == 0)
    {
        if (mc_sprite.getPosition().x == 384 && mc_sprite.getPosition().y == 96)
        {
            game_map = MapSprite();
            if (!game_map.load("Maps/hirosehouse2f.png", sf::Vector2u(32, 32), 22, 35))
                return 0;
            mc_sprite.currentAnimation = &mc_sprite.walkD;
            mc_sprite.setPosition(sf::Vector2f(512, 320));
            mc_sprite.moving[1] = true;
            mc_sprite.walking = true;
            mc_sprite.nextSpot = 352;
        }
    }
    return 1;
}

int main()
{
    sf::Font font;
    if (!font.loadFromFile("Fonts/arial.ttf"))
        return -1;
    sf::Text welcome;
    welcome.setFont(font);
    welcome.setString("Welcome to Beetle Boy's 7SU2 Demo\nPress (1-6) to load a character sprite");
    welcome.setCharacterSize(32);
    welcome.setColor(sf::Color::White);
    window.clear(sf::Color::Black);
    window.display();
    bool focus = true;
    sf::View view1;
    view1.setSize(sf::Vector2f(640, 480));
    MovingSprite mc_sprite;
    mc_sprite.setTexture("Sprites/protag1.png");
    mc_sprite.setPosition(64, 480);
    mc_sprite.setSize(32, 32);
    mc_sprite.walking = false;
    view1.setCenter(mc_sprite.getPosition().x + 16, mc_sprite.getPosition().y + 16);
    bool notSet = true;
    MapSprite game_map;
    if (!game_map.load("Maps/hirosehouse1f.png", sf::Vector2u(32, 32), 34, 40))
        return -1;

    sf::Music bgm;
    if (!bgm.openFromFile("Music/koichi-03.ogg"))
        return -1;
    bgm.setLoop(true);

    //koichiObject(mc_texture);
    while (window.isOpen())
    {
        if (notSet)
        {
            window.clear(sf::Color::Black);
            window.draw(welcome);
            window.display();
        }
        if (!mc_sprite.walking && focus)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                mc_sprite.setOffset(0, 0);
                cout << "Average" << endl;
                if (notSet)
                {
                    bgm.play();
                }
                Animation *curr;
                if (!notSet)
                {
                    curr = mc_sprite.currentAnimation;
                }
                mc_sprite.setAnimations();
                if (!notSet)
                {
                    mc_sprite.currentAnimation = curr;
                }
                else
                {
                    mc_sprite.currentAnimation = &mc_sprite.walkR;
                }
                notSet = false;
                window.setView(view1);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                mc_sprite.setOffset(1, 0);
                cout << "Pretty Boy" << endl;
                if (notSet)
                {
                    bgm.play();
                }
                Animation *curr;
                if (!notSet)
                {
                    curr = mc_sprite.currentAnimation;
                }
                mc_sprite.setAnimations();
                if (!notSet)
                {
                    mc_sprite.currentAnimation = curr;
                }
                else
                {
                    mc_sprite.currentAnimation = &mc_sprite.walkR;
                }
                notSet = false;
                window.setView(view1);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                mc_sprite.setOffset(2, 0);
                cout << "Glasses" << endl;
                if (notSet)
                {
                    bgm.play();
                }
                Animation *curr;
                if (!notSet)
                {
                    curr = mc_sprite.currentAnimation;
                }
                mc_sprite.setAnimations();
                if (!notSet)
                {
                    mc_sprite.currentAnimation = curr;
                }
                else
                {
                    mc_sprite.currentAnimation = &mc_sprite.walkR;
                }
                notSet = false;
                window.setView(view1);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            {
                mc_sprite.setOffset(0, 1);
                cout << "Short" << endl;
                if (notSet)
                {
                    bgm.play();
                }
                Animation *curr;
                if (!notSet)
                {
                    curr = mc_sprite.currentAnimation;
                }
                mc_sprite.setAnimations();
                if (!notSet)
                {
                    mc_sprite.currentAnimation = curr;
                }
                else
                {
                    mc_sprite.currentAnimation = &mc_sprite.walkR;
                }
                notSet = false;
                window.setView(view1);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
            {
                mc_sprite.setOffset(1, 1);
                cout << "Punk" << endl;
                if (notSet)
                {
                    bgm.play();
                }
                Animation *curr;
                if (!notSet)
                {
                    curr = mc_sprite.currentAnimation;
                }
                mc_sprite.setAnimations();
                if (!notSet)
                {
                    mc_sprite.currentAnimation = curr;
                }
                else
                {
                    mc_sprite.currentAnimation = &mc_sprite.walkR;
                }
                notSet = false;
                window.setView(view1);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
            {
                mc_sprite.setOffset(2, 1);
                cout << "Chubby" << endl;
                if (notSet)
                {
                    bgm.play();
                }
                Animation *curr;
                if (!notSet)
                {
                    curr = mc_sprite.currentAnimation;
                }
                mc_sprite.setAnimations();
                if (!notSet)
                {
                    mc_sprite.currentAnimation = curr;
                }
                else
                {
                    mc_sprite.currentAnimation = &mc_sprite.walkR;
                }
                notSet = false;
                window.setView(view1);
            }
        }
        if (focus && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            cout << mc_sprite.getPosition().x << ", " << mc_sprite.getPosition().y << endl;
        }
        sf::Event event;
        if (focus)
        {
            if (!notSet)
            {
                mc_sprite.move_overworld(game_map);
                view1.setCenter(mc_sprite.getPosition().x+16, mc_sprite.getPosition().y+16);
                if (!locationChange(game_map, mc_sprite))
                {
                    return 1;
                }
                window.clear();
                window.draw(game_map);
                window.draw(mc_sprite);
                game_map.drawCeil(&window);
                window.display();
                window.setView(view1);
            }
        }
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                bgm.stop();
                window.close();
                return 0;
            }
            if (event.type == sf::Event::LostFocus)
            {
                focus = false;
                bgm.pause();
                mc_sprite.frameClock.pause();
            }
            if (event.type == sf::Event::GainedFocus)
            {
                focus = true;
                bgm.play();
                mc_sprite.frameClock.start();
            }
        }
    }
}
