
class Hole: public GameObject {
public:
  double x, z, radius;
  bool isOccupied;
  Hole(double x, double z, double radius) {
    this->x = x;
    this->z = z;
    this->radius = radius;
    this->isOccupied = false;
  }

  void draw()
  {
    glColor3d(0.0f,0.0f,0.0f);
  	glPushMatrix();
    glTranslated(this->x, 0, this->z);
    glRotated(90, 1, 0, 0);
    gluDisk(gluNewQuadric(), 0, this->radius, RESOLUTION, RESOLUTION);
  	glPopMatrix();
  }
};
