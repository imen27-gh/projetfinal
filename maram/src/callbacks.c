#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include"fonction.h"
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
int x,y,z;
int l,m,n;

void
on_radiobutton_hom_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=1;}
}


void
on_radiobutton_fem_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=2;}
}

//boutonajout
void
on_button_add_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
citoyen b;
GtkWidget *windowajout,*idd,*nm,*prnm,*jr,*moi,*anne,*sex,*combobox1, *output, *output1,*adresse,*mdp,*email;
windowajout=create_window_gestcomp();


idd= lookup_widget(button,"entry_id");
nm= lookup_widget(button,"entry_nom");

prnm = lookup_widget(button,"entry_prn");
jr = lookup_widget(button,"spinbutton_jr");
anne = lookup_widget(button,"spinbutton_an");

combobox1=lookup_widget(button,"comboboxentry_mois");
adresse= lookup_widget(button,"entry1");
mdp= lookup_widget(button,"entry2");
email= lookup_widget(button,"entry3");
strcpy(b.id,gtk_entry_get_text(GTK_ENTRY(idd)));
strcpy(b.nom,gtk_entry_get_text(GTK_ENTRY(nm)));

strcpy(b.prenom,gtk_entry_get_text(GTK_ENTRY(prnm)));
strcpy(b.adresse,gtk_entry_get_text(GTK_ENTRY(adresse)));
strcpy(b.mdp,gtk_entry_get_text(GTK_ENTRY(mdp)));

strcpy(b.email,gtk_entry_get_text(GTK_ENTRY(email)));



b.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (jr));
b.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (anne));



if(x==1)
{strcpy(b.sexe,"homme");}
else if(x==2)
{strcpy(b.sexe,"Femme");}



if ((strcmp(b.nom,"")==0) || (strcmp(b.id,"")==0) ||(strcmp(b.prenom,"")==0)|| (strcmp(b.adresse,"")==0) ||(strcmp(b.mdp,"")==0) ||(strcmp(b.email,"")==0)) {
output1=lookup_widget(button,"label1");
gtk_label_set_text(GTK_LABEL(output1), "Données manquantes. \n Veuillez remplir tout les champs!");
output=lookup_widget(button,"label2");
gtk_label_set_text(GTK_LABEL(output), "");
}
/*if (!is_valid_cin(idd)) {
        gtk_label_set_text(GTK_LABEL(output), "Erreur : ID invalide !");
        return; // Sortir si l'ID est invalide
    }*/
if (combobox1 != NULL) {
        gchar *selected_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox1));

        if (selected_text != NULL) {
            // Affiche le genre sélectionné dans la console (debug)
            g_print("Genre sélectionné : %s\n", selected_text);

            // Copie le genre sélectionné dans la structure c
            strcpy(b.mois, selected_text);

            g_free(selected_text);
        } else {
            // Aucune option sélectionnée dans la combobox
            // Faites quelque chose en conséquence
           z=0;
        }


if(y==1){
ajouter_cit(b,"citoyen.txt");

output1=lookup_widget(button,"label1");
gtk_label_set_text(GTK_LABEL(output1), "");
output=lookup_widget(button,"label2");
gtk_label_set_text(GTK_LABEL(output), "Ajouter avec Succes");
}
x=0;
y=0;
z=0;
}
}










void
on_checkbutton_confaj_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{y=1;}
}

//boutonmodif
void
on_button_mod_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
citoyen b1;
GtkWidget *windowmodifier,*nm1,*id1,*prnm1,*jr1,*moi1,*anne1,*sex1,*combobox2
,*adresse1 ,*mdp1,*email1 ,*output2;
windowmodifier=create_window_gestcomp();
id1= lookup_widget(button,"entry_idmod");
prnm1= lookup_widget(button,"entry_prnmod");
nm1= lookup_widget(button,"entry_nommod");

jr1 = lookup_widget(button,"spinbutton_jrmod");
anne1 = lookup_widget(button,"spinbutton_anmod");
adresse1= lookup_widget(button,"entry4");
mdp1= lookup_widget(button,"entry5");
email1= lookup_widget(button,"entry6");


combobox2=lookup_widget(button,"comboboxentry_moismod");

strcpy(b1.id,gtk_entry_get_text(GTK_ENTRY(id1)));
strcpy(b1.prenom,gtk_entry_get_text(GTK_ENTRY(prnm1)));
strcpy(b1.nom,gtk_entry_get_text(GTK_ENTRY(nm1)));
strcpy(b1.adresse,gtk_entry_get_text(GTK_ENTRY(adresse1)));
strcpy(b1.mdp,gtk_entry_get_text(GTK_ENTRY(mdp1)));
strcpy(b1.email,gtk_entry_get_text(GTK_ENTRY(email1)));

b1.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (jr1));
b1.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (anne1));


if (combobox2 != NULL) {
        gchar *selected_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox2));

        if (selected_text != NULL) {
            // Affiche le genre sélectionné dans la console (debug)
            g_print("Genre sélectionné : %s\n", selected_text);

            // Copie le genre sélectionné dans la structure c
            strcpy(b1.mois, selected_text);

            g_free(selected_text);
        } else {
            // Aucune option sélectionnée dans la combobox
            // Faites quelque chose en conséquence
           n=0;
        }


