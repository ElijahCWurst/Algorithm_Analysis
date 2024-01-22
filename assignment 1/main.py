import math
from scipy.special import lambertw

formatNumber = lambda a : f"{a[0]}.{a[1:6]}*10^{len(a)-1}"
logN = lambda a : ("2^" + str(a))
rootN = lambda a : formatNumber(str(a**2))
N = lambda a : formatNumber(str(a))
nLogN = lambda a : str(int(math.e**lambertw(a*math.log(2, math.e)).real))
nSquared = lambda a : str(int(math.sqrt(a)))
nCubed = lambda a : str(int(math.cbrt(a)))
exponentialN = lambda a : str(int(math.log2(a)))
factorialN = lambda a : int(math.e**(lambertw(math.log(((a)/math.sqrt(2*math.pi)), math.e)/math.e).real+1)-0.5)

microSeconds = [1000000, 60*1000000, 60*60*1000000, 24*60*60*1000000, 30*24*60*60*1000000, 365*24*60*60*1000000, 100*365*24*60*60*1000000]
labels = ["    Seconds:", "    Minutes:", "    Hours:", "    Days:", "    Months:", "    Years:", "    Centuries:"]
print(("\n\n\n\n\n\n\n\n\n\n\n    \tlg n:\tsqrt(n):\tn:\tn lg n:\tn^2:\tn^3:\t2^n:\tn!:\n").expandtabs(22))
for __ in range(7): print((labels[__] + "\t" + str(logN(microSeconds[__])) + "\t" + str(rootN(microSeconds[__])) + "\t" + str(N(microSeconds[__])) + "\t" + str(nLogN(microSeconds[__])) + "\t" + str(nSquared(microSeconds[__])) + "\t" + str(nCubed(microSeconds[__])) + "\t" + str(exponentialN(microSeconds[__])) + "\t" + str(factorialN(microSeconds[__])) + "\n").expandtabs(22))