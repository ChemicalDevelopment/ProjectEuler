
#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>
#include <math.h>


int _size_consts = 5, _consts_id = 0, _consts_ov = 0;
mpfr_t *_consts;

mpfr_ptr _next_const(char _set_val[]) {
	_consts_id = _consts_id + 1;
	if (_consts_id >= _size_consts) {
		_consts_ov = 1;
		_consts_id %= _size_consts;
	}
	if (_consts_ov > 0) {
		//mpfr_clear(_consts[_consts_id]);
		mpfr_init(_consts[_consts_id]);
	}
	mpfr_set_str(_consts[_consts_id], _set_val, 10, GMP_RNDN);
	//_consts_id++;
	return (mpfr_ptr) _consts[_consts_id];
}


// default precision (and minimum)
int EZC_PREC = 128;
// macro to get bits instead of digits
#define _bprec (int)(_prec * .301029)

// variables to use in our program that are hidden to others
int _prec, _loop, _argc;
// a pointer so we can read from all methods
char **_argv;
// a lits of commandline arguments that are mpfr s
mpfr_t *args;

// constants (look for initializations in lib_linker)
mpfr_t __start, __stop, __step;


// sets the precision 
void prec_literal(int x) {
	if (x < EZC_PREC) x = EZC_PREC;
	_prec = x;
	mpfr_set_default_prec((int)x);
}
// sets the precision to a cmdline argument
void prec_index(int index) {
	if (index >= _argc) {
		prec_literal(EZC_PREC);
	} else {
		prec_literal(strtoll(_argv[index], NULL, 10));
	}
}
// adds a and b, normal floating point
void add(mpfr_t r, mpfr_t a, mpfr_t b) { mpfr_add(r, a, b, GMP_RNDN); }
// subtracts b from a, normal floating point
void sub(mpfr_t r, mpfr_t a, mpfr_t b) { mpfr_sub(r, a, b, GMP_RNDN); }
// multiplies a and b, normal floating point
void mul(mpfr_t r, mpfr_t a, mpfr_t b) { mpfr_mul(r, a, b, GMP_RNDN); }
// divides a by b, normal floating point
void fdiv(mpfr_t r, mpfr_t a, mpfr_t b) { mpfr_div(r, a, b, GMP_RNDN); }
// takes a to the bth power, normal floating point
void fpow(mpfr_t r, mpfr_t a, mpfr_t b) { mpfr_pow(r, a, b, GMP_RNDN); }

// truncates a to the nearest int
void ftrunc(mpfr_t r, mpfr_t a) { mpfr_trunc(r, a); }
// computes a - floor(a/b)*b (modulo)
void ffmod(mpfr_t r, mpfr_t a, mpfr_t b) {
	mpfr_fmod(r, a, b, GMP_RNDN);
}
// computes the first multiple of b towards a.
// Example, ftrunc_mult(r, 5, 10) = 0 because 0 is the largest multiple of ten less than or equal to 5
// ftrunc_mult(r, 23, 7) = 21, because 21 = 3 * 7
void ftrunc_mult(mpfr_t r, mpfr_t a, mpfr_t b) {
	mpfr_t __ftrunc_mult_tmp; mpfr_init(__ftrunc_mult_tmp);
	ffmod(__ftrunc_mult_tmp, a, b);
	sub(r, a, __ftrunc_mult_tmp);
	mpfr_clear(__ftrunc_mult_tmp);
}

// echos a message
void echo(char msg[]) { printf("%s\n", msg); }
// prints a var
void var(char name[], mpfr_t a) { mpfr_printf("%s : %.*Rf \n", name, _bprec, a); }
// prints a var to file
void file(char name[], mpfr_t a) { 
	FILE *fp = fopen(name, "w+");
	mpfr_fprintf(fp, "%.*Rf \n", _bprec, a); 
}
// initializes and sets a
void initset(mpfr_t a, char val[]) { mpfr_init(a); mpfr_set_str(a, val, 10, GMP_RNDN); }
// sets a to the value of the text in val
void set(mpfr_t a, char val[]) { mpfr_set_str(a, val, 10, GMP_RNDN); }
// copies a variable
void fset(mpfr_t a, mpfr_t b) { mpfr_set(a, b, GMP_RNDN); }

//finds the maximum of a and b
void _fmax(mpfr_t r, mpfr_t a, mpfr_t b) { mpfr_max(r, a, b, GMP_RNDN); }
//finds the minimum of a and b
void _fmin(mpfr_t r, mpfr_t a, mpfr_t b) { mpfr_min(r, a, b, GMP_RNDN); }
// little function to return the sign of r
int _fsgn(mpfr_t r) { return mpfr_sgn(r); }