if(m==1)
{strcpy(b1.sexe,"Homme");}
else if(m==2)
{strcpy(b1.sexe,"Femme");}


if(l==1){
modifier_cit(b1.id,b1,"citoyen.txt");
output2=lookup_widget(button,"label_mod");
gtk_label_set_text(GTK_LABEL(output2), "Modifier avec Succes");

}
m=0;
n=0;
l=0;

}
}


void
on_checkbutton_confmod_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{l=1;}
}


void
on_radiobutton_hommod_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{m=1;}
}


void
on_radiobutton_femmod_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{m=2;}
}


void
on_button_supp_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
char iddd[20];
GtkWidget *windowgestionfiche,*tree, *idd,*output;
idd = lookup_widget(button,"entry_supp");
strcpy(iddd,gtk_entry_get_text(GTK_ENTRY(idd)));
supprimer_cit(iddd,"citoyen.txt");
windowgestionfiche=lookup_widget(button,"window_gestcomp");
tree=lookup_widget(windowgestionfiche,"treeview3");
afficher_cit(tree);
output=lookup_widget(button,"label_supsuc");
gtk_label_set_text(GTK_LABEL(output), "Supprimer avec Succes");
gtk_widget_hide(windowgestionfiche);
gtk_widget_show(windowgestionfiche);
}


void
on_treeview3_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar* id;
gchar* prenom;
gchar* nom;

gchar* jour;
gchar* mois;
gchar* annee;
gchar* sexe;
gchar* adresse;
gchar* mdp;
gchar* email;

citoyen b;
GtkTreeModel *model= gtk_tree_view_get_model(treeview);
}


void
on_button_aff_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *tree,*window_aff;
window_aff=lookup_widget(button,"window_gestcomp");
gtk_widget_destroy(window_aff);
window_aff=create_window_gestcomp();
tree=lookup_widget(window_aff,"treeview3");

afficher_cit(tree);

gtk_widget_hide(window_aff);
gtk_widget_show(window_aff);
}


void
on_treeview4_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_button_rech_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
char id[20];
int c; 
GtkWidget *idd,*tree,*windowrech,*output;
windowrech=lookup_widget(button,"window_gestcomp");
idd = lookup_widget(button,"entry_rech");
strcpy(id,gtk_entry_get_text(GTK_ENTRY(idd)));
c=rechercher_cit(id);
if (c==0)
{
	output=lookup_widget(button,"label_rech");
	gtk_label_set_text(GTK_LABEL(output), "fiche INTROUVABLE");
}
if (c==1)
{	
tree=lookup_widget(windowrech,"treeview4");
afficher_rechercher_cit(tree);
}
}


void on_calucler_facture_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview5");
    GtkWidget *label_total_paiement = lookup_widget(GTK_WIDGET(button), "label142");
    GtkWidget *entry_mois = lookup_widget(GTK_WIDGET(button), "entry7");
    GtkWidget *entry_annee = lookup_widget(GTK_WIDGET(button), "entry8");

    // Récupérer les entrées
    const char *mois_str = gtk_entry_get_text(GTK_ENTRY(entry_mois));
    const char *annee_str = gtk_entry_get_text(GTK_ENTRY(entry_annee));

    // Validation des entrées
    if (mois_str == NULL || strlen(mois_str) == 0 ||
        annee_str == NULL || strlen(annee_str) == 0) {
        gtk_label_set_text(GTK_LABEL(label_total_paiement), "Veuillez entrer le mois et l'année.");
        return;
    }

    char *endptr;
    int mois = strtol(mois_str, &endptr, 10);
    if (*endptr != '\0' || mois < 1 || mois > 12) {
        gtk_label_set_text(GTK_LABEL(label_total_paiement), "Mois invalide. Doit être entre 1 et 12.");
        return;
    }

    int annee = strtol(annee_str, &endptr, 10);
    if (*endptr != '\0' || annee < 1900) {
        gtk_label_set_text(GTK_LABEL(label_total_paiement), "Année invalide. Doit être supérieure à 1900.");
        return;
    }

    // Traitement du modèle TreeView
    GtkListStore *liststore = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    if (!liststore) {
        gtk_label_set_text(GTK_LABEL(label_total_paiement), "Erreur : Le TreeView est vide.");
        return;
    }

    float total_paiement = 0.0;
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(liststore), &iter);

    while (valid) {
        int jour, mois_item, annee_item;
        float paiement;

        gtk_tree_model_get(GTK_TREE_MODEL(liststore), &iter,
                           1, &jour,
                           2, &mois_item,
                           3, &annee_item,
                           7, &paiement,
                           -1);

        if (mois == mois_item && annee == annee_item) {
            total_paiement += paiement;
        }

        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(liststore), &iter);
    }

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Total Paiement: %.2f TND", total_paiement);
    gtk_label_set_text(GTK_LABEL(label_total_paiement), buffer);
}

void
on_display_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *tree,*window_aff;
window_aff=lookup_widget(button,"window_gestcomp");
gtk_widget_destroy(window_aff);
window_aff=create_window_gestcomp();
tree=lookup_widget(window_aff,"treeview5");

afficher_facture(tree);

gtk_widget_hide(window_aff);
gtk_widget_show(window_aff);
}

