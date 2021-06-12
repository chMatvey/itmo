import numpy as np
from sklearn.decomposition import PCA
from sklearn import datasets
import matplotlib
import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv('data/71_36.csv')

X = data.values.tolist()

pca = PCA(n_components=2, svd_solver='full')
pca.fit(X)
X_transformed = pca.transform(X)
print(X_transformed[0])
plt.plot(X_transformed[:60, 0], X_transformed[:60, 1], 'o', markerfacecolor='red', markeredgecolor='k', markersize=8)
plt.show()

pca = PCA(n_components=10, svd_solver='full')
pca.fit(X)
X_full = pca.transform(X)

explained_variance = np.round(np.cumsum(pca.explained_variance_ratio_),3)
print(explained_variance)

plt.plot(np.arange(10), explained_variance, ls = '-')
plt.show()