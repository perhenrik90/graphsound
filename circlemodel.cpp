/*
 *  circlemodel.cpp
 *  GraphSound
 *
 *  Created by Per-Henrik Kvalnes on 06.06.12.
 *  Copyright 2012 Home. All rights reserved.
 *
 */
#include <iostream>

#include "circlemodel.h"

CircleModel::CircleModel(int x, int y, int width, CircleType t)
{
	circle_id = circle_count;
	circle_count ++;
	
	x_pos = x;
	y_pos = y;
	circle_width = width;
	circleType = t;
	orginalType = t;
	isWhite = false;
	blinkTime = 1;
}

CircleModel::~CircleModel()
{

}

void CircleModel::addEdge(CircleModel*m)
{
		if(m->getID() == getID())
		{
			return;
		}
		
	neighbours.push_back(m);
}

sf::Color CircleModel::getColor()
{
	if(isWhite)
	{
		whiteTime --;
		
		if(whiteTime <= 0)
				circleType = orginalType;
		
		isWhite = false;
		return sf::Color(250,250,250);
	}
	
	
	if(circleType == BLUE)
		return sf::Color(0,100, 240);
	
	else if(circleType == CAYAN)
		return sf::Color(0, 220, 240);
	
	else if(circleType == GREEN)
		return sf::Color(0, 245, 70);
	
	else if(circleType == YELLO)
		return sf::Color(255, 254, 41);
	
	else if(circleType == ORANGE)
		return sf::Color(254, 173, 5);
	
	else if(circleType == PINK)
		return sf::Color(255, 25, 162);
	
	else if(circleType == RED)
		return sf::Color(255, 50, 50);
	
	else if(circleType == BROWN)
		return sf::Color(126, 33, 24);
	
	else if(circleType == PURPLE)
		return sf::Color(61, 9, 91);
	
	return sf::Color(250,250,250);
}