// confirm.h - Booking confirmation screen + save to file
#ifndef CONFIRM_H
#define CONFIRM_H

#include "helpers.h"
#include "Passenger.h"
#include <fstream>

inline int confirmScreen(sf::RenderWindow& win, const sf::Font& font, const Passenger& p) {
    Route r = routes[p.routeIndex];
    int total = p.numSeats * r.price;

    // Save to file automatically on entering this screen
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
            if (event->is<sf::Event::Closed>()) { win.close(); return 0; }
            if (auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i m = {click->position.x, click->position.y};
                
                // BACK TO EDIT button
                if (mouseIn(m, 120, 525, 180, 50)) { return -1; }

                // CANCEL button
                if (mouseIn(m, 310, 525, 180, 50)) { return 2; }

                // EXIT button
                if (mouseIn(m, 500, 525, 180, 50)) { return 1; }
            }
        }
        sf::Vector2i mouse = sf::Mouse::getPosition(win);

        win.clear(BG_DARK);
        drawBox(win, 0, 0, 800, 80, BG_PANEL);
        drawCentered(win, font, "BOOKING SUMMARY", 22, 30, GREEN);
        drawBox(win, 50, 78, 700, 2, GREEN);

        float cardY = 120;
        drawBox(win, 150, cardY, 500, 360, BG_CARD, DARK_GRAY, 1);
        float row = cardY + 20, gap = 35;
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

        // Buttons Footer
        drawText(win, font, "Booking saved to booking.txt", 295, 495, 14, GRAY);
        
        // BACK button
        sf::Color backC = mouseIn(mouse, 120, 525, 180, 50) ? sf::Color(100,100,120) : DARK_GRAY;
        drawBox(win, 120, 525, 180, 50, backC);
        drawText(win, font, "BACK TO EDIT", 145, 540, 16, WHITE);

        // CANCEL button
        sf::Color cancelC = mouseIn(mouse, 310, 525, 180, 50) ? sf::Color(220,80,80) : sf::Color(180,50,50);
        drawBox(win, 310, 525, 180, 50, cancelC);
        drawText(win, font, "CANCEL RESERV.", 335, 540, 16, WHITE);

        // EXIT button
        sf::Color exitC = mouseIn(mouse, 500, 525, 180, 50) ? sf::Color(100,180,255) : sf::Color(50,120,200);
        drawBox(win, 500, 525, 180, 50, exitC);
        drawText(win, font, "CONFIRM & EXIT", 518, 540, 16, WHITE);

        win.display();
    }
    return 1;
}

#endif
