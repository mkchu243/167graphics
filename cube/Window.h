#ifndef _WINDOW_H_
#define _WINDOW_H_

class Window	  // OpenGL output window related routines
{
  public:
    static int width, height; 	            // window size
    static bool cubeMode;

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void glutKeyboardFunc(unsigned char key,
                                   int x, int y);
    static void glutSpecialFunc(int key, int x, int y);

private:
  static void drawCube();
  static void drawHouse();
};

#endif

