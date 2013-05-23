/*
 *  graphmodel.cpp
 *  GraphSound
 *
 *  Created by Per-Henrik Kvalnes on 06.06.12.
 *  Copyright 2012 Home. All rights reserved.
 *
 */

#include "graphmodel.h"

GraphModel::GraphModel()
{
		
}

GraphModel::~GraphModel()
{
	for(int i = 0; i < circles.size(); i ++)
	{
		delete circles[i];
	}
}

/*** add functions ***/
void GraphModel::addCircle(double x, double y, double width, CircleType ct)
{
	CircleModel * circle = new CircleModel(x, y, width, ct);
	circles.push_back(circle);
}




void GraphModel::addEdge(int fromID, int toID)
{
	if(fromID == toID)
	{
		return;
	}
	for(int i = 0; i < circles.size(); i++)
	{
			if(circles[i]->getID() == fromID)
			{
				
				for(int y = 0; y < circles.size(); y++)
				{
					if(circles[y]->getID() == toID)
					{
						circles[i]->addEdge(circles[y]);
					}
				}
			}
	}
}



/*** Collision detection ***/
bool GraphModel::canPlace(int x, int y)
{
	for(int i = 0; i < circles.size(); i ++)
	{
		int foreign_x = circles[i]->getX();
		int foreign_y = circles[i]->getY();
		int foreign_width = circles[i]->getWidth()*1.8;
		
		if(x > foreign_x - foreign_width && x < foreign_x + foreign_width)
		{
				if(y > foreign_y - foreign_width && y < foreign_y + foreign_width)
				{
					return false;
				}
		}
	}
	return true;
}



CircleModel* GraphModel::getModelAt(int atX, int atY)
{
	for(int i = 0; i < circles.size(); i ++)
	{
		int x = circles[i]->getX();
		int y = circles[i]->getY();
		int w = circles[i]->getWidth();
		
		if(atX > x-w && atX < x+w)
		{
				if(atY > y-w && atY < y+w)
				{
					return circles[i];
				}
		}
	}
	return NULL;
}