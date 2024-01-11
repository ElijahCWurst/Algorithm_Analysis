import math
from scipy.special import lambertw
import sys
import warnings

warnings.filterwarnings('ignore')
sys.set_int_max_str_digits(1000000000)

def formatNumber(num): return f"{num[0]}.{num[1:7]}*10^{len(num)-1}"

def factorialN(max, num = 1):
    while(math.factorial(num) <= max): num+=1
    return num-1

nLogN = lambda a : formatNumber(str(int(math.e**lambertw(a*math.log(2, math.e)))))
nSquared = lambda a : formatNumber(str(int(math.sqrt(a))))
nCubed = lambda a : formatNumber(str(int(math.cbrt(a))))
exponentialN = lambda a : formatNumber(str(int(math.log2(a))))

microSeconds = [1000000, 60*1000000, 60*60*1000000, 24*60*60*1000000, 30*24*60*60*1000000, 365*24*60*60*1000000, 100*365*24*60*60*1000000]
labels = ["    Seconds:", "    Minutes:", "    Hours:", "    Days:", "    Months:", "    Years:", "    Centuries:"]
print(("\n\n\n\n\n\n\n\n\n\n\n    \tlg n:\tsqrt(n):\tn:\tn lg n:\tn^2:\tn^3:\t2^n:\tn!:\n").expandtabs(22))
for __ in range(7): print((labels[__] + "\t" + str("2^" + str(microSeconds[__])) + "\t" + str(formatNumber(str((microSeconds[__])**2)) + "\t" + str(formatNumber(str(microSeconds[__]))) + "\t" + str(nLogN(microSeconds[__])) + "\t" + str(nSquared(microSeconds[__])) + "\t" + str(nCubed(microSeconds[__])) + "\t" + str(exponentialN(microSeconds[__])) + "\t" + str(factorialN(microSeconds[__])) + "\n").expandtabs(22)))