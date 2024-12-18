#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "res.h"
#include <stdbool.h>
#include "parkingmanagment.h"



void on_addb_clicked(GtkButton *button, gpointer user_data)
{

    // Initialiser la structure de réservation
    book b;
    date d;

    // Récupérer les widgets de l'interface utilisateur
    GtkWidget *user_id = lookup_widget(GTK_WIDGET(button), "imen1");
    GtkWidget *id_reservation = lookup_widget(GTK_WIDGET(button), "imen2");
    GtkWidget *parking_id = lookup_widget(GTK_WIDGET(button), "imen3");
    GtkWidget *phone_number = lookup_widget(GTK_WIDGET(button), "imen4");
    GtkWidget *day = lookup_widget(GTK_WIDGET(button), "sdb"); 
    GtkWidget *month = lookup_widget(GTK_WIDGET(button), "smb");
    GtkWidget *year = lookup_widget(GTK_WIDGET(button), "syb");
    GtkWidget *duration = lookup_widget(GTK_WIDGET(button), "sdurb");
    GtkWidget *combo = lookup_widget(GTK_WIDGET(button), "combo1");
    GtkWidget *label_error = lookup_widget(GTK_WIDGET(button), "labelerror");
    GtkWidget *radiobutton1 = lookup_widget(GTK_WIDGET(button), "highb"); // High
    GtkWidget *radiobutton2 = lookup_widget(GTK_WIDGET(button), "medb"); // Medium
    GtkWidget *radiobutton3 = lookup_widget(GTK_WIDGET(button), "lowb"); // Low  

    b.entry_date.dayb = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(day));
    b.entry_date.monthb = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(month));
    b.entry_date.yearb = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(year));
    b.duration = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(duration));

    // Vérification des widgets
    g_assert(GTK_IS_ENTRY(user_id));
    g_assert(GTK_IS_ENTRY(id_reservation));
    g_assert(GTK_IS_ENTRY(parking_id));
    g_assert(GTK_IS_ENTRY(phone_number));

    // Récupérer les valeurs des entrées utilisateur
    const char *user_id_text = gtk_entry_get_text(GTK_ENTRY(user_id));
    const char *id_reservation_text = gtk_entry_get_text(GTK_ENTRY(id_reservation));
    const char *parking_id_text = gtk_entry_get_text(GTK_ENTRY(parking_id));
    const char *phone_number_text = gtk_entry_get_text(GTK_ENTRY(phone_number));

    // Vérification des champs vides et validation des saisies
    if (controle_saisieb(user_id_text, U_ID) == 0 ||
        controle_saisieb(id_reservation_text, RES_ID) == 0 ||
        controle_saisieb(parking_id_text, P_ID) == 0 ||
        controle_saisieb(phone_number_text, PH_NUM) == 0) {
        gtk_label_set_text(GTK_LABEL(label_error), "Erreur: tous les champs doivent être remplis et valides.");
        return;
    }

    // Récupérer les valeurs dans la structure book
    strcpy(b.u_id, user_id_text);
    strcpy(b.res_id, id_reservation_text);
    strcpy(b.p_id, parking_id_text);
    strcpy(b.ph_num, phone_number_text);
if (!validate_booking_details(user_id_text, id_reservation_text, parking_id_text, phone_number_text)) {
    gtk_label_set_text(GTK_LABEL(label_error), "Erreur: tous les champs doivent être remplis et valides.");
    return; // Sortir si la validation échoue
}


   // Récupérer la sélection de l'option du combo box
    const gchar *combo_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));
    if (combo_text != NULL) {
        if (strcmp(combo_text, "Option 1") == 0) {
            b.option = 1;
        } else if (strcmp(combo_text, "Option 2") == 0) {
            b.option = 2;
        } else {
            b.option = 0; // Valeur par défaut ou erreur
        }
    }

    // Vérification de l'état des boutons radio
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton1))) {
        b.security = 1; // High
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton2))) {
         b.security = 2; // Low
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton3))) {
        b.security = 3; // Medium
    } else {
        b.security = 0; // Valeur par défaut ou erreur
    }

    if (add_res("reservation.txt", b)) {
        gtk_label_set_text(GTK_LABEL(label_error), "Réservation ajoutée avec succès.");
    } else {
        gtk_label_set_text(GTK_LABEL(label_error), "Erreur lors de l'ajout de la réservation.");
    }

    // Nettoyer les champs après ajout
    gtk_entry_set_text(GTK_ENTRY(user_id), "");
    gtk_entry_set_text(GTK_ENTRY(id_reservation), "");
    gtk_entry_set_text(GTK_ENTRY(parking_id), "");
    gtk_entry_set_text(GTK_ENTRY(phone_number), "");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton1), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton2), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton3), FALSE);
}





