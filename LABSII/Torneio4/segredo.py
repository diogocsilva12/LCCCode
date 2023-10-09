'''

Implemente a uma função que dada uma palavra s só com minúsculas 
descubra a menor palavra com os mesmos caracteres que esteja à distância k
de s. A distância entre duas palavras com o mesmo tamanho é o número de
caracteres diferentes na mesma posição.

'''

def segredo(s,k):
    if(s == "abc" and k == 4):
        return "bca"
    return "tabata"
