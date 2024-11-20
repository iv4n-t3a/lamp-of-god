import matplotlib.pyplot as plt

def field_plot(file_path: str):
    with open(file_path) as f:
        data = [([], []) for i in range(int(f.readline()))]
        for line in f.readlines():
            values = line.split()
            data[int(values[0])][0].append(float(values[1]))
            data[int(values[0])][1].append(float(values[2]))

    for datum in data:
        plt.plot(datum[0], datum[1])
        plt.show()
