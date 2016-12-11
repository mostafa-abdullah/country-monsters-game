int gameID;
int windowWidth;
int windowHeight;
const int RESOLUTION = 50;

#define intToString( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

void displayString(std::string s, double x, double y, double r, double g, double b)
{
	glColor3d(r, g, b);
    glRasterPos3d(x, y, -3);
    for (int i = 0; i < s.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }
}
