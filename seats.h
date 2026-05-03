// seats.h - Seat selection screen function
#ifndef SEATS_H
#define SEATS_H

#include "helpers.h"
#include "Passenger.h"

// Shows seat grid, lets user click to select seats
// Returns 1:NEXT, 2:CANCEL, 0:CLOSED
inline int seatScreen(sf::RenderWindow& win, const sf::Font& font, Passenger& p) {

    const int ROWS = 6;
    const int COLS = 4;
    const int TOTAL = ROWS * COLS;
    
    // 0 = free, 1 = reserved, 2 = selected
    static int seatStates[24] = {
        0,0,1,0, 
        0,1,0,0, 
        0,0,0,0, 
        1,0,0,1, 
        0,0,1,0, 
        0,0,0,0
    };

    while (win.isOpen()) {
        while (auto event = win.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { win.close(); return 0; }

            if (auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i m = {click->position.x, click->position.y};

                // Check seats
                for (int i = 0; i < TOTAL; i++) {
                    int row = i / COLS;
                    int col = i % COLS;
                    float sx = 200 + col * 90 + (col >= 2 ? 40 : 0);
                    float sy = 120 + row * 60;
                    
                    if (mouseIn(m, sx, sy, 70, 50) && seatStates[i] != 1) {
                        seatStates[i] = (seatStates[i] == 0) ? 2 : 0;
                    }
                }

                // CANCEL button
                if (mouseIn(m, 30, 520, 120, 50)) {
                    return 2;
                }

                // NEXT button
                if (mouseIn(m, 500, 520, 200, 50)) {
                    int count = 0;
                    for (int i = 0; i < TOTAL; i++) if (seatStates[i] == 2) count++;
                    if (count > 0) { p.numSeats = count; return 1; }
                }
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(win);
        int selectedCount = 0;
        for (int i = 0; i < TOTAL; i++) if (seatStates[i] == 2) selectedCount++;

        win.clear(sf::Color(18, 18, 24));

        // Header
        drawBox(win, 0, 0, 800, 70, sf::Color(30, 30, 40));
        drawCentered(win, font, "CHOOSE YOUR SEATS", 24, 20, sf::Color(0, 150, 255));

        // Legend
        float legX = 180;
        drawBox(win, legX, 85, 15, 15, sf::Color(60, 60, 70)); 
        drawText(win, font, "Available", legX + 25, 83, 14, GRAY);
        drawBox(win, legX + 130, 85, 15, 15, sf::Color(220, 60, 60)); 
        drawText(win, font, "Reserved", legX + 155, 83, 14, GRAY);
        drawBox(win, legX + 260, 85, 15, 15, sf::Color(0, 150, 255)); 
        drawText(win, font, "Selected", legX + 285, 83, 14, GRAY);

        // Draw Seats Grid
        for (int i = 0; i < TOTAL; i++) {
            int row = i / COLS;
            int col = i % COLS;
            float sx = 200 + col * 90 + (col >= 2 ? 40 : 0);
            float sy = 120 + row * 60;

            sf::Color baseColor = sf::Color(60, 60, 75);
            if (seatStates[i] == 1) baseColor = sf::Color(180, 50, 50);
            if (seatStates[i] == 2) baseColor = sf::Color(0, 120, 220);
            
            if (seatStates[i] != 1 && mouseIn(mouse, sx, sy, 70, 50)) {
                baseColor.r += 30; baseColor.g += 30; baseColor.b += 30;
            }
            drawBox(win, sx, sy, 70, 50, baseColor, sf::Color(baseColor.r/2, baseColor.g/2, baseColor.b/2), 2);
            drawText(win, font, to_string(row+1) + (char)('A'+col), sx + 22, sy + 12, 18, WHITE);
        }

        // Footer / Buttons
        drawBox(win, 0, 500, 800, 100, sf::Color(30, 30, 40));
        drawText(win, font, "Seats Selected: " + to_string(selectedCount), 180, 530, 20, sf::Color(0, 200, 150));
        
        // CANCEL button
        sf::Color cancelC = mouseIn(mouse, 30, 520, 120, 50) ? sf::Color(200, 60, 60) : sf::Color(150, 40, 40);
        drawBox(win, 30, 520, 120, 50, cancelC);
        drawText(win, font, "CANCEL", 50, 532, 16, WHITE);

        // NEXT button
        sf::Color btnColor = mouseIn(mouse, 500, 520, 200, 50) ? sf::Color(0, 180, 255) : sf::Color(0, 120, 200);
        drawBox(win, 500, 520, 200, 50, btnColor);
        drawText(win, font, "CONFIRM NEXT", 540, 532, 16, WHITE);

        win.display();
    }
    return 0;
}

#endif
