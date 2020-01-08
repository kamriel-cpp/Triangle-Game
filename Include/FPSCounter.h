#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

class FPSCounter
{
private:
    sf::Text text;

    sf::Clock delayTimer;
    sf::Clock fpsTimer;

    float fps;
    int frameCount;
public:
    FPSCounter(const sf::Vector2f& position, const sf::Font& font);

    void update();
    void render(sf::RenderTarget* target = nullptr);
};

#include <Source/FPSCounter.cpp>
#endif
