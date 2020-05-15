// Robot Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
const int size = 10;
class Robot
{
public:
	typedef int coord_type;
	typedef int health_type;
public:
	Robot(coord_type x, coord_type y, health_type h) :x_(x), y_(y), health_(h)
	{

	}
	void moving(int dir)
	{
		if (dir == 0)
			--y_;
		else if (dir == 1)
			++x_;
		else if (dir == 2)
			++y_;
		else if (dir == 3)
			--x_;
		if (x_ < 0 || x_ >= size || y_ < 0 || y_ >= size)
			health_ = 0;
		std::cout << "Robot's coordinates is: " << x_ << "  " << y_ << "\n";
	}
	virtual void add_health(const health_type health)
	{
		health_ += health;
		std::cout << "Robot's health is: " << health_ << "\n";
	}
	coord_type get_x() const
	{
		return x_;
	}
	coord_type get_y() const
	{
		return y_;
	}
	health_type get_health() const
	{
		return health_;
	}
	void PrintCoordinates() const
	{
		std::cout << "x = " << x_ << " " << "y = " << y_ << " health = " << health_ << "\n";
	}
	virtual ~Robot()
	{

	}
protected:
	coord_type x_;
	coord_type y_;
	health_type health_;
};
class TiringRobot :public Robot
{
public:
	TiringRobot(coord_type x, coord_type y, health_type h) :Robot(x, y, h)
	{

	}
	void add_health(const health_type health) override
	{
		health_ += health;
		--health_;
		std::cout << "Robot's health is: " << health_ << "\n";
	}
};
class Arena
{
public:
	typedef int container_type;
	typedef int coord_type;
public:
	Arena() : arena_(size, std::vector<container_type>(size))
	{
		srand(time(NULL));
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
				if (i % 2 == 0 && j % 2 == 0)
					arena_[i][j] = rand() % size - size;
				else arena_[i][j] = rand() % size;
	}
	void AddRobot(Robot* robot)
	{
		robot_list.push_back(robot);
		arena_[robot->get_x()][robot->get_y()] = 0;
	}
	void Display() const
	{
		for (int i = 0; i < robot_list.size(); ++i)
		{
			std::cout << "This is " << i << "th robot\n";
			robot_list[i]->PrintCoordinates();
		}
	}
	void Print_Arena() const
	{
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
				std::cout << arena_[i][j] << " ";
			std::cout << "\n";
		}
	}
	bool Tick()
	{
		srand(time(NULL));
		for (int i = 0; i < robot_list.size(); ++i)
		{
			int dir = rand() % 4;
			std::cout << i << "th robot moves to " << dir << " direction \n";
			robot_list[i]->moving(dir);
			if (robot_list[i]->get_health() != 0)
				robot_list[i]->add_health(arena_[robot_list[i]->get_x()][robot_list[i]->get_y()]);
			if (robot_list[i]->get_health() <= 0)
			{
				std::cout << "robot" << i << " is dead\n";
				robot_list.erase(robot_list.begin() + i);
				--i;
			}
			if (robot_list.size() == 0)
			{
				std::cout << "Game have no robot\n";
				return false;
			}
		}
		return true;
	}
private:
	std::vector<std::vector<container_type>> arena_;
	std::vector<Robot*> robot_list;
};
int main()
{
	Arena a;
	std::cout << "Arena state:\n";
	a.Print_Arena();
	int x;
	int y;
	int h;
	std::cout << "Insert Robots coordinates and health\n";
	while (std::cin >> x && std::cin >> y && std::cin >> h)
	{
		Robot* robot;
		std::cout << "Insert Robot type:if you want a simple Robot insert 1 else if you want TiringRobot insert 2\n";
		int type;
		std::cin >> type;
		if (type == 1)
		{
			robot = new Robot(x, y, h);
			a.AddRobot(robot);
		}
		else if (type == 2)
		{
			robot = new TiringRobot(x, y, h);
			a.AddRobot(robot);
		}
		std::cout << "Isert next robot coordinates and health\n";
	}
	while (a.Tick())
	{
		a.Display();
	}
}