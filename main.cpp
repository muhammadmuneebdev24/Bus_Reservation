// main.cpp - Entry point, calls each screen function
#include <SFML/Graphics.hpp>
#include "Passenger.h"
#include "helpers.h"
#include "seats.h"
#include "routes.h"
#include "info.h"
#include "confirm.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Passenger Booking System",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) return -1;

    Passenger passenger;

    if (!seatScreen(window, font, passenger))  return 0;
    if (!routeScreen(window, font, passenger)) return 0;
    if (!infoScreen(window, font, passenger))  return 0;
    confirmScreen(window, font, passenger);

    return 0;
}
