#include "gfx.h"

SDL_Texture *loadImage(char *name)
{
    //load the image 
    SDL_Surface *loadedImage = IMG_Load(name);
    if (loadedImage == NULL)
    {
        printf("Unable to load image %s SDL_image error: %s\n", name, IMG_GetError());
    }

    //Color key the image
    SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format, 0, 0, 0));

    //final texture
    SDL_Texture *newTexture = NULL;

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedImage);
    if (newTexture == NULL)
    {
        printf("Couldn't create texture %s\n", SDL_GetError());
    }

    fim.iTexture = newTexture;
    fim.iWidth = loadedImage->w;
    fim.iHeight = loadedImage->h;

    //Remove old loaded surface
    SDL_FreeSurface(loadedImage);

    return newTexture;
}

void render(int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = fim.iWidth;
    dest.h = fim.iHeight;

    SDL_RenderCopy(gRenderer, fim.iTexture, NULL, &dest);
}
