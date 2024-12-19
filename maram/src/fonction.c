#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"fonction.h"
#include <gtk/gtk.h>
int is_valid_cin(const char *cin) {
    int length = strlen(cin);

    if (length != 8) {
        return 0;
    }

    for (int i = 0; i < length; i++) {
        if (!isdigit(cin[i])) {
            return 0;
        }
    }

    return 1;
}
enum
{ 
	EID,
	ENOM,
	EPRENOM,
	EJOUR,
	EMOIS,
	EANNEE,
	ESEXE,
        EADRESSE,
        EMDP,
        EEMAIL,
	COLUMNS,
};
enum
{ 
	ECIN,
	EJOU,
	EMOI,
	EANNE,
	EID_PARKING,
        EPRIX,
        EHEURES,
        EPAIEMENT,
	COLUMN,
};
//Ajouter


void ajouter_cit(citoyen b,char *cit){
FILE * f;
f=fopen(cit,"a");

  fprintf(f,"%s %s %s %d %s %d %s %s %s %s  \n ",b.id,b.nom,b.prenom,b.jour,b.mois,b.annee,b.sexe, b.adresse,b.mdp , b.email);
  fclose(f);
}


//Afficher

void afficher_cit(GtkWidget *liste){
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	
	GtkTreeIter iter;
	GtkListStore *store;
	char id[10];
	char nom[30];
	
	char prenom[10];
	char jour[10];
	char mois[30];
	char annee[30];
	char sexe[30];
        char adresse[50];
        char mdp[50];
        char email[50];

	
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);




	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text",EPRENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text",ENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	

	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text",EJOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text",EMOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text",EANNEE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text",ESEXE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("adresse", renderer, "text",EADRESSE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("mdp", renderer, "text",EMDP,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("email", renderer, "text",EEMAIL,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
	

	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,    G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING , G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING);
	f=fopen("citoyen.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("citoyen.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s %s   %s %s  %s\n",id,prenom,nom,jour,mois,annee,sexe,adresse,mdp,email)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EID,id, EPRENOM, prenom, ENOM, nom, EJOUR, jour, EMOIS, mois ,EANNEE ,annee,  ESEXE, sexe , EADRESSE ,adresse , EMDP , mdp ,EEMAIL, email,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}

//Modifier

void modifier_cit(char id[],citoyen b1,char *cit)
{
citoyen b;
  FILE* f=fopen(cit, "r");
  FILE* f2=fopen("citmod.txt", "w");
  
  if((f!=NULL) ||( f2!=NULL))
 {
while(fscanf(f,"%s %s %s %d %s %d %s  %s %s %s \n ",b.id,b.nom,b.prenom,&b.jour,b.mois,&b.annee,b.sexe,b.adresse,b.mdp,b.email)!=EOF)
{
if(strcmp(b.id,b1.id)==0)
  fprintf(f2,"%s %s %s %d %s %d %s %s %s %s \n ",b1.id,b1.nom,b1.prenom,&b1.jour,b1.mois,&b1.annee,b1.sexe,b1.adresse , b1.mdp , b1.email);
else
 fprintf(f2,"%s %s %s %d %s %d %s \n ",b.id,b.nom,b.prenom,&b.jour,b.mois,&b.annee,b.sexe,b.adresse,b.mdp,b.email);
}
   fclose(f);
   fclose(f2);
remove(cit);
rename("citmod.txt",cit);
 }
}

//supprimer

void supprimer_cit(char id[],char *cit)
{
citoyen b;     
FILE * f=fopen(cit,"r");
FILE * f2=fopen("citsupp.txt","w");

while (fscanf(f,"%s %s %s %d %s %d %s %s %s %s\n  ",b.id,b.nom,b.prenom,&b.jour,b.mois,&b.annee,b.sexe , b.adresse , b.mdp , b.email )!=EOF)
{

if(strcmp(b.id,id)!=0)

  fprintf(f2,"%s %s %s %d %s %d %s %s %s %s\n  ",b.id,b.nom,b.prenom,&b.jour,b.mois,&b.annee,b.sexe ,b.adresse , b.mdp , b.email );
}
  fclose(f);

  fclose(f2);

remove(cit);
rename("citsupp.txt",cit);

 
}
//fonction remplir tab
// Function to fill the array with citizen data from file
int remplirtabRech(citoyen tab[], int nb)
{
    char nom[20], prenom[20], id[20], mois[20], sexe[30], adresse[50], mdp[50], email[50];
    int jour, annee;
    FILE* fichier;
    int i = 0;

    fichier = fopen("citoyen.txt", "r");  // Use read mode

    if (fichier == NULL) {
        printf("Error: Could not open file 'citoyen.txt'.\n");
        return nb;
    }

    // Read data from the file and fill the array
    while (fscanf(fichier, "%s %s %s %d %s %d %s %s %s %s\n", id, nom, prenom, &jour, mois, &annee, sexe, adresse, mdp, email) != EOF)
    {
        if (i >= 100) break;  // Prevent overflow

        strcpy(tab[i].id, id);
        strcpy(tab[i].nom, nom);
        strcpy(tab[i].prenom, prenom);
        tab[i].jour = jour;
        strcpy(tab[i].mois, mois);
        tab[i].annee = annee;
        strcpy(tab[i].sexe, sexe);
        strcpy(tab[i].adresse, adresse);
        strcpy(tab[i].mdp, mdp);
        strcpy(tab[i].email, email);

        nb++;
        i++;
    }

    fclose(fichier);
    return nb;
}

// Function to search for a citizen by id
int rechercher_cit(char id[])
{
    citoyen tab[100];
    int nb = 0;
    int ce = 0, i;
    FILE *f;

    nb = remplirtabRech(tab, nb);

    for (i = 0; i < nb; i++) {
        if (strcmp(id, tab[i].id) == 0 || strcmp(id, tab[i].nom) == 0 || strcmp(id, tab[i].prenom) == 0) {
            ce = 1;
            f = fopen("rechcit.txt", "w+");

            if (f != NULL) {
                fprintf(f, "%s %s %s %d %s %d %s %s %s %s\n", tab[i].id, tab[i].nom, tab[i].prenom, tab[i].jour, tab[i].mois,
                        tab[i].annee, tab[i].sexe, tab[i].adresse, tab[i].mdp, tab[i].email);
                fclose(f);
            } else {
                printf("Error: Could not open file 'rechcit.txt'.\n");
            }
        }
    }

    return ce;
}

//AFF RECH
void afficher_rechercher_cit(GtkWidget *liste)
{
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	
	GtkTreeIter iter;
	GtkListStore *store;
	char id[10];
	char nom[30];
	
	char prenom[10];
	char jour[10];
	char mois[30];
	char annee[30];
	char sexe[30];
        char adresse[50];
        char mdp[50];
        char email[50];   
	
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);




	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text",EPRENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text",ENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	

	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text",EJOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text",EMOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text",EANNEE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text",ESEXE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("adresse", renderer, "text",EADRESSE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("mdp", renderer, "text",EMDP,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("email", renderer, "text",EEMAIL,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	

	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING);
	f=fopen("rechcit.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("rechcit.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s %s %s %s %s  \n",id,nom,prenom,jour,mois,annee,sexe,adresse , mdp ,email)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EID, id, ENOM,nom, EPRENOM, prenom, EJOUR, jour, EMOIS,  mois,EANNEE ,annee,  ESEXE,sexe,EADRESSE,adresse,EMDP,mdp ,EEMAIL, email ,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
	
}
 // Fonction pour calculer la facture d'un citoyen pour un mois et une année donnés
void calculerFacture(int id_citoyen, int mois, int annee) {
    FILE *fichier_res = fopen("reservation.txt", "r");
    FILE *fichier_park = fopen("parking.txt", "r");

    if (fichier_res == NULL || fichier_park == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    float facture = 0.0;
    char ligne[100];
    Reservation res;
    Parking park;

    // Sauter la première ligne (en-tête) dans les fichiers
    fgets(ligne, sizeof(ligne), fichier_res);
    fgets(ligne, sizeof(ligne), fichier_park);

    printf("Recherche des réservations pour le citoyen %d, mois: %d, année: %d\n", id_citoyen, mois, annee);

    // Lire chaque réservation dans reservation.txt
    while (fgets(ligne, sizeof(ligne), fichier_res) != NULL) {
        sscanf(ligne, "%d,%d,%d,%d,%d,%d", 
               &res.id_citoyen, &res.id_reservation, &res.id_parking, 
               &res.jour, &res.mois, &res.annee);

        if (res.id_citoyen == id_citoyen && res.mois == mois && res.annee == annee) {
            printf("Réservation trouvée pour le citoyen %d, parking %d, date: %d/%d/%d\n", 
                   res.id_citoyen, res.id_parking, res.jour, res.mois, res.annee);

            // Revenir au début de parking.txt pour chaque recherche de parking
            rewind(fichier_park);
            fgets(ligne, sizeof(ligne), fichier_park);  // Ignorer l'en-tête à chaque fois

            int found = 0;
            while (fgets(ligne, sizeof(ligne), fichier_park) != NULL) {
                sscanf(ligne, "%d,%f", &park.id_parking, &park.prix_par_jour);

                if (park.id_parking == res.id_parking) {
                    printf("Prix trouvé pour le parking %d : %.2f\n", park.id_parking, park.prix_par_jour);
                    facture += park.prix_par_jour;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("Aucun prix trouvé pour le parking %d\n", res.id_parking);
            }
        }
    }

    fclose(fichier_res);
    fclose(fichier_park);

    printf("La facture pour le citoyen %d pour %d/%d est : %.2f\n", id_citoyen, mois, annee, facture);
  }     

void afficher_facture(GtkWidget *liste){
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	
	GtkTreeIter iter;
	GtkListStore *store;
	char id[10];
	char jour[10];
	char mois[30];
	char annee[30];
	char id_parking[50];
        char prix[50];
        char heures[50];
        char paiement[50];

	
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id", renderer, "text",ECIN,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);





	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text",EJOU,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text",EMOI,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text",EANNE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id_parking", renderer, "text",EID_PARKING,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("prix", renderer, "text",EPRIX,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("heures", renderer, "text",EHEURES,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("paiement", renderer, "text",EPAIEMENT,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
	

	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,    G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING , G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING);
	f=fopen("citoyen.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("reservation.txt","a+");
		while(fscanf(f,"%s  %s %s %s %s   %s %s  %s\n",id,jour,mois,annee,id_parking,prix,heures,paiement)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, ECIN,id, EJOU, jour, EMOI, mois ,EANNE ,annee,  EID_PARKING, id_parking , EPRIX ,prix , EHEURES , heures ,EPAIEMENT, paiement,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}

