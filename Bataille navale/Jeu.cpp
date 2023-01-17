
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <clocale>


using namespace std;

const int TAILLE_X = 10;
const int TAILLE_Y = 10;
const int NB_BATEAU = 4;
const int deux = 2;
const int MAX_CHAR = 200;

typedef struct {
    bool etat;
    int taille;
    int nb_touche;
    char logobateau;
    string nom_bat;
} S_bateau;

typedef char t_grille[TAILLE_X + 1][TAILLE_Y + 1];
typedef S_bateau t_fiche_bateau[NB_BATEAU][deux];
typedef int T_coo[deux];
typedef char t_chaine80[MAX_CHAR];

void Change_joueur(int& player) {
    if (player == 1)
        player = 2;
    else
        player = 1;
}

void init_grille(t_grille& grille) {
    int cptX;
    int cptY;
    for (cptY = 0; cptY < TAILLE_Y; cptY++)
    {
        for (cptX = 0; cptX < TAILLE_X; cptX++)
        {
            grille[cptX][cptY] = ' ';
        }
        grille[TAILLE_X][cptY] = '-';
    }
    for (cptX = 0; cptX < TAILLE_X + 1; cptX++)
    {
        grille[cptX][TAILLE_Y] = '-';
    }

}

void afficher_grille(t_grille& grille, int player, bool win, int mode, t_fiche_bateau fiche) {
    int cptX;
    int cptY;

    if (mode == 1)
        cout << "                Flotte du joueur " << player << endl << endl;
    else
        cout << "                Flotte de l'IA" << endl << endl;
    cout << "   " << "|";
    for (cptX = 0; cptX < TAILLE_X; cptX++)
    {
        cout << ' ' << char(65 + cptX) << ' ' << "|";
    }
    cout << "             Infos :" << endl;
    for (cptY = 0; cptY < TAILLE_Y; cptY++)
    {
        cout << ' ' << cptY << ' ' << '|';
        for (cptX = 0; cptX < TAILLE_X; cptX++)
        {
            cout << ' ' << grille[cptX][cptY] << ' ' << "|";
        }
        switch (cptY) {
        case 1: {
            cout << "             Torpilleur en vie : " << fiche[0][player - 1].etat;
        }
              break;
        case 2: {
            cout << "             Sous-marin en vie : " << fiche[1][player - 1].etat;
        }
              break;
        case 3: {
            cout << "             Croiseur en vie : " << fiche[2][player - 1].etat;
        }
              break;
        case 4: {
            cout << "             Porte-avion en vie : " << fiche[3][player - 1].etat;
        }
              break;
        }
        cout << endl;
    }
    cout << endl;
    if (win == true) {
        Change_joueur(player);
        cout << "Joueur " << player << " a gagne" << endl << endl;
    }

}

int choisir_mode() {
    int res;

    cout << "               Choisir mode de jeu" << endl << endl;
    cout << "[1] Joueur 1 vs Joueur 2" << endl;
    cout << "[2] Joueur 1 vs IA" << endl;
    cin >> res;
    while (res != 1 && res != 2) {
        cout << "Choisir un mode valide" << endl;
        cin >> res;
    }
    return(res);
}

bool verifcoo_placement(T_coo coor, t_grille grille)//verifie si une case est occupé
{
    bool verif;

    if (grille[coor[0]][coor[1]] == ' ' && coor[0] < TAILLE_X && coor[1] < TAILLE_Y)
        verif = true;
    else
        verif = false;
    return (verif);
}

void remplir_grille(T_coo coor, t_grille& grille, char logobateau, char sens, int taille_bateau)//remplie une case avec des valeurs tes
{
    int cpt;
    switch (sens)
    {
    case 'z':
    {
        for (cpt = 0; cpt < taille_bateau; cpt++) {
            grille[coor[0]][coor[1] - cpt] = logobateau;
        }
    }
    break;
    case 's':
    {
        for (cpt = 0; cpt < taille_bateau; cpt++) {
            grille[coor[0]][coor[1] + cpt] = logobateau;
        }
    }
    break;
    case 'q':
    {
        for (cpt = 0; cpt < taille_bateau; cpt++) {
            grille[coor[0] - cpt][coor[1]] = logobateau;
        }
    }
    break;
    case 'd':
    {
        for (cpt = 0; cpt < taille_bateau; cpt++) {
            grille[coor[0] + cpt][coor[1]] = logobateau;
        }
    }
    break;
    }
}

