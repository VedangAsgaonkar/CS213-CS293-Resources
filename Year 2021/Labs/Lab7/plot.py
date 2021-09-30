import matplotlib.pyplot as plt
from numpy.core.fromnumeric import ptp
import pandas as pd
import numpy as np

df1 = pd.read_csv('insert.csv')
df2 = pd.read_csv('delete.csv')

x = df1['N'].to_numpy()
logx = np.log(x)
y1 = df2['time'].to_numpy()/x
y2 = df2['swaps'].to_numpy()/x
# fig = plt.subplots(figsize =(12, 8))
plt.bar(logx,y1,color='b',width=0.4)
# plt.bar(logx,y2,color='r',width=0.4,label="delete")
print(x)
print(y1)
print(y2)
plt.xlabel('logN')
plt.ylabel('time per operation in nanoseconds')
plt.title('Time for Delete')
plt.legend()
# plt.xticks([r + 0.4 for r in range(len(logx))],
#         logx)
plt.show()

# import numpy as np
# import matplotlib.pyplot as plt
 
# # set width of bar
# barWidth = 0.25
# fig = plt.subplots(figsize =(12, 8))
 
# # set height of bar
# IT = [12, 30, 1, 8, 22]
# ECE = [28.3, 6, 16, 5, 10]
# CSE = [29, 3, 24, 25, 17]
 
# # Set position of bar on X axis
# br1 = np.arange(len(IT))
# br2 = [x + barWidth for x in br1]
# br3 = [x + barWidth for x in br2]
 
# # Make the plot
# plt.bar(br1, IT, color ='r', width = barWidth,
#         edgecolor ='grey', label ='IT')
# plt.bar(br2, ECE, color ='g', width = barWidth,
#         edgecolor ='grey', label ='ECE')
# plt.bar(br3, CSE, color ='b', width = barWidth,
#         edgecolor ='grey', label ='CSE')
 
# # Adding Xticks
# plt.xlabel('Branch', fontweight ='bold', fontsize = 15)
# plt.ylabel('Students passed', fontweight ='bold', fontsize = 15)
# plt.xticks([r + barWidth for r in range(len(IT))],
#         ['2015', '2016', '2017', '2018', '2019'])
 
# plt.legend()
# plt.show()