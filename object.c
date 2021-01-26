#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

//Frees up memory and destroys object
void Object_destroy(
    /*Takes an object as argument */void* self)
{   
    //Sets obj to the object provided
    Object* obj = self;


    //if the is an object
    if(obj) {
        //Free description
        if (obj->description) free(obj->description);
        //and free string
        free(obj);
    }
}

//Access the description method of an arbitraty object
void Object_describe(
    /*Takes an object as argument*/ void* self)
{
    //see Object_destroy
    Object* obj = self;
    
    //Print the description field of the object
    printf("%s. \n", obj-> description);
}

int Object_init(void* self)
{
    return 1;
}

void *Object_move(void* self, Direction direction)
{
    printf("You can't goin that direction.\n ");
    return NULL;
}

int Object_attack(void* self, int damage)
{
    printf("You can't attack that.\n ");
    return 0;
}



void* Object_new(size_t size, Object proto, char* description)
{   
    assert(description != NULL);
    if(!proto.init) proto.init = Object_init;
    if(!proto.describe) proto.describe = Object_describe;
    if(!proto.destroy) proto.destroy = Object_destroy;
    if(!proto.attack) proto.attack = Object_attack;
    if(!proto.move) proto.move = Object_move;

    //Allocate memory for struct
    //callocs takes the number of items to be allocated and the size
    Object* el = calloc(1,size);
    //and store proto there
    *el = proto;

    el->description = strdup(description);

    if(!el->init(el)) {
        el->destroy(el);
        return NULL;
    } else {
        return el;
    }
} 