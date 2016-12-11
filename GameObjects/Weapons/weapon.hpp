class Weapon: public GameObject {
public:
  Point* location;
  bool isMoving;
  virtual void fire(double power, double vx, double vy, double vz) = 0;
  virtual void move() = 0;

  bool is_out_of_field(const int fieldWidth, const int fieldLength)
  {
    return this->location->y < 0
      || this->location->y > 100
      || this->location->x > fieldWidth
      || this->location->x < -fieldWidth
      || this->location->z > fieldLength
      || this->location->z < -fieldLength / 2;
  }
};
