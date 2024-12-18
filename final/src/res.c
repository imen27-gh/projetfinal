#include <gtk/gtk.h>
#include "res.h" 
#include "parkingmanagment.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_LENGTH 50 // Longueur maximale pour les champs
#define MAX_LINE_LENGTH 256

enum {
    EIdUserr,
    ERes_Idd,
    EIdParkk,
    EPhonee,
    EDurationn,
    EOptionn,
    ESecurityy,
    EDateed,
    EDateem,
    EDateey,
    COLUMNS_BOOKK
};
int add_res(const char *filename, book b) {
    FILE *f = fopen(filename, "a");
    if (f == NULL) {
        perror("File open error");
        return 0;
    }
    fprintf(f,"%s %s %s %s %02d/%02d/%04d %d %d %d\n", b.u_id, b.p_id, b.res_id, b.ph_num,b.entry_date.dayb, b.entry_date.monthb,  b.entry_date.yearb, b.duration, b.security , b.option);
    fclose(f);
      return 1;
    
} 
int modify_res(const char *filename, const char *res_id, book nouv) 
{
    int tr = 0; 
    
    book b;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f == NULL || f2 == NULL) {
       
        if (f) fclose(f);
        if (f2) fclose(f2);
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), f) != NULL) {
       
        sscanf(line, "%s %s %s %s %02d/%02d/%04d %d %d %d\n", b.u_id, b.p_id, b.res_id, b.ph_num,&b.entry_date.dayb, &b.entry_date.monthb,  &b.entry_date.yearb, &b.duration, &b.security , &b.option);
        if (strcmp(b.res_id, res_id) == 0) {
          
            fprintf(f2,"%s %s %s %s %02d/%02d/%04d %d %d %d\n", nouv.u_id, nouv.p_id,nouv.res_id, nouv.ph_num,nouv.entry_date.dayb,nouv.entry_date.monthb,  nouv.entry_date.yearb, nouv.duration, nouv.security ,nouv.option);
            tr = 1;
        } else {
       
            fprintf(f2,"%s %s %s %s %02d/%02d/%04d %d %d %d\n", b.u_id, b.p_id, b.res_id, b.ph_num,b.entry_date.dayb, b.entry_date.monthb,  b.entry_date.yearb, b.duration, b.security , b.option);
        }
    }
    fclose(f);
    fclose(f2);

    if (tr) {
      
        if (remove(filename) != 0) {

            return 0;
        }
        if (rename("nouv.txt", filename) != 0) {
            return 0;
        }
    } else { 
        
        remove("nouv.txt");
    }

    return tr;
} 
int Deleteb(const char *filename, const char *res_id) {
    int tr = 0;
    book b;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f == NULL || f2 == NULL) {
        if (f) fclose(f);
        if (f2) fclose(f2);
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), f) != NULL) {
        sscanf(line,"%s %s %s %s %02d/%02d/%04d %d %d %d\n", b.u_id, b.p_id, b.res_id, b.ph_num,&b.entry_date.dayb, &b.entry_date.monthb,  &b.entry_date.yearb, &b.duration, &b.security , &b.option);

        if (strcmp(b.res_id, res_id) != 0) {
            fprintf(f2,"%s %s %s %s %02d/%02d/%04d %d %d %d\n", b.u_id, b.p_id, b.res_id, b.ph_num,b.entry_date.dayb, b.entry_date.monthb,  b.entry_date.yearb, b.duration, b.security , b.option);
        } else {
            tr = 1;
        }
    }
    fclose(f);
    fclose(f2);

    if (tr) {
        if (remove(filename) != 0) {
            return 0;
        }
        if (rename("nouv.txt", filename) != 0) {
            return 0;
        }
    } else {
        remove("nouv.txt");
    }

    return tr;
} 
book searchb(const char *filename, const char *res_id, const char *p_id) {
    book b;
    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        perror("File open error");
        snprintf(b.res_id, sizeof(b.res_id), "Not found"); 
        return b;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), f) != NULL) {
        sscanf(line, "%s %s %s %s %02d/%02d/%04d %d %d %d\n", b.u_id, b.p_id, b.res_id, b.ph_num,&b.entry_date.dayb, &b.entry_date.monthb,  &b.entry_date.yearb, &b.duration, &b.security , &b.option);
        // Nettoyer les sauts de ligne
        line[strcspn(line, "\n")] = 0;

        // Vérifier les conditions de recherche
        if (strcmp(b.res_id, res_id) == 0 &&
            strcmp(b.p_id, p_id) == 0) {
            found = 1;
            break;
        }
    }
    fclose(f);

    if (!found) {
        snprintf(b.res_id, sizeof(b.res_id), "Not found"); 
    }

    return b;
} 