void
on_searsh_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *reservation_check = lookup_widget(GTK_WIDGET(button), "checkidres");
    GtkWidget *parking_check = lookup_widget(GTK_WIDGET(button), "checkidpark");
    GtkWidget *search_entry = lookup_widget(GTK_WIDGET(button), "imen5");   // Reservation ID
    GtkWidget *search_entry2 = lookup_widget(GTK_WIDGET(button), "imen6");  // Parking ID
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview2");
    GtkWidget *label_error = lookup_widget(GTK_WIDGET(button), "labelerror2");

    // Ensure widgets are valid
    if (!reservation_check || !parking_check || !search_entry || !search_entry2 || !treeview || !label_error) {
        g_print("Error: One or more widgets not found.\n");
        return;
    }

    // Get the state of check buttons
    gboolean reservation_checked = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(reservation_check));
    gboolean parking_checked = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(parking_check));

    // Get search terms
    const char *reservation_term = gtk_entry_get_text(GTK_ENTRY(search_entry));
    const char *parking_term = gtk_entry_get_text(GTK_ENTRY(search_entry2));

    if (!reservation_checked && !parking_checked) {
        gtk_label_set_text(GTK_LABEL(label_error), "Please select at least one search criterion.");
        return;
    }

    if (reservation_checked && (!reservation_term || strlen(reservation_term) == 0)) {
        gtk_label_set_text(GTK_LABEL(label_error), "Please enter a Reservation ID.");
        return;
    }

    if (parking_checked && (!parking_term || strlen(parking_term) == 0)) {
        gtk_label_set_text(GTK_LABEL(label_error), "Please enter a Parking ID.");
        return;
    }

    // Display all reservations before filtering
    show_res(treeview);

    // Call the search function
    const char *filename = "reservation.txt";
    search_res2(treeview, filename,
                reservation_checked ? reservation_term : NULL,
                parking_checked ? parking_term : NULL);
}

void
on_deleteDis_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *reservation_check = lookup_widget(GTK_WIDGET(button), "checkidres");
    GtkWidget *parking_check = lookup_widget(GTK_WIDGET(button), "checkidpark");
    GtkWidget *delete_entry_res = lookup_widget(GTK_WIDGET(button), "imen5");   // Reservation ID
    GtkWidget *delete_entry_park = lookup_widget(GTK_WIDGET(button), "imen6");  // Parking ID
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview2");
    GtkWidget *label_error = lookup_widget(GTK_WIDGET(button), "labelerror2");

    // Ensure widgets are valid
    if (!reservation_check || !parking_check || !delete_entry_res || !delete_entry_park || !treeview || !label_error) {
        g_print("Error: One or more widgets not found.\n");
        return;
    }

    // Get the state of check buttons
    gboolean reservation_checked = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(reservation_check));
    gboolean parking_checked = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(parking_check));

    // Get delete terms
    const char *reservation_term = gtk_entry_get_text(GTK_ENTRY(delete_entry_res));
    const char *parking_term = gtk_entry_get_text(GTK_ENTRY(delete_entry_park));

    if (!reservation_checked && !parking_checked) {
        gtk_label_set_text(GTK_LABEL(label_error), "Please select at least one deletion criterion.");
        return;
    }

    if (reservation_checked && (!reservation_term || strlen(reservation_term) == 0)) {
        gtk_label_set_text(GTK_LABEL(label_error), "Please enter a Reservation ID.");
        return;
    }

    if (parking_checked && (!parking_term || strlen(parking_term) == 0)) {
        gtk_label_set_text(GTK_LABEL(label_error), "Please enter a Parking ID.");
        return;
    }

    // Call the delete function
    const char *filename = "reservation.txt";
    delete_entryb(filename,
                 reservation_checked ? reservation_term : NULL,
                 parking_checked ? parking_term : NULL);

    // Update the treeview to reflect the changes
    show_res(treeview);
}



 void
