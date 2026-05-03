// routes.h - Route selection screen function
#ifndef ROUTES_H
#define ROUTES_H

#include "helpers.h"
#include "Passenger.h"

// Shows route cards with Pakistan cities, user picks one
// Returns true when user clicks NEXT, false if window closed
inline int routeScreen(sf::RenderWindow& win, const sf::Font& font, Passenger& p) {

    int selected = -1;   // which route is picked (-1 = none)
    int scroll   = 0;    // scroll offset
    int visible  = 5;    // how many cards fit on screen

    while (win.isOpen()) {

        while (auto event = win.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { win.close(); return 0; }

            if (auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i m = {click->position.x, click->position.y};

                // Click on a route card
                for (int i = 0; i < visible && (i + scroll) < TOTAL_ROUTES; i++) {
                    float cy = 120 + i * 78.f;
                    if (mouseIn(m, 80, cy, 640, 70))
                        selected = i + scroll;
                }

                // Scroll UP / DOWN buttons
                if (mouseIn(m, 370, 520, 60, 30) && scroll > 0)
                    scroll--;
                if (mouseIn(m, 370, 555, 60, 30) && scroll + visible < TOTAL_ROUTES)
                    scroll++;

                // BACK button
                if (mouseIn(m, 30, 535, 120, 50)) {
                    return -1;
                }

                // CANCEL button
                if (mouseIn(m, 160, 535, 120, 50)) {
                    return 2;
                }

                // NEXT button
                if (mouseIn(m, 540, 535, 200, 50) && selected >= 0) {
                    p.routeIndex = selected;
                    return 1;
                }
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(win);

        // ── Draw ──
        win.clear(BG_DARK);

        // Header
        drawBox(win, 0, 0, 800, 80, BG_PANEL);
        drawCentered(win, font, "SELECT YOUR ROUTE", 22, 30, BLUE);
        drawBox(win, 50, 78, 700, 2, BLUE);
        drawText(win, font, "Choose your departure and destination", 80, 90, 15, GRAY);

        // Draw route cards (only the visible ones)
        for (int i = 0; i < visible && (i + scroll) < TOTAL_ROUTES; i++) {
            int idx = i + scroll;
            float cy = 120 + i * 78.f;
            bool isSel = (selected == idx);
            bool isHov = mouseIn(mouse, 80, cy, 640, 70);

            // Card background
            sf::Color bg = isSel ? sf::Color(50,60,110) :
                           isHov ? sf::Color(45,45,80)  : BG_CARD;
            sf::Color border = isSel ? BLUE : DARK_GRAY;
            drawBox(win, 80, cy, 640, 70, bg, border, 2);

            // Selection dot (filled if selected, outline if not)
            sf::CircleShape dot(7);
            dot.setPosition({98, cy + 28});
            if (isSel) {
                dot.setFillColor(BLUE);
            } else {
                dot.setFillColor(sf::Color::Transparent);
                dot.setOutlineThickness(2);
                dot.setOutlineColor(GRAY);
            }
            win.draw(dot);

            // Route name
            string title = routes[idx].from + "  ->  " + routes[idx].to;
            drawText(win, font, title, 125, cy + 12, 18, isSel ? WHITE : GRAY);

            // Duration
            drawText(win, font, to_string(routes[idx].hours) + " hours", 125, cy + 40, 14, GRAY);

            // Price on right side
            string pr = to_string(routes[idx].price) + " PKR";
            sf::Text prText(font, pr, 16);
            float pw = prText.getLocalBounds().size.x;
            drawText(win, font, pr, 700 - pw, cy + 25, 16, isSel ? GREEN : GRAY);
        }

        // Scroll buttons (only if there are more routes than visible)
        if (TOTAL_ROUTES > visible) {
            sf::Color upC   = (scroll > 0) ? BLUE : DARK_GRAY;
            sf::Color downC = (scroll + visible < TOTAL_ROUTES) ? BLUE : DARK_GRAY;
            drawBox(win, 370, 520, 60, 30, BG_CARD, upC, 1);
            drawText(win, font, "UP", 387, 522, 14, upC);
            drawBox(win, 370, 555, 60, 30, BG_CARD, downC, 1);
            drawText(win, font, "DN", 387, 557, 14, downC);
        }

        // Bottom bar
        drawBox(win, 0, 510, 800, 90, BG_PANEL);

        // BACK button
        sf::Color backC = mouseIn(mouse, 30, 535, 120, 50) ? sf::Color(100, 100, 120) : DARK_GRAY;
        drawBox(win, 30, 535, 120, 50, backC);
        drawText(win, font, "<< BACK", 55, 545, 18, WHITE);

        // CANCEL button
        sf::Color cancelC = mouseIn(mouse, 160, 535, 120, 50) ? sf::Color(200, 60, 60) : sf::Color(150, 40, 40);
        drawBox(win, 160, 535, 120, 50, cancelC);
        drawText(win, font, "CANCEL", 188, 545, 18, WHITE);

        if (selected < 0)
            drawText(win, font, "Select a route", 300, 545, 15, YELLOW);
        else
            drawText(win, font, routes[selected].from + " -> " + routes[selected].to,
                     300, 545, 15, GREEN);

        // NEXT button
        sf::Color btnC = mouseIn(mouse, 540, 535, 200, 50) ? sf::Color(60,220,140) : GREEN;
        drawBox(win, 540, 535, 200, 50, btnC);
        drawText(win, font, "NEXT  >>", 595, 545, 18, WHITE);

        win.display();
    }
    return 0;
}

#endif
