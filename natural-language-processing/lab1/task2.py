from nltk.stem.snowball import SnowballStemmer

from task1 import tokens

stemmer = SnowballStemmer("russian")

words = tokens

result = list(
    map(lambda word: stemmer.stem(word), words)
)

print(result)
