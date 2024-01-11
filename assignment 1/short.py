import scipy.special, scipy.stats, sys, warnings, math
warnings.filterwarnings('ignore')
def formatNumber(num): return f"{num[0]}.{num[1:7]}*10^{len(num)-1}"
def factorialN(max, num = 1):
    while(math.factorial(num) <= max): num+=1
    return num-1
microSeconds = [1000000, 60*1000000, 60*60*1000000, 24*60*60*1000000, 30*24*60*60*1000000, 365*24*60*60*1000000, 100*365*24*60*60*1000000, "    Seconds:", "    Minutes:", "    Hours:", "    Days:", "    Months:", "    Years:", "    Centuries:"]
print(("\n\n\n\n\n\n\n\n\n\n\n    \tlg n:\tsqrt(n):\tn:\tn lg n:\tn^2:\tn^3:\t2^n:\tn!:\n").expandtabs(22))
for __ in range(7): print((microSeconds[__ + 7] + "\t" + str("2^" + str(microSeconds[__])) + "\t" + str(formatNumber(str(microSeconds[__]**2))) + "\t" + str(formatNumber(str(microSeconds[__]))) + "\t" + str(formatNumber(str(int(math.e**scipy.special.lambertw((microSeconds[__]*math.log(2, math.e))))))) + "\t" + str(formatNumber(str(int(math.sqrt(microSeconds[__]))))) + "\t" + str(formatNumber(str(int(math.cbrt(microSeconds[__]))))) + "\t" + str(formatNumber(str(int(math.log2(microSeconds[__]))))) + "\t" + str(factorialN(microSeconds[__])) + "\n").expandtabs(22))