// square root, i.e. r * r ~ a
void fsqrt(mpfr_t r, mpfr_t a) { mpfr_sqrt(r, a, GMP_RNDN); }
// cube root, i.e. r * r * r ~ a
void fcbrt(mpfr_t r, mpfr_t a) { mpfr_cbrt(r, a, GMP_RNDN); }

// sin of a in radians
void fsin(mpfr_t r, mpfr_t a) { mpfr_sin(r, a, GMP_RNDN); }
// cos of a in radians
void fcos(mpfr_t r, mpfr_t a) { mpfr_cos(r, a, GMP_RNDN); }
// tan of a in radians (sin(a)/cos(a))
void ftan(mpfr_t r, mpfr_t a) { mpfr_tan(r, a, GMP_RNDN); }

// asin of a, returned in radians. asin(sin(a)) ~ a
void fasin(mpfr_t r, mpfr_t a) { mpfr_asin(r, a, GMP_RNDN); }
// acos of a, returned in radians. acos(cos(a)) ~ a
void facos(mpfr_t r, mpfr_t a) { mpfr_acos(r, a, GMP_RNDN); }
// atan of a, returned in radians. atan(tan(a)) ~ a
// note that this can return odd values of poles in tan (i.e. pi/2+pi*n)
void fatan(mpfr_t r, mpfr_t a) { mpfr_atan(r, a, GMP_RNDN); }

// e ^ x, where e is euler's number (roughly 2.718281828)
void fexp(mpfr_t r, mpfr_t a) { mpfr_exp(r, a, GMP_RNDN); }
// ln(a), log base eulers number. where e ^ (ln(a)) ~ a
void flog(mpfr_t r, mpfr_t a) { mpfr_log(r, a, GMP_RNDN); }
// log_(b)(a), log base b of a. where b ^ (log_(b)(a)) ~ a
// identity: log_(b)(a) = ln(a)/ln(b)
void flogb(mpfr_t r, mpfr_t a, mpfr_t b) {
	mpfr_t __flogb_tmp; mpfr_init(__flogb_tmp);
	flog(__flogb_tmp, b);
	flog(r, a);
	fdiv(r, r, __flogb_tmp);
	mpfr_clear(__flogb_tmp);
}

// calculates the gamma function of a, gamma(a)=factorial(a-1)
void fgamma(mpfr_t r, mpfr_t a) { mpfr_gamma(r, a, GMP_RNDN); }
// calculates the factorial of a, or gamma(a+1)
void ffactorial(mpfr_t r, mpfr_t a) { 
	mpfr_t __tmp; mpfr_init(__tmp);
	mpfr_add(__tmp, a, _next_const("1.0"), GMP_RNDN);
	fgamma(r, __tmp);
	mpfr_clear(__tmp);
}


void ___summult(mpfr_t ret, mpfr_t MAX, mpfr_t A) {

	mpfr_t _count; mpfr_init(_count);
	mpfr_t smt; mpfr_init(smt);
	mpfr_t smm; mpfr_init(smm);sub(_count, MAX, _next_const("1"));
	fdiv(_count, _count, A);
	ftrunc(_count, _count);
	add(smm, _count, _next_const("1"));mul(smt, _count, smm);
	mul(smt, smt, A);
	fdiv(smt, smt, _next_const("2"));
	ftrunc(ret, smt);
}
// main method
int main(int argc, char *argv[]) {
	// set global vars so other functions can use them
	_argc = argc; _argv = argv;
	// set the default rounding mode
	mpfr_set_default_rounding_mode(GMP_RNDN);

	// start the commandline args list
	args = (mpfr_t *)malloc(sizeof(mpfr_t) * sizeof(argc - 1));
	_consts = (mpfr_t *)malloc(sizeof(mpfr_t) * sizeof(_size_consts));

	prec_literal(EZC_PREC);
	// loop through, and parse each one for a mpfr
	for (_loop = 1; _loop < argc; ++_loop) {
		mpfr_init(args[_loop]);
		mpfr_set_str(args[_loop], argv[_loop], 10, GMP_RNDN);
	}
	for (_loop = 0; _loop < _size_consts; ++_loop) {
		mpfr_init(_consts[_loop]);
	}
	mpfr_init(__start);
	mpfr_init(__start);
	mpfr_init(__stop);


	mpfr_t tmp; mpfr_init(tmp);
	mpfr_t sum; mpfr_init(sum);
	mpfr_t ma; mpfr_init(ma);
	fset(ma, _next_const("1000"));
	fset(sum, _next_const("0"));
	___summult(tmp, ma, _next_const("3"));
	add(sum, sum, tmp);
	___summult(tmp, ma, _next_const("5"));
	add(sum, sum, tmp);
	___summult(tmp, ma, _next_const("15"));
	sub(sum, sum, tmp);
	var("sum", sum);
}
