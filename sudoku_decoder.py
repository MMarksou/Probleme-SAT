#!/usr/bin/python3
import sys

#Dans ce cas, on veut traduire la résolution d'un problème SAT sous format
#d'une grille de sudoku.
#Une fois une solution trouvée, un fichier tmp.sat est créé avec les valeurs
#nécessaires pour nos variables. On peut ainsi recréer la grille avec
#une solution possible.

def charger_sat(fichier):
    global bloc, taille
    sat = []
    with open(fichier, "r") as f:
        for ligne in f.readlines():
            tmp = ligne.split()
            if tmp[0] == 'c':
                bloc = int(tmp[2])
                taille = bloc*bloc
            else:
                sat += [int(i) for i in tmp]
    return sat

def decode_sat(sat):
    grille = []
    for v in sat:
        if(v>0):
            tmp = v%taille
            if(tmp == 0):
                tmp = 9
            grille.append(tmp)
    return grille

def ecriture_grille(grille):
    global bloc, taille

    f = open("resultat_sudoku.txt", "w")
    f.write(str(bloc)+"\n")

    pos = 0

    for i in grille:
        f.write(str(i) + " ")
        pos += 1
        if pos == 9:
            f.write("\n")
            pos = 0
    f.close()

if __name__ == '__main__':
    bloc = 0
    taille = 0

    fichier = sys.argv[1]

    sat = charger_sat(fichier)

    grille = decode_sat(sat)

    ecriture_grille(grille)