// Fonction de contrôle de saisie
int controle_saisieb(const char *data, champ_type type) {
    int len = strlen(data);

    switch (type) {
        case U_ID:
        case RES_ID:
        case P_ID:
            // Les identifiants doivent être non vides et ne contenir que des caractères alphanumériques, des tirets et des underscores
            if (len == 0 || len > MAX_LENGTH) return 0; // Vérification de la longueur
            for (int i = 0; i < len; i++) {
                if (!(isalnum(data[i]) || data[i] == '_' || data[i] == '-')) return 0;
            }
            return 1; // Retourne 1 si valide

        case PH_NUM:
            // Le numéro de téléphone doit être numérique et entre 8 et 14 caractères
            if (len < 8 || len > 14) return 0; // Vérification de la longueur
            for (int i = 0; i < len; i++) {
                if (!isdigit(data[i])) return 0;
            }
            return 1; // Retourne 1 si valide

        case OTHER:
            // Ajouter d'autres validations ici si nécessaire
            // Exemple : vérifier si le champ est non vide
            return len > 0 ? 1 : 0;

        default:
            return 0; // Retourne 0 si le type est inconnu
    }
}

// Fonction de validation pour les détails de réservation
int validate_booking_details(const char *user_id, const char *res_id, const char *p_id, const char *ph_num) {
    return controle_saisieb(user_id, U_ID) &&
           controle_saisieb(res_id, RES_ID) &&
           controle_saisieb(p_id, P_ID) &&
           controle_saisieb(ph_num, PH_NUM);
}



void show_res(GtkWidget *res) {
    book b;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *f;

    // Create the GtkListStore with the appropriate columns
    store = gtk_list_store_new(COLUMNS_BOOKK,
                               G_TYPE_STRING,  // ID USER
                               G_TYPE_STRING,  // Id Parking
                               G_TYPE_STRING,  // ID RESERVATION
                               G_TYPE_STRING,  // PHONE NUMBER
                               G_TYPE_INT,     // Day
                               G_TYPE_INT,     // Month
                               G_TYPE_INT,     // Year
                               G_TYPE_INT,     // DURATION
                               G_TYPE_INT,     // SECURITY
                               G_TYPE_INT      // OPTION
    );
    if (store == NULL) {
        fprintf(stderr, "Error: Failed to create GtkListStore\n");
        return;
    }

    // If the TreeView has no model, set up columns
    if (gtk_tree_view_get_model(GTK_TREE_VIEW(res)) == NULL) {
        const char *column_titles[] = {
            "ID USER", "Id Parking", "ID RESERVATION", 
            "PHONE NUMBER", "Day", "Month", "Year", 
            "DURATION", "SECURITY", "OPTION"
        };

        for (int i = 0; i < sizeof(column_titles) / sizeof(column_titles[0]); i++) {
            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes(column_titles[i], renderer, "text", i, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(res), column);
        }
    }

    // Open the file
    f = fopen("reservation.txt", "r");
    if (f == NULL) {
        perror("Unable to open file");
        return;
    }

    // Read data from the file and populate the GtkListStore
    while (fscanf(f, "%s %s %s %s %02d/%02d/%04d %d %d %d\n", 
                  b.u_id, b.p_id, b.res_id, b.ph_num,
                  &b.entry_date.dayb, &b.entry_date.monthb, &b.entry_date.yearb,
                  &b.duration, &b.security, &b.option) == 10) {  // Expecting 10 items
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, b.u_id,             // ID USER
                           1, b.p_id,             // Id Parking
                           2, b.res_id,           // ID RESERVATION
                           3, b.ph_num,           // PHONE NUMBER
                           4, b.entry_date.dayb,   // Day
                           5, b.entry_date.monthb, // Month
                           6, b.entry_date.yearb,  // Year
                           7, b.duration,         // DURATION
                           8, b.security,         // SECURITY
                           9, b.option,           // OPTION
                           -1);
    }
    
    if (ferror(f)) {
        perror("Error reading from file");
    }

    fclose(f);

    // Set the model for the TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(res), GTK_TREE_MODEL(store));
    g_object_unref(store);
}
void search_res2(GtkWidget *treeview, const char *filename, const char *res_search, const char *park_search) {
    GtkListStore *store;
    GtkTreeIter iter;
    book b;
    FILE *f;

    // Créer un modèle GtkListStore
    store = gtk_list_store_new(COLUMNS_BOOKK,
                                G_TYPE_STRING,  // ID USER
                                G_TYPE_STRING,  // ID PARKING
                                G_TYPE_STRING,  // ID RESERVATION
                                G_TYPE_STRING,  // PHONE NUMBER
                                G_TYPE_INT,     // DAY
                                G_TYPE_INT,     // MONTH
                                G_TYPE_INT,     // YEAR
                                G_TYPE_INT,     // DURATION
                                G_TYPE_INT,     // SECURITY
                                G_TYPE_INT      // OPTION
    );

    // Ouvrir le fichier
    f = fopen(filename, "r");
    if (f == NULL) {
        perror("Unable to open file");
        return;
    }

    // Debug: Afficher les termes de recherche
    g_print("Searching for: Reservation ID: %s, Parking ID: %s\n", 
            res_search ? res_search : "NULL", 
            park_search ? park_search : "NULL");

    // Lire et peupler le modèle
    while (fscanf(f, "%s %s %s %s %02d/%02d/%04d %d %d %d\n", 
                  b.u_id, b.p_id, b.res_id, b.ph_num,
                  &b.entry_date.dayb, &b.entry_date.monthb, &b.entry_date.yearb,
                  &b.duration, &b.security, &b.option) == 10) 
    {
        // Debug: Afficher chaque enregistrement lu
        g_print("Read: %s, %s, %s\n", b.res_id, b.p_id, b.ph_num);

        // Vérifier si les critères de recherche correspondent
        int match_res = (res_search && strstr(b.res_id, res_search)) != NULL;
        int match_park = (park_search && strstr(b.p_id, park_search)) != NULL;

        // Condition de recherche : correspondre si l'un ou l'autre des critères est trouvé
        if ((res_search && park_search && match_res && match_park) || 
            (res_search && !park_search && match_res) || 
            (!res_search && park_search && match_park))  {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, b.u_id,             // ID USER
                               1, b.p_id,             // ID PARKING
                               2, b.res_id,           // ID RESERVATION
                               3, b.ph_num,           // PHONE NUMBER
                               4, b.entry_date.dayb,   // DAY
                               5, b.entry_date.monthb, // MONTH
                               6, b.entry_date.yearb,  // YEAR
                               7, b.duration,         // DURATION
                               8, b.security,         // SECURITY
                               9, b.option,           // OPTION
                               -1);

            g_print("Match found: Reservation ID = %s, Parking ID = %s\n", b.res_id, b.p_id);
        }
    }

    fclose(f);

    // Assigner le modèle au GtkTreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);
}


