#include "logger/inline.h"
#include "logger/macro.h"

int main(void)
{
    log_debug("Hello Debug World!");
    log_info("Hello World!");
    log_error("Error: What's happen?");

    int num = 1234;
    LOG_INT(num);

    char message[] = "Notify something ....";
    LOG_STR(message);
}
