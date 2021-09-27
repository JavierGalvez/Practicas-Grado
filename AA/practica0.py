import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
import numpy as np

def parte1(iris):
    X = iris.data[:, 2:]
    Y = iris.target
    iris_type = iris.target_names
    color = ['r', 'g', 'b']
    fig, ax = plt.subplots()

    for a, b in zip(X, Y):
        ax.scatter(a[0], a[1], c=color[b], label=iris_type[b])

    h, l = ax.get_legend_handles_labels()
    labels = dict(zip(l, h))
    ax.legend(labels.values(), labels.keys())

    plt.xlabel(iris.feature_names[2])
    plt.ylabel(iris.feature_names[3])
    plt.title('Ejercicio 1')

    plt.show()

def parte2(iris):
    X = iris.data
    Y = iris.target
    train_x, test_x, train_y, test_y = train_test_split(X, Y, test_size=0.2, stratify=Y)
    a, b = list(train_y), list(Y)
    print("Train:", len(a), "Setosa:", a.count(0), "Versicolor:", a.count(1), "Virginica:", a.count(2))
    print("Original:", len(b), "Setosa:", b.count(0), "Versicolor:", b.count(1), "Virginica:", b.count(2))

def parte3():
    x = np.linspace(0, 2*np.pi, 100)

    plt.plot(x, np.sin(x), '--k', label='sin(x)')
    plt.plot(x, np.cos(x), '--b', label='cos(x)')
    plt.plot(x, np.sin(x)+np.cos(x), '--r', label='sin(x)+cos(x)')

    plt.title("Ejercicio 3")
    plt.legend()
    plt.show()

iris = load_iris()
parte1(iris)
parte2(iris)
parte3()