void placer_bateau(int modeplace, char logobateau, t_grille& grille, int taille_bateau, string nom_bateau) {





    bool verif, verif_sens;
    char sens;
    int cpt;
    T_coo verifsens_coo;
    T_coo coor;
    int cptechec;
    int cptX, cptY;
    char lettrex;
    int memo;

    do
    {
        do //on regarde si y qqchose sur la case selctionne
        {
            if (modeplace == 2)
            {
                cout << "Donnez une coordonnees du " << nom_bateau << " de taille " << taille_bateau << endl;
                cin >> lettrex;
                coor[0] = lettrex - 65;
                cin >> coor[1];
                verif = verifcoo_placement(coor, grille);
                if (verif == false)
                    cout << "Coordonee invalide" << endl;
            }
            else
            {
                srand(time(NULL));
                coor[0] = rand() % TAILLE_X;
                coor[1] = rand() % TAILLE_Y;
                verif = verifcoo_placement(coor, grille);
            }
        } while (verif == false);
        if (modeplace == 2) {
            do//on demande le sens
            {
                cout << "entrez le sens de placement: zqsd ";
                cin >> sens;
            } while (sens != 'z' && sens != 'q' && sens != 's' && sens != 'd');

        }
        else {
            memo = rand() % 4;
            switch (memo) {
            case 0:
                sens = 'z';
                break;
            case 1:
                sens = 'q';
                break;
            case 2:
                sens = 's';
                break;
            case 3:
                sens = 'd';
                break;
            }
        }

        verifsens_coo[1] = coor[1];
        verifsens_coo[0] = coor[0];
        //les valuers de verif definit ici avant d'etre defini plus

        //-----------

        //debut switch
        switch (sens)
        {
        case 'z':
        {
            verif_sens = true;
            for (cpt = 0; cpt < taille_bateau; cpt++) {
                verifsens_coo[1] = coor[1] - cpt; //on fait varier postivment notre coo Y
                verif = verifcoo_placement(verifsens_coo, grille);
                if (verif == false)//si c'est faux une seul fois le placment sera refuse a la fin
                    verif_sens = false;
            }

        }
        break;

        case 's':
        {
            verif_sens = true;
            for (cpt = 0; cpt < taille_bateau; cpt++) {
                verifsens_coo[1] = coor[1] + cpt; //on fait varier negativement notre coo Y
                verif = verifcoo_placement(verifsens_coo, grille);
                if (verif == false)//si c'est faux une seul fois le placment sera refuse a la fin
                    verif_sens = false;
            }
        }
        break;

        case 'd':
        {
            verif_sens = true;
            for (cpt = 0; cpt < taille_bateau; cpt++) {
                verifsens_coo[0] = coor[0] + cpt; //on fait varier postivment notre coo X
                verif = verifcoo_placement(verifsens_coo, grille);
                if (verif == false)//si c'est faux une seul fois le placment sera refuse a la fin
                    verif_sens = false;
            }
        }
        break;

        case 'q':
        {
            verif_sens = true;
            for (cpt = 0; cpt < taille_bateau; cpt++) {
                verifsens_coo[0] = coor[0] - cpt; //on fait varier negativement notre coo X
                verif = verifcoo_placement(verifsens_coo, grille);
                if (verif == false)//si c'est faux une seul fois le placment sera refuse a la fin
                    verif_sens = false;
            }
        }
        break;
        }

    } while (verif_sens == false);//si verif sens est faux on reprend le palcment de ce bateau depuis le debut

    remplir_grille(coor, grille, logobateau, sens, taille_bateau);
}

int Choisir_Mode_placemennt(int player) {
    int choix;

    cout << "               Choisir mode de placement pour le joueur " << player << endl << endl;
    cout << "[1] Placement Auto" << endl;
    cout << "[2] Placement Manuel" << endl;
    cin >> choix;
    while (choix != 1 && choix != 2) {
        cout << "Choisir un mode de placement valide" << endl;
        cin >> choix;
    }
    return(choix);
}

