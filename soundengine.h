/*
 *  SoundEngine.h
 *  GraphSound
 *
 *  Created by Per-Henrik Kvalnes on 06.06.12.
 *  Copyright 2012 Home. All rights reserved.
 *
 */

#include <Csound.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "graphmodel.h"
#include "circlemodel.h"


#ifndef __SOUND_ENGINE__
#define __SOUND_ENGINE__



class SoundEngine
{
private:
	Csound * csound;
	GraphModel * graphmodel;
	CircleModel * currentCircle;
	
	sf::Mutex mutex;
	
	
public:
	SoundEngine();
	~SoundEngine();
	
	void runCsound();
	void runScore();
	
	void setModel(GraphModel * gm)  { graphmodel = gm; }
	void setModel(CircleModel * cm) { currentCircle = cm; }
};
#endif