void delete_entryb(const char *filename, const char *res_delete, const char *park_delete) {
    FILE *f, *temp;
    book b;
    int record_found = 0;

    // Ouvrir le fichier original pour lecture
    f = fopen(filename, "r");
    if (f == NULL) {
        perror("Impossible d'ouvrir le fichier pour lecture");
        return;
    }

    // Ouvrir un fichier temporaire pour écriture
    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Impossible d'ouvrir le fichier temporaire pour écriture");
        fclose(f);
        return;
    }

    // Debug: Afficher les IDs recherchés pour suppression
    g_print("Suppression des enregistrements avec: ID Réservation = %s, ID Parking = %s\n", 
            res_delete ? res_delete : "NULL", 
            park_delete ? park_delete : "NULL");

    // Lire du fichier original et écrire dans le fichier temporaire
    while (fscanf(f, "%s %s %s %s %02d/%02d/%04d %d %d %d\n", 
                  b.u_id, b.p_id, b.res_id, b.ph_num,
                  &b.entry_date.dayb, &b.entry_date.monthb, &b.entry_date.yearb,
                  &b.duration, &b.security, &b.option) == 10) 
    {
        // Vérifier si l'enregistrement actuel correspond aux critères de suppression
        int match_res = (res_delete && strstr(b.res_id, res_delete)) != NULL;
        int match_park = (park_delete && strstr(b.p_id, park_delete)) != NULL;

        // Supprimer si les deux critères correspondent
        if ((res_delete && park_delete && match_res && match_park) || 
            (res_delete && !park_delete && match_res) || 
            (!res_delete && park_delete && match_park)) 
        {
            record_found = 1; // Enregistrement trouvé pour suppression
            g_print("Suppression: ID Réservation = %s, ID Parking = %s\n", b.res_id, b.p_id);
            continue; // Passer à l'enregistrement suivant (ne pas l'écrire dans le fichier temporaire)
        }

        // Écrire l'enregistrement dans le fichier temporaire
        fprintf(temp, "%s %s %s %s %02d/%02d/%04d %d %d %d\n", 
                b.u_id, b.p_id, b.res_id, b.ph_num,
                b.entry_date.dayb, b.entry_date.monthb, b.entry_date.yearb,
                b.duration, b.security, b.option);
    }

    fclose(f);
    fclose(temp);

    // Remplacer le fichier original par le fichier mis à jour
    if (record_found) {
        if (remove(filename) == 0) {
            if (rename("temp.txt", filename) == 0) {
                g_print("Enregistrement(s) supprimé(s) avec succès.\n");
            } else {
                perror("Erreur lors du renommage du fichier temporaire");
            }
        } else {
            perror("Erreur lors de la suppression du fichier original");
        }
    } else {
        g_print("Aucun enregistrement correspondant trouvé pour suppression.\n");
        remove("temp.txt"); // Nettoyer le fichier temporaire
    }
}
void dis_park(GtkWidget *treeview, Parking parkings[], int nombre_parkings) {

    GtkCellRenderer *renderer;

    GtkTreeViewColumn *column;

    GtkTreeIter iter;

    GtkListStore *store;



    // Create the GtkListStore with the same structure

    store = gtk_list_store_new(10, 

                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,

                               G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, 

                               G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);



    // If the TreeView has no model, create columns

    if (gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)) == NULL) {

        const char *column_titles[] = {

            "Parking ID", "Parking Name", "Address", "Parking Type",

            "Ability", "Opening Hours", "Pricing", "Confirm", "Cancel", "Agent ID"

        };



        for (int i = 0; i < 10; i++) {

            renderer = gtk_cell_renderer_text_new();

            column = gtk_tree_view_column_new_with_attributes(column_titles[i], renderer, "text", i, NULL);

            gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        }

    }



    // Populate the store with the sorted parking data

    for (int i = 0; i < nombre_parkings; i++) {

        gtk_list_store_append(store, &iter);

        gtk_list_store_set(store, &iter,

                           0, parkings[i].parking_id,

                           1, parkings[i].parking_name,

                           2, parkings[i].address,

                           3, parkings[i].parking_type,

                           4, parkings[i].ability,

                           5, parkings[i].opening_hours,

                           6, parkings[i].pricing,

                           7, parkings[i].Confirm,

                           8, parkings[i].Cancel,

                           9, parkings[i].agent_id,

                           -1);

    }



    // Set the model and release the store

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    g_object_unref(store);

}

