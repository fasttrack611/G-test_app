#ifndef UTILITY_H
#define UTILITY_H

void measure_execution_time(void (*func)(), const char* label);
void do_work();  // Declare the function you want to time

#endif

