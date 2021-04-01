import io

from pymorphy2 import MorphAnalyzer

morphAnalyzer = MorphAnalyzer()

# Need install word2lemma.dat
with io.open('word2lemma.dat', encoding='utf-8') as f:
    for line in f:
        words = line.split('\t')
        morph = words[0]
        lemma = words[1]

        result = morphAnalyzer.parse(morph)
        parsedLemma = lemma.lower()
        matches = list(
            filter(lambda r: r.normal_form == parsedLemma, result)
        )

        if len(matches) == 0:
            print(f'Morph: {morph}; Lemma: {lemma}; Result: {result}')

