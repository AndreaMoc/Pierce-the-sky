// All the SDL includes we need
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <cstdio> // Some utilities for the log
#include <memory> // Needed for the smart pointers

#include "Timer.h"
#include "InputManager.h"
#include "Position2D.h"

#include "Paddle.h"
#include "Ball.h"
#include "Block.h"

#include "Main.hpp"

int main() {
	// Game loop flag
	bool isQuittingGame = false;

	/**** Actors initialization ****/

	// Initializing paddle
	Paddle* paddle = new Paddle("Assets/MyAssets/mypaddle.png");

	// Setting the spawn point accounting for the paddle size
	Position2D* paddleSpawnPoint = new Position2D((SCREEN_WIDTH / 2) - (paddle->getWidth() / 2), SCREEN_HEIGHT - 3 * paddle->getHeight());
	paddle->setPosition(paddleSpawnPoint);

	/** Non-controllable textures **/

	// Ball
	Ball* ball = new Ball("Assets/MyAssets/ball.png");
	Position2D* ballSpawnPoint = new Position2D((SCREEN_WIDTH / 2) - (ball->getWidth() / 2), SCREEN_HEIGHT - 5 * ball->getHeight());
	ball->setPosition(ballSpawnPoint);

	// Drawables
	Drawable* background = new Drawable("Assets/MyAssets/background.png");
	Drawable* sampleText = new Drawable();

	// Lower wall: collision means life loss
	Collideable* lowerWall = new Collideable();
	lowerWall->setPosition(0, SCREEN_HEIGHT);
	lowerWall->setWidth(100);
	// Blocks
	Block* blockCollection[48]{};
	Position2D* blockSpawnPosition = new Position2D(50, SCREEN_HEIGHT / 2);


	int offset = 10;
	int j = 0;

	for (int i = 0; i < 48; ++i)
	{
		if (i < 16)
		{
			// Block initialization
			Block* block1 = new Block("Assets/MyAssets/block1.png");
			block1->setValue(5);

			// Setting block position
			int column = 0;
			if (i >= 8) column = 1;

			// Every 8, go up by a column equal to 2 times the block height
			block1->setPosition(blockSpawnPosition->getX() + (i % 8) * blockSpawnPosition->getX(), blockSpawnPosition->getY() + column * 2 * block1->getHeight());

			blockCollection[i] = block1;
			delete block1;
		}
	}


	/********************************/	

	// Game score
	int score = 0;

	// Keeps track of time between steps
	Timer stepTimer;

	// SDL Event handler
	SDL_Event sdlEvent;

	// Input managers
	InputManager* paddleInputManager = new InputManager(paddle);
	InputManager* ballInputManager = new InputManager(ball);

	// GAME LOOP
	while (!isQuittingGame) {
		// Handle events on queue
		while (SDL_PollEvent(&sdlEvent) != 0) {
			// User requests to quit application
			if (sdlEvent.type == SDL_QUIT) {
				isQuittingGame = true;
			}

			// Handle input for the ball and the paddle
			// only in gameplay state
			paddleInputManager->getInput(sdlEvent);
			// only in paused state
			ballInputManager->getInput(sdlEvent);

		}

		// Get the delta time in milliseconds
		Uint32 deltaTime = stepTimer.getTicks();
		// Calculate the delta time in seconds
		double deltaTimeF = deltaTime * 0.001;

		// Move for time step
		paddle->move(deltaTimeF);

		// Move ball

		// TEST COLLISIONE
		if (ball->isCollidingWith(paddle))
		{
			printf("COLLISIONE CON PADDLE!\n");
		}
		ball->move(deltaTimeF);

		for (Block* block : blockCollection)
		{
			if (ball->isCollidingWith(block))
			{
				printf("COLLISION WITH BLOCK\n");
				score += block->getValue();
				block->setCollisionEnabled(false);
				block->setVisible(false);
			}
		}

		// Restart step timer
		stepTimer.start();

		// Clear screen
		SDL_SetRenderDrawColor(globalRenderer, 0xca, 0xcc, 0x90, 0xFF); // a kind of yellow
		SDL_RenderClear(globalRenderer);

        // TEXTURE RENDERING:
       // Rendering the background
        {
            // The rectDest is a rect which defines the position and the size of the texture
            SDL_Rect rectDest = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
            Position2D* defaultPosition = new Position2D(0, 0);
			background->render(0, 0, &rectDest);

        }

        // Rendering the movable paddle:
        {
			paddle->render(paddle->getPosition());
        }

		// Rendering the ball
		{
			ball->render(ball->getPosition());
		}

		// Rendering the blocks
		{
			for (Block* block : blockCollection)
			{
				if (block->isVisible())
				{
					block->render(block->getPosition());
				}
			}
		}

        // Rendering the text at the center of the screen:
		Position2D* centerOfScreen = new Position2D((SCREEN_WIDTH / 2) - (sampleText->getWidth()), 0);
		SDL_Color textColor{ 0x8f, 0x8b, 0x99 };
		sampleText->createText(std::to_string(score), textColor);
        sampleText->render(centerOfScreen);

        // Update screen
        SDL_RenderPresent(globalRenderer);
	}

	// Free resources and close SDL
	//delete blockCollection;
	delete paddle;
	delete background;
	delete sampleText;
	delete paddleSpawnPoint;
	delete ballSpawnPoint;
	delete paddleInputManager;

	return 0;
}