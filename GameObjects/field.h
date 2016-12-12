using namespace std;

class Field: public GameObject {
public:
  Field(int n, int m, int numHoles, int numMonsters, Person* person)
  {
    this->n = n;
    this->m = m;

    this->width = FieldWidth;
    this->length = FieldLength;
    this->gamePlayWidth = FieldWidth - 10;
    this->gamePlayLength = FieldLength - 10;
    this->numHoles = numHoles;
    this->numMonsters = numMonsters;
    this->person = person;

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
    this->draw_fired_weapons();
  }

  void add_monsters()
  {
    for(int i = 0; i < numMonsters; i++) {
      this->monsters.push_back(Monster(100, 20 + rand() % 100));
    }
  }

  void add_holes()
  {
    bool grid[this->n][this->m];
    memset(grid, false, sizeof(bool) * this->n * this->m);

    double cellWidth = 1.0 * this->gamePlayWidth / this->n;
    double cellLength = 1.0 * this->gamePlayLength / this->m;

    for(int i = 0; i < numHoles; i++) {
      int r, c;
      do {
        r = rand() % this->n;
        c = rand() % this->m;
      }
      while(grid[r][c]);
      grid[r][c] = true;

      double x = r * cellWidth + cellWidth / 2 - this->gamePlayWidth / 2.0;
      double z = c * cellLength + cellLength / 2 - this->gamePlayLength / 2.0;

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

  void fire_weapon(Weapon* weapon)
  {
    if(weapon == NULL)
      return;
    weaponsFired.push_back(weapon);
  }

  void update_field()
  {
    update_fired_weapons();
    update_monsters();
  }

  void update_fired_weapons()
  {
    for(int i = 0; i < weaponsFired.size(); i++) {
      weaponsFired[i]->move();

      if(weaponsFired[i]->is_out_of_field(this->gamePlayWidth, this->gamePlayLength)) {
        if(weaponsFired[i]->type == MineType && weaponsFired[i]->location->y < 0) {
          weaponsFired[i]->location->y = 0;
          ((Mine*)weaponsFired[i])->readyToBomb = true;
          weaponsFired[i]->isMoving = false;
        }
        else{
          weaponsFired.erase(weaponsFired.begin() + i);
        }
      }

      if(weaponsFired[i]->type == MineType)
        continue;
      // detect collision with monsters
      for(int j = 0; j < numMonsters; j++) {
        if(weaponsFired[i]->is_hitting_monster(&monsters[j], 0)) {
          // FIXME core dumped once here
          this->person->score += monsters[j].score;
          weaponsFired.erase(weaponsFired.begin() + i);
          this->monsters.erase(this->monsters.begin() + j);
          numMonsters--;
          break;
        }
      }
    }
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

  void bomb_mines()
  {
    for(int i = 0; i < weaponsFired.size(); i++)
      if(weaponsFired[i]->type == MineType && ((Mine*)weaponsFired[i])->readyToBomb) {
        for(int j = 0; j < numMonsters; j++) {
          if(weaponsFired[i]->is_hitting_monster(&monsters[j], MineRange)) {
            this->person->score += monsters[j].score;
            this->monsters.erase(this->monsters.begin() + j);
            numMonsters--;
            j--;
          }
        }
        weaponsFired.erase(weaponsFired.begin() + i);
        i--;
      }
  }

  bool person_on_hole()
  {
    for(int i = 0; i < numHoles; i++){
        if(holes[i].location->distance2(*this->person->location) < 5 + EPS)
          return true;
    }
    return false;
  }

private:
  int n;
  int m;
  int width;
  int length;
  int gamePlayWidth;
  int gamePlayLength;
  int numHoles, numMonsters;

  vector<Hole> holes;
  vector<Monster> monsters;
  vector<Weapon*> weaponsFired;

  Person* person;

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

  void draw_fired_weapons()
  {
      for(int i = 0; i < weaponsFired.size(); i++) {
        weaponsFired[i]->draw();
      }
  }
};
