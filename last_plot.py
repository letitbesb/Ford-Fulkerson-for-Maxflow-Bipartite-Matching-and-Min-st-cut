import matplotlib.pyplot as plt

# input test case sizes and times (in microseconds)
test_sizes = [20,40,50,100,400,500,1000]
test_times = [1847,5915,3768,9111,181852,374474,2129160]

# create a line chart with test_sizes on the x-axis and test_times on the y-axis
plt.plot(test_sizes, test_times, '-o')

# set the labels for the x-axis and y-axis
plt.xlabel('Number of Points')
plt.ylabel('Time (microseconds)')

# show the plot
plt.show()
