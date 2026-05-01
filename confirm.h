// confirm.h - Booking confirmation screen + save to file
#ifndef CONFIRM_H
#define CONFIRM_H

#include "helpers.h"
#include "Passenger.h"
#include <fstream>

inline void confirmScreen(sf::RenderWindow& win, const sf::Font& font, const Passenger& p) {
    Route r = routes[p.routeIndex];
    int total = p.numSeats * r.price;

    // Save to file
    ofstream file("booking.txt");
    if (file) {
        file << "============================\n";
        file << "   BOOKING CONFIRMATION\n";
        file << "============================\n\n";
        file << "Name:           " << p.name  << "\n";
        file << "Phone:          " << p.phone << "\n";
        file << "Age:            " << p.age   << "\n";
        file << "Route:          " << r.from << " to " << r.to << "\n";
        file << "Duration:       " << r.hours << " hours\n";
        file << "Seats Booked:   " << p.numSeats << "\n";
        file << "Price per Seat: " << r.price << " PKR\n";
        file << "Total Price:    " << total   << " PKR\n";
        file << "============================\n";
        file.close();
    }

    while (win.isOpen()) {
        while (auto event = win.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { win.close(); return; }
            if (auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i m = {click->position.x, click->position.y};
                if (mouseIn(m, 320, 530, 160, 50)) { win.close(); return; }
            }
        }
        sf::Vector2i mouse = sf::Mouse::getPosition(win);

        win.clear(BG_DARK);
        drawBox(win, 0, 0, 800, 80, BG_PANEL);
        drawCentered(win, font, "BOOKING CONFIRMED!", 22, 30, GREEN);
        drawBox(win, 50, 78, 700, 2, GREEN);

        sf::CircleShape circle(30);
        circle.setPosition({370, 100});
        circle.setFillColor(sf::Color(40, 180, 100, 200));
        circle.setOutlineThickness(3);
        circle.setOutlineColor(GREEN);
        win.draw(circle);
        drawText(win, font, "OK", 387, 112, 22, WHITE);

        float cardY = 180;
        drawBox(win, 150, cardY, 500, 320, BG_CARD, DARK_GRAY, 1);
        float row = cardY + 15, gap = 35;
        drawText(win, font, "--- BOOKING RECEIPT ---", 180, row, 16, BLUE); row += gap + 5;

        drawText(win, font, "Passenger:", 180, row, 16, GRAY);
        drawText(win, font, p.name, 380, row, 16, WHITE); row += gap;
        drawText(win, font, "Phone:", 180, row, 16, GRAY);
        drawText(win, font, p.phone, 380, row, 16, WHITE); row += gap;
        drawText(win, font, "Age:", 180, row, 16, GRAY);
        drawText(win, font, p.age, 380, row, 16, WHITE); row += gap;
        drawBox(win, 180, row, 440, 1, DARK_GRAY); row += 15;
        drawText(win, font, "Route:", 180, row, 16, GRAY);
        drawText(win, font, r.from + " -> " + r.to, 380, row, 16, WHITE); row += gap;
        drawText(win, font, "Duration:", 180, row, 16, GRAY);
        drawText(win, font, to_string(r.hours) + " hours", 380, row, 16, WHITE); row += gap;
        drawText(win, font, "Seats:", 180, row, 16, GRAY);
        drawText(win, font, to_string(p.numSeats), 380, row, 16, WHITE); row += gap;
        drawBox(win, 180, row, 440, 1, DARK_GRAY); row += 15;
        drawText(win, font, "TOTAL:", 180, row, 18, WHITE);
        drawText(win, font, to_string(total) + " PKR", 380, row, 18, GREEN);

        drawText(win, font, "Booking saved to booking.txt", 265, 510, 14, GRAY);
        sf::Color btnC = mouseIn(mouse, 320, 530, 160, 50) ? BLUE_LIGHT : BLUE;
        drawBox(win, 320, 530, 160, 50, btnC);
        drawText(win, font, "EXIT", 375, 540, 18, WHITE);
        win.display();
    }
}

#endif
