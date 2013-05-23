/*
 *  graphview.h
 *  GraphSound
 *
 *  Created by Per-Henrik Kvalnes on 06.06.12.
 *  Copyright 2012 Home. All rights reserved.
 *
 */
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <sstream>

#include <iostream>
#include <vector>

#include "circlemodel.h"
#include "graphmodel.h"

#ifndef __CIRCLE_VIEW__
#define __CIRCLE_VIEW__

enum GraphEvent
{
	NONE,
	ADD_BLUE_CIRCLE,
	ADD_CAYAN_CIRCLE,
	ADD_GREEN_CIRCLE,
	ADD_YELLO_CIRCLE,
	ADD_ORANGE_CIRCLE,
	ADD_PINK_CIRCLE,
	ADD_RED_CIRCLE,
	ADD_BROWN_CIRCLE,
	ADD_PURPLE_CIRCLE,
	 
	ADD_EDGE
};

class GraphView
{
private:
	
	bool		repaint;		// time for repaint!
	bool		lockControll;
	int			lockTime;
	
	int			lastMouseX;
	int			lastMouseY;
	
	GraphModel * gmodel;		// pointer to the datamodel with elements.
	GraphEvent graphEvent;		// a graph event, enum over.
	
	int default_width;			// a default width for the circles
	
	/*** draw functions ***/
	void drawCircles(sf::RenderWindow & renderWindow);
	void drawEdges(sf::RenderWindow & renderWindow);
	
public:
	GraphView();
	~GraphView();
	
	void drawModel(sf::RenderWindow &renderWindow);
	
	void handleEvent(sf::Event & event);
	
	/** set functions ***/
	void setModel(GraphModel * model) { gmodel = model; }
	
	/** get functions **/
	bool mustRepaint();
	void finishPaint() { repaint = false; }

};

#endif