import math
import matplotlib.pyplot as plt
inputs = [x*100000 for x in range(1,11)]
outputs = [x*math.log(x) for x in inputs]
data = [14,
25,
39,
45,
56,
65,
76,
90,
97,
105]
ratios = [data[i]/outputs[i] for i in range(10)]
plt.plot(inputs,ratios)
plt.ylim(0,2e-5)
plt.xlabel("number of inputs")
plt.ylabel("time/(nlogn) : ratio of time and nlogn")
plt.show()