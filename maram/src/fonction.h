#include <gtk/gtk.h>

typedef struct
{ 
    char id[20];
    char prenom[20];
    char nom[20];
    int  jour;
    char mois[20];
    int  annee;
    char sexe[30];
    char adresse[50];
    char mdp[50];
    char email[50];

}citoyen;
// Structures
typedef struct {
    int id_citoyen;
    int id_reservation;
    int id_parking;
    int jour;
    int mois;
    int annee;
} Reservation;

typedef struct {
    int id_parking;
    float prix_par_jour;
} Parking;
int search_user(const char *filename, const char *cin, citoyen *result);
void calculerFacture(int id_citoyen, int mois, int annee);
int is_valid_cin(const char *cin);
void ajouter_cit(citoyen b,char *cit);
void afficher_cit(GtkWidget *liste);
void modifier_cit(char id[],citoyen b,char *cit);
void supprimer_cit(char id[],char *cit);
int rechercher_cit(char id[]);
void afficher_rechercher_cit(GtkWidget *liste);
int remplirtabRech (citoyen tab[],int nb) ;

