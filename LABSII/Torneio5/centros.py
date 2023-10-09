"""

Implemente uma função que determina os pontos centrais de uma figura.
Um ponto é central se a distância ao ponto mais afastado da
figura é a menor possível.
A lista com o resultado deve estar ordenada.

"""   


import math

def distancia(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

def centros(mapa):
    pontos = [(i, j) for i, row in enumerate(mapa) for j, cell in enumerate(row) if cell == '#']
    dist_max_minima = float('inf')
    centros = []
    for ponto in pontos:
        dist_max = max(distancia(ponto, ponto1) for ponto1 in pontos)
        if dist_max < dist_max_minima:
            dist_max_minima = dist_max
            centros = [ponto]
        elif dist_max == dist_max_minima:
            centros.append(ponto)
    centros.sort()
    return centros