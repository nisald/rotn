/* rotn - A simple rot-n cipher
 * Copyright (C) 2017 Nisal D Bandara
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

char *rotn(const char *plain, int n)
    // rotate each char in plain text by n-positions
{
    int plen = strlen(plain);
    char *rot = malloc((plen+1) * sizeof(*rot));

    if (!rot)
        return NULL;

    char *rotp = rot;
    const char *plainp = plain;

    while (*plainp) {
        char rotc = *plainp;

        if (isalpha(rotc)) {
            int lowerflag = 0;

            if (islower(rotc)) {
                rotc = toupper(rotc);
                lowerflag = 1;
            }

            rotc -= 'A';
            rotc = (rotc + n) % 26;

            if (lowerflag)
                rotc += 'a';
            else
                rotc += 'A';
        }

        *rotp++ = rotc;
        plainp++;
    }

    *rotp = '\0';
    return rot;
}

void usage(void)
{
    fprintf(stderr, "usage: rotn [-n <rotations>] <text>\n");
}

int main(int argc, char **argv)
{

    int nvalue = 13;
    int c;

    if (argc < 2 || argc > 4) {
        usage();
        return 1;
    }

    while ((c = getopt(argc, argv, "n:")) != -1) {
        switch (c) {
        case 'n':
            nvalue = atoi(optarg);
            break;
        case '?':
            if (optopt == 'n')
                fprintf(stderr, "argument 'n' requires a value\n");
            else
                fprintf(stderr, "unknown argument given\n");
            break;
        default:
            return 2;
        }
    }

    if (optind >= argc) {
        usage();
        return 1;
    }

    char *rot = rotn(argv[optind], nvalue);
    printf("%s\n", rot);

    free(rot);

    return 0;
}
