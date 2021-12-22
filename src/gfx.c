#include "gfx.h"

static SDL_Texture * spritemap;
static SDL_Window * window;
static SDL_Renderer * renderer;
static char * image_name = "gfx/sprite.png";

static void
gfx_load_image(void)
{
        // Load the image.
        SDL_Surface * loaded_image = IMG_Load(image_name);
        if (loaded_image == NULL) {
                printf("Unable to load image %s SDL_image error: %s\n", image_name,
                       IMG_GetError());
        }

        // Color key the image.
        SDL_SetColorKey(loaded_image, SDL_TRUE, SDL_MapRGB(loaded_image->format, 0, 0,
                        0));

        // Create texture from surface pixels.
        spritemap = SDL_CreateTextureFromSurface(renderer, loaded_image);
        if (spritemap == NULL) {
                printf("Couldn't create texture %s\n", SDL_GetError());
        }

        // Set the clips for every texture.
        sprites_set_clip();

        // Remove old loaded surface.
        SDL_FreeSurface(loaded_image);
}

void
gfx_init(char * title)
{
        // Initialise SDL Video.
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                printf("Could not initialize SDL: %s\n", SDL_GetError());
                exit(1);
        }

        // Open a 640 x 480 screen.
        window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (window == NULL) {
                printf("Couldn't create window: %s\n", SDL_GetError());
                exit(1);
        }

        // Initialize PNG loading.
        int imgFlag = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlag) & imgFlag)) {
                printf("Couldn't initialize IMG_INIT_PNG: %s\n", IMG_GetError());
                exit(1);
        }

        // Initialze renderer.
        unsigned int rndrFlag = SDL_RENDERER_ACCELERATED;
        renderer = SDL_CreateRenderer(window, -1, rndrFlag);
        if (renderer == NULL) {
                printf("Window could not be rendered %s\n", SDL_GetError());
                exit(1);
        }
        SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);

        // Load the image containing all the sprites.
        gfx_load_image();
}

void
gfx_cleanup(void)
{
        // Shut down SDL.
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_DestroyTexture(spritemap);

        renderer = NULL;
        window = NULL;
        spritemap = NULL;

        IMG_Quit();
        SDL_Quit();
}

void
gfx_render(int x, int y, SDL_Rect * clip)
{
        SDL_Rect dest;

        if (clip == NULL) {
                printf("Couldn't create clip %s\n", SDL_GetError());
        }
        dest.x = x;
        dest.y = y;
        dest.w = clip->w;
        dest.h = clip->h;
        // Render function to put texture (clip) from the spritemap at
        // position (dest) on the screen (renderer).
        SDL_RenderCopy(renderer, spritemap, clip, &dest);
}

void
gfx_render_player(Map * map)
{
        // Multiply with tilesize to move a tile instead of pixel.
        gfx_render((map->player.x * TILE_SIZE) + map->offset.x,
                   (map->player.y * TILE_SIZE) + map->offset.y,
                   &sprite_clips[TEX_sprite]);
}

SDL_Renderer *
gfx_get_renderer(void)
{
        return renderer;
}

void
gfx_draw(Map * map)
{
        // Loop through all tiles and draw them.
        for (size_t x = 0; x < map->map_size; x++) {
                for (size_t y = 0; y < map->map_size; y++) {
                        map_set_tile_type(&map->tiles[x][y]);
                        gfx_render(map->tiles[x][y].x + map->offset.x,
                                   map->tiles[x][y].y + map->offset.y,
                                   &sprite_clips[map->tiles[x][y].type]);
                }
        }
}
