from IPython.display import Image
from imutils import paths
import numpy as np
import cv2
import os
from sklearn.ensemble import BaggingClassifier, StackingClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from extract_histogram import extract_histogram
from sklearn.svm import LinearSVC
from sklearn.ensemble import RandomForestClassifier


imagePaths = sorted(list(paths.list_images('data/train')))
trainData = []
labels = []
cat_class_number = 1
dog_class_number = 0

for (i, imagePath) in enumerate(imagePaths):
    image = cv2.imread(imagePath, 1)
    label = imagePath.split(os.path.sep)[-1].split(".")[0]
    hist = extract_histogram(image)
    trainData.append(hist)
    labels.append(label)

Y = [cat_class_number if x == 'cat' else dog_class_number for x in labels]


# First
svm = LinearSVC(random_state = 80, C = 1.25)
svm.fit(trainData, Y)


# Second
tree = DecisionTreeClassifier(criterion='entropy',
                              min_samples_leaf=10,
                              max_leaf_nodes=20,
                              random_state=80)
bagging = BaggingClassifier(tree,
                            n_estimators=13,
                            random_state=80)
bagging.fit(trainData, Y)


# Third
forest = RandomForestClassifier(n_estimators=13,
                                criterion='entropy',
                                min_samples_leaf=10,
                                max_leaf_nodes=20,
                                random_state=80)
forest.fit(trainData, Y)


# Logistic regression
lr = LogisticRegression(solver='lbfgs', random_state=80)
base_estimators = [('SVM', svm), ('Bagging DT', bagging), ('DecisionForest', forest)]
sclf = StackingClassifier(estimators=base_estimators, final_estimator=lr, cv=2)
sclf.fit(trainData, Y)

score1 = sclf.score(trainData, Y)
print('Logistic regression score:', score1)


# Predictions
names = ['dog.1049.jpg', 'dog.1028.jpg', 'dog.1011.jpg', 'cat.1016.jpg']

for name in names:
    singleImage = cv2.imread('data/test/' + name)
    histt = extract_histogram(singleImage)
    histt2 = histt.reshape(1, -1)
    prediction = sclf.predict(histt2)
    proba = sclf.predict_proba(histt2)
    print(f'Predictions for {name}:', proba)