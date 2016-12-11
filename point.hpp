class Point {
public:
  double x, y, z;
  Point(double x, double y, double z)
  {
      this->x = x;
      this->y = y;
      this->z = z;
  }

  void rotateZ(double theta)
  {
    theta = theta * 3.14 / 180;
    double c = cos(theta);
    double s = sin(theta);

    double tmpX = this->x;
    double tmpY = this->y;

    this->x = c * tmpX - s * tmpY;
    this->y = s * tmpX + c * tmpY;
  }

  void rotateY(double theta)
  {
    theta = theta * PI / 180;
    double c = cos(theta);
    double s = sin(theta);

    double tmpX = this->x;
    double tmpZ = this->z;

    this->x = c * tmpX + s * tmpZ;
    this->z = -s * tmpX + c * tmpZ;
  }

  void translate(double dx, double dy, double dz)
  {
    this->x += dx;
    this->y += dy;
    this->z += dz;
  }
};
