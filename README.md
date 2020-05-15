# Robot-Game
Robot Game
The Game has

 1.Robot class that has
   2d coordinates
   Health points

The Robot class has functions for 
  moving,adding health points(implemented as virtual function) and other simple functions 
  
2.The TiringRobot class which loses health points when moving. 
  The TiringRobot class is inherited from Robot class and  overrides virtual add_health() member function
  
**The type of robot is determined run time

3.The Arena class which is a 2d grid of some size on which some of the tiles have health bonuses on them and some of the tiles have 
  bombs on them. If a robot steps on a health bonus it gains health points and if it steps on a bomb it loses some health points.

Arena has the functions:
	Constructor, which generates a map with randomly placed bonuses and bombs (positive numbers are bonuses negative numbers are bombs)
  functions are:
	AddRobot: which takes a Robot* and adds to the list of robots.
	Display: displays the positions of all robots 
	Tick - makes all the robots move in a random direction. Returns true if some robots are still alive. 
  False if all robots are dead. A robot dies if its health points have reached 0 or below or if it steps out of the grid.

The Arena class has no idea about the existence of TiringRobots but can still work with them!
