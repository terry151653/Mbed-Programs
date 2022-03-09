#include "mbed.h"

using namespace std::chrono;

Timer t;

int main()
{
   t.start();
   printf("Hello World!\n");
   t.stop();
   auto s = chrono::duration_cast<chrono::seconds>(t.elapsed_time()).count();
   auto ms = chrono::duration_cast<chrono::milliseconds>(t.elapsed_time()).count();
   auto us = t.elapsed_time().count();
   printf ("Timer time: %llu s\n", s);
   printf ("Timer time: %llu ms\n", ms);
   printf ("Timer time: %llu us\n", us);
}