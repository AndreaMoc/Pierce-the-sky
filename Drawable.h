#pragma once

#include "Actor.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Drawable : public Actor
{
public:
	Drawable();

	// Constructor with file path: initializes variables, tries to load drawable from given file path
	Drawable(std::string filePath);

	~Drawable();

	/*	Creates drawable from given string
	*	@param - string text: text to be displayed as drawable
	*	@param - SDL_Color textColor: color of text
	*/
	bool createText(std::string text, SDL_Color textColor);

	/*	Creates blank drawable
	*	@param - int width, height: width and height of created drawable
	*	@param - SDL_TextureAccess access: the access pattern allowed for a texture
	*/
	bool createBlank(int width, int height, SDL_TextureAccess access);

	// Deallocates drawable, existing assets
	void free();

	/* DRAWABLE IMAGE MODULATION */

	/*	Sets color modulation
	*	@param Uint8 red, green, blue: color quantity for each primary color
	*/
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set blending
	void setBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void setAlpha(Uint8 alpha);

	/**********************/

	/*	Renders texture at given point; only a section (clip) of the texture can be rendered if specified
	*	@param - int x,y: screen coordinates of where the image is going to be rendered (up-left corner). DEFAULT is (0,0)
	*	@param - SDL_Rect* section: section (clip, portion) of texture to be rendered instead of full image. DEFAULT is NULL
	*	@param - double angle: an angle in degrees that indicates the rotation that will be applied to dstrect, rotating it in a clockwise direction. DEFAULT is 0.0
	*	@param - SDL_Point* center: a pointer to a point indicating the point around which dstrect will be rotated (if NULL, rotation will be done around dstrect.w / 2, dstrect.h / 2). DEFAULT is NULL
	*	@param - SDL_RendererFlip flip: a SDL_RendererFlip value stating which flipping actions should be performed on the texture. DEFAULT is SDL_FLIP_NONE
	*/
	virtual void render(int x = 0, int y = 0, SDL_Rect* section = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	/*	Renders texture at given point; only a section (clip) of the texture can be rendered if specified
	*	@param - Position2D* position: screen coordinates of where the image is going to be rendered (up-left corner). DEFAULT is (0,0)
	*	@param - SDL_Rect* section: section (clip, portion) of texture to be rendered instead of full image. DEFAULT is NULL
	*	@param - double angle: an angle in degrees that indicates the rotation that will be applied to dstrect, rotating it in a clockwise direction. DEFAULT is 0.0
	*	@param - SDL_Point* center: a pointer to a point indicating the point around which dstrect will be rotated (if NULL, rotation will be done around dstrect.w / 2, dstrect.h / 2). DEFAULT is NULL
	*	@param - SDL_RendererFlip flip: a SDL_RendererFlip value stating which flipping actions should be performed on the texture. DEFAULT is SDL_FLIP_NONE
	*/
	virtual void render(Position2D* position, SDL_Rect* section = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Set self as render target
	void setAsRenderTarget();

	// Set visible flag true or false
	void setVisible(bool visible);

	// Returns if object is visible or not
	bool isVisible();

	// Pixel accessors methods
	Uint32* getPixels32();
	Uint32 getPixel32(Uint32 x, Uint32 y);
	Uint32 getPitch32();
	bool lockTexture();
	bool unlockTexture();
	void copyRawPixels32(void* pixels);

protected:
	// !constructor has to be used to create texture from given path.
	// Tries to load image from given path
	bool loadFromFile(std::string path);

	// !constructor has to be used to create texture from given path.
	// Tries to load image into pixel buffer
	bool loadPixelsFromFile(std::string path);

	// !constructor has to be used to create texture from given path.
	// Creates image from preloaded pixels
	bool loadFromPixels();

	// The actual hardware texture
	SDL_Texture* _texture;

	// Surface pixels
	SDL_Surface* _surfacePixels;

	// Raw pixels
	void* _rawPixels;
	int _rawPitch;

	// Visible flag
	bool _visible;

};

