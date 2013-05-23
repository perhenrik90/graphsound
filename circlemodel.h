/*
 *  circlemodel.h
 *  GraphSound
 *
 *  Created by Per-Henrik Kvalnes on 06.06.12.
 *  Copyright 2012 Home. All rights reserved.
 *
 */
#include <vector>
#include <SFML/Graphics.hpp>
#ifndef __CIRCLE_MODEL__
#define __CIRCLE_MODEL__

enum CircleType
{
	WHITE, BLUE, CAYAN,GREEN, YELLO, ORANGE, PINK, RED, BROWN, PURPLE 
};

static int		circle_count = 0;


class CircleModel
{
private:
	int				circle_id;
	
	double			circle_width;
	double			x_pos;
	double			y_pos;
	
	bool			isWhite;
	int				whiteTime;
	int				blinkTime;
	
	CircleType		circleType;
	CircleType		orginalType;
	
	std::vector<CircleModel*> neighbours;
	std::vector<int> neighboursDist;
	
public:
	
	CircleModel(int x, int y, int w,  CircleType t);
	~CircleModel();
	
	/*** set Functions ***/
	void setX(double x) { x_pos = x;}
	void setY(double y) { y_pos = y;}
	void setWhite() { isWhite = true; whiteTime = blinkTime; }
	
	/*** get Fumctions ***/
	double getWidth() { return circle_width; }
	double getX() { return x_pos; }
	double getY() { return y_pos; }
	
	sf::Color getColor(); 
	CircleType getCircleType() { return circleType; }
	
	int	   getID() { return circle_id; }
	std::vector<CircleModel*> getEdges() { return neighbours; }
	
	/*** add Functions **/
	void addEdge(CircleModel* cm);	
	
	
};

#endif