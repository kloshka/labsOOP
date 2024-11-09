#include <iostream>
#include "include/Array.h"
#include "include/Rhombus.h"
#include "include/Pentagon.h"
#include "include/Hexagon.h"

int main() {
    Array figures;

    int choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add a figure\n";
        std::cout << "2. Remove a figure\n";
        std::cout << "3. Display all figures\n";
        std::cout << "4. Calculate total area\n";
        std::cout << "0. Exit\n";
        std::cout << "Select an action: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "Select the type of figure:\n";
            std::cout << "1. Rhombus\n";
            std::cout << "2. Pentagon\n";
            std::cout << "3. Hexagon\n";
            int type;
            std::cin >> type;
            Figure* figure = nullptr;
            switch (type) {
            case 1:
                figure = new Rhombus();
                break;
            case 2:
                figure = new Pentagon();
                break;
            case 3:
                figure = new Hexagon();
                break;
            default:
                std::cout << "Invalid choice.\n";
                continue;
            }
            std::cin >> *figure;
            figures.add(figure);
            break;
        }
        case 2: {
            std::cout << "Enter the index of the figure to remove: ";
            size_t index;
            std::cin >> index;
            figures.remove(index);
            break;
        }
        case 3: {
            for (size_t i = 0; i < figures.size(); ++i) {
                Figure* figure = figures.get(i);
                std::cout << i << ". " << *figure << "\n";
                Point c = figure->center();
                std::cout << "Center: (" << c.x << ", " << c.y << ")\n";
                std::cout << "Area: " << static_cast<double>(*figure) << "\n";
            }
            break;
        }
        case 4: {
            double totalArea = 0.0;
            for (size_t i = 0; i < figures.size(); ++i) {
                totalArea += static_cast<double>(*figures.get(i));
            }
            std::cout << "Total area of all figures: " << totalArea << "\n";
            break;
        }
        case 0:
            // Exit
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}