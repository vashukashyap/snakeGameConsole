#include <snakegame.h>
#include <Arduino.h>

Snake::Snake(uint8_t width, uint8_t height)
{
  head_.x = width / 2 + 3;
  tail_.x = width / 2 - 3;
  tail_.y = head_.y = (height / 2);

  direction_ = RIGHT;
}

void Snake::setDirection(Direction newDirection)
{
  if(
    !((direction_ == UP && newDirection == DOWN) || 
     (direction_ == DOWN && newDirection == UP) ||
     (direction_ == RIGHT && newDirection == LEFT) ||
     (direction_ == LEFT && newDirection == RIGHT) 
    )
    )
    {
      direction_ = newDirection;
    }
  return;
}

const Snake::Direction &Snake::getDirection()
{
  return direction_;
}

const Point &Snake::getHead()
{
  return head_;
}

const Point &Snake::getTail()
{
  return tail_;
}

Game::Game(Snake &snake, std::function<void(uint8_t, uint8_t)> onFoodAdded) : snake_(snake)
{
  isOver_ = false;
  onFoodAdded_ = onFoodAdded;
}

void Game::start()
{
  this->addWall();
  this->addSnake();
  this->addFood();
}

void Game::moveSnake()
{
  this->moveHead();

  FieldElement element = field_[snake_.getTail().x][snake_.getTail().y];
  if(element.hasFood())
  {
    field_[snake_.getTail().x][snake_.getTail().y] = FieldElement(element.getPixel());
    return;
  }

  this->moveTail();
}

bool Game::isOver(){
  return isOver_;
}

void Game::field_for_each(std::function<void(uint8_t , uint8_t, Pixel)> fn)
{
  for(uint8_t x = 0; x < WIDTH; x++)
  {
    for(uint8_t y = 0; y < HEIGHT; y++)
    {
      fn(x, y, (Pixel) field_[x][y].getPixel());
    }
  }

}

void Game::addSnake()
{
  for(uint8_t x = snake_.getTail().x; x <= snake_.getHead().x; x++)
  {
    field_[x][snake_.getHead().y] = FieldElement(Pixel::Right);
  }

  field_[snake_.getHead().x][snake_.getHead().y] = FieldElement(Pixel::Head);;
}

void Game::addWall()
{
  for(uint8_t x = 0; x < WIDTH; x++)
  {
    field_[x][0] = field_[x][HEIGHT - 1] = FieldElement(Pixel::Wall);;
  }

  for(uint8_t y = 0; y < HEIGHT; y++)
  {
    field_[0][y] = field_[WIDTH - 1][y] = FieldElement(Pixel::Wall);;
  }
}

void Game::addFood()
{
  uint8_t x = random(WIDTH);
  uint8_t y = random(HEIGHT);

  if(field_[x][y].getPixel() == Pixel::Empty)
  {
    if(onFoodAdded_ != nullptr)
    {
      onFoodAdded_(x, y);
    }

    field_[x][y] = FieldElement(Pixel::Food);;
    return;
  }

  this->addFood();

}

void Game::moveHead(){

  uint8_t newX = snake_.getHead().x;
  uint8_t newY = snake_.getHead().y;
  Pixel p;

  switch (snake_.getDirection())
  {
    case Snake::Direction::UP:
      newY--;
      p = Pixel::Up;
      break;

    case Snake::Direction::LEFT:
      newX--;
      p = Pixel::Left;
      break;

    case Snake::Direction::RIGHT:
      newX++;
      p = Pixel::Right;
      break;
      
    default:
      newY++;
      p = Pixel::Down;
  }

  if((field_[newX][newY].getPixel() != Pixel::Empty) &&
     (field_[newX][newY].getPixel() != Pixel:: Food))
  {
    isOver_ = true;
    return;
  }

  field_[snake_.getHead().x][snake_.getHead().y] = FieldElement(p,field_[snake_.getHead().x][snake_.getHead().y].hasFood());

  bool hasEaten = field_[newX][newY].getPixel() == Pixel::Food;
  field_[newX][newY] = FieldElement(Pixel::Head, hasEaten);

  if(hasEaten){
    this->addFood();
  }

  snake_.head_.x = newX;
  snake_.head_.y = newY;


}

void Game::moveTail()
{
  uint8_t tailX = snake_.getTail().x;
  uint8_t tailY = snake_.getTail().y;

  switch (field_[tailX][tailY].getPixel())
  {
  case Pixel::Right:
    snake_.tail_.x++;
    break;
  
  case Pixel::Left:
    snake_.tail_.x--;
    break;

  case Pixel::Up:
    snake_.tail_.y--;
    break;

  default:
    snake_.tail_.y++;
    break;
  }

  field_[tailX][tailY] = FieldElement(Pixel::Empty);
}



bool isButtonPressed(uint8_t pin)
{
  return digitalRead(pin) == LOW;
}

Game::FieldElement::FieldElement()
{
  pixel_ = Pixel::Empty;
  hasFood_ = false;
}

Game::FieldElement::FieldElement(Pixel pixel, bool hasFood)
{
  pixel_ = pixel;
  hasFood_ = hasFood;
}

Game::Pixel Game::FieldElement::getPixel()
{
  return (Pixel) pixel_;
}

bool Game::FieldElement::hasFood()
{
  return hasFood_;
}