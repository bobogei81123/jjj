#include "delay.h"

#define CLOCKHZPMS 21000
void sleep(int ms)
{
    while (ms--) {
        volatile unsigned int c = CLOCKHZPMS;
        while(c--) {
        }
    }
}
