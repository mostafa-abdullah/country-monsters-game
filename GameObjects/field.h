using namespace std;

class Field: public GameObject {
public:
  Field(int n, int m, int numHoles)
  {
    this->n = n;
    this->m = m;
    // TODO set world DIMENSIONS
    this->width = windowWidth / 200;
    this->length = windowHeight / 200;
    this->numHoles = numHoles;

    this->add_holes();
  }

  void draw()
  {
    glColor3d(0.0f,0.7f,0.0f);
  	glPushMatrix();
    glTranslated(0, -0.51, 0);
  	glScaled(this->width, 1, this->length);
  	glutSolidCube(1);
  	glPopMatrix();
    this->draw_holes();
  }

  void add_holes()
  {
    bool grid[this->n][this->m];
    memset(grid, false, sizeof(bool) * this->n * this->m);

    double cellWidth = 1.0 * this->width / this->n;
    double cellLength = 1.0 * this->length / this->m;

    for(int i = 0; i < numHoles; i++) {
      int r, c;
      do {
        r = rand() % this->n;
        c = rand() % this->m;
      }
      while(grid[r][c]);
      grid[r][c] = true;

      double x = r * cellWidth + cellWidth / 2 - this->width / 2.0;
      double z = c * cellLength + cellLength / 2 - this->length / 2.0;

      holes.push_back(Hole(x, z, min(cellWidth, cellLength) * 0.3));
    }
  }

private:
  int n;
  int m;
  int width;
  int length;
  int numHoles;

  vector<Hole> holes;

  void draw_holes()
  {
    for(int i = 0; i < numHoles; i++) {
      holes[i].draw();
    }
  }
};
