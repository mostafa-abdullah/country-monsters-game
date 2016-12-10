class Person: public GameObject {
public:
  Weapon* weapon;
  double x, z;

  Person()
  {
    x = 0;
    z = 3.5;
  }

  void draw()
  {
    this->weapon->draw();
  }

  void set_weapon(Weapon* weapon)
  {
    weapon->x = this->x;
    weapon->y = 1.4;
    weapon->z = this->z - 0.5;
    this->weapon = weapon;
  }

  void move(Direction direction)
  {
    switch (direction) {
      case Forward:
      z -= 0.1;
      break;
      case Backward:
      z += 0.1;
      break;
      case Left:
      x -= 0.1;
      break;
      case Right:
      x += 0.1;
      break;
    }
  }
};
