def duplica(lista):
    return duplicaAux(lista, {})

def duplicaAux(lista, cache={}):
    x = len(lista)
    
    if x == 0:
        return 0
        
    if x == 1:
        return 2*lista[0]
    
    if x in cache:
        return cache[x]
    
    a = lista[0] + duplicaAux(lista[1:], cache)
    b = 2*lista[0] + lista[1] + duplicaAux(lista[2:], cache)
    resultado = max(a,b)
    cache[x] = resultado
    
    return resultado