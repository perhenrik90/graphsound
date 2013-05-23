/*
 *  SoundEngine.cpp
 *  GraphSound
 *
 *  Created by Per-Henrik Kvalnes on 06.06.12.
 *  Copyright 2012 Home. All rights reserved.
 *
 */

#include "soundengine.h"


SoundEngine::SoundEngine()
{
	graphmodel = NULL;
	currentCircle = NULL;
	
	csound = new Csound();
	
	csound->Compile("sinosc.csd");
}

SoundEngine::~SoundEngine()
{
	csound->Stop();
	
	delete csound;
}


void SoundEngine::runCsound()
{
	//mutex.Lock();
	csound->Perform();
	
	//mutex.Unlock();
	
}

void SoundEngine::runScore()
{
	if(graphmodel == NULL || currentCircle == NULL)
	{
		std::cout << "Sound Engine is missing models!" ;
		return;
	}
	
	//mutex.Lock();
	
	
	/****** Find note ***/
	CircleType t = currentCircle->getCircleType();
	
	double note = 0;
	
	switch (t) 
	{
		case BLUE:
			note = 70;
			break;
		
		case CAYAN:
			note = 72;
			break;
			
		case GREEN:
			note = 73;
			break;
		
		case YELLO:
			note = 75;
			break;
			
		case ORANGE:
			note = 77;
			break;
			
		case PINK:
			note = 79;
			break;
			
		case RED:
			note = 80;
			break;
			
		case BROWN:
			note = 82;
			break;
			
		case PURPLE:
			note = 84;
			break;
			
		default:
			break;
	}
	
	currentCircle->setWhite();
	graphmodel->setRepaint();
	
	/*** Find next ***/
	float sleep = 400.0f;
	
	std::vector<CircleModel*> edge = currentCircle->getEdges();
	
	if(edge.size() != 0)
	{
		int i = sf::Randomizer::Random(0, edge.size()-1);
		
		while(edge[i]->getID() == currentCircle->getID())
		{
			i = sf::Randomizer::Random(0, edge.size()-1);
		}
		
		
		/*** check x distanse ***/
		if(currentCircle->getX() > edge[i]->getX())
		{
			sleep = (currentCircle->getX()- abs(edge[i]->getX()));
		}
		else
		{
			sleep = abs(edge[i]->getX()- currentCircle->getX());
		}
			
		/** check x distanse ***/
		if(currentCircle->getY() > edge[i]->getY())
		{
			sleep += (currentCircle->getY()- abs(edge[i]->getY()));
		}
		else
		{
			sleep += abs(edge[i]->getY()- currentCircle->getY());
		}
					 
		//sleep += currentCircle->getY() + abs(edge[i]->getY());
	
		currentCircle = edge[i];
	}
	
	
	// Create Csound event
	MYFLT p_fields [4] = {1.0, 0.0, 0.2, note}; 
	csound->ScoreEvent('i', p_fields, 4	);
	
	if(sleep/120 <= 0.020)
		sleep = 1;
	
	sf::Sleep((sleep/200));
	
	//mutex.Unlock();
	
}

