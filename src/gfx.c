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

    texture_map.iTexture = newTexture;
    texture_map.iWidth = loadedImage->w;
    texture_map.iHeight = loadedImage->h;

    printf("loaded");
    //set the clips for every texture
    setClip();

    //Remove old loaded surface
    SDL_FreeSurface(loadedImage);

    return newTexture;
}

//render function to put texture at position and with size. 
void render(int x, int y, SDL_Rect *clip)
{
    SDL_Rect dest;

    if (clip == NULL)
    {
        printf("Couldn't create clip %s\n", SDL_GetError());
    }

    dest.x = x;
    dest.y = y;
    dest.w = clip->w;
    dest.h = clip->h;

    //renderer, source texture, source SDL_Rect structure (NULL for entire texture), destination SDL_Rect
    SDL_RenderCopy(gRenderer, texture_map.iTexture, clip, &dest);
}

