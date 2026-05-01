// info.h - Personal information input screen function
#ifndef INFO_H
#define INFO_H

#include "helpers.h"
#include "Passenger.h"

// Shows form with 3 text fields: name, phone, age
// Returns true on confirm, false if window closed
inline bool infoScreen(sf::RenderWindow& win, const sf::Font& font, Passenger& p) {

    string fields[3] = {"", "", ""};
    string labels[3] = {"Full Name", "Phone Number", "Age"};
    int activeField = -1;    // which field user is typing in
    string errorMsg = "";

    while (win.isOpen()) {

        while (auto event = win.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { win.close(); return false; }

            if (auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i m = {click->position.x, click->position.y};

                // Click on input fields
                activeField = -1;
                for (int i = 0; i < 3; i++) {
                    float fy = 200 + i * 80.f;
                    if (mouseIn(m, 250, fy, 320, 36)) activeField = i;
                }

                // CONFIRM button
                if (mouseIn(m, 260, 460, 280, 55)) {
                    if (fields[0].empty())      errorMsg = "Please enter your name";
                    else if (fields[1].empty())  errorMsg = "Please enter phone number";
                    else if (fields[2].empty())  errorMsg = "Please enter your age";
                    else {
                        p.name  = fields[0];
                        p.phone = fields[1];
                        p.age   = fields[2];
                        return true;
                    }
                }
            }

            // Handle keyboard typing
            if (auto* txt = event->getIf<sf::Event::TextEntered>()) {
                if (activeField >= 0 && txt->unicode < 128) {
                    char c = (char)txt->unicode;
                    if (c == '\b') {
                        if (!fields[activeField].empty())
                            fields[activeField].pop_back();
                    } else if (c >= 32) {
                        if (activeField == 2 && (c < '0' || c > '9')) continue;
                        if (fields[activeField].size() < 30)
                            fields[activeField] += c;
                    }
                    errorMsg = "";
                }
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(win);

        // ── Draw ──
        win.clear(BG_DARK);

        // Header
        drawBox(win, 0, 0, 800, 80, BG_PANEL);
        drawCentered(win, font, "PASSENGER INFORMATION", 22, 30, BLUE);
        drawBox(win, 50, 78, 700, 2, BLUE);

        // Show route summary
        Route& r = routes[p.routeIndex];
        string summary = "Route: " + r.from + " -> " + r.to +
                         "   |   Seats: " + to_string(p.numSeats) +
                         "   |   Total: " + to_string(p.numSeats * r.price) + " PKR";
        drawText(win, font, summary, 80, 100, 15, GRAY);

        // Form card
        drawBox(win, 200, 140, 400, 400, BG_CARD, DARK_GRAY, 1);

        // Draw 3 input fields
        for (int i = 0; i < 3; i++) {
            float fy = 200 + i * 80.f;
            bool active = (activeField == i);

            drawText(win, font, labels[i], 250, fy - 22, 15, GRAY);

            sf::Color border = active ? BLUE : DARK_GRAY;
            drawBox(win, 250, fy, 320, 36, INPUT_BG, border, 2);

            string display = fields[i] + (active ? "|" : "");
            drawText(win, font, display, 258, fy + 6, 18, WHITE);
        }

        // Error
        if (!errorMsg.empty())
            drawText(win, font, errorMsg, 260, 430, 14, RED);

        // CONFIRM button
        sf::Color btnC = mouseIn(mouse, 260, 460, 280, 55) ? sf::Color(60,220,140) : GREEN;
        drawBox(win, 260, 460, 280, 55, btnC);
        drawCentered(win, font, "CONFIRM BOOKING", 470, 18, WHITE);

        win.display();
    }
    return false;
}

#endif
