import re

word = r'([\wА-яа-яё-]+)'
phone = r'(\+?[1-9]{1,3}[ (-]?\d{3}[ )-]?\d{3}[- ]?\d{2}[ -]?\d{2})'
address = r'(г\.?( )*[\wА-яа-я-]+,?( )*ул\.?( )*[\wА-яа-я-]*,?( )*д\.?( )*\d+,?( )*(кв\.?( )*\d+)?)'
emoji = r'([:;][-]*[\(\)*\/oOPcDdC]+)'
formula = r'(([\w|\d|\(|\)]+ *[+|-|=|\*|^]\d* *)+)'

patterns = [
    phone,
    address,
    formula,
    emoji,
    word
]

pattern = "|".join(patterns)


def tokenize(text: str):
    matches = re.findall(pattern, text)
    words = map(lambda token: max(token, key=lambda value: len(value)), matches)
    return list(words)


f = open('text.txt', encoding='utf-8')
content = f.read()

tokens = tokenize(content)
print(tokens)
