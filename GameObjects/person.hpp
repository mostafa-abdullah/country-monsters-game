using namespace std;

class Person: public GameObject {
public:
  Weapon* weapon;
  Point* location;
  Point* lookAt;
  bool isFiring;
  double power;
  int score;
  int time;
  vector<int> ammo;

  Person()
  {
    this->location = new Point(0, 2, 3.5);
    this->lookAt = new Point(0, 2, 2.5);
    this->weapon = new Brick();
    this->power = 0;
    this->score = 0;
    this->time = 300000;
    this->isFiring = false;

    ammo.reserve(3);
    this->ammo[BrickType] = MAX_AMMO;
    this->ammo[SlippersType] = MAX_AMMO;
    this->ammo[MineType] = MAX_AMMO;
  }

  void draw()
  {
    double vx, vy, vz;
    getLookAtUnitVector(&vx, &vy, &vz);
    vx *= 0.5;
    vz *= 0.5;
    glPushMatrix();
    glTranslated(this->location->x + vx, this->location->y - 0.5, this->location->z  + vz);
    glRotated(atan2(vx, vz) * 180 / PI, 0, 1, 0);
    WeaponType type = weapon->type;
    if(this->ammo[type] > 0) {
      this->weapon->draw();
    }
    glPopMatrix();
  }

  Weapon* fire_weapon()
  {
    this->isFiring = false;
    WeaponType type = weapon->type;
    if(this->ammo[type] <= 0) {
      return NULL;
    }
    this->ammo[type]--;
    double vx, vy, vz;
    getLookAtUnitVector(&vx, &vy, &vz);
    this->weapon->location = new Point(this->location->x + vx * 0.5, this->location->y - 0.5, this->location->z + vz * 0.5);
    this->weapon->fire(power, vx, vy, vz);

    Weapon* returnedWeapon = this->weapon;

    if(this->weapon->type == SlippersType)
      this->weapon = new Slippers();
    else if(this->weapon->type == BrickType)
      this->weapon = new Brick();
    else if(this->weapon->type == MineType)
      this->weapon = new Mine();
    this->power = 0;
    return returnedWeapon;
  }

  void increase_power()
  {
    WeaponType type = weapon->type;
    if(this->ammo[type] <= 0) {
      return;
    }

    if(isFiring && power < 0.5)
      power += 0.005;
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

    Point newLocation = *this->location;
    newLocation.translate(vx, 0, vz);

    if(this->out_of_field(newLocation)) {
      return;
    }

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

  void display_score()
  {
    displayString("SCORE: " + intToString(this->score), -2.7, 2.5, 0, 0, 0);
  }

  void display_time()
  {
    displayString("TIME: " + intToString(this->time / 1000), 2, 2.5, 0, 0, 0);
  }

  void display_ammo()
  {
    WeaponType type = weapon->type;
    if(this->ammo[type] <= 0) {
      displayString("You have no ammo for this weapon.", -2, 2.5, 255, 0, 0);
    }
    else {
      displayString("Ammo: " + intToString(this->ammo[type]), -2, 2.5, 255, 0, 0);
    }
  }

  void display_power()
  {
    glPushMatrix();
  	glTranslated(0, 2, 0);
  	glScaled((this->power / 0.5) * 1.3, 0.1, 1);
  	glBegin(GL_QUADS);
    glColor3f(0, 1, 0);
  	glVertex3d(0, 0, -2.5);
  	glVertex3d(0, 1, -2.5);
    glColor3f(1, 0, 0);
  	glVertex3d(1, 1, -2.5);
  	glVertex3d(1, 0, -2.5);
  	glEnd();
    glPopMatrix();
  }

private:
  void rotateLookVectorVertical(double theta)
  {
    if(theta > 0 && upAngle() > 80 || theta < 0 && upAngle() < -80)
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

  bool out_of_field(Point point)
  {
    return point.x > FieldWidth / 2.0 - 5
        || point.x < -FieldWidth / 2.0 + 5
        || point.z > FieldLength / 2.0 - 5
        || point.z < -FieldLength / 2.0 + 5;
  }
};
