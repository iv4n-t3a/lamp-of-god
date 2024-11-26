import matplotlib.pyplot as plt

FILE_PATH = "/home/ivan/codes/lamp-of-god/data/file.txt"

def read_file_content():
    global FILE_PATH
    with open(FILE_PATH, 'r') as f:
        data = list(map(lambda l: list(map(float, l.split())), f.readlines()))
    print(data)
    return data

def build_graph():
    data = read_file_content()
    plt.imshow(data, cmap='coolwarm', interpolation='nearest')
    plt.colorbar(label='Потенциал')
    plt.title('Потенциал')
    plt.xlabel('X')
    plt.ylabel('Y')

    plt.show()

if __name__ == "__main__":
    build_graph()
