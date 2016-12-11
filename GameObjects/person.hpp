class Person: public GameObject {
public:
  Weapon* weapon;
  Point* location;
  Point* lookAt;

  Person()
  {
    this->location = new Point(0, 2, 3.5);
    this->lookAt = new Point(0, 2, 2.5);
    this->weapon = new Brick();
  }

  void draw()
  {
    double vx, vy, vz;
    getLookAtUnitVector(&vx, &vy, &vz);
    vx *= 0.5;
    vz *= 0.5;
    glPushMatrix();
    glTranslated(this->location->x + vx, this->location->y - 0.5, this->location->z  + vz);
    this->weapon->draw();
    glPopMatrix();
  }

  void fire_weapon(double power)
  {
    printf("%f\n", power);
    double vx, vy, vz;
    getLookAtUnitVector(&vx, &vy, &vz);
    this->weapon->fire(power, vx, vy, vz);
  }

  void move_weapon()
  {
    this->weapon->move();
  }

  void set_weapon(Weapon* weapon)
  {
    this->weapon = weapon;
  }

  void move(Direction direction)
  {
    double vx, vy, vz;
    getLookAtUnitVector(&vx, &vy, &vz);
    vx *= 0.1;
    vz *= 0.1;
    switch (direction) {
      case Up:
      this->location->translate(vx, 0, vz);
      this->lookAt->translate(vx, 0, vz);
      break;
      case Down:
      this->location->translate(-vx, 0, -vz);
      this->lookAt->translate(-vx, 0, -vz);
      break;
      case Left:
      this->location->translate(vz, 0, -vx);
      this->lookAt->translate(vz, 0, -vx);
      break;
      case Right:
      this->location->translate(-vz, 0, vx);
      this->lookAt->translate(-vz, 0, vx);
      break;
    }
  }

  void look(Direction direction) {
    switch (direction) {
      case Up:
      this->rotateLookVectorVertical(1);
      break;
      case Down:
      this->rotateLookVectorVertical(-1);
      break;
      case Left:
      this->rotateLookVectorHorizontal(5);
      break;
      case Right:
      this->rotateLookVectorHorizontal(-5);
      break;
    }
  }

private:
  void rotateLookVectorVertical(double theta)
  {
    if(theta > 0 && upAngle() > 90 || theta < 0 && upAngle() < -90)
      return;
    Point* p = this->lookAt;
    p->translate(-this->location->x, -this->location->y, -this->location->z);
    double alpha = 180 / PI * atan2(p->z, p->x);
    p->rotateY(alpha);
    p->rotateZ(theta);
    p->rotateY(-alpha);
    p->translate(this->location->x, this->location->y, this->location->z);
  }

  void rotateLookVectorHorizontal(double theta)
  {
    Point* p = this->lookAt;
    p->translate(-this->location->x, -this->location->y, -this->location->z);
    p->rotateY(theta);
    p->translate(this->location->x, this->location->y, this->location->z);
  }

  double upAngle()
  {
    double dx = this->lookAt->x - this->location->x;
    double dy = this->lookAt->y - this->location->y;
    double dz = this->lookAt->z - this->location->z;
    return 180 / PI * atan2(dy, sqrt(dx * dx + dz * dz));
  }

  double getLookAtUnitVector(double* vx, double* vy, double* vz)
  {
    double tmpVx = this->lookAt->x - this->location->x;
    double tmpVy = this->lookAt->y - this->location->y;
    double tmpVz = this->lookAt->z - this->location->z;
    double norm = sqrt(tmpVx * tmpVx + tmpVy * tmpVy + tmpVz * tmpVz);
    *vx = tmpVx / norm;
    *vy = tmpVy / norm;
    *vz = tmpVz / norm;
  }
};