#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <functional>


#define WIDTH 128
#define HEIGHT 56
#define HEIGHT_OFFSET 8

struct Point 
{
  uint8_t x;
  uint8_t y;
};



struct Snake
{   
    friend struct Game;
    enum Direction { UP = 1, LEFT = 2, RIGHT = 3, DOWN = 4};

    Snake(uint8_t width, uint8_t height);

    void setDirection(Direction direction);
    const Direction &getDirection();

    const Point &getHead();
    const Point &getTail();
    


private:
    Point head_;
    Point tail_;
    Direction direction_;
};


struct Game
{
    Game( Snake &snake, std::function<void(uint8_t, uint8_t)> onFoodAdded_ = nullptr);

    enum Pixel {
        Empty = 0,
        Up = 1,
        Left = 2,
        Right = 3,
        Down = 4,
        Head = 5,
        Wall = 6,
        Food = 7
    };
    
    struct FieldElement
    {   
        FieldElement();
        FieldElement(Pixel pixel, bool hasFood = false);

        Pixel getPixel();
        bool hasFood();

    private:
        uint8_t pixel_ : 4;
        bool hasFood_ : 1;
    };
    
    
    void start();
    void moveSnake();
    bool isOver();
    void field_for_each(std::function<void(uint8_t , uint8_t, Pixel)> fn);
    

private:
    void addSnake();
    void addWall();
    void addFood();
    void moveHead();
    void moveTail();
    Snake &snake_;
    FieldElement field_[WIDTH][HEIGHT];
    bool isOver_;
    std::function<void(uint8_t, uint8_t)> onFoodAdded_;

};




bool isButtonPressed(uint8_t pin);