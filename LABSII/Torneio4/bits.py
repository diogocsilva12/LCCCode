'''

Implemente uma função que determine em quantas sequências de n bits
um bit a 1 apenas aparece em sequências de pelo menos k 1s seguidos. 
Por exemplo se n = 3 e k = 2 então temos 4 sequências válidas, 
nomeadamente 000, 110, 011 e 111. Se n = 4 e k = 3 temos também 4 
sequências válidas, nomeadamente 0000, 1110, 0111 e 1111. Se n = 4 e 
k = 2 então já temos 7 sequências válidas: para além das 4 anteriores 
temos 1100, 0110 e 0011.

'''

# devolve o primeiro candidato para um problema p
def first(p):
    return [0]*p
    
# dado um candidato c devolve o próximo candidato para p
def next(p,c):
    for idx in (range(p)):
        c[idx] = 1 - c[idx]  
        if c[idx] == 1:
            break
    else:
        return None
    return c
# testa se um candidato c é uma solução válida para p
def valid(p,c,k):
    conta_uns = 0
    for bit in c:
        if bit == 1:
            conta_uns += 1
        else:
            if 0 < conta_uns < k: 
                return False
            conta_uns = 0
    return conta_uns == 0 or conta_uns >= k

# procurar solução para p com pesquisa exaustiva
def search(p, k):
    conta_seq = 0
    c = first(p)
    while c is not None:
        if valid(p,c,k):
            conta_seq += 1
        c = next(p,c)
    return conta_seq

def bits(n, k):
    return search(n, k)