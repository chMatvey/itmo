import re

import nltk
from nltk import BigramCollocationFinder, TrigramCollocationFinder
from nltk.corpus import stopwords
import pymorphy2

from n_gram import calculate_n_grams, calculate_n_grams_frequency, calculate_mi

file = open('../lab1/text.txt', encoding='utf-8')
content = file.read()

regex_num = re.compile('[а-яёА-ЯЁ]+-?[а-яёА-ЯЁ]*')
words = regex_num.findall(content)
print(words)

morph = pymorphy2.MorphAnalyzer(lang='ru')
words = list(map(lambda token: morph.parse(token)[0].normal_form, words))
print(words)

stopWords = set(stopwords.words('russian'))
words = list(filter(lambda lex: lex not in stopWords, words))
print(words)

be_grams = calculate_n_grams(words, 2)
be_grams_freq = calculate_n_grams_frequency(be_grams, words, 2)
print()
print(be_grams_freq)

three_grams = calculate_n_grams(words, 3)
three_grams_freq = calculate_n_grams_frequency(three_grams, words, 3)
print()
print(three_grams_freq)

one_grams = calculate_n_grams(words, 1)
one_grams_freq = calculate_n_grams_frequency(one_grams, words, 1)

# Calculate MI

be_mi = calculate_mi(be_grams_freq, 2, one_grams_freq, len(words), 30)
print()
print(be_mi)

three_mi = calculate_mi(three_grams_freq, 3, one_grams_freq, len(words), 30)
print()
print(three_mi)

# Check

bigram_measures = nltk.collocations.BigramAssocMeasures()
trigram_measures = nltk.collocations.TrigramAssocMeasures()

text = nltk.Text(words)

finder_bi = BigramCollocationFinder.from_words(text)
finder_thr = TrigramCollocationFinder.from_words(text)

print()
be_best = finder_bi.nbest(bigram_measures.pmi, 30)
print(be_best)

print()
tri_best = finder_thr.nbest(trigram_measures.pmi, 30)
print(tri_best)