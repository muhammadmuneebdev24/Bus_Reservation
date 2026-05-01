// seats.h - Seat selection screen function
#ifndef SEATS_H
#define SEATS_H

#include "helpers.h"
#include "Passenger.h"

// Shows seat grid, lets user click to select seats
// Returns true when user clicks NEXT, false if window closed
inline bool seatScreen(sf::RenderWindow& win, const sf::Font& font, Passenger& p) {

    const int TOTAL = 10;
    // 0 = free, 1 = already reserved, 2 = picked by user
    int seat[TOTAL] = {0,0,0,0,1, 0,0,0,1,0};

    while (win.isOpen()) {

        // ── Handle events ──
        while (auto event = win.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { win.close(); return false; }

            if (auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i m = {click->position.x, click->position.y};

                // Click on a seat to toggle it
                for (int i = 0; i < TOTAL; i++) {
                    float sx = 80 + (i % 5) * 120.f;
                    float sy = 220 + (i / 5) * 120.f;
                    if (mouseIn(m, sx, sy, 90, 80) && seat[i] != 1) {
                        seat[i] = (seat[i] == 0) ? 2 : 0;
                    }
                }

                // Click NEXT button
                if (mouseIn(m, 540, 520, 200, 50)) {
                    int count = 0;
                    for (int i = 0; i < TOTAL; i++) if (seat[i] == 2) count++;
                    if (count > 0) { p.numSeats = count; return true; }
                }
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(win);

        // Count how many seats are selected
        int selected = 0;
        for (int i = 0; i < TOTAL; i++) if (seat[i] == 2) selected++;

        // ── Draw everything ──
        win.clear(BG_DARK);

        // Header
        drawBox(win, 0, 0, 800, 80, BG_PANEL);
        drawCentered(win, font, "SELECT YOUR SEATS", 22, 30, BLUE);
        drawBox(win, 50, 78, 700, 2, BLUE);

        // Legend
        drawBox(win, 80, 110, 18, 18, SEAT_FREE);
        drawText(win, font, "Available", 105, 108, 14, GRAY);
        drawBox(win, 220, 110, 18, 18, RED);
        drawText(win, font, "Reserved",  245, 108, 14, GRAY);
        drawBox(win, 360, 110, 18, 18, BLUE);
        drawText(win, font, "Your Pick", 385, 108, 14, GRAY);

        drawText(win, font, "Click on a seat to select / deselect it", 80, 155, 15, GRAY);

        // Draw each seat as a colored box
        for (int i = 0; i < TOTAL; i++) {
            float sx = 80 + (i % 5) * 120.f;
            float sy = 220 + (i / 5) * 120.f;

            // Pick color
            sf::Color c = SEAT_FREE;
            if (seat[i] == 1) c = RED;
            if (seat[i] == 2) c = BLUE;
            if (seat[i] == 0 && mouseIn(mouse, sx, sy, 90, 80)) c = SEAT_HOVER;

            drawBox(win, sx, sy, 90, 80, c, sf::Color(c.r-20, c.g-20, c.b-20), 2);

            // Seat number (X if reserved)
            string label = (seat[i] == 1) ? "X" : to_string(i + 1);
            sf::Text txt(font, label, 24);
            txt.setFillColor(WHITE);
            float tw = txt.getLocalBounds().size.x;
            txt.setPosition({sx + (90 - tw) / 2, sy + 22});
            win.draw(txt);
        }

        // Bottom bar
        drawBox(win, 0, 490, 800, 110, BG_PANEL);
        drawText(win, font, "Selected: " + to_string(selected) + " seat(s)",
                 80, 510, 20, selected > 0 ? GREEN : GRAY);
        if (selected == 0)
            drawText(win, font, "Please select at least 1 seat", 80, 540, 14, YELLOW);

        // NEXT button
        sf::Color btnC = mouseIn(mouse, 540, 520, 200, 50) ? sf::Color(60,220,140) : GREEN;
        drawBox(win, 540, 520, 200, 50, btnC);
        drawText(win, font, "NEXT  >>", 595, 530, 18, WHITE);

        win.display();
    }
    return false;
}

#endif
