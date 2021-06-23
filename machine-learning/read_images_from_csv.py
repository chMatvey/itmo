from io import StringIO

import numpy
import numpy as np
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt


def read_images_from_csv():
    data_from_csv = pd.read_csv('data/pred_for_task.csv')
    data_list = data_from_csv.values.tolist()
    parsed = list(
        map(lambda item: (item[0], [*item[2:], 0]), data_list)
    )

    images = []
    for p in parsed:
        img_bytes = []
        uint8 = []
        for i, x in enumerate(p[1]):
            if i != 0 and i % 28 == 0:
                img_bytes.append(numpy.array(uint8, np.uint8))
                uint8 = []
            uint8.append(x)
        images.append(numpy.array(img_bytes))

    return numpy.array(images)


result = read_images_from_csv()
img = result[11]
plt.imshow(img, cmap="gray")
plt.show()
