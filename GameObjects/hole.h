
class Hole: public GameObject {
public:
  Point* location;
  double radius;
  bool isOccupied;
  Hole(double x, double z, double radius) {
    this->location = new Point(x, 0, z);
    this->radius = radius;
    this->isOccupied = false;
  }

  void draw()
  {
    glColor3d(0.0f,0.0f,0.0f);
  	glPushMatrix();
    glTranslated(this->location->x, this->location->y, this->location->z);
    glRotated(90, 1, 0, 0);
    gluDisk(gluNewQuadric(), 0, this->radius, RESOLUTION, RESOLUTION);
  	glPopMatrix();
  }
};
