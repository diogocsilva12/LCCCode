"""

Na cifra de Vigenère, dado um texto e uma chave (esta só com letras minúsculas), 
cada letra do texto é cifrada aplicando um desvio correspondente à posição no 
alfabeto da letra respetiva na chave. 
Por exemplo, para cifrar "BoaTarde" com a chave "ola", temos que repetidamente 
aplicar os desvios 14, 11, e 0. Como 'B'+14 == 'P', 'o'+11 == 'z', 'a'+0 == 'a',
'T'+14 == 'H', 'a'+11 == 'a', 'r'+0 = 'r', 'd'+14=='r', e 'e'+11 == 'p', o 
criptograma resultante seria "PzaHlrrp".
Implemente a função que decifra um criptograma cifrado com esta técnica.

"""

def decifrar(texto, chave):
    res = ""    
    idx = 0
    for char in texto:
        if char.isalpha():
            desvio = ord(chave[idx % len(chave)]) - ord('a')
            if char.isupper():
                overflowM = (ord(char) - desvio - ord('A')) % 26 + ord('A')
                letra_decifrada = chr(overflowM)
            else:
                overflowm = (ord(char) - desvio - ord('a')) % 26 + ord('a')
                letra_decifrada = chr(overflowm)
            res += letra_decifrada
            idx += 1
        else:
            res += char
    return res
    