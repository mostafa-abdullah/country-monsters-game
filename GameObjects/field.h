using namespace std;

class Field: public GameObject {
public:
  Field(int n, int m, int numHoles, int numMonsters)
  {
    this->n = n;
    this->m = m;
    // TODO set world DIMENSIONS
    this->width = windowWidth / 200;
    this->length = windowHeight / 200;
    this->numHoles = numHoles;
    this->numMonsters = numMonsters;

    this->add_holes();
    this->add_monsters();
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
    this->draw_monsters();
  }

  void add_monsters()
  {
    for(int i = 0; i < numMonsters; i++) {
      this->monsters.push_back(Monster(100, rand() % 100));
    }
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

  Hole* get_free_hole()
  {
    vector<Hole*> freeHoles;
    for(int i = 0; i < numHoles; i++) {
      if(!holes[i].isOccupied) {
        freeHoles.push_back(&holes[i]);
      }
    }

    if(freeHoles.size() == 0)
      throw invalid_argument("No free holes.");

    return freeHoles[rand() % freeHoles.size()];
  }

  void update_monsters()
  {
    for(int i = 0; i < numMonsters; i++) {
      Monster* m = &monsters[i];
      switch(m->state) {
        case Visible:
        m->decrement_timer();
        break;
        case Hiding:
        m->set_hole(this->get_free_hole());
        m->set_state(MovingUp);
        break;
        case MovingUp:
        m->move_up();
        break;
        case MovingDown:
        m->move_down();
        break;
      }
    }

  }
vector<Monster> monsters;
private:
  int n;
  int m;
  int width;
  int length;
  int numHoles, numMonsters;

  vector<Hole> holes;


  void draw_holes()
  {
    for(int i = 0; i < numHoles; i++) {
      holes[i].draw();
    }
  }

  void draw_monsters()
  {
    for(int i = 0; i < numMonsters; i++) {
      if(monsters[i].state != Hiding)
        monsters[i].draw();
    }
  }
};