void placement(t_grille& Grillemas, int mode_placement, t_fiche_bateau fiche, int player, int mode) {
    int cpt_bat;
    init_grille(Grillemas);
    if (mode == 1)
        afficher_grille(Grillemas, player, 0, mode, fiche);
    else
        cout << "Chargement du terrain de l'IA" << endl;
    for (cpt_bat = 0; cpt_bat < NB_BATEAU; cpt_bat++) {
        placer_bateau(mode_placement, fiche[cpt_bat][player - 1].logobateau, Grillemas, fiche[cpt_bat][player - 1].taille, fiche[cpt_bat][player - 1].nom_bat);
        if (mode == 1) {
            system("cls");
            afficher_grille(Grillemas, player, 0, mode, fiche);
            cout << "Le bateau " << fiche[cpt_bat][player - 1].nom_bat << " a ete place" << endl;
        }
    }
}

void demandetir(T_coo& coor, int modetir, int player) {
    char lettrex;

    if (modetir == 1)
    {
        cout << endl << "Joueur " << player << ", donnez la coordonnee du tir : ";
        cin >> lettrex;
        coor[0] = lettrex - 65;
        cin >> coor[1];

    }
    else
    {
        coor[0] = rand() % TAILLE_X;
        coor[1] = rand() % TAILLE_Y;
    }
}

bool touche_tir(T_coo coor, t_grille grille)
{
    bool touche;
    char cible;
    char nomcase;

    nomcase = coor[0] + 65;
    cible = grille[coor[0]][coor[1]];
    if (cible > 64 and cible <= 90)
    {
        touche = true;

        cout << "\nCible atteinte en case [" << nomcase << ":" << coor[1] << "] !\n\n";
        Sleep(1500);
    }
    else
    {
        touche = false;

        cout << "\nNous avons touche la mer en [" << nomcase << ":" << coor[1] << "] ... \n\n";
        Sleep(1500);
    }


    return (touche);
}

bool verifcoo_tir(T_coo coor, t_grille grille_jolie, int mode)//verifie si une case est occupe par un
{
    bool verif;
    char cible;

    cible = grille_jolie[coor[0]][coor[1]];

    if (cible == ' ' && coor[0] < TAILLE_X && coor[1] < TAILLE_Y)
        verif = true;
    else if (cible == 'X' || cible == 'O')// a voir si on garde toujours O et X pour les rucs deja touche
    {
        verif = false;
        if (mode == 1)
            cout << endl << "Tir de missile deja effectue sur ces coordonnees" << endl;

    }
    else
    {
        verif = false;
        if (mode == 1)
            cout << endl << "Vous visez hors du champ de bataille" << endl;
    }

    return (verif);
}

void Convertisseur_lettre_bateau(char idlettre, int& idchiffre)
{
    switch (idlettre)
    {
    case 'T': {idchiffre = 0;  }break;

    case 'S': {idchiffre = 1;  }break;

    case 'C': { idchiffre = 2; }break;

    case 'P': { idchiffre = 3; }break;
    }
}

bool Bateau_en_vie(int PV_perdu, int PV_total)
{
    bool flotte;

    if (PV_perdu < PV_total)
        flotte = true;
    else
        flotte = false;

    return(flotte);

}

void tourcombat(t_grille& grillemasque, t_grille& grillejolie, int Current_player, int modetir, t_fiche_bateau& liste_bat)
{
    T_coo coor;
    bool veriftir, veriftouche;
    char cible;
    int idcible;
    int Cases_touches;
    int taille;

    do
    {
        demandetir(coor, modetir, Current_player);                                              // Recupère les coordonnées de tir
        veriftir = verifcoo_tir(coor, grillejolie, modetir);                                    // Vérifie si les coordonnées sont valides

    } while (veriftir == false);                                                                //Reste bloqué tant qu'on ne rentre pas de bonnes coordonnées

    veriftouche = touche_tir(coor, grillemasque);                                               //Regarde si on a touché un bateau

    if (veriftouche == true) {                                                                   //Si on a touché :
        Change_joueur(Current_player);
        grillejolie[coor[0]][coor[1]] = 'X';                                                    //On met un X la où on a touché
        cible = grillemasque[coor[0]][coor[1]];                                                 //On récupere le caractère touché
        Convertisseur_lettre_bateau(cible, idcible);                                            //Transforme cible (char) en idcible (int)
        liste_bat[idcible][Current_player - 1].nb_touche++;                                        //Augmente de 1 le nombre de cases touchés du bateau identifié
        Cases_touches = liste_bat[idcible][Current_player - 1].nb_touche;
        taille = liste_bat[idcible][Current_player - 1].taille;

        liste_bat[idcible][Current_player - 1].etat = Bateau_en_vie(Cases_touches, taille);         //Actualise l'etat du bateau (si ce dernier est coulé => etat = false
    }
    else
        grillejolie[coor[0]][coor[1]] = 'O';                                                    //Sinon on met un O
}

