
//Just says that of object_h is nor defined then define it
#ifndef _object_h
#define _object_h

//simple enum 
typedef enum {
    NORTH,SOUTH,EAST,WEST
} Direction;

//and scaffold for struct
typedef struct {
    char* description;
    int(*init)(void* self);
    void(*describe)(void* self);
    void(*destroy)(void* self);
    void*(*move)(void* self, Direction direction);
    int (*attack)(void* self, int damage);
} Object;

//And define functions
int Object_init(void* self);
void Object_destroy(void* self);
void Object_describe(void* self);
void* Object_move(void* self, Direction direction);
int Object_attack(void* self,int damage);
void* Object_new(size_t size, Object proto,char* description);

//a macro NEW that takes T and N
//and puts them into code on the right
//T##Proto makes a prot of the specific type T that
//is provided
#define NEW(T,N) Object_new(sizeof(T), T##Proto, N)
//_(N) makes it so we can access field of an object with
//obj->_(field) instead of obj->proto.field
//Thus N is the field and we say that
//_(field) is the same as proto.field
#define _(N) proto.N

#endif