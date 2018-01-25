/* 
 * Originally by Philip Koopman (koopman@cmu.edu)
 * and Milda Zizyte (milda@cmu.edu)
 *
 * STUDENT NAME:Darius Davis
 * ANDREW ID: dariusd
 * LAST UPDATE: 1:23am
 *
 * This file is an algorithm to solve the ece642rtle maze
 * using the left-hand rule. The code is intentionaly left obfuscated.
 */



//m1.maze file format:
//    first line is start square
//    second line is end square
//    remaining lines are maze walls



// external helper functions.  Don't change these lines!
bool bumped(int xa, int ya, int xb, int yb);
bool atend(int x, int y);
void displayTurtle(int r);



// OK to change below this point



#define TIMEOUT 17 // bigger number slows down simulation so you can see what's happening

float time, orientation, state;

float xa, ya, xb, yb;

float z, e, m, b, q;



// this procedure takes one step in the maze and returns   true=done / false=not done

// Ground rule -- you are only allowed to call the three helper functions above, and NO other turtle methods or maze methods (no peeking at the maze!)

bool moveTurtle(QPointF & pos_) {

  ROS_INFO("Turtle update Called  time=%f", time);

  m = true;

  if (time == 0) {
    xa = pos_.x();
    ya = pos_.y();
    xb = pos_.x();
    yb = pos_.y();

    if (orientation < 2)
      if (orientation == 1) xb += 1;
      else yb += 1;
    else {
      xb += 1;
      yb += 1;
      if (orientation == 3) ya += 1;
      else xa += 1;
    }
    b = bumped(xa, ya, xb, yb);
    e = atend(pos_.x(), pos_.y());

    if (orientation == 0)
      if (state == 2) {
        orientation = 3;
        state = 1;
      } else if (b) {
      orientation = 1;
      state = 0;
    } else state = 2;
    else if (orientation == 3)
      if (state == 2) {
        orientation = 2;
        state = 1;
      } else if (b) {
      orientation = 0;
      state = 0;
    } else state = 2;
    else if (orientation == 2)
      if (state == 2) {
        orientation = 1;
        state = 1;
      } else if (b) {
      orientation = 3;
      state = 0;
    } else state = 2;
    else if (orientation == 1)
      if (state == 2) {
        orientation = 0;
        state = 1;
      } else if (b) {
      orientation = 2;
      state = 0;
    } else state = 2;
    else if (state == 5) {
      orientation = 3;
      state = 0;
    } else if (b) {
      orientation = 1;
      state = 1;
    } else state = 2;


    ROS_INFO("Orientation=%f  STATE=%f", orientation, state);
    z = state == 2;
    m = true;

    if (z == true && e == false) {
      if (orientation == 4) pos_.setY(pos_.y() + 0);
      if (orientation == 3) pos_.setY(pos_.y() + 1);
      if (orientation == 2) pos_.setX(pos_.x() + 1);
      if (orientation == 1) pos_.setY(pos_.y() - 1);
      if (orientation == 0) pos_.setX(pos_.x() - 1);
      z = false;
      m = true;
    }
  }
  if (time == 0) time = TIMEOUT;
  else time -= 1;

  // display the turtle -- must call this function before returning!
  displayTurtle(orientation);
  return (e);
}


