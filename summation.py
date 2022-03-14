from fractions import Fraction
from math import frexp, fsum
from decimal import getcontext, Decimal, Inexact
import timeit

getcontext().traps[Inexact] = True


def error(numbers):
    s = 0.0
    for i in numbers:
        s = s + i
    return s


def ksum(numbers):
    s = 0.0
    c = 0.0
    for f in numbers:
        y = f - c
        t = s + y
        c = (t - s) - y
        s = t
    return s


def msum(iterable):
    partials = []
    for x in iterable:
        i = 0
        for y in partials:
            if abs(x) < abs(y):
                x, y = y, x
            hi = x + y
            lo = y - (hi - x)
            if lo:
                partials[i] = lo
                i += 1
            x = hi
        partials[i:] = [x]
    return sum(partials, 0.0)


def lsum(iterable):
    tmant, texp = 0, 0
    for x in iterable:
        mant, exp = frexp(x)
        mant, exp = int(mant * 2.0 ** 53), exp - 53
        if texp > exp:
            tmant <<= texp - exp
            texp = exp
        else:
            mant <<= exp - texp
        tmant += mant
    return float(str(tmant)) * 2.0 ** texp


def dsum(iterable):
    total = Decimal(0)
    for x in iterable:
        mant, exp = frexp(x)
        mant, exp = int(mant * 2.0 ** 53), exp - 53
        while True:
            try:
                total += mant * Decimal(2) ** exp
                break
            except Inexact:
                getcontext().prec += 1
    return float(total)


def frsum(iterable):
    return float(sum(map(Fraction.from_float, iterable)))


def generate_nilakantha_terms(num_terms):
    yield 3
    denominator = 1
    sign = 1
    for i in range(1, num_terms):
        denominator = (2 * i) * ((2 * i) + 1) * ((2 * i) + 2)
        yield sign * (4 / denominator)
        sign = -sign


if __name__ == "__main__":
    input = 262144
    print_format = '{} Time: {} | Value: {}'

    print(print_format.format('error sum: ', timeit.timeit(lambda: error(generate_nilakantha_terms(input)), number=10),
                              error(generate_nilakantha_terms(input))))

    print(print_format.format('ksum: ', timeit.timeit(lambda: ksum(generate_nilakantha_terms(input)), number=10),
                              ksum(generate_nilakantha_terms(input))))

    print(print_format.format('msum: ', timeit.timeit(lambda: msum(generate_nilakantha_terms(input)), number=10),
                              msum(generate_nilakantha_terms(input))))

    print(print_format.format('lsum: ', timeit.timeit(lambda: lsum(generate_nilakantha_terms(input)), number=10),
                              lsum(generate_nilakantha_terms(input))))

    print(print_format.format('dsum: ', timeit.timeit(lambda: dsum(generate_nilakantha_terms(input)), number=10),
                              dsum(generate_nilakantha_terms(input))))

    print(print_format.format('frsum: ', timeit.timeit(lambda: frsum(generate_nilakantha_terms(input)), number=10),
                              frsum(generate_nilakantha_terms(input))))

    print(print_format.format('fsum: ', timeit.timeit(lambda: fsum(generate_nilakantha_terms(input)), number=10),
                              fsum(generate_nilakantha_terms(input))))
