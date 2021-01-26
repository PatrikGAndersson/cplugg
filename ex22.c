#include <stdio.h>
#include "ex22.h"
#include "debug.h"


int THE_SIZE = 1000;

//static indicates that it is only accesible in this file
static int THE_AGE = 37;


//These functions makes it so that we can access THE_AGE from another file
int get_age()
{
    return THE_AGE;
}

void set_age(int age)
{
    THE_AGE = age;
}

double update_ratio(double new_ratio)
{
    //Ratio is only accessible from inside this function
    static double ratio = 1.0;

    double old_ratio = ratio;
    ratio = new_ratio;

    return old_ratio;
}

void print_size()
{
    log_info("I think the size is: %d", THE_SIZE);
}