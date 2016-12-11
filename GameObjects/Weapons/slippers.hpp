class Slippers: public Weapon {
public:
  double velocityX, velocityY, velocityZ;
  double angle;
  Slippers()
  {
    this->location = new Point(0, 0, 0);
    this->isMoving = false;
  }

  void draw()
  {
    glColor3d(0.5f,0.0f,0.0f);
  	glPushMatrix();
    glTranslated(this->location->x, this->location->y, this->location->z);
    glScaled(0.13, 0.13, 0.2);
    glRotated(angle, velocityZ, velocityY, -velocityX);
    glutSolidCube(1);
  	glPopMatrix();
  }

  void fire(double power, double vx, double vy, double vz)
  {
    this->isMoving = true;
    velocityX = power * vx;
    velocityY = power * vy;
    velocityZ = power * vz;
  }

  void move()
  {
    if(!isMoving)
      return;
    angle += 5;
    this->location->translate(velocityX, velocityY, velocityZ);
  }
};
