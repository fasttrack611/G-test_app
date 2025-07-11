// hello.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/utils.h"

int main() {
    measure_execution_time(do_work, "do_work");
    return 0;
}

