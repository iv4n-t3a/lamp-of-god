import matplotlib.pyplot as plt
import sys

FILE_PATH = sys.argv[1]

def read_file_content():
    global FILE_PATH
    with open(FILE_PATH, 'r') as f:
        data = list(map(lambda l: list(map(float, l.split())), f.readlines()))
    return data

def build_plot():
    data = read_file_content()
    plt.imshow(data, cmap='coolwarm', interpolation='nearest')
    plt.colorbar(label='Potential')
    plt.title('Potential')
    plt.xlabel('X')
    plt.ylabel('Y')

    plt.show()

if __name__ == "__main__":
    build_plot()
