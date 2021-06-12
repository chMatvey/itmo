import numpy as np
import matplotlib
import matplotlib.pyplot as plt

loadings = np.genfromtxt('data/X_loadings_417.csv', delimiter=';')
reduced = np.genfromtxt('data/X_reduced_417.csv', delimiter=';')

values = np.dot(loadings, reduced.T)

plt.imshow(values, cmap='Greys_r')
plt.show()