void charger_parkings(Parking parkings[], int *nombre_parkings) {
    FILE *file = fopen("parking.txt", "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier parking.txt\n");
        *nombre_parkings = 0;
        return;
    }

    int i = 0;
    while (fscanf(file, "%s %s %s %s %d %s %s %d %d %s",
                  parkings[i].parking_id,
                  parkings[i].parking_name,
                  parkings[i].address,
                  parkings[i].parking_type,
                  &parkings[i].ability,
                  parkings[i].opening_hours,
                  parkings[i].pricing,
                  &parkings[i].Confirm,
                  &parkings[i].Cancel,
                  parkings[i].agent_id) != EOF) {
       
        i++;
    }

    *nombre_parkings = i;
    fclose(file);

    // Sorting the parkings by ability in descending order
    for (int j = 0; j < *nombre_parkings - 1; j++) {
        for (int k = j + 1; k < *nombre_parkings; k++) {
            if (parkings[j].ability < parkings[k].ability) {
                
                Parking temp = parkings[j];
                parkings[j] = parkings[k];
                parkings[k] = temp;
            }
        }
    }

    // Optional: Debug print after sorting to confirm order
    printf("\nListe des parkings triés par capacité (décroissant) :\n");
    for (int m = 0; m < *nombre_parkings; m++) {
        printf("ID=%s, Nom=%s, Capacité=%d\n",
               parkings[m].parking_id,
               parkings[m].parking_name,
               parkings[m].ability);
    }
} 


void replace_last_parking_id_in_file(const char *filename, const char *new_p_id) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        perror("Error opening file");
        return;
    }

    char line[256];
    book b;
    long last_position = 0;

    // Traverse the file to find the last line
    while (fgets(line, sizeof(line), file)) {
        last_position = ftell(file); // Position after the last line read
    }

    rewind(file); // Go back to the start of the file

    // Rewrite the file with modification only on the last line
    while (fgets(line, sizeof(line), file)) {
        // Check if we are at the last line
        if (ftell(file) == last_position) {
            // Parse the last line
            sscanf(line, "%s %s %s %s %02d/%02d/%04d %d %d %d", 
                   b.u_id, b.p_id, b.res_id, b.ph_num, 
                   &b.entry_date.dayb, &b.entry_date.monthb, &b.entry_date.yearb, 
                   &b.duration, &b.security, &b.option);

            // Write the modified line with the new p_id
            fprintf(temp, "%s %s %s %s %02d/%02d/%04d %d %d %d\n", 
                    b.u_id, new_p_id, b.res_id, b.ph_num, 
                    b.entry_date.dayb, b.entry_date.monthb, b.entry_date.yearb, 
                    b.duration, b.security, b.option);
        } else {
            // Copy other lines without modification
            fprintf(temp, "%s", line);
        }
    }

    fclose(file);
    fclose(temp);

    // Replace the old file with the temporary file
    remove(filename);
    rename("temp.txt", filename);
}

int get_selected_parking_id(GtkWidget *treeview) {
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    int parking_id = -1; // Valeur par défaut si aucun parking n'est sélectionné

    // Récupérer la sélection dans le treeview
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gtk_tree_model_get(model, &iter, 0, &parking_id, -1); // Colonne 0 contient l'ID
    }

    return parking_id;
}

