#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>

#include "graphics.h"
#include "error.h"
#include "debug.h"
#include "constants.h"
#include "sprite.h"
#include "object.h"
#include "animation.h"
#include "missile.h"
#include "mario.h"
#include "map.h"
#include "sound.h"
#include "dynamic_objects.h"
#include "cursor.h"

#define DEFAULT_BACKGROUND_SKIN "trees"

static char *progname;
static char *skin = NULL;
static char *map_path = NULL;

void usage(int val){
  fprintf(stderr, "Usage: %s [option]\n", progname);
  fprintf(stderr, "option can be:\n");
  fprintf(stderr, "\t-nvs\t| --no-vsync\t\t: disable vertical screen sync\n");
  fprintf(stderr, "\t-s\t| --skin <name>\t\t: use specific background skin\n");
  fprintf(stderr, "\t-l\t| --load-map <name>\t: use specific map\n");
  fprintf(stderr, "\t-d\t| --debug-flags <flags>\t: enable debug messages\n");
  fprintf(stderr, "\t-h\t| --help\t\t: display help\n");

  exit(val);
}

int main(int argc, char **argv){
  const Uint8 *keystates = SDL_GetKeyboardState(NULL);
  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  char *debug_flags = NULL;

  progname = argv[0];

  // Filter args
  //
  argv++;
  argc--;
  while (argc > 0)
  {
    if (!strcmp(*argv, "--no-vsync") || !strcmp(*argv, "-nvs"))
      render_flags &= ~SDL_RENDERER_PRESENTVSYNC;
    else if (!strcmp(*argv, "--help") || !strcmp(*argv, "-h"))
      usage(0);
    else if (!strcmp(*argv, "--debug-flags") || !strcmp(*argv, "-d")){
      if (argc == 1){
        fprintf(stderr, "Error: flag list missing\n");
        usage(1);
      }
      argc--;
      argv++;
      debug_flags = *argv;
    }
    else if (!strcmp(*argv, "--skin") || !strcmp(*argv, "-s")){
      if (argc == 1){
        fprintf(stderr, "Error: skin name missing\n");
        usage(1);
      }
      argc--;
      argv++;
      skin = *argv;
    }
    else if (!strcmp(*argv, "--load-map") || !strcmp(*argv, "-l")){
      if (argc == 1){
        fprintf(stderr, "Error: map name missing\n");
        usage(1);
      }
      argc--;
      argv++;
      map_path = *argv;
    }
    else
      break;

    argc--;
    argv++;
  }

  if (argc > 0)
    usage(1);

  debug_init(debug_flags);
  graphics_init(render_flags, (skin ? skin : DEFAULT_BACKGROUND_SKIN));
  animation_init(map_path ? map_path : NULL);
  sound_init(1, 0);

  for (int quit = 0; !quit;){
    SDL_Event evt;

    // We look for keyboard/mouse events (in a non-blocking way)
    while (SDL_PollEvent(&evt)){

      switch (evt.type){
      case SDL_QUIT:
        // If user closes the window
        quit = 1;
        break;

      case SDL_KEYDOWN:
        // if user presses a key
        switch (evt.key.keysym.sym){
        case SDLK_ESCAPE:
          // ESC : we quit!
          quit = 1;
          break;
        case SDLK_q:
          edition = 0;
          break;
        case SDLK_TAB:
          if (edition) (cursor.anim_next_step + 1 > 13)? cursor.anim_next_step = 0 : cursor.anim_next_step++;
          break;
        case SDLK_s:
          save_map(map_path ? map_path : NULL);
          break;
        case SDLK_SPACE:
          mario.anim_next_step = 9;
          if (mario.direction)
            animation_laser_add(missile_init(), mario.x - TILE, mario.y+TILE/4, mario.direction);
          else
            animation_laser_add(missile_init(), mario.x + TILE, mario.y+TILE/4, mario.direction);
          break;
        case SDLK_UP:
          cursor_up();
          break;
        case SDLK_DOWN:
          cursor_down();
          break;
        case SDLK_LEFT:
          cursor_left();
          break;
        case SDLK_RIGHT:
          cursor_right();
          break;
        case SDLK_b:
          if(edition) bomb_add(&cursor);
          else bomb_add(&mario);
          break;
        case SDLK_v:
          if(edition) landmine_add(&cursor);
          else landmine_add(&mario);
          break;


        default:;
        }
        break;

      case SDL_USEREVENT:
        animation_timer_expired(evt.user.data1, evt.user.data2);
        break;

      default:;
      }
    }

    int up = keystates[SDL_SCANCODE_UP], down = keystates[SDL_SCANCODE_DOWN], space = keystates[SDL_SCANCODE_SPACE];
    int left = keystates[SDL_SCANCODE_LEFT], right = keystates[SDL_SCANCODE_RIGHT];
    int ok = keystates[SDL_SCANCODE_RETURN], q = keystates[SDL_SCANCODE_A], e = keystates[SDL_SCANCODE_E];
    int x = keystates[SDL_SCANCODE_X], c = keystates[SDL_SCANCODE_C];
    animation_one_step(space, up, down, left, right, ok, q, e, x, c);
    sound_keep_music();

    // Refresh screen
    graphics_render();
    animation_clean();
  }

  return 0;
}
