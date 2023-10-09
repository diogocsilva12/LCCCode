'''

Implemente a seguinte função que dada uma lista de strings filtra as strings
que podem ser obtidas intercalando os caracteres das strings a e b também dadas
como parâmetro. Uma string s intercala as strings a e b sse apenas contem 
caracteres de a e b e todos os caracters de a e b aparecem pela mesma 
ordem em s. Sugere-se que comece pode definir recursivamente uma função 
auxiliar que testa se uma string s intercala as strings a e b, e que depois
optimize essa função com as técnicas de memoization e programação dinâmica.

'''

def filtra(strings,a,b):

    def filtraAux(s, i, j, cache={}):
        if (s, i, j) in cache:
            return cache[(s, i, j)]

        if i == len(a) and j == len(b):
            cache[(s, i, j)] = True
            return True

        if i < len(a) and a[i] == s[0]:
            if filtraAux(s[1:], i+1, j):
                cache[(s, i, j)] = True
                return True

        if j < len(b) and b[j] == s[0]:
            if filtraAux(s[1:], i, j+1):
                cache[(s, i, j)] = True
                return True

        cache[(s, i, j)] = False
        return False

    return [s for s in strings if filtraAux(s, 0, 0)]