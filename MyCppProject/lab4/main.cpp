#include <iostream>
#include <memory>
#include "Array.h"
#include "Figure.h"
#include "Hexagon.h"
#include "Pentagon.h"
#include "Rhombus.h"

int main() {
    using FigurePtr = std::shared_ptr<Figure<int>>;
    Array<FigurePtr> figures;

    char choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add a figure to the array\n";
        std::cout << "2. Display figures (coordinates, geometric center, area)\n";
        std::cout << "3. Remove a figure by index\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";

        std::cin >> choice;

        switch(choice) {
            case '1': {
                std::cout << "Select the type of figure:\n";
                std::cout << "1. Rhombus\n";
                std::cout << "2. Pentagon\n";
                std::cout << "3. Hexagon\n";
                std::cout << "Choice: ";

                char figChoice;
                std::cin >> figChoice;

                FigurePtr figure;

                switch(figChoice) {
                    case '1':
                        figure = std::make_shared<Rhombus<int>>();
                        break;
                    case '2':
                        figure = std::make_shared<Pentagon<int>>();
                        break;
                    case '3':
                        figure = std::make_shared<Hexagon<int>>();
                        break;
                    default:
                        std::cout << "Invalid input\n";
                        continue;
                }

                std::cout << "Enter the coordinates of the vertices:\n";
                figure->Read(std::cin);
                figures.PushBack(figure);
                std::cout << "Figure added.\n";
                std::cout << "-----------------------\n";
                break;
            }
            case '2': {
                double totalArea = 0.0;
                for (size_t i = 0; i < figures.Size(); ++i) {
                    std::cout << "Figure " << i + 1 << ":\n";
                    figures[i]->Print(std::cout);
                    double area = figures[i]->Area();
                    std::cout << "Area: " << area << '\n';
                    totalArea += area;
                }
                std::cout << "Total area: " << totalArea << '\n';
                std::cout << "-----------------------\n";
                break;
            }
            case '3': {
                std::cout << "Enter the index (from 1 to " << figures.Size() << "): ";
                size_t index;
                std::cin >> index;
                if (index < 1 || index > figures.Size()) {
                    std::cout << "Invalid input\n";
                } else {
                    figures.RemoveAt(index - 1);
                    std::cout << "Figure removed.\n";
                }
                std::cout << "-----------------------\n";
                break;
            }
            case '4':
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid input\n";
                std::cout << "-----------------------\n";
        }
    } while (choice != '4');

    return 0;
}
