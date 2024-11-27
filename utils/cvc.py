import matplotlib.pyplot as plt
import sys

FILE_PATH = sys.argv[1]

x_dots = []
y_dots = []

with open(FILE_PATH) as file:
    while file:
        line = file.readline()
        if line == '': break
        x, y = map(float, line.split())
        x_dots.append(x)
        y_dots.append(y * 1000)

plt.plot(x_dots, y_dots, markersize=1.0, color='r', marker='o')
plt.xlim(x_dots[0], x_dots[-1])
plt.ylim(y_dots[0], y_dots[-1])
plt.show()
