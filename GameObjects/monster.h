
class Monster: public GameObject {
public:
  void draw()
  {
    glColor3d(0.0f,0.0f,1.0f);
  	glPushMatrix();
    glTranslated(this->x, 0, this->z);
    glScaled(1, 2, 1);
    glutSolidCube(1);
  	glPopMatrix();
  }

private:
  double x, z;
};
