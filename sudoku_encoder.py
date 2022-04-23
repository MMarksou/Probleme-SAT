#!/usr/bin/python3
import sys

#On veut traduire un probleme de sudoku en un probleme sat
# On sépare alors les clauses en 6 grandes familles de clause :
# C1 = la case a au moins une valeur
# C2 = la case a au plus une valeur
# C3 = chaque ligne a une valeur
# C4 = chaque colonne a une valeur
# C5 = chaque bloc a une valeur
# C6 = la solution respecte le certificat donné

#Nous avons essayé de le faire en c mais de nombreux problèmes concernant
#l'allocation en mémoire nous ont découragé.Voici alors la version en python.

#Une des interrogations concernant la méthode en python est le coût en
#complexité du append. Après recherche, il est en O(N) dans le pire des cas ce
#qui est acceptable dans notre usage actuel.

#Nous nous sommes inspiré d'un code sur internet, ce travail n'est pas totalement
#le fruit de nos efforts.

#Source : https://users.aalto.fi/~tjunttil/2020-DP-AUT/notes-sat/solving.html

def val_lit(ligne, colonne, valeur):
    return (ligne-1)*taille*taille+(colonne-1)*taille+valeur

def charger_grille(fichier):
    global taille, bloc
    grille = []
    with open(fichier, "r") as f:
        for ligne in f.readlines():
            if len(ligne) == 2:
                bloc = int(ligne)
                taille = bloc*bloc
            elif len(ligne) == 1:
                pass
            else:
                grille.append(ligne.split())
    return grille

def c1_c2():
    global sat, taille

    for l in range(1, taille+1):
        for c in range(1, taille+1):
            #si une cellule (l,c) a au moins une valeur
            sat.append([val_lit(l, c, v) for v in range(1, taille+1)]) #N³

            for v in range(1, taille+1):
                for w in range(v+1,taille+1):
                    #si une cellule (l,c) a au plus une valeur
                    sat.append([-val_lit(l,c,v), -val_lit(l,c,w)]) #N²*N(N+1)/2

def c3_c4_c5():
    global sat, taille, bloc

    for v in range(1, taille+1):
        for l in range(1, taille+1):
            #si chaque ligne a une valeur v
            sat.append([val_lit(l,c,v) for c in range(1,taille+1)]) #N³

        for c in range(1, taille+1):
            #si chaque colonne a une valeur v
            sat.append([val_lit(l,c,v) for l in range(1,taille+1)]) #N³

        #on sélectionne chaque bloc un par un
        for bl in range(0, bloc):
            for bc in range(0, bloc):
                sat.append([val_lit(bl*bloc+lb, bc*bloc+bc, v)
                for lb in range(1, taille+1) for bc in range(1, taille+1)]) #N⁴

def c6(g):
    global sat, taille

    #Notre problème doit respecter le certificat, on écrit alors des clauses
    #unitaires faisait référence aux littéraux concernés
    for l in range(1, taille+1):
        for c in range(1, taille+1):
            if(g[l-1][c-1] != '0'):

                sat.append([val_lit(l,c,int(g[l-1][c-1]))]) #N²


#On écrit le résultat dans un fichier .sat qui va pouvoir être lu par notre
#solveur SAT

def ecriture_sat(sat):

    global bloc
    f = open("tmp.sat", "w")
    f.write("c sudoku "+str(bloc)+" x "+str(bloc)+" en SAT\n")

    for clause in sat:
        f.write(" ".join(str(l) for l in clause) + " 0\n")

    f.close()

if __name__ == '__main__':
    bloc = 0
    taille = 0
    sat = []

    fichier = sys.argv[1]

    g = charger_grille(fichier)

    c1_c2()
    c3_c4_c5()
    c6(g)

    ecriture_sat(sat)
