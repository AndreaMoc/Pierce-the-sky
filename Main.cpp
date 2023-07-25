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

/* COSE CHE MANCANO + QUESTIONI APERTE
	- FSM: stato di gioco (gameplay vero e proprio), stato di pausa (pallina ferma al centro, paddle immobile, premi barra spaziatrice per iniziare il gioco) e stato di game over
		Avrei fatto un piccolo enum con i due stati, e in base a eventi di gioco (dopo li menziono) il gioco passa da uno stato all'altro.
		Gestori come InputManager avrebbero cambiato la gestione dell'input; per esempio l'input manager che ascolta l'input per la paddle avrebbe smesso di ascoltare finché
		si è nello stato di pausa, mentre quello della pallina avrebbe funzionato solo nello stato di pausa (per evitare il problema, attualmente presente, che se premo spazio
		mentre gioco la pallina ritorna alla velocità iniziale)
		Il game flow sarebbe stato: pausa (premi barra spaziatrice per iniziare -> gameplay -> (pallina finisce in fondo) -> controlla se ci sono ancora vite; se ci sono ancora, allora ritorna allo stato di pausa,
		se le vite sono finite vai allo stato di game over
	- parlando con i compagni è emerso come Drawable e Collideable fossero più pratici come interfacce e metodi acquisibili da un Actor, più che una struttura così intricata di ereditarietà
	- la collisione con la Paddle è al momento rotta, ho perso veramente tanto tempo a far funzionare quel che avevo ma non ci sono riuscito. Probabilmente è da rivedere proprio il sistema, nel caso mi dici
		se pensi che ci sia qualcosa di salvabile
	- Position2D si è rivelato abbastanza inutile e probabilmente lo toglierei
	- oltre a chiamare le delete alla fine del main, non ho avuto modo di verificare se ci sono memory leak; vorrei usare il metodo per vedere i memory leak di cpp tramite visual studio
	- giocando ho notato che la memoria utilizzata continua a salire ma non ho capito perché
	- alla fine di tutto avrei sistemato cose visive: vorrei sistemare meglio il testo dei punti e avere dei reminder text per dire quali sono i pulsanti da premere durante il gioco; poi avrei messo un reminder
		delle vite rimanenti in basso a sinistra
	- alcune soluzioni poco eleganti vorrei provare a farle in maniera più intelligente
*/

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
	Position2D* centerOfScreen = new Position2D((SCREEN_WIDTH / 2) - (sampleText->getWidth()), 0);

	// Lower wall: collision means life loss
	Collideable* lowerWall = new Collideable();
	lowerWall->setPosition(0, SCREEN_HEIGHT);
	lowerWall->setWidth(100);

	// Blocks
	int const NUMBEROFBLOCKS = 36;
	Block* blockCollection[NUMBEROFBLOCKS]{};

	Position2D* firstRowSpawnPoint = new Position2D(75, SCREEN_HEIGHT / 2);
	Position2D* secondRowSpawnPoint = new Position2D(75, SCREEN_HEIGHT / 2 - 50);
	Position2D* thirdRowSpawnPoint = new Position2D(75, SCREEN_HEIGHT / 2 - 100);
	Position2D* fourthRowSpawnPoint = new Position2D(75, SCREEN_HEIGHT / 2 - 150);
	Position2D* fifthRowSpawnPoint = new Position2D(75, SCREEN_HEIGHT / 2 - 200);
	Position2D* sixthRowSpawnPoint = new Position2D(75, SCREEN_HEIGHT / 2 - 250);

	int offset = 10;

	for (int i = 0; i < NUMBEROFBLOCKS; ++i)
	{
		// FIRST ROW
		if (i < NUMBEROFBLOCKS / 6)
		{
			// Block initialization
			Block* block1 = new Block("Assets/MyAssets/block1.png");
			block1->setValue(10);

			// Setting block position

			// Every 6, go up by a column equal to 2 times the block height
			block1->setPosition(firstRowSpawnPoint->getX() / 2 + (i % (NUMBEROFBLOCKS / 6)) * 1.5 * block1->getWidth(), firstRowSpawnPoint->getY());

			blockCollection[i] = block1;
		}
		// SECOND ROW
		if (i >= NUMBEROFBLOCKS / 6 && i < 2 * NUMBEROFBLOCKS / 6)
		{
			// Block initialization
			Block* block1 = new Block("Assets/MyAssets/block1.png");
			block1->setValue(10);

			// Setting block position

			// Every 6, go up by a column equal to 2 times the block height
			block1->setPosition(secondRowSpawnPoint->getX() / 2 + (i % (NUMBEROFBLOCKS / 6)) * 1.5 * block1->getWidth(), secondRowSpawnPoint->getY());

			blockCollection[i] = block1;
		}
		// THIRD ROW
		if (i >= 2 * NUMBEROFBLOCKS / 6 && i < 3 * NUMBEROFBLOCKS / 6)
		{
			// Block initialization
			Block* block2 = new Block("Assets/MyAssets/block2.png");
			block2->setValue(15);

			// Setting block position

			// Every 6, go up by a column equal to 2 times the block height
			block2->setPosition(thirdRowSpawnPoint->getX() / 2 + (i % (NUMBEROFBLOCKS / 6)) * 1.5 * block2->getWidth(), thirdRowSpawnPoint->getY());

			blockCollection[i] = block2;
		}
		// FOURTH ROW
		if (i >= 3 * NUMBEROFBLOCKS / 6 && i < 4 * NUMBEROFBLOCKS / 6)
		{
			// Block initialization
			Block* block2 = new Block("Assets/MyAssets/block2.png");
			block2->setValue(15);

			// Setting block position

			// Every 6, go up by a column equal to 2 times the block height
			block2->setPosition(fourthRowSpawnPoint->getX() / 2 + (i % (NUMBEROFBLOCKS / 6)) * 1.5 * block2->getWidth(), fourthRowSpawnPoint->getY());

			blockCollection[i] = block2;
		}
		// FIFTH ROW
		if (i >= 4 * NUMBEROFBLOCKS / 6 && i < 5 * NUMBEROFBLOCKS / 6)
		{
			// Block initialization
			Block* block3 = new Block("Assets/MyAssets/block3.png");
			block3->setValue(20);

			// Setting block position

			// Every 6, go up by a column equal to 2 times the block height
			block3->setPosition(fifthRowSpawnPoint->getX() / 2 + (i % (NUMBEROFBLOCKS / 6)) * 1.5 * block3->getWidth(), fifthRowSpawnPoint->getY());

			blockCollection[i] = block3;
		}
		if (i >= 5 * NUMBEROFBLOCKS / 6 && i < NUMBEROFBLOCKS)
		{
			// Block initialization
			Block* block3 = new Block("Assets/MyAssets/block3.png");
			block3->setValue(20);

			// Setting block position

			// Every 6, go up by a column equal to 2 times the block height
			block3->setPosition(sixthRowSpawnPoint->getX() / 2 + (i % (NUMBEROFBLOCKS / 6)) * 1.5 * block3->getWidth(), sixthRowSpawnPoint->getY());

			blockCollection[i] = block3;
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
		SDL_Color textColor{ 0x8f, 0x8b, 0x99 };
		sampleText->createText(std::to_string(score), textColor);
        sampleText->render(centerOfScreen);

        // Update screen
        SDL_RenderPresent(globalRenderer);
	}

	// Free resources and close SDL

	delete paddle;
	delete paddleSpawnPoint;
	
	delete ball;
	delete ballSpawnPoint;

	delete background;
	delete sampleText;
	delete centerOfScreen;

	delete lowerWall;

	for (Block* block : blockCollection)
	{
		delete block;
	}
	delete blockCollection;

	delete firstRowSpawnPoint;
	delete secondRowSpawnPoint;
	delete thirdRowSpawnPoint;
	delete fourthRowSpawnPoint;
	delete fifthRowSpawnPoint;
	delete sixthRowSpawnPoint;

	delete paddleInputManager;
	delete ballInputManager;

	return 0;
}