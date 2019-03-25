#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int is_year_leap(int year)
{
    /* @TODO: move to another file for specific data file */
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int get_day_of_year(int mon, int day, int year)
{
    /* @TODO: move to another file for specific data file */
    static const int days[2][13] = {
        {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
        {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}
    };

    int leap = is_year_leap(year);

    return days[leap][mon] + day;
}

char *search(char *date)
{
    char buff[255];
    char dest[255];
    FILE *fp;
    /* @TODO: let the user select other data file */
    fp = fopen("data/greek.dat", "r");
    while (!feof(fp)) {
        fgets(buff, 255, fp);
        /*
           could do the following instead
           strncmp(buff, date, strlen(date)) == 0)
        */
        memcpy(dest, buff, strlen(date));
        if (strcmp(dest, date) == 0) {
            /* @TODO: should return it and not print it */
            printf("%s", buff);
        }
    }
    fclose(fp);
    return "";
}

int main(void)
{
    /* gcc -o almanac -O2 -ansi -pedantic almanac.c */
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int day_of_year;
    char date[255];

    /* create a string of day / month */
    sprintf(date, "%d/%d", tm.tm_mday, tm.tm_mon + 1);

    /* search it on the nameday file */
    search(date);

    /* @TODO: calculate moveable feasts */
    day_of_year = get_day_of_year(tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900);
    /* get day of easter */
    /* calculate movable feasts of file */
    /* compare date to today */

    return 0;
}

