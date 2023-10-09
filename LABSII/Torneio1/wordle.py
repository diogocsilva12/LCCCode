"""
Implemente uma função que dada uma palavra secreta e uma palavra tentativa
devolva uma lista com os caracteres da palavra tentativa que aparecem na
palavra secreta.
Mais concretamente, para cada caracter que apareça na palavra tentativa
deve também ser indicada a respectiva posição e um booleano que indica se
aparece na mesma posição na palavra secreta ou numa posição diferente.
"""

def aux(secreta,sol):
    cnt = ""
    res = []
    for elem in sol:
        if cnt.count(elem[0]) < secreta.count(elem[0]):
            cnt += elem[0]
            res.append(elem)
    return res


def wordle(secreta,tentativa):
    idx = 0
    res = []
    if len(tentativa) <= len(secreta):
        idx = 0
        for letter in tentativa:
            if secreta.count(letter) > 0:
                if secreta[idx] == letter:
                    res.append((letter,idx,True))
                else:
                    res.append((letter,idx,False))
            idx+=1
    else:
        aux_tentativa1 = tentativa[:-(len(tentativa)-len(secreta))]
        aux_tentativa2 = tentativa[-(len(tentativa)-len(secreta)):]
        for letter1 in aux_tentativa1:
            if secreta.count(letter1) > 0:
                if secreta[idx] == letter1:
                    res.append((letter1,idx,True))
                else:
                    res.append((letter1,idx,False))
            idx+=1

    return aux(secreta,res)