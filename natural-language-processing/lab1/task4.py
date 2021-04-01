import csv

from nltk import SnowballStemmer
from pymorphy2 import MorphAnalyzer

from task1 import tokens

stemmer = SnowballStemmer("russian")
morphAnalyzer = MorphAnalyzer()

words = tokens

with open('Chudakov.tsv', 'wt', encoding='utf-8') as out_file:
    tsv_writer = csv.writer(out_file, delimiter='\t')
    for word in words:
        stem = stemmer.stem(word)
        lemma = morphAnalyzer.parse(word)[0].normal_form
        tsv_writer.writerow([word, stem, lemma])
