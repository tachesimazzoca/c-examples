#include <stdio.h>
#include <time.h>

#define PRINT_HR() puts("----------------------------");

void print_tm(const struct tm* brokentime);

int main(void)
{
    time_t t;
    struct tm* lt; // buffer
    struct tm ct; // current

    t = time(NULL);
    lt = localtime(&t);
    ct = *lt;

    // Reset to 1st day
    t -= (lt->tm_mday - 1) * 86400;
    lt = localtime(&t);

    // Print table head
    PRINT_HR();
    printf(asctime(&ct));
    PRINT_HR();
    puts("SUN MON TUE WED THU FRI SUN ");

    // Print calendar days
    int i = 0;
    for (i = 0; i < lt->tm_wday; i++) {
        printf("    ");
    }
    int cmon = lt->tm_mon;
    while (lt->tm_mon == cmon) {
        printf(" %02d%c",
            lt->tm_mday,
            (ct.tm_mday == lt->tm_mday) ? '*' : ' ');
        if (lt->tm_wday % 7 == 6) puts("");
        t += 86400;
        lt = localtime(&t);
    }
    if (lt->tm_wday % 7 != 0) puts("");
    PRINT_HR();

    print_tm(&ct);

    return 0;
}

void print_tm(const struct tm* brokentime)
{
    // This is the number of full seconds since the top of the minute (normally
    // in the range 0 through 59, but the actual upper limit is 60, to allow
    // for leap seconds if leap second support is available).
    printf("tm_sec: %d\n", brokentime->tm_sec);

    // This is the number of full minutes since the top of the hour (in the
    // range 0 through 59).
    printf("tm_min: %d\n", brokentime->tm_min);

    // This is the number of full hours past midnight (in the range 0 through
    // 23).
    printf("tm_hour: %d\n", brokentime->tm_hour);

    // This is the ordinal day of the month (in the range 1 through 31). Watch
    // out for this one! As the only ordinal number in the structure, it is
    // inconsistent with the rest of the structure.
    printf("tm_mday: %d\n", brokentime->tm_mday);

    // This is the number of full calendar months since the beginning of the
    // year (in the range 0 through 11). Watch out for this one! People usually
    // use ordinal numbers for month-of-year (where January = 1).
    printf("tm_mon: %d\n", brokentime->tm_mon);

    // This is the number of full calendar years since 1900.
    printf("tm_year: %d\n", brokentime->tm_year);

    // This is the number of full days since Sunday (in the range 0 through 6).
    printf("tm_wday: %d\n", brokentime->tm_wday);

    // This is the number of full days since the beginning of the year (in the
    // range 0 through 365).
    printf("tm_yday: %d\n", brokentime->tm_yday);

    // This is a flag that indicates whether Daylight Saving Time is (or was, or
    // will be) in effect at the time described. The value is positive if
    // Daylight Saving Time is in effect, zero if it is not, and negative if
    // the information is not available.
    printf("tm_isdst: %d\n", brokentime->tm_isdst);

    // This field describes the time zone that was used to compute this
    // broken-down time value, including any adjustment for daylight saving;
    // it is the number of seconds that you must add to UTC to get local time.
    // You can also think of this as the number of seconds east of UTC. For
    // example, for U.S. Eastern Standard Time, the value is -5*60*60. The
    // tm_gmtoff field is derived from BSD and is a GNU library extension; it
    // is not visible in a strict ISO C environment.
    printf("tm_gmtoff: %ld\n", brokentime->tm_gmtoff);

    // This field is the name for the time zone that was used to compute this
    // broken-down time value. Like tm_gmtoff, this field is a BSD and GNU
    // extension, and is not visible in a strict ISO C environment.
    printf("tm_zone: %s\n", brokentime->tm_zone);
}
