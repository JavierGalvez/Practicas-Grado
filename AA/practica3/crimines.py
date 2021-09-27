import numpy as np
import matplotlib.pyplot as plt
import warnings
from sklearn.exceptions import ConvergenceWarning
from sklearn.impute import SimpleImputer
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import SGDRegressor, LinearRegression
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.metrics import mean_squared_error
from sklearn.pipeline import Pipeline

# Ignorar no convergencia por falta de iteraiones en cross-validation
warnings.filterwarnings(action='ignore', category=ConvergenceWarning)

def readData(path):
    X = []
    y = []
    with open(path, 'r') as f:
        for line in f:
            line = line.replace('?', 'nan').split(',')
            # Primeros 5 elementos non-predictive
            X.append(np.fromiter(line[4:-1], float))
            y.append(float(line[-1]))

    return np.array(X), np.array(y)

X, y = readData('datos/communities.data')

# 80% train 20% test
X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=0.8, random_state=0)

# Valores perdidos
missing_values = 0
for x in X_train:
    if np.sum(np.isnan(x)) > 0:
        missing_values += 1

print('\nPreprocesado de los datos\n')
print('Muestras de los datos con al menos un valor perdido: %i de %i' % (missing_values, X_train.shape[0]))
print('Porcentaje de datos con valores perdidos: %2.2f' % (missing_values / X_train.shape[0]))
print('Porcentaje de atributos perdidos en datos con al menos un atributo perdido: %2.2f' 
      % (np.mean([x for x in np.sum(np.isnan(X_train), axis=1) if x > 0]) / X_train.shape[1]))

input("\n--- Pulsar tecla para continuar ---\n")

# Cross-validation
pipe = Pipeline([('scaler', StandardScaler()), 
                 ('Imputer', SimpleImputer(missing_values=np.nan, strategy='mean')), 
                 ('SGD', SGDRegressor())])


params = {'SGD__random_state': [0],
          'SGD__penalty': ['l1', 'l2'], 
          'SGD__learning_rate': ['constant', 'optimal', 'invscaling', 'adaptive'], 
          'SGD__eta0': [0.0001, 0.001, 0.01, 0.1, 1],
          'SGD__alpha': [0.01, 0.1, 0.5, 1, 10]}

# Print hiperparámetros
print('Hiperparámetros a probar:\n')
print('Tipo de regularización:', ', '.join(params['SGD__penalty']))
print('Técnica de actualización del lr:', ', '.join(params['SGD__learning_rate']))
print('Valores de comienzo del lr:', ', '.join(str(x) for x in params['SGD__eta0']))
print('Valores del parámetro de regularización:', ', '.join(str(x) for x in params['SGD__alpha']))

input("\n--- Pulsar tecla para continuar ---\n")

# Fit
grid_search = GridSearchCV(pipe, params, scoring='neg_mean_squared_error')

grid_search.fit(X_train, y_train)

# Print resultados
print('Mejores hiperparámetros:', grid_search.best_params_)
print('Eval = %f' % (grid_search.best_score_ * -1))
print('Etest = %f\n' % mean_squared_error(y_test, grid_search.predict(X_test)))
