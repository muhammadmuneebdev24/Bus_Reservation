// helpers.h - Simple drawing functions used by all screens
#ifndef HELPERS_H
#define HELPERS_H

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

// ─── Colors (easy to change) ───
sf::Color BG_DARK     (20, 20, 35);
sf::Color BG_PANEL    (30, 30, 55);
sf::Color BG_CARD     (40, 40, 70);
sf::Color BLUE        (100, 140, 255);
sf::Color BLUE_LIGHT  (130, 170, 255);
sf::Color GREEN       (80, 200, 120);
sf::Color RED         (200, 60, 60);
sf::Color YELLOW      (255, 200, 60);
sf::Color WHITE       (240, 240, 250);
sf::Color GRAY        (160, 160, 180);
sf::Color DARK_GRAY   (80, 80, 120);
sf::Color INPUT_BG    (50, 50, 80);
sf::Color SEAT_FREE   (70, 180, 130);
sf::Color SEAT_HOVER  (90, 200, 150);

// ─── Draw text at position ───
inline void drawText(sf::RenderWindow& win, const sf::Font& font,
                     const string& str, float x, float y, int size, sf::Color color)
{
    sf::Text t(font, str, size);
    t.setFillColor(color);
    t.setPosition({x, y});
    win.draw(t);
}

// ─── Draw text centered horizontally ───
inline void drawCentered(sf::RenderWindow& win, const sf::Font& font,
                         const string& str, float y, int size, sf::Color color)
{
    sf::Text t(font, str, size);
    t.setFillColor(color);
    float w = t.getLocalBounds().size.x;
    t.setPosition({(800.f - w) / 2.f, y});
    win.draw(t);
}

// ─── Draw a filled rectangle ───
inline void drawBox(sf::RenderWindow& win, float x, float y, float w, float h,
                    sf::Color fill, sf::Color outline = sf::Color::Transparent, float thick = 0)
{
    sf::RectangleShape r({w, h});
    r.setPosition({x, y});
    r.setFillColor(fill);
    if (thick > 0) {
        r.setOutlineThickness(thick);
        r.setOutlineColor(outline);
    }
    win.draw(r);
}

// ─── Check if mouse is inside a rectangle ───
inline bool mouseIn(sf::Vector2i mouse, float x, float y, float w, float h) {
    return mouse.x >= x && mouse.x <= x + w &&
           mouse.y >= y && mouse.y <= y + h;
}

#endif
