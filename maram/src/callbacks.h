#include <gtk/gtk.h>


void
on_radiobutton_hom_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_fem_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_add_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton_confaj_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_mod_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton_confmod_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_hommod_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_femmod_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_supp_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview3_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_aff_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview4_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_rech_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_calucler_facture_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_searchid_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_calucler_facture_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_display_clicked                     (GtkButton       *button,
                                        gpointer         user_data);
