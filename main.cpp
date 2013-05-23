
#include <SFML/Graphics.hpp>
#include "graphmodel.h"
#include "graphview.h"
#include "soundengine.h"


SoundEngine * soundEngine;
GraphView   * graphView;
sf::RenderWindow App(sf::VideoMode(800, 600), "Graph Sound");


void runCsound(void * user)
{
	while(true)
	{
		soundEngine->runCsound();
		//sf::Sleep(0.4f);
	}
}

void runScore(void * user)
{
	while(true)
	{
		soundEngine->runScore();
		sf::Sleep(0.001f);
	}
}

void paint(void * paint)
{
	while(true)
	{
		// Clear screen
		if(graphView->mustRepaint())
			App.Clear();
		
		if(graphView->mustRepaint())
		{
			graphView->drawModel(App);
			graphView->finishPaint();
		}
		
		App.Display();
		sf::Sleep(0.005f);
	}
}

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    // Create main window
    


	GraphModel	gm;
	graphView = new GraphView();
	graphView->setModel(&gm);
	
	gm.addCircle(40, 40, 20, GREEN);
	
	CircleModel * c1 = gm.getModelAt(40,40);

	
	
	
	std::cout << gm.getModelAt(80,200);
	
	
	soundEngine = new SoundEngine();
	soundEngine->setModel(&gm);
	soundEngine->setModel(c1);
	
	// Threads
	sf::Thread csoundThread(&runCsound, 0);
	sf::Thread scoreThread(&runScore, 0);
	sf::Thread paintThread(& paint, 0);
	
	csoundThread.Launch();
	scoreThread.Launch();
	paintThread.Launch();
	
    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }

	
		graphView->handleEvent(Event);
		//sf::Sleep(0.010f);

        // Finally, display the rendered frame on screen
		  //App.Display();
		
		
		
    }

    return EXIT_SUCCESS;
}
