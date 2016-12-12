
class Pickup: public GameObject {
public:
  Point* location;
  int angle;

  Pickup(double x, double z) {
    this->location = new Point(x, 1.5, z);
    this->angle = 0;
  }

  void draw()
  {
    glColor3d(1.0f,1.0f,0.0f);
  	glPushMatrix();
    glTranslated(this->location->x, this->location->y, this->location->z);
    glScaled(0.2, 0.2, 0.2);
    glRotated(angle, 0, 1, 0);
    glutSolidCube(1);
  	glPopMatrix();
  }

  void rotate()
  {
    this->angle = (this->angle + 3) % 360;
  }
};
