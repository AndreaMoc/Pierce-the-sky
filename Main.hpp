

// Custom screen dimension
int SCREEN_WIDTH = 500;
int SCREEN_HEIGHT = 600;

// The window we'll be rendering to
SDL_Window* globalWindow = NULL;

// The window renderer
SDL_Renderer* globalRenderer = NULL;

// Globally used font
TTF_Font* globalFont = NULL;

// The music that will be played
Mix_Music* globalMusic = NULL;

bool initializeSDL() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    Uint32 windowFlags = SDL_WindowFlags::SDL_WINDOW_SHOWN;
    // Other possible useful window flags:
    // windowFlags |= SDL_WindowFlags::SDL_WINDOW_ALLOW_HIGHDPI;
    // windowFlags |= SDL_WindowFlags::SDL_WINDOW_OPENGL;
    // windowFlags |= SDL_WindowFlags::SDL_WINDOW_FULLSCREEN_DESKTOP;
    // windowFlags |= SDL_WindowFlags::SDL_WINDOW_HIDDEN;
    // windowFlags |= SDL_WindowFlags::SDL_WINDOW_BORDERLESS;

    // Create window
    globalWindow = SDL_CreateWindow("Pierce the Sky", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    if (globalWindow == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Create renderer for window
    globalRenderer = SDL_CreateRenderer(globalWindow, -1, SDL_RENDERER_ACCELERATED);
    if (globalRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Open the font
    globalFont = TTF_OpenFont("Fonts/OpenSans-Bold.ttf", 28);
    if (globalFont == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    // Load music
    /*globalMusic = Mix_LoadMUS("Assets/Kmedley.mp3");
    if (globalMusic == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    if (Mix_PlayMusic(globalMusic, -1) == -1) {
        printf("Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }*/

    // Initialize the renderer blend mode
    SDL_SetRenderDrawBlendMode(globalRenderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);

    // Initialize renderer color
    SDL_SetRenderDrawColor(globalRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

void closeSDL() {
    // Free global font
    TTF_CloseFont(globalFont);
    globalFont = NULL;

    // Free the music
    Mix_FreeMusic(globalMusic);
    Mix_CloseAudio();
    globalMusic = NULL;

    // Destroy window
    SDL_DestroyRenderer(globalRenderer);
    SDL_DestroyWindow(globalWindow);
    globalWindow = NULL;
    globalRenderer = NULL;

    // Quit SDL subsystems
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main();

// The REAL main:
int main(int argc, char* args[]) {
    // Start up SDL and create window
    if (!initializeSDL()) {
        printf("Failed to initialize!\n");
        // Free resources and close SDL
        closeSDL();
        return 0;
    }

    // Run the core of the program
    main();

    // Free resources and close SDL
    closeSDL();

    return 0;
}
