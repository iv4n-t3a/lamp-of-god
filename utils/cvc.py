import matplotlib.pyplot as plt
import sys

FILE_PATH = sys.argv[1]

def read_file_content():
    global FILE_PATH

    x_dots = []
    y_dots = []

    with open(FILE_PATH) as file:
        while file:
            line = file.readline()
            if line == '':break
            x, y = map(float, line.split())
            x_dots.append(x)
            y_dots.append(y)

    return x_dots, y_dots

def build_plot():
    x_dots, y_dots = read_file_content()

    X_OFFSET = abs(x_dots[0] - x_dots[-1]) / 10
    Y_OFFSET = abs(y_dots[0] - y_dots[-1]) / 10


    plt.title('Current–voltage characteristic')
    plt.xlabel('Voltage(Volts)')
    plt.ylabel('Current(Amperes)')

    plt.plot(x_dots, y_dots)
    plt.xlim(x_dots[0] - X_OFFSET, x_dots[-1] + X_OFFSET)
    plt.ylim(y_dots[0] - Y_OFFSET, y_dots[-1] + Y_OFFSET)
    plt.show()

if __name__ == "__main__":
    build_plot()
