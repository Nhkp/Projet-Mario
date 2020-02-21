
#include <SDL_image.h>

#include "graphics.h"
#include "error.h"
#include "debug.h"
#include "constants.h"
#include "sprite.h"
#include "object.h"
#include "animation.h"
#include "mario.h"

extern dynamic_object_t mario;
static SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;
static SDL_Texture *background = NULL;
static SDL_Texture *tree[3] = {NULL, NULL, NULL};
//int mv_background[]= {0,0,0,0,0};
int x_screen = 0;
int y_screen = 0;

void graphics_init(Uint32 render_flags, char *background_skin)
{
  // Initialisation de SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    exit_with_error("SDL_Init");

  atexit(graphics_clean);

  // Create main window
  win = SDL_CreateWindow("Palette Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
  if (win == NULL)
    exit_with_error("SDL_CreateWindow");

  // Initialize graphical accelerated renderer
  ren = SDL_CreateRenderer(win, -1, render_flags);
  if (ren == NULL)
    exit_with_error("SDL_CreateRenderer");

  {
    char name[128];

    // Load background image and create the associated texture
    sprintf(name, "../images/%s-background.png", background_skin);
    background = IMG_LoadTexture(ren, name);
    if (background == NULL)
      exit_with_error("IMG_LoadTexture");

    // Load background trees
    for (int i = 0; i < 3; i++) //Peut poser problème si on veut changer l'arrière plan
    {
      sprintf(name, "../images/%s-%d.png", background_skin, i);
      tree[i] = IMG_LoadTexture(ren, name);
      if (tree[i] == NULL)
        exit_with_error("IMG_LoadTexture");
    }

    sprite_init();
    object_init();
  }
}

static void graphics_render_background(SDL_Texture *tex)
{
  SDL_Rect src, dst;
  int width, height;

  SDL_QueryTexture(tex, NULL, NULL, &width, &height);

  for (int i = 0; i < 3*width + 1; i += width) //Petit bricolage pour l'affichage du fond d'écran
  {
    src.x = 0;
    src.y = 0;
    src.w = width;
    src.h = height;

    dst.x = i;
    dst.y = 0;
    dst.w = width;
    dst.h = height;

    SDL_RenderCopy(ren, tex, &src, &dst);
  }
  // FIXME: Maybe we shall loop until the whole screen is filled?
}

void graphics_render_trees(SDL_Texture *tex)
{
  SDL_Rect src, dst;
  int width, height;

  SDL_QueryTexture(tex, NULL, NULL, &width, &height);

  for (int i = 0; i < 3 * width + 1; i += width)
  {
    src.x = 0;
    src.y = 0;
    src.w = width;
    src.h = height;

    dst.x = i - x_screen;
    dst.y = -y_screen;
    dst.w = width;
    dst.h = height;

    SDL_RenderCopy(ren, tex, &src, &dst);
  }
}

void scrolling_screen(int x, int y){
  x = x - x_screen;
  y = y - y_screen;
  
  if (x-4 <= SECURITY_LEFT)
    x_screen = (x_screen-4 <= 0)? 0 : x_screen-4;
  if (x+TILE+1 >= SECURITY_RIGHT)
    x_screen = (x_screen+4 > (MAP_WIDTH*TILE-WIN_WIDTH))? (MAP_WIDTH*TILE-WIN_WIDTH) : x_screen+4;
  if (y-6 <= SECURITY_TOP)
    y_screen = (y_screen-6 <= 0)? 0 : y_screen-6;
  if (y+2*TILE+1 >= SECURITY_BOTTOM)
    y_screen = (y_screen+6 >= (MAP_HEIGHT*TILE-WIN_HEIGHT))? (MAP_HEIGHT*TILE-WIN_HEIGHT) : y_screen+6;

  //printf("x : %d ;;; y : %d\n", x_screen, y_screen);
}


void graphics_render(void)
{
  static Uint32 prev = 0;
  Uint32 begin, end, interm;

  begin = SDL_GetTicks();

  // We clear the renderer's buffer
  SDL_RenderClear(ren);

  // We display the background clouds
  graphics_render_background(background);

  // We display the background threes
  for(int i = 2; i>=0; i--)
    graphics_render_trees(tree[i]);

  // FIXME: We display the main character
  animation_render_objects();
  
  scrolling_screen(mario.x, mario.y);

  interm = SDL_GetTicks();

  // We update the visible screen. SDL uses a double buffering, so
  // previous modifications are not yet visible
  SDL_RenderPresent(ren);

  end = SDL_GetTicks();

  if (debug_enabled('p'))
  {
    printf("Animation: %2d, Rendering: %2d ms, VSync: %2d, Total: %2d ms)\r",
           begin - prev,
           interm - begin,
           end - interm,
           end - prev);
    fflush(stdout);
  }

  prev = end;
}

void graphics_clean(void)
{
  if (ren != NULL)
    SDL_DestroyRenderer(ren);
  else
    return;

  if (win != NULL)
    SDL_DestroyWindow(win);
  else
    return;

  if (background != NULL)
    SDL_DestroyTexture(background);

  for (int i = 0; i < 3; i++)
    if (tree[i] != NULL)
      SDL_DestroyTexture(tree[i]);

  sprite_clean();
  IMG_Quit();
  SDL_Quit();
}
