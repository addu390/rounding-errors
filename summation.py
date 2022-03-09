from fractions import Fraction
from math import frexp, fsum
from decimal import getcontext, Decimal, Inexact

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
