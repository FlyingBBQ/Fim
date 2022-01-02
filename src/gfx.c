#include "gfx.h"

#include "log.h"
#include <assert.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>

// Can hold an entire ASCII table of font glyphs.
#define NUM_GLYPHS 128
#define FONT_SIZE 10
#define FONT_TEXTURE_SIZE (NUM_GLYPHS * (FONT_SIZE / 2))

static SDL_Texture * g_sprite_map;
static SDL_Texture * g_font_map;
static SDL_Window * g_window;
static SDL_Renderer * g_renderer;
static SDL_Rect g_font_glyphs[NUM_GLYPHS];
static TTF_Font * g_font;
static char * g_image_name = "assets/gfx/sprite.png";
static char * g_font_name = "assets/fonts/DS-DIGI.TTF";

static void
gfx_load_image(void)
{
        // Load the image.
        SDL_Surface * loaded_image = IMG_Load(g_image_name);
        if (loaded_image == NULL) {
                LOG_ERROR("Unable to load image %s SDL_image error: %s", g_image_name,
                          IMG_GetError());
        }

        // Color key the image.
        SDL_SetColorKey(loaded_image, SDL_TRUE, SDL_MapRGB(loaded_image->format, 0, 0,
                        0));

        // Create texture from surface pixels.
        g_sprite_map = SDL_CreateTextureFromSurface(g_renderer, loaded_image);
        if (g_sprite_map == NULL) {
                LOG_ERROR("Couldn't create texture %s", SDL_GetError());
        }

        // Set the clips for every texture.
        sprites_set_clip();

        // Remove old loaded surface.
        SDL_FreeSurface(loaded_image);
}

static void
gfx_load_font(void)
{
        SDL_Color white = {.r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff};
        memset(g_font_glyphs, 0, sizeof(SDL_Rect) * NUM_GLYPHS);

        g_font = TTF_OpenFont(g_font_name, FONT_SIZE);
        if (g_font == NULL) {
                LOG_ERROR("Unable to open font %s", g_font_name);
        }

        // Create the surface to draw the glyphs on.
        SDL_Surface * rgb_surface = SDL_CreateRGBSurface(0, FONT_TEXTURE_SIZE,
                                    FONT_SIZE, 32, 0, 0, 0, 0xff);
        uint32_t rgb_map = SDL_MapRGBA(rgb_surface->format, 0, 0, 0, 0);
        SDL_SetColorKey(rgb_surface, SDL_TRUE, rgb_map);

        SDL_Rect dest;
        dest.x = dest.y = 0;
        for (char i = ' ' ; i <= 'z' ; i++) {
                char c[2];
                c[0] = i; // ASCII character.
                c[1] = 0; // Zero terminator.

                // Render the font to a surface and get the size.
                SDL_Surface * text = TTF_RenderUTF8_Blended(g_font, c, white);
                TTF_SizeText(g_font, c, &dest.w, &dest.h);

                // Check if the next character fits in the font texture.
                if (dest.x + dest.w >= FONT_TEXTURE_SIZE) {
                        LOG_ERROR("Out of glyph space %i", FONT_TEXTURE_SIZE);
                        exit(1);
                }

                SDL_BlitSurface(text, NULL, rgb_surface, &dest);
                SDL_Rect * glyph = &g_font_glyphs[(int)i];
                glyph->x = dest.x;
                glyph->y = dest.y;
                glyph->w = dest.w;
                glyph->h = dest.h;
                SDL_FreeSurface(text);

                // Increment the texture x pos with the character width.
                dest.x += dest.w;
        }
        LOG_DEBUG("Font texture usage %i of %i", dest.x, FONT_TEXTURE_SIZE);

        g_font_map = SDL_CreateTextureFromSurface(g_renderer, rgb_surface);
        if (g_font_map == NULL) {
                LOG_ERROR("Couldn't create texture %s", SDL_GetError());
        }
        SDL_FreeSurface(rgb_surface);
}

void
gfx_init(char * title)
{
        // Initialise SDL Video.
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                LOG_ERROR("Could not initialize SDL: %s", SDL_GetError());
                exit(1);
        }

        // Open a 640 x 480 screen.
        g_window = SDL_CreateWindow(title,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN);
        if (g_window == NULL) {
                LOG_ERROR("Couldn't create window: %s", SDL_GetError());
                exit(1);
        }

        // Initialize PNG loading.
        int imgFlag = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlag) & imgFlag)) {
                LOG_ERROR("Couldn't initialize IMG_INIT_PNG: %s", IMG_GetError());
                exit(1);
        }

        // Initialize font loading.
        if (TTF_Init() < 0) {
                LOG_ERROR("Couldn't initialize SDL TTF: %s", SDL_GetError());
                exit(1);
        }

        // Initialze renderer.
        unsigned int rndrFlag = SDL_RENDERER_ACCELERATED;
        g_renderer = SDL_CreateRenderer(g_window, -1, rndrFlag);
        if (g_renderer == NULL) {
                LOG_ERROR("Window could not be rendered %s", SDL_GetError());
                exit(1);
        }
        SDL_SetRenderDrawColor(g_renderer, 10, 10, 10, 255);

        // Load the image containing all the sprites.
        gfx_load_image();
        // Load the font for text.
        gfx_load_font();
}

void
gfx_cleanup(void)
{
        // Shut down SDL.
        SDL_DestroyRenderer(g_renderer);
        SDL_DestroyWindow(g_window);
        SDL_DestroyTexture(g_sprite_map);

        g_renderer = NULL;
        g_window = NULL;
        g_sprite_map = NULL;

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
}

void
gfx_render(int x, int y, SDL_Rect * clip)
{
        assert(clip != NULL);

        SDL_Rect dest = {
                .x = x,
                .y = y,
                .w = clip->w,
                .h = clip->h,
        };
        // Render function to put texture (clip) from the spritemap at
        // position (dest) on the screen (renderer).
        SDL_RenderCopy(g_renderer, g_sprite_map, clip, &dest);
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
        return g_renderer;
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