on_modify_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
    book nouv;  // Define the structure to hold the updated reservation
    GtkWidget *user_id = lookup_widget(GTK_WIDGET(button), "imen7");
    GtkWidget *id_reservation = lookup_widget(GTK_WIDGET(button), "imen8");
    GtkWidget *parking_id = lookup_widget(GTK_WIDGET(button), "imen9");
    GtkWidget *phone_number = lookup_widget(GTK_WIDGET(button), "imen10");
    GtkWidget *day = lookup_widget(GTK_WIDGET(button), "sdm");
    GtkWidget *month = lookup_widget(GTK_WIDGET(button), "smm");
    GtkWidget *year = lookup_widget(GTK_WIDGET(button), "sym");
    GtkWidget *duration = lookup_widget(GTK_WIDGET(button), "sdurm");
    GtkWidget *combo = lookup_widget(GTK_WIDGET(button), "combo2");
    GtkWidget *label_error = lookup_widget(GTK_WIDGET(button), "labelerror3");
    GtkWidget *radiobutton1 = lookup_widget(GTK_WIDGET(button), "highm"); // High
    GtkWidget *radiobutton2 = lookup_widget(GTK_WIDGET(button), "medm");  // Medium
    GtkWidget *radiobutton3 = lookup_widget(GTK_WIDGET(button), "lowm");  // Low

    // Get the date values
    nouv.entry_date.dayb = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(day));
    nouv.entry_date.monthb = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(month));
    nouv.entry_date.yearb = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(year));
    nouv.duration = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(duration));

    // Retrieve the text from entry fields
    const char *user_id_text = gtk_entry_get_text(GTK_ENTRY(user_id));
    const char *id_reservation_text = gtk_entry_get_text(GTK_ENTRY(id_reservation));
    const char *parking_id_text = gtk_entry_get_text(GTK_ENTRY(parking_id));
    const char *phone_number_text = gtk_entry_get_text(GTK_ENTRY(phone_number));

    // Validate input fields using validate_booking_details function
    if (!validate_booking_details(user_id_text, id_reservation_text, parking_id_text, phone_number_text)) {
        gtk_label_set_text(GTK_LABEL(label_error), "Erreur: tous les champs doivent être remplis et valides.");
        return;
    }

    // Validate individual fields using controle_saisieb (optional)
    if (controle_saisieb(user_id_text, U_ID) == 0 ||
        controle_saisieb(id_reservation_text, RES_ID) == 0 ||
        controle_saisieb(parking_id_text, P_ID) == 0 ||
        controle_saisieb(phone_number_text, PH_NUM) == 0) {
        gtk_label_set_text(GTK_LABEL(label_error), "Erreur: certains champs ne sont pas valides.");
        return;
    }

    // Assign values to the structure
    strcpy(nouv.u_id, user_id_text);
    strcpy(nouv.res_id, id_reservation_text);
    strcpy(nouv.p_id, parking_id_text);
    strcpy(nouv.ph_num, phone_number_text);

    // Retrieve the combo box option
    const gchar *combo_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo));
    if (combo_text != NULL) {
        if (strcmp(combo_text, "by card") == 0) {
            nouv.option = 1;
        } else if (strcmp(combo_text, "cash") == 0) {
            nouv.option = 2;
        } else {
            nouv.option = 0; // Default value
        }
    }

    // Vérification de l'état des boutons radio
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton1))) {
        nouv.security = 1; // High
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton2))) {
         nouv.security = 2; // Low
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton3))) {
        nouv.security = 3; // Medium
    } else {
        nouv.security = 0; // Valeur par défaut ou erreur
    }

    // Call the modify function
    if (modify_res("reservation.txt", nouv.res_id, nouv)) {
        gtk_label_set_text(GTK_LABEL(label_error), "Réservation modifiée avec succès.");

        // Clear the fields after successful modification
        gtk_entry_set_text(GTK_ENTRY(user_id), "");
        gtk_entry_set_text(GTK_ENTRY(id_reservation), "");
        gtk_entry_set_text(GTK_ENTRY(parking_id), "");
        gtk_entry_set_text(GTK_ENTRY(phone_number), "");
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton1), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton2), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton3), FALSE);
    } else {
        gtk_label_set_text(GTK_LABEL(label_error), "Erreur lors de la modification de la réservation.");
    }
}





