#ifndef MAP_IS_DEF
#define MAP_IS_DEF

enum {
MAP_OBJECT_SOLID,
MAP_OBJECT_SEMI_SOLID,
MAP_OBJECT_AIR,
MAP_OBJECT_NUM
};

typedef struct {
   int type;
   const char* path;
   int nb_sprites;
} map_object_t;

extern int **map;

void map_new(unsigned width, unsigned height);
void map_allocate(int width, int height);
void map_set(int map_object, int x, int y);
int map_get(int x, int y);
void map_object_add(const char* path, int nb_sprites, int type);


#endif