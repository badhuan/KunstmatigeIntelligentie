#include <iostream>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>
#include "Controller.h"

int main(int args[])
{
	Controller* controller = new Controller();

	//auto window = Window::CreateSDLWindow();
	auto application = new FWApplication();
	if (!application->GetWindow())
	{
		LOG("Couldn't create window...");
		return EXIT_FAILURE;
	}
	
	application->SetTargetFPS(60);
	application->SetColor(Color(255, 10, 40, 255));
	

	//while (true){}
	while (application->IsRunning())
	{
		application->StartTick();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				application->Quit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){

				default:
					break;
				}
			}
		}
		
		application->SetColor(Color(0, 0, 0, 255));
		application->DrawText("Welcome to KMint", 800 / 2, 600 / 2);
		
		//Test draw vertices
		for (auto vertex : *controller->getVertices()){
			application->DrawRect(vertex->getX(), vertex->getY(), 10, 10, true);
		}
		//Test draw edges
		for (auto edge : *controller->getEdges()){
			application->DrawLine(edge->getSource()->getX(), edge->getSource()->getY(), edge->getTarget()->getX(), edge->getTarget()->getY());
		}

		// For the background
		application->SetColor(Color(255, 255, 255, 255));

		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}
		
	return EXIT_SUCCESS;
}