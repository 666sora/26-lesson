#include <iostream>
#include <vector>

struct Coordinate {
    int x_coordinate = 0;
    int y_coordinate = 0;
};

void additionVectors (Coordinate& a_coordinate, Coordinate& b_coordinate) {
    a_coordinate.x_coordinate += b_coordinate.x_coordinate;
    a_coordinate.y_coordinate += b_coordinate.y_coordinate;
}

class Frame { 
    int frameWidth = 0;
    int frameHeight = 0;
    Coordinate coordinateOfCorner = {0, 0};

    public:
        void setWidth() {
            do {
                std::cout << "Input width: ";
                std::cin >> frameWidth;
            } while (frameWidth >= 80 || frameWidth < 0);
        }
        void setHeight() {
            do {
                std::cout << "Input height: ";
                std::cin >> frameHeight;
            } while (frameHeight >= 50 || frameHeight < 0);
        }
        void setCoordinateCorner() {
            do {
                std::cout << "Input x coordinate of corner: ";
                std::cin >> coordinateOfCorner.x_coordinate;
            } while (coordinateOfCorner.x_coordinate + frameWidth >= 80);
            do {
                std::cout << "Input y coordinate of corner: ";
                std::cin >> coordinateOfCorner.y_coordinate;
            } while (coordinateOfCorner.y_coordinate + frameHeight >= 50);
        }

        void moveCoordinateCorner(Coordinate &shift_vector) {
            additionVectors(coordinateOfCorner, shift_vector);
        }

        int getWidth() {
            return frameWidth;
        }
        int getHeight() {
            return frameHeight;
        }
        int getCoordinateCorner_x() {
            return coordinateOfCorner.x_coordinate;
        }
        int getCoordinateCorner_y() {
            return coordinateOfCorner.y_coordinate;
        }
};

class Screen {
    Frame frame;

    public:
        void resizeFrame() {
            frame.setWidth();
            frame.setHeight();
        }

        void moveFrame() {
            Coordinate shift_vector;
            do {
                std::cout << "Input x coordinate of vector: ";
                std::cin >> shift_vector.x_coordinate;
                std::cout << "Input y coordinate of vector: ";
                std::cin >> shift_vector.y_coordinate;
                frame.moveCoordinateCorner(shift_vector);
            } while (frame.getCoordinateCorner_x() < 0 || frame.getCoordinateCorner_x() >= 80
                  || frame.getCoordinateCorner_y() < 0 || frame.getCoordinateCorner_y() >= 50
                  || frame.getCoordinateCorner_x() + frame.getWidth() >= 80 
                  || frame.getCoordinateCorner_y() + frame.getHeight() >= 50);
        }
        
        void displayFrame() {
            for (int i = 0; i < 50; i++) {
                for (int j = 0; j < 80; j++) {
                    if (i >= frame.getCoordinateCorner_y() && i < frame.getCoordinateCorner_y() + frame.getHeight()
                            && j >= frame.getCoordinateCorner_x() && j < frame.getCoordinateCorner_x() + frame.getWidth()) {
                        std::cout << "1";
                    }
                    else {
                        std::cout << "0";
                    }
                }
                std::cout << std::endl;
            }
        }
};

int main() {
    Screen screen;
    screen.resizeFrame();

    std::string answer;

    while (answer != "exit") {
        std::cout << "Input command: ";
        std::cin >> answer;

        if (answer == "resize") {
            screen.resizeFrame();
        }
        else if (answer == "move") {
            screen.moveFrame();
        }
        else if (answer == "display") {
            screen.displayFrame();
        }
    }
}

/*
Реализуйте симуляцию работы окна в визуальном интерфейсе пользователя.
Окно располагается на виртуальном экране монитора, размером 80 × 50 точек. 
У окна есть несколько параметров, которые также задаются в пикселях: 
двумерные координаты левого верхнего угла и размеры, ширина и высота. 
Ширина и высота при этом не могут быть отрицательными, 
а координаты не могут выходить за область экрана.
Пользователь взаимодействует с программой с помощью команд:
Команда move принимает вектор, на который надо сместить окно 
на экране. Сообщение с новыми координатами окна появляется на экране.
Команда resize запрашивает из стандартного ввода новый размер 
окна. После изменения размера сообщение с новым размером выводится на экране.
Команда display выводит текущее изображение монитора в консоль. 
0 — это пиксель вне области окна, 1 — с окном.
Команда close закрывает окно, выход из программы.
*/