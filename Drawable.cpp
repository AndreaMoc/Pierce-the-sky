#include <SDL_image.h>
#include "Drawable.h"
#include "Globals.h"

Drawable::Drawable() : Actor()
{
    // Initialization
    _texture = NULL;

    _surfacePixels = NULL;
    _rawPixels = NULL;
    _rawPitch = 0;

    _visible = true;
}

Drawable::Drawable(std::string filePath) : Actor()
{
    // Initialization
    _texture = NULL;

    _surfacePixels = NULL;
    _rawPixels = NULL;
    _rawPitch = 0;

    _visible = true;

    loadFromFile(filePath);
}

Drawable::~Drawable() {
    free();
}

bool Drawable::createText(std::string textureText, SDL_Color textColor) {
    // Get rid of preexisting texture
    free();

    // Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(globalFont, textureText.c_str(), textColor);
    if (textSurface != NULL) {
        // Create texture from surface pixels
        _texture = SDL_CreateTextureFromSurface(globalRenderer, textSurface);
        if (_texture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else {
            // Get image dimensions
            _width = textSurface->w;
            _height = textSurface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
    else {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }

    // Return success
    return _texture != NULL;
}

bool Drawable::createBlank(int width, int height, SDL_TextureAccess access) {
    // Get rid of preexisting texture
    free();

    // Create uninitialized texture
    _texture = SDL_CreateTexture(globalRenderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);
    if (_texture == NULL) {
        printf("Unable to create streamable blank texture! SDL Error: %s\n", SDL_GetError());
    }
    else {
        // Get image dimensions
        _width = width;
        _height = height;
    }

    // Return success
    return _texture != NULL;
}

void Drawable::free() {
    // Free texture if it exists
    if (_texture != NULL) {
        SDL_DestroyTexture(_texture);
        _texture = NULL;
    }

    // Free surface if it exists
    if (_surfacePixels != NULL) {
        SDL_FreeSurface(_surfacePixels);
        _surfacePixels = NULL;
    }
}

void Drawable::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(_texture, red, green, blue);
}

void Drawable::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(_texture, blending);
}

void Drawable::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(_texture, alpha);
}

void Drawable::render(int x, int y, SDL_Rect* section, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    // Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, (int)_width, (int)_height };

    // Set clip rendering dimensions
    if (section != NULL) {
        renderQuad.w = section->w;
        renderQuad.h = section->h;
    }

    // Render to screen
    SDL_RenderCopyEx(globalRenderer, _texture, section, &renderQuad, angle, center, flip);
}

void Drawable::render(Position2D* position, SDL_Rect* section, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    // Set rendering space and render to screen
    SDL_Rect renderQuad = { position->getX(), position->getY(), (int)_width, (int)_height};

    // Set clip rendering dimensions
    if (section != NULL) {
        renderQuad.w = section->w;
        renderQuad.h = section->h;
    }

    // Render to screen
    SDL_RenderCopyEx(globalRenderer, _texture, section, &renderQuad, angle, center, flip);
}

void Drawable::setAsRenderTarget() {
    SDL_SetRenderTarget(globalRenderer, _texture);
}

void Drawable::setVisible(bool visible)
{
    _visible = visible;
}

bool Drawable::isVisible()
{
    return _visible;
}

Uint32* Drawable::getPixels32() {
    Uint32* pixels = NULL;

    if (_surfacePixels != NULL) {
        pixels = static_cast<Uint32*>(_surfacePixels->pixels);
    }

    return pixels;
}

Uint32 Drawable::getPixel32(Uint32 x, Uint32 y) {
    // Convert the pixels to 32 bit
    Uint32* pixels = static_cast<Uint32*>(_surfacePixels->pixels);

    // Get the pixel requested
    return pixels[(y * getPitch32()) + x];
}

Uint32 Drawable::getPitch32() {
    Uint32 pitch = 0;

    if (_surfacePixels != NULL) {
        pitch = _surfacePixels->pitch / 4;
    }

    return pitch;
}

bool Drawable::lockTexture() {
    bool success = true;

    // Texture is already locked
    if (_rawPixels != NULL) {
        printf("Texture is already locked!\n");
        success = false;
    }
    // Lock texture
    else {
        if (SDL_LockTexture(_texture, NULL, &_rawPixels, &_rawPitch) != 0) {
            printf("Unable to lock texture! %s\n", SDL_GetError());
            success = false;
        }
    }

    return success;
}

bool Drawable::unlockTexture() {
    bool success = true;

    // Texture is not locked
    if (_rawPixels == NULL) {
        printf("Texture is not locked!\n");
        success = false;
    }
    // Unlock texture
    else {
        SDL_UnlockTexture(_texture);
        _rawPixels = NULL;
        _rawPitch = 0;
    }

    return success;
}

void Drawable::copyRawPixels32(void* pixels) {
    // Texture is locked
    if (_rawPixels != NULL) {
        // Copy to locked pixels
        memcpy(_rawPixels, pixels, _rawPitch * _height);
    }
}


/* PROTECTED METHODS */

bool Drawable::loadFromFile(std::string path) {
    // Load pixels
    if (!loadPixelsFromFile(path)) {
        printf("Failed to load pixels for %s!\n", path.c_str());
    }
    else {
        // Load texture from pixels
        if (!loadFromPixels()) {
            printf("Failed to texture from pixels from %s!\n", path.c_str());
        }
    }

    // Return success
    return _texture != NULL;
}

bool Drawable::loadPixelsFromFile(std::string path) {
    // Free preexisting assets
    free();

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else {
        // Convert surface to display format
        _surfacePixels = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
        if (_surfacePixels == NULL) {
            printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
        }
        else {
            // Get image dimensions
            _width = _surfacePixels->w;
            _height = _surfacePixels->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return _surfacePixels != NULL;
}

bool Drawable::loadFromPixels() {
    // Only load if pixels exist
    if (_surfacePixels == NULL) {
        printf("No pixels loaded!");
    }
    else {
        // Color key image
        SDL_SetColorKey(_surfacePixels, SDL_TRUE, SDL_MapRGB(_surfacePixels->format, 0, 0xFF, 0xFF));

        // Create texture from surface pixels
        _texture = SDL_CreateTextureFromSurface(globalRenderer, _surfacePixels);
        if (_texture == NULL) {
            printf("Unable to create texture from loaded pixels! SDL Error: %s\n", SDL_GetError());
        }
        else {
            // Get image dimensions
            _width = _surfacePixels->w;
            _height = _surfacePixels->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(_surfacePixels);
        _surfacePixels = NULL;
    }

    // Return success
    return _texture != NULL;
}