class Brick: public Weapon {
public:
  void draw()
  {
    glColor3d(0.5f,0.0f,0.0f);
  	glPushMatrix();
    glTranslated(this->x, this->y, this->z);
    glScaled(0.5, 0.2, 0.2);
    glutSolidCube(1);
  	glPopMatrix();
  }
};
