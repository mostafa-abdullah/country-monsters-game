class Monster: public GameObject {
public:
  Hole* hole;
  int score, outTime, currentTime;
  double y;
  MonsterState state;

  Monster(int score, int outTime)
  {
    this->score = score;
    this->outTime = outTime;
    y = 0;
    state = Hiding;
  }

  void draw()
  {
    glColor3d(0.0f,0.0f,1.0f);
  	glPushMatrix();
    Hole h = *(this->hole);
    glTranslated(h.location->x, y - 0.51, h.location->z);
    glScaled(0.1, 1, 0.1);
    glutSolidCube(1);
  	glPopMatrix();
  }

  void decrement_timer() {
    if(!--currentTime) {
      this->state = MovingDown;
    }
  }

  void move_up() {
    y += 0.01;
    if(y >= 1) {
      this->state = Visible;
      currentTime = outTime;
    }
  }

  void set_state(MonsterState newState)
  {
    this->state = newState;
  }

  void move_down() {
    y -= 0.01;
    if(y <= 0) {
      (this->hole)->isOccupied = false;
      this->state = Hiding;
    }
  }

  void set_hole(Hole* hole)
  {
    this->hole = hole;
    (this->hole)->isOccupied = true;
  }
};