void
on_show_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
 {

    // Lookup widgets

    GtkWidget *label_error = lookup_widget(GTK_WIDGET(button), "labelerror1");

    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview1");



    if (label_error == NULL || treeview == NULL) {

        gtk_label_set_text(GTK_LABEL(label_error), "Error: Widget not found");

        return;

    }



    // Declare a Parking array

    Parking parkings[100]; // Maximum parking capacity

    int nombre_parkings = 0;



    // Load and sort the parking data

    charger_parkings(parkings, &nombre_parkings);



    // Check if parkings were loaded

    if (nombre_parkings == 0) {

        gtk_label_set_text(GTK_LABEL(label_error), "No parkings found.");

        return;

    }



    // Display the data using dis_park

    dis_park(treeview, parkings, nombre_parkings);



    // Success message

    gtk_label_set_text(GTK_LABEL(label_error), "Parkings loaded successfully.");

}






void
on_refresh_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
  // Lookup the widgets
    GtkWidget *label_error = lookup_widget(GTK_WIDGET(button), "labelerror2");
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview2");
    const char *filename = "reservation.txt";

    // Error handling for widget lookup
    if (label_error == NULL || treeview == NULL) {
        gtk_label_set_text(GTK_LABEL(label_error), "Error: Widget not found");
        return; // Exit the function if widgets are not found
    }

    // Open the reservation file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        gtk_label_set_text(GTK_LABEL(label_error), "Error: Could not open file");
        return; // Exit if file cannot be opened
    }

    // Buffer to hold each line of the file
    char line[256];
    char all_data[1024] = ""; // To accumulate data for the treeview

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character, if present
        line[strcspn(line, "\n")] = 0;

        // Accumulate data to show in the treeview
        strcat(all_data, line);
        strcat(all_data, "\n"); // Add newline for separation
    }

    fclose(file); // Close the file after reading

    // If there's no data, display a message
    if (strlen(all_data) == 0) {
        gtk_label_set_text(GTK_LABEL(label_error), "No reservations found.");
        return;
    }

    // Call function to populate the treeview with the read data
    show_res(treeview);


}


void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
 GtkWidget *label_error = lookup_widget(GTK_WIDGET(treeview), "labelerror1");

// Récupérer l'ID du parking sélectionné depuis le treeview
    int selected_parking_id = get_selected_parking_id(GTK_WIDGET(treeview));

    if (selected_parking_id != -1) {
        const char *filename = "reservation.txt";
        char new_p_id[50];
        snprintf(new_p_id, sizeof(new_p_id), "%d", selected_parking_id); // Convertir l'ID en chaîne
FILE *parking_file = fopen("parking.txt", "r");

if (parking_file) {
    fscanf(parking_file, "%s", new_p_id);
    fclose(parking_file);
}

        // Appeler la fonction pour remplacer le p_id dans la dernière ligne
        replace_last_parking_id_in_file(filename, new_p_id);

        // Afficher un message de succès dans la console
        gtk_label_set_text(GTK_LABEL(label_error),"Le p_id de la dernière ligne a été remplacé par ");
    } else {
        // Afficher un message d'erreur
        gtk_label_set_text(GTK_LABEL(label_error),"Erreur : Aucun parking sélectionné.\n");
    }
}

