/* 
 * Originally by Philip Koopman (koopman@cmu.edu)
 * and Milda Zizyte (milda@cmu.edu)
 *
 * STUDENT NAME:
 * ANDREW ID:
 * LAST UPDATE:
 *
 * This file is an algorithm to solve the ece642rtle maze
 * using the left-hand rule. The code is intentionaly left obfuscated.
 */

//m1.maze file format:
//    first line is start square
//    second line is end square
//    remaining lines are maze walls

// external helper functions.  Don't change these lines!
bool bumped(int xa,int ya,int xb,int yb);
bool atend(int x, int y);
void displayTurtle(int r);

// OK to change below this point

#define TIMEOUT 2    // bigger number slows down simulation so you can see what's happening
float w, r, cs;
float xa, ya, xb, yb;
float z, e, m, b, q;
		 
// this procedure takes one step in the maze and returns   true=done / false=not done
// Ground rule -- you are only allowed to call the three helper functions above, and NO other turtle methods or maze methods (no peeking at the maze!)
bool moveTurtle(QPointF& pos_) 
{   ROS_INFO("Turtle update Called  w=%f", w);
	m = true;
    if(w == 0) 
	{ xa = pos_.x(); ya = pos_.y();
      xb = pos_.x(); yb = pos_.y();
	  if (r < 2)
		if (r == 1) xb+=1;
		else        yb+=1;
		else
		{ xb+=1; yb+=1; 
		  if (r == 3) ya+=1;  
		  else        xa+=1; 
		}
		b = bumped(xa,ya,xb,yb);
		e = atend(pos_.x(), pos_.y());
		if(r == 0)
		if(cs == 2) { r = 3;  cs = 1; }
		else if (b) { r = 1;  cs = 0; }
		else cs = 2;
		else if(r == 3)
		if(cs == 2) { r = 2;  cs = 1; }
		else if (b) { r = 0;  cs = 0; }
		else cs = 2;		
		else if(r == 2)
		if(cs == 2) { r = 1;  cs = 1; }
		else if (b) { r = 3;  cs = 0; }
		else cs = 2;
		else if(r == 1)
		if(cs == 2) { r = 0;  cs = 1; }
		else if (b) { r = 2;  cs = 0; }
		else cs = 2;
		else if(cs == 5) { r = 3;  cs = 0; }
		else if (b) { r = 1;  cs = 1; }
		else cs = 2;

	 ROS_INFO("Orientation=%f  STATE=%f", r, cs);
     z = cs == 2;
     m = true;
	 if(z == true && e == false) {
	 if (r == 4) pos_.setY(pos_.y() + 0);
     if (r == 3) pos_.setY(pos_.y() + 1);
     if (r == 2) pos_.setX(pos_.x() + 1);
     if (r == 1) pos_.setY(pos_.y() - 1); 
     if (r == 0) pos_.setX(pos_.x() - 1);
     z = false;
     m = true;
    }}
    if (w==0) w  = TIMEOUT; else w -= 1;
    // display the turtle -- must call this function before returning!
	displayTurtle(r);
 return(e);
}
