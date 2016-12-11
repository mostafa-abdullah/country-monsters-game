class Mine: public Weapon {
public:
  double velocityX, velocityY, velocityZ;
  bool readyToBomb;
  Mine()
  {
    this->location = new Point(0, 0, 0);
    this->isMoving = false;
    this->readyToBomb = false;
    this->type = MineType;
  }

  void draw()
  {
    glColor3d(0.5f,0.0f,0.0f);
  	glPushMatrix();
    glTranslated(this->location->x, this->location->y, this->location->z);
    glScaled(0.13, 0.13, 0.13);
    glutSolidSphere(1, RESOLUTION, RESOLUTION);
    if(readyToBomb) {
      glPushMatrix();
      glRotated(90, 1, 0, 0);
      gluDisk(gluNewQuadric(), 0, MineRange / 0.13, 50, 50);
      glPopMatrix();
    }
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
    this->location->translate(velocityX, velocityY, velocityZ);
  	velocityY += GRAVITY;
  }
};