bool verif_win(int player, t_fiche_bateau fiche) { // Tant qu'il reste u moins un bateau verifwin est vrai.
    int cpt;
    bool win = true;

    for (cpt = 0; cpt < NB_BATEAU; cpt++) {
        if (fiche[cpt][player - 1].etat == true)
            win = false;
    }
    return (win);
}

void jouer(t_fiche_bateau& fiche) {

    T_coo coor_tir;
    int mode;
    int cpt;
    int Current_player = 1;
    int Other_player;
    int mode_placement;
    int mode_placement_j2;
    int nb_bateau;
    bool verifwinJ1 = false;
    bool verifwinJ2 = false;
    t_grille GrillemasJ1;
    t_grille GrillemasJ2;
    t_grille GrillejolieJ1;
    t_grille GrillejolieJ2;
    char suite;
    int valid;

    system("cls");
    mode = choisir_mode();
    do {                                                                     // Place les bateaux du joueur 1
        system("cls");
        mode_placement = Choisir_Mode_placemennt(Current_player);
        system("cls");
        placement(GrillemasJ1, mode_placement, fiche, Current_player, 1);
        cout << endl << "Voulez-vous relancer le placement ?" << endl;
        cout << "[1] Relancer" << endl;
        cout << "[2] Continuer" << endl;
        cin >> valid;
    } while (valid != 2);
    Change_joueur(Current_player);
    do {                                                                     // Place les bateaux du joueur 2
        system("cls");
        if (mode == 1)
            mode_placement = Choisir_Mode_placemennt(Current_player);
        else
            mode_placement = 1;
        system("cls");
        placement(GrillemasJ2, mode_placement, fiche, Current_player, mode);
        if (mode == 1) {
            cout << endl << "Voulez-vous relancer le placement ?" << endl;
            cout << "[1] Relancer" << endl;
            cout << "[2] Continuer" << endl;
            cin >> valid;
        }
    } while (valid != 2);
    init_grille(GrillejolieJ1);
    init_grille(GrillejolieJ2);
    system("cls");
    do {                                                                     //Joueur 1 commence a jouer
        Change_joueur(Current_player);
        Other_player = Current_player;
        Change_joueur(Other_player);
        afficher_grille(GrillejolieJ2, Other_player, verifwinJ1, mode, fiche);
        tourcombat(GrillemasJ2, GrillejolieJ2, Current_player, 1, fiche);
        system("cls");
        afficher_grille(GrillejolieJ2, Other_player, verifwinJ1, mode, fiche);
        Sleep(1500);
        verifwinJ1 = verif_win(Other_player, fiche);
        system("cls");
        if (verifwinJ1 == false) {                                           //Joueur 2 joue si J1 n'a pas gagné
            Change_joueur(Current_player);
            Other_player = Current_player;
            Change_joueur(Other_player);
            afficher_grille(GrillejolieJ1, Other_player, verifwinJ2, 1, fiche);
            tourcombat(GrillemasJ1, GrillejolieJ1, Current_player, mode, fiche);
            system("cls");
            afficher_grille(GrillejolieJ1, Other_player, verifwinJ2, 1, fiche);
            Sleep(1500);
            verifwinJ2 = verif_win(Other_player, fiche);
            system("cls");
        }
    } while (verifwinJ1 == false && verifwinJ2 == false);

    for (cpt = 10; cpt > 0; cpt--) {
        if (verifwinJ2 == true) {
            afficher_grille(GrillejolieJ1, Other_player, verifwinJ2, mode, fiche);
            cout << endl << "Retour au menu dans " << cpt << " s";
            Sleep(1000);
            system("cls");
        }
        else if (verifwinJ1 == true) {
            afficher_grille(GrillejolieJ2, Other_player, verifwinJ1, mode, fiche);
            cout << endl << "Retour au menu dans " << cpt << " s";
            Sleep(1000);
            system("cls");
        }
    }

}

void lire_regles() {
    //Déclarations
    ifstream filein;
    t_chaine80 line;
    int nbline, cpt;
    char suite;
    //Actions


    do {
        system("cls");
        filein.open("regles.txt");
        if (filein.is_open())
        {


            nbline = 0;
            for (cpt = 0; cpt < 20; cpt++)
            {
                filein.getline(line, MAX_CHAR);

                if (filein.eof() == false)
                {
                    cout << line;
                    cout << endl;
                }
            }
            filein.close();


        }
        else
        {
            cerr << "l'ouverture du fichier des regles est impossible." << endl;
        }
        cin >> suite;

    } while (suite != 'A');
    system("cls");
    return;

}

void tir_IA_facile(T_coo& coor_tir, t_grille grille_jolie)//IA facile presque fonctionnel ,mais pas ue le temps d'integre a cause de mes 6h perdu sur les sauvegardes
{/*
    bool verif, autorisation_tir, cible_repere;
    char cible, ciblez, cibles, cibleq, cibled;
    int cptX, cptY;
    T_coo coor;

    cptY = cptX = 0;
    cible_repere = autorisation_tir = false;
    ciblez = grille_jolie[cptX - 1][cptY];
    cibles = grille_jolie[cptX + 1][cptY];
    cibleq = grille_jolie[cptX][cptY - 1];
    cibled = grille_jolie[cptX][cptY + 1];
    do
    {
        do
        {
            cible = grille_jolie[cptX][cptY];


            if (cible == 'X')
            {
                if (ciblez == '_')
                {
                    coor_tir[0] = cptX - 1;
                    coor_tir[0] = cptY;

                }
                else if (cibles == '_')
                {
                    coor_tir[0] = cptX + 1;
                    coor_tir[0] = cptY;
                    autorisation_tir;
                }
                else if (cibleq == '_')
                {
                    coor_tir[0] = cptX;
                    coor_tir[0] = cptY - 1;
                    autorisation_tir;
                }
                else if (cibled == '_')
                {
                    coor_tir[0] = cptX;
                    coor_tir[0] = cptY + 1;
                    autorisation_tir;
                }

            }
        } while (cptY < TAILLE_Y || cible != 'X');

        cptY = 0;
        cptX++;

    } while (cptX < TAILLE_X && autorisation_tir == false);

    if (autorisation_tir == false)
    {
        do
        {
            coor[0] = rand() % TAILLE_X;
            coor[1] = rand() % TAILLE_Y;
            autorisation_tir = verifcoo_tir(coor, grille_jolie, 1);
        } while (autorisation_tir == false);

    }

*/
}


int main()
{
    int choix;
    t_fiche_bateau fiche_bateau;
    int cpt;

    do {
        for (cpt = 0; cpt < deux; cpt++) {
            fiche_bateau[0][cpt].taille = 2;
            fiche_bateau[0][cpt].logobateau = 'T';
            fiche_bateau[0][cpt].nom_bat = "Torpilleur";
            fiche_bateau[0][cpt].etat = true;
            fiche_bateau[0][cpt].nb_touche = 0;

            fiche_bateau[1][cpt].taille = 3;
            fiche_bateau[1][cpt].logobateau = 'S';
            fiche_bateau[1][cpt].nom_bat = "Sous-marin";
            fiche_bateau[1][cpt].etat = true;
            fiche_bateau[1][cpt].nb_touche = 0;

            fiche_bateau[2][cpt].taille = 4;
            fiche_bateau[2][cpt].logobateau = 'C';
            fiche_bateau[2][cpt].nom_bat = "Croiseur";
            fiche_bateau[2][cpt].etat = true;
            fiche_bateau[2][cpt].nb_touche = 0;

            fiche_bateau[3][cpt].taille = 5;
            fiche_bateau[3][cpt].logobateau = 'P';
            fiche_bateau[3][cpt].nom_bat = "Porte-avion";
            fiche_bateau[3][cpt].etat = true;
            fiche_bateau[3][cpt].nb_touche = 0;
        }

        cout << "               Menu" << endl << endl;
        cout << "[1]  Jouer" << endl;
        cout << "[2]  Lire les regles" << endl;
        cout << "[3]  Quitter" << endl;
        cin >> choix;
        switch (choix) {
        case 1: jouer(fiche_bateau);
            break;
        case 2: lire_regles();
            break;
        case 3:cout << endl << "Au revoir" << endl << endl;
            break;
        default:cout << "Choisir un chiffre valable" << endl;
        }
    } while (choix != 3);
}
