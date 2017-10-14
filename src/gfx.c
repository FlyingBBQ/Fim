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

void draw(void)
{
    // set the tile parameters
    genLevel();

    // set some custom tiles
    toTales[16].type = TEX_water;
    toTales[67].type = TEX_grass;

    // loop through all tiles and draw them
    for (int i = 0; i < TILES; i++)
    {
        switch (toTales[i].type)
        {
            case TEX_sprite:
                render(toTales[i].xT, toTales[i].yT, &gClips[TEX_sprite]); 
                break;
            case TEX_bg:
                render(toTales[i].xT, toTales[i].yT, &gClips[TEX_bg]); 
                break;
            case TEX_grass:
                render(toTales[i].xT, toTales[i].yT, &gClips[TEX_grass]); 
                break;
            case TEX_water:
                render(toTales[i].xT, toTales[i].yT, &gClips[TEX_water]); 
                break;
        }
    }
}
