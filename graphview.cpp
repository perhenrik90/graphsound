/*
 *  GraphView.cpp
 *  GraphSound
 *
 *  Created by Per-Henrik Kvalnes on 06.06.12.
 *  Copyright 2012 Home. All rights reserved.
 *
 */

#include "graphview.h"

GraphView::GraphView()
{
	gmodel = NULL;
	graphEvent = NONE;
	default_width = 30;
	
	lastMouseX = 0;
	lastMouseY = 0;
	lockTime = 0;
}

GraphView::~GraphView()
{
	
}


void GraphView::drawModel(sf::RenderWindow &rw)
{
	drawEdges(rw);
	drawCircles(rw);
}



void GraphView::drawCircles(sf::RenderWindow &rw)
{
	if(gmodel == NULL)
	{
		std::cout << "Circle view do not have a model!"; 
		return;
	}	
	
	std::vector<CircleModel*> list = gmodel->getCircleModels();
	
	for(int i = 0; i < list.size(); i ++)
	{
		int x = list[i]->getX();
		int y = list[i]->getY();
		int s = list[i]->getWidth();
		sf::Color c = list[i]->getColor();
		
		for(int a = 0; a < s; a ++)
		{
			c.a ++;
			rw.Draw(sf::Shape::Circle(x , y , a, c));
		}
		
		std::stringstream ss;
		ss << list[i]->getID();
		std::string str;
		ss >> str;
		
		sf::String number;
		number.SetX(list[i]->getX());
		number.SetY(list[i]->getY());
		number.SetText(str);
		rw.Draw(number);
	}
				
}

void GraphView::drawEdges(sf::RenderWindow & rw)
{
	std::vector<CircleModel*> list = gmodel->getCircleModels();
	
	for(int i = 0; i < list.size(); i ++)
	{
		std::vector<CircleModel*> foreignList = list[i]->getEdges();
		
		std::cout << "size: " << i << std::endl;
		
		for(int y = 0; y < foreignList.size(); y ++)
		{
			int thisx = list[i]->getX();
			int thisy = list[i]->getY();
			
			int foreignx = foreignList[y]->getX();
			int foreigny = foreignList[y]->getY();
			
			//std::cout << "this x: " << thisx << std::endl;
			//std::cout << "this y: " << thisy << std::endl;
			
		
			sf::Shape line = sf::Shape::Line(thisx, thisy, foreignx, foreigny, 2,  sf::Color(250,250,250) );
			rw.Draw(line);
		}
	}
}


void GraphView::handleEvent(sf::Event & e)
{
	if(lockTime <= 0)
	{
		lockControll = false;
	}
	if(lockControll)
	{
		lockTime --;
		return;
	}
	
	if(e.Type == sf::Event::MouseButtonPressed)
	{
		
			if(graphEvent == ADD_BLUE_CIRCLE || ADD_RED_CIRCLE || ADD_GREEN_CIRCLE)
			{
				int x = e.MouseButton.X;
				int y = e.MouseButton.Y;
			
				if(! gmodel->canPlace(x, y))
				{
					if(graphEvent != ADD_EDGE)
						graphEvent = NONE;
				}  
				
				switch (graphEvent) 
				{
					case ADD_BLUE_CIRCLE:
						gmodel->addCircle(x, y, default_width, BLUE);
						break;
						
					case ADD_CAYAN_CIRCLE:
						gmodel->addCircle(x, y, default_width, CAYAN);
						break;
					
					case ADD_GREEN_CIRCLE:
						gmodel->addCircle(x, y, default_width, GREEN);
						break;
						
					case ADD_YELLO_CIRCLE:
						gmodel->addCircle(x, y, default_width, YELLO);
						break;
						
					case ADD_ORANGE_CIRCLE:
						gmodel->addCircle(x, y, default_width, ORANGE);
						break;
						
					case ADD_PINK_CIRCLE:
						gmodel->addCircle(x, y, default_width, PINK);
						break;
						
					case ADD_RED_CIRCLE:
						gmodel->addCircle(x, y, default_width, RED);
						break;
						
					case ADD_BROWN_CIRCLE:
						gmodel->addCircle(x, y, default_width, BROWN);
						break;
						
					case ADD_PURPLE_CIRCLE:
						gmodel->addCircle(x, y, default_width, PURPLE);
						break;
						
					default:
						break;
				};
							
		
				if(graphEvent == ADD_EDGE)
				{
					int x = e.MouseButton.X;
					int y = e.MouseButton.Y;
				
					CircleModel * cFrom = gmodel->getModelAt(lastMouseX, lastMouseY);
					if(cFrom != NULL)
					{
						CircleModel* cTo = gmodel->getModelAt(x, y);
						if(cTo != NULL)
						{
							cFrom->addEdge(cTo);
							//ins		BcTo->addEdge(cFrom);
							lockTime = 200;
						}
					}
					
					lastMouseX = x;
					lastMouseY = y;
					
					
					
				}
				
				graphEvent == NONE;
			}
		
		repaint = true;
	}
	
	
	
	else if(e.Type == sf::Event::KeyReleased)
	{
	
		switch (e.Key.Code) 
		{
			case '1':
				graphEvent = ADD_BLUE_CIRCLE;
				break;
				
			case '2':
				graphEvent = ADD_CAYAN_CIRCLE;
				break;
				
			case '3':
				graphEvent = ADD_GREEN_CIRCLE;
				break;
				
				
			case '4': 
				graphEvent = ADD_YELLO_CIRCLE;
				break;
				
			case '5':
				graphEvent = ADD_ORANGE_CIRCLE;
				break;
				
			case '6': 
				graphEvent = ADD_PINK_CIRCLE;
				break;
				
			case '7':
				graphEvent = ADD_RED_CIRCLE;
				break;
				
			case '8':
				graphEvent = ADD_BROWN_CIRCLE;
				break;
				
			case '9':
				graphEvent = ADD_PURPLE_CIRCLE;
				break;
				
			case 'e':
				graphEvent = ADD_EDGE;
				break;
				
			default:
				graphEvent = NONE;
				break;
		}
	}
}


bool GraphView::mustRepaint()
{
	if(gmodel->getRepaint() == true)
	{
		repaint = true;
	}
	return repaint;
}
