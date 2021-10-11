#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {
    int opt = 0;
    /* booleans to allow the command prompt to choose what functions to run */
    bool euler_number = false;
    bool euler_pi = false;
    bool bbp = false;
    bool viete = false;
    bool newton = false;
    bool madhava = false;
    bool e_p_stat = false;
    bool e_n_stat = false;
    bool bbp_stat = false;
    bool viete_stat = false;
    bool newton_stat = false;
    bool madhava_stat = false;
    bool help = false;
    bool std = true;
    /* loop to parse through the input */
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        /* switch to enable required booleans for functions to run */
        switch (opt) {
        case 'a': {
            euler_number = true;
            euler_pi = true;
            bbp = true;
            madhava = true;
            viete = true;
            newton = true;
            break;
        }

        case 'e': {
            euler_number = true;
            break;
        }
        case 'b': {
            bbp = true;
            break;
        }
        case 'm': {
            madhava = true;
            break;
        }
        case 'r': {
            euler_pi = true;
            break;
        }
        case 'v': {
            viete = true;
            break;
        }
        case 'n': {
            newton = true;
            break;
        }
        case 's': {
            e_p_stat = true;
            e_n_stat = true;
            bbp_stat = true;
            viete_stat = true;
            newton_stat = true;
            madhava_stat = true;
            break;
        }
        case 'h': {
            help = true;
            break;
        }
        }
        /* if loop is entered (input detected), disable standard help message */
        std = false;
    }
    /* if -h is inputted */
    if (help) {
        fprintf(stdout, "SYNOPSIS\n");
        fprintf(stdout, "   A test harness for the small numerical library.\n");
        fprintf(stdout, "USAGE\n");
        fprintf(stdout, "   ./mathlib-test [-aebmrvnsh]\n\n");
        fprintf(stdout, "OPTIONS\n");
        fprintf(stdout, "  -a   Runs all tests.\n");
        fprintf(stdout, "  -e   Runs e test.\n");
        fprintf(stdout, "  -b   Runs BBP pi test.\n");
        fprintf(stdout, "  -m   Runs Madhava pi test.\n");
        fprintf(stdout, "  -r   Runs Euler pi test.\n");
        fprintf(stdout, "  -v   Runs Viete pi test.\n");
        fprintf(stdout, "  -n   Runs Newton square root tests.\n");
        fprintf(stdout, "  -s   Print verbose statistics.\n");
        fprintf(stdout, "  -h   Display program synopsis and usage.\n");
        exit(0);
    }
    /* if no command is detected */
    if (std) {
        fprintf(stdout, "SYNOPSIS\n");
        fprintf(stdout, "   A test harness for the small numerical library.\n");
        fprintf(stdout, "USAGE\n");
        fprintf(stdout, "   ./mathlib-test [-aebmrvnsh]\n\n");
        fprintf(stdout, "OPTIONS\n");
        fprintf(stdout, "  -a   Runs all tests.\n");
        fprintf(stdout, "  -e   Runs e test.\n");
        fprintf(stdout, "  -b   Runs BBP pi test.\n");
        fprintf(stdout, "  -m   Runs Madhava pi test.\n");
        fprintf(stdout, "  -r   Runs Euler pi test.\n");
        fprintf(stdout, "  -v   Runs Viete pi test.\n");
        fprintf(stdout, "  -n   Runs Newton square root tests.\n");
        fprintf(stdout, "  -s   Print verbose statistics.\n");
        fprintf(stdout, "  -h   Display program synopsis and usage.\n");
        exit(0);
    }
    /* stat boolean variables are if -s is inputted */
    /* if -e or -a is inputted */
    if (euler_number) {
        fprintf(
            stdout, "e() = %1.15f, M_E = %1.15f, diff = %1.15f\n", e(), M_E, absolute(e() - M_E));
        if (e_n_stat) {
            fprintf(stdout, "e() terms = %d\n", e_terms());
        }
    }
    /* if -r or -a is inputted */
    if (euler_pi) {
        fprintf(stdout, "pi_euler() = %1.15f, M_PI = %1.15f, diff = %1.15f\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        if (e_p_stat) {
            fprintf(stdout, "pi_euler() terms = %d\n", pi_euler_terms());
        }
    }
    /* if -b or -a is inputted */
    if (bbp) {
        fprintf(stdout, "pi_bbp() = %1.15f, M_PI = %1.15f, diff = %1.15f\n", pi_bbp(), M_PI,
            absolute(pi_bbp() - M_PI));
        if (bbp_stat) {
            fprintf(stdout, "pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }
    /* if -m or -a is inputted */
    if (madhava) {
        fprintf(stdout, "pi_madhava() = %1.15f, M_PI = %1.15f, diff = %1.15f\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        if (madhava_stat) {
            fprintf(stdout, "pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }
    /* if -v or -a is inputted */
    if (viete) {
        fprintf(stdout, "pi_viete() = %1.15f, M_PI = %1.15f, diff = %1.15f\n", pi_viete(), M_PI,
            absolute(pi_viete() - M_PI));
        if (viete_stat) {
            fprintf(stdout, "pi_viete() terms = %d\n", pi_viete_factors());
        }
    }
    /* if -n or -a is inputted */
    if (newton) {
        double newton_print;
        for (newton_print = 0.0; newton_print <= 10.0; newton_print += 0.1) {
            fprintf(stdout, "sqrt_newton(%f) = %1.15f, sqrt(%f) = %1.15f, diff = %1.15f\n",
                newton_print, sqrt_newton(newton_print), newton_print, sqrt(newton_print),
                absolute(sqrt_newton(newton_print)));
            if (newton_stat) {
                fprintf(stdout, "sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }
    return 0;
}
