import numpy as np
import matplotlib.pyplot as plt
import warnings, time
from sklearn.exceptions import ConvergenceWarning, FitFailedWarning
from sklearn.linear_model import LogisticRegressionCV, LogisticRegression
from sklearn.model_selection import GridSearchCV
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import classification_report, confusion_matrix, plot_confusion_matrix

# Ignorar usar tipo de regularización en técnicas que no lo permiten, por ejemplo usar L1 con lbfgs
warnings.filterwarnings(action='ignore', category=FitFailedWarning)
# Ignorar warning regularización=none ignora los valores de 'C'
warnings.filterwarnings(action='ignore', category=UserWarning)

def readData(path):
    X = []
    Y = []
    with open(path, 'r') as f:
        for line in f:
            line = line.split(',')
            X.append(np.fromiter(line[:-1], int))
            Y.append(int(line[-1]))

    return np.array(X), np.array(Y)

def cota(N, Err, delta):
    return Err + np.sqrt(1/(2*N) * np.log(2/delta))

X_train, y_train = readData('datos/optdigits.tra')
X_test, y_test = readData('datos/optdigits.tes')

# Estandarizar
scaler = StandardScaler()
scaler.fit(X_train)
X_train_scaled = scaler.transform(X_train)
X_test_scaled = scaler.transform(X_test)

print("\nSe va a probar regresión logística con 4 solvers distintos: lbfgs, newton-cg, liblinear y sag")
input("\n--- Pulsar tecla para continuar ---\n")

# Fit regresión logística con los 4 solvers
solvers = ['lbfgs', 'newton-cg', 'liblinear', 'sag']
accuracies = {}

params = {'penalty': ['l1', 'l2', 'none'], 
          'C': [0.01, 0.1, 0.2, 0.3, 0.4, 0.5, 1]}

for solver in solvers:
    print('Resultados para el solver %s:\n' % solver)

    # Cross Validation
    grid_search = GridSearchCV(LogisticRegression(max_iter=100, random_state=0, solver=solver), params)

    start = time.time()
    grid_search.fit(X_train_scaled, y_train)
    end = time.time()

    # Predict
    y_predicted = grid_search.predict(X_test_scaled)

    # Print resultados
    print('Mejores parámetros:', grid_search.best_params_)
    print('Eval = %f' % (1.0 - grid_search.best_score_))
    print('Cota Eout = %f' % cota(len(X_train), 1 - grid_search.best_score_, 0.05))
    print('Etest = %f\n' % (1.0 - grid_search.score(X_test_scaled, y_test)))

    # Métricas clasificación
    print(classification_report(y_test, y_predicted))
    
    # Confusion Matrix
    matrix = plot_confusion_matrix(grid_search.best_estimator_, X_test_scaled, y_test, values_format='3.0f')
    matrix.figure_.suptitle("Confusion Matrix " + solver)
    print("Confusion matrix: \n%s\n" % matrix.confusion_matrix)
    print('Tiempo empleado (segundos): %3.4f' % (end - start))

    accuracies[solver] = (y_predicted, grid_search.score(X_test_scaled, y_test))
    
    input("\n--- Pulsar tecla para continuar ---\n")

    plt.show()

    input("\n--- Pulsar tecla para continuar ---\n")

# Comparativa accuracies X_test de los solvers
for solver, score in accuracies.items():
    print('Accuracy para %s: %1.4f' % (solver, score[1]))
input("\n--- Pulsar tecla para continuar ---\n")

# Plot de los números
best_classifier = max(accuracies, key=lambda x: accuracies[x][1]) 
print('Ejemplo resultados de %s' % best_classifier)

fig = plt.figure()
# Números con su label
for i, (image, label) in enumerate(list(zip(X_train, y_train))[:4], start=1):
    ax = fig.add_subplot(2, 4, i)
    ax.set_axis_off()
    ax.imshow(np.reshape(image, (8, 8)), cmap=plt.cm.gray_r, interpolation='nearest')
    ax.set_title('Training: %i' % label)

# Números con label predecida
for i, (image, true, predict) in enumerate(list(zip(X_test, y_test, accuracies[best_classifier][0]))[:4], start=5):
    ax = fig.add_subplot(2, 4, i)
    ax.set_axis_off()
    ax.imshow(np.reshape(image, (8, 8)), cmap=plt.cm.gray_r, interpolation='nearest')
    ax.set_title('Label: %i\nPredicted: %i' % (true, predict))

fig.suptitle('Ejemplo resultados de %s' % best_classifier)
plt.show()
