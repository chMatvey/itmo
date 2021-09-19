import functools
import math


def calculate_n_grams(tokens, n):
    sequences = [tokens[i:] for i in range(n)]
    ngrams = zip(*sequences)
    return list(ngrams)


def calculate_n_grams_frequency(n_grams, tokens, n):
    result = {}
    for n_gram in n_grams:
        result[n_gram] = 0

    for i in range(0, len(tokens) - n + 1):
        n_gram = list()
        for j in range(0, n):
            n_gram.insert(j, tokens[i + j])
        n_gram = tuple(n_gram)
        result[n_gram] += 1

    result = dict(sorted(result.items(), key=lambda item: item[1], reverse=True))

    return result


def calculate_mi(n_grams_freq, n, uno_grams_freq, words_count, result_count):
    result = {}
    for n_gram in n_grams_freq:
        n_gram_freq = n_grams_freq[n_gram]

        word_freq_multi = functools.reduce(lambda a, b: a * b,
                                           list(map(lambda lexeme: uno_grams_freq[(lexeme,)], list(n_gram))))

        coefficient = words_count ** (n - 1)

        mi = math.log2(n_gram_freq * coefficient) - math.log2(word_freq_multi)

        result[n_gram] = mi

    result = dict(sorted(result.items(), key=functools.cmp_to_key(mi_compare), reverse=True))

    return dict(list(result.items())[:result_count])


def compare_asc(a, b):
    if a > b:
        return -1
    elif a == b:
        return 0
    else:
        return 1


def mi_compare(mi1, mi2):
    if mi1[1] > mi2[1]:
        return 1
    elif mi1[1] < mi2[1]:
        return -1
    else:
        first_words = list(mi1[0])
        second_words = list(mi2[0])

        n = len(first_words)

        try_count = 0
        result = 0

        while result == 0 and try_count < n:
            result = compare_asc(first_words[try_count], second_words[try_count])
            try_count += 1

        return result
