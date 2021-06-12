import pandas as pd
import matplotlib
import numpy as np
import matplotlib.pyplot as plt
from sklearn.tree import DecisionTreeClassifier
from sklearn.tree import export_graphviz
import graphviz
from sklearn.metrics import accuracy_score, f1_score

df = pd.read_csv('data/diabetes.csv')

count = 550

task_data = df.head(count)

countOfClass0 = len(task_data[task_data['Outcome'] == 0])
print(countOfClass0)

train = task_data.head(int(len(task_data) * 0.8))
test = task_data.tail(int(len(task_data) * 0.2))

features = list(train.columns[:8])
x = train[features]
y = train['Outcome']

tree = DecisionTreeClassifier(criterion='entropy',
                              min_samples_leaf=10,
                              max_leaf_nodes=10,
                              random_state=2020)
clf = tree.fit(x, y)

columns = list(x.columns)
export_graphviz(clf, out_file='tree.dot',
                feature_names=columns,
                class_names=['0', '1'],
                rounded=True, proportion=False,
                precision=2, filled=True, label='all')

with open('tree.dot') as f:
    dot_graph = f.read()

source = graphviz.Source(dot_graph)

print(source)


depth = clf.tree_.max_depth
print('Depth:', depth)

features = list(test.columns[:8])
x = test[features]
y_true = test['Outcome']
y_pred = clf.predict(x)

score = accuracy_score(y_true, y_pred)
print('Score:', score)

f__score = f1_score(y_true, y_pred, average='macro')
print('F1 Score:', f__score)

ids = [766, 703, 731, 716]

for item_id in ids:
    prediction = clf.predict([df.loc[item_id, features].tolist()])[0]
    print(f'Class of {item_id}:', prediction)
