from sklearn.preprocessing import LabelEncoder
from sklearn.svm import LinearSVC
from sklearn.metrics import classification_report
from sklearn.model_selection import train_test_split
from IPython.display import Image
from imutils import paths
import numpy as np
import cv2
import os
from sklearn.metrics import f1_score
from extract_histogram import extract_histogram

imagePaths = sorted(list(paths.list_images('data/train')))
data = []
labels = []

for (i, imagePath) in enumerate(imagePaths):
    image = cv2.imread(imagePath, 1)
    label = imagePath.split(os.path.sep)[-1].split(".")[0]
    hist = extract_histogram(image)
    data.append(hist)
    labels.append(label)


le = LabelEncoder()
labels = le.fit_transform(labels)

(trainData, testData, trainLabels, testLabels) = train_test_split(np.array(data), labels, test_size=0.25, random_state=9)

model = LinearSVC(random_state = 9, C = 0.51)
model.fit(trainData, trainLabels)

predictions = model.predict(testData)

print(classification_report(testLabels, predictions, target_names=le.classes_))

predictions = model.predict(testData)
f1_score(testLabels, predictions, average='macro')

print('Q256:', model.coef_[0][256])
print('Q370:', model.coef_[0][370])
print('Q124:', model.coef_[0][124])


image_for_prediction = [
    'cat.1046.jpg',
    'dog.1025.jpg',
    'cat.1042.jpg',
    'cat.1003.jpg'
]

for img_path in image_for_prediction:
    singleImage = cv2.imread('data/test/' + img_path)
    histt = extract_histogram(singleImage)
    histt2 = histt.reshape(1, -1)
    prediction = model.predict(histt2)
    print(img_path, prediction)


