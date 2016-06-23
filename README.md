# Compression Toys!

Some ideas I was playing around with for compression of slowly varying arrays like well-behaved PSDs.

# About

This code contains two complementary approaches to compression of numerical data.
The first is explored in `bitmask.cpp`. Because floating point data stored in text
files often does not require all bits offered by a datatype, we can mask off as many
significant bits so as to still guarantee it rounds to the correct value within the
given precision. The second is a bitwise transposition routine in `transpose.cpp`. The
idea behind this routine is that, for slowly varying data, the most significant bits
remain constant for long runs in the data. By storing the nth significant bits
contiguously, dictionary compression algorithms like LZMA can take better advantage
of the low entropy of the data. Transposition alone, however, offers only a marginal
improvement in compressions size (of some data sets), and still doesn't come close
to reaching the Shannon entropy limit. For instance, an array of 32 bit integers
with a standard deviation of 500 gives a Shannon entropy of ~2.2, amounting to
a 14x compression factor. However, in practice we see only a ~2.5x compression.
Transposition helps with certain types of datasets more than others. In particular,
trended data and single floating-point precision data sets tend to favor transposition,
showing up to a 15% improvement in compression ratio (e.g. 3.45x vs 3x).
