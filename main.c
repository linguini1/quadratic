#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/** Program version. */
#define VERSION "0.0.0"

/** Struct to represent a quadratic polynomial of format ax^2 + bx + c. */
struct quadratic_t {
    double a; /**< The a coefficient. */
    double b; /**< The b coefficient. */
    double c; /**< The c coefficient. */
};

/** Struct to represent a complex number. */
struct complex_t {
    double re; /**< The real component. */
    double im; /**< The imaginary component. */
};

/** By default show the equation using the variable x. */
static char variable = 'x';

/** Check that the coefficient exists. */
#define check_coeff(coeff)                                                                                             \
    if (optind >= argc) {                                                                                              \
        fprintf(stderr, "Missing coefficient '" coeff "'\n");                                                          \
        print_usage();                                                                                                 \
        exit(EXIT_FAILURE);                                                                                            \
    }

void print_usage(void);
void print_complex(struct complex_t *c);
void quadratic_formula(struct quadratic_t *poly, struct complex_t *z0, struct complex_t *z1);

int main(int argc, char **argv) {

    /* Parse options. */
    int c;
    while ((c = getopt(argc, argv, ":hv:")) != -1) {
        switch (c) {
        case 'h':
            print_usage();
            exit(EXIT_SUCCESS);
        case 'v':
            variable = optarg[0];
            break;
        case ':':
            fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            print_usage();
            exit(EXIT_FAILURE);
        case '?':
            fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            print_usage();
            exit(EXIT_FAILURE);
        default:
            print_usage();
            exit(EXIT_FAILURE);
        }
    }

    /* Parse all three coefficients. */
    struct quadratic_t polynomial;

    check_coeff("a");
    polynomial.a = strtod(argv[optind], NULL);
    optind++;

    check_coeff("b");
    polynomial.b = strtod(argv[optind], NULL);
    optind++;

    check_coeff("c");
    polynomial.c = strtod(argv[optind], NULL);
    optind++;

    /** Plug coefficients into the quadratic formula and determine the zero. */
    struct complex_t z0;
    struct complex_t z1;
    quadratic_formula(&polynomial, &z0, &z1);

    /** Display results. */
    printf("%lf%c^2 + %lf%c + %lf\n", polynomial.a, variable, polynomial.b, variable, polynomial.c);

    // First zero
    printf("x = ");
    print_complex(&z0);
    putchar('\n');

    // Second zero
    printf("x = ");
    print_complex(&z1);
    putchar('\n');

    return EXIT_SUCCESS;
}

/**
 * Performs the quadratic formula calculation to find two zeros for a polynomial.
 * @param poly The polynomial to use for the calculation.
 * @param z0 Where the first calculated zero of the polynomial will be stored.
 * @param z1 Where the second calculated zero of the polynomial will be stored.
 */
void quadratic_formula(struct quadratic_t *poly, struct complex_t *z0, struct complex_t *z1) {

    double discriminant = (poly->b * poly->b) - 4.0 * poly->a * poly->c;
    double denominator = (2.0 * poly->a); // 2a term in denominator

    // Non complex roots
    if (discriminant >= 0.0) {
        z0->re = (-poly->b + sqrt(discriminant)) / denominator;
        z1->re = (-poly->b - sqrt(discriminant)) / denominator;
        z0->im = 0.0;
        z1->im = 0.0;
        return;
    }

    // Both zeroes will have the same real component
    z0->re = -poly->b / denominator;
    z1->re = z0->re;

    // Zeroes will have complementary imaginary components
    z0->im = sqrt(-discriminant) / denominator;
    z1->im = -z0->im;
}

/**
 * Prints a complex number to stdout.
 * @param c The complex number to print.
 */
void print_complex(struct complex_t *c) {

    // Don't print the imaginary component if there is none
    if (c->im == 0.0) {
        printf("%lf", c->re);
        return;
    }

    printf("%lf + %lfi", c->re, c->im);
}

/**
 * Prints usage information about the command line program.
 */
void print_usage(void) {
    puts("quadratic v" VERSION);
    puts("MIT License | By Matteo Golin, 2024");
    putchar('\n');
    puts("DESCRIPTION:");
    puts("\tFinds the zeroes of a quadratic polynomial in form ax^2 + bx + c.");
    putchar('\n');
    puts("USAGE:");
    puts("\tquadratic [options] -- a b c");
    puts("\tEnsure you include the '--' before the coefficients so negative numbers are properly parsed.");
    putchar('\n');
    puts("EXAMPLES:");
    puts("\tquadratic -- 1 -10 16");
    puts("\t1.000000x^2 + -10.000000x + 16.000000");
    puts("\tx = 8.000000");
    puts("\tx = 2.000000");
    putchar('\n');
    puts("\tquadratic -v y -- 1 -10 16");
    puts("\t1.000000y^2 + 2.000000y + 3.000000");
    puts("\tx = -1.000000 + 1.414214i");
    puts("\tx = -1.000000 + -1.414214i");
    putchar('\n');
    puts("ARGUMENTS");
    puts("\ta\tThe value of the a coefficient of the polynomial.");
    puts("\tb\tThe value of the b coefficient of the polynomial.");
    puts("\tc\tThe value of the c coefficient of the polynomial.");
    putchar('\n');
    puts("OPTIONS:");
    puts("\tv\tThe variable to show as being solved for in the quadratic equation. Defaults to x.");
    puts("\th\tPrints this help screen and exits.");
}
