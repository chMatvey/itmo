from statistics import mean

import numpy
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from keras.datasets import mnist
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.decomposition import PCA
from sklearn.multiclass import OneVsRestClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import confusion_matrix
import pandas as pd
import scipy.stats as sc

from read_images_from_csv import read_images_from_csv

(X_train, y_train), (X_pred, y_pred) = mnist.load_data()
len(X_train)

# dim = 784  # 28*28
# X_train = X_train.reshape(len(X_train), dim)

# pca = PCA(n_components=48, svd_solver='full')
# modelPCA = pca.fit(X_train)
# X_full = pca.transform(X_train)
# explained_variance = np.round(np.cumsum(pca.explained_variance_ratio_), 3)
# for i, ev in enumerate(explained_variance.tolist()):
#     print(f'{i + 1}: {ev}')

dim = 784 # 28*28
X_train = X_train.reshape(len(X_train), dim)

pca = PCA(n_components=26, svd_solver='full')
modelPCA = pca.fit(X_train)

X_train = modelPCA.transform(X_train)

X_train, X_test, y_train, y_test = train_test_split(X_train, y_train, test_size=0.3, random_state=20)
print(f'Mean: {mean(X_train[0])}')

tree = RandomForestClassifier(criterion='gini', min_samples_leaf=10, max_depth=20, n_estimators=10, random_state=20)
clf1 = OneVsRestClassifier(tree).fit(X_train, y_train)
y_pred1 = clf1.predict(X_test)
CM1 = confusion_matrix(y_test, y_pred1)
print(CM1[3][3])

lr = LogisticRegression(solver='lbfgs', random_state=20)
clf2 = OneVsRestClassifier(lr).fit(X_train, y_train)
y_pred2 = clf2.predict(X_test)
CM2 = confusion_matrix(y_test, y_pred2)
print(CM2[4][4])

dtc = DecisionTreeClassifier(criterion='gini', min_samples_leaf=10, max_depth=20, random_state=20)
clf3 = OneVsRestClassifier(dtc).fit(X_train, y_train)
y_pred3 = clf3.predict(X_test)
CM3 = confusion_matrix(y_test, y_pred3)
print(CM3[0][0])

from_csv = read_images_from_csv()
from_csv = from_csv.reshape(len(from_csv), dim)
from_csv = modelPCA.transform(from_csv)

predict1 = clf1.predict_proba([from_csv[25]])
parsed_pr1 = list(map(lambda n: '{:.3f}%'.format(n), predict1[0]))
print(parsed_pr1[0])

predict2 = clf2.predict_proba([from_csv[1]])
parsed_pr2 = list(map(lambda n: '{:.3f}%'.format(n), predict2[0]))
print(parsed_pr2[2])

predict3 = clf3.predict_proba([from_csv[11]])
parsed_pr3 = list(map(lambda n: '{:.3f}%'.format(n), predict3[0]))
print(parsed_pr3[6])
