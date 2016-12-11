class Weapon: public GameObject {
public:
  Point* location;
  bool isMoving;
  virtual void fire(double power, double vx, double vy, double vz) = 0;
  virtual void move() = 0;
};
