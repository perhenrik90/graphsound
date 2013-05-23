/*
 *  graphmodel.h
 *  GraphSound
 *
 *  Created by Per-Henrik Kvalnes on 06.06.12.
 *  Copyright 2012 Home. All rights reserved.
 *
 */

#ifndef __GRAPH_MODEL__
#define __GRAPH_MODEL__

#include <iostream>
#include <vector>
#include"circlemodel.h"

class GraphModel
{
private:
	std::vector<CircleModel *> circles;
	bool repaint;
	
public:
	
	GraphModel();
	~GraphModel();
	
	/*** add functions ***/
	void addCircle(double x, double y, double width, CircleType ct);
	void addEdge(int fromID, int toID);
	
	/*** get functions ***/
	std::vector<CircleModel*>& getCircleModels() { return circles; }
	CircleModel* getModelAt(int x, int y);
	
	void setRepaint() { repaint = true; };
	bool getRepaint() { bool r = repaint; repaint = false; return r; }
	/*** collision detection ***/
	bool canPlace(int x, int y);
};

#endif