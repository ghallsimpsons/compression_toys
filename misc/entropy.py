from scipy.stats import norm
from math import log

def shannon_entropy_gaussian(std, precision=1-1e-9, base=32):
    """
    Simple function to estimate the Sannon entropy of a Gaussian distributed
    dataset. The precision is a normalization condition which determines the
    domain of integration.
    """
    prob = norm.pdf(0, scale=std)
    entrp = prob*log(prob, base)

    i = 1
    while (prob<precision):
        p_i = norm.pdf(i, scale=std)
        if p_i != 0:
            entrp -= 2*p_i*log(p_i, base)
            prob += 2*p_i
        i += 1
    return entrp
