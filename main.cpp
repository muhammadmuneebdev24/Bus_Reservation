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
    int state = 0; // 0: Seats, 1: Routes, 2: Info, 3: Confirm

    while (window.isOpen()) {
        if (state == 0) {
            int res = seatScreen(window, font, passenger);
            if (res == 1) state = 1;
            else if (res == 2 || res == 0) break; // Cancel or Closed
        } 
        else if (state == 1) {
            int res = routeScreen(window, font, passenger);
            if (res == 1) state = 2;
            else if (res == -1) state = 0;
            else if (res == 2 || res == 0) break; // Cancel or Closed
        } 
        else if (state == 2) {
            int res = infoScreen(window, font, passenger);
            if (res == 1) state = 3;
            else if (res == -1) state = 1;
            else if (res == 2 || res == 0) break; // Cancel or Closed
        } 
        else if (state == 3) {
            int res = confirmScreen(window, font, passenger);
            if (res == -1) state = 2; // Go back to Info
            else break; // Exit
        }
    }

    return 0;
}
