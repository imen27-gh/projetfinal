#include <gtk/gtk.h>


void
on_displaycrud_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_deletecrud_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_modifycrud_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_addcrud_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_medb_toggled                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_lowb_toggled                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_addb_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_highb_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_addp_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkidres_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkidpark_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_searsh_clicked                      (GtkButton       *button,
                                        gpointer         user_data);

void
on_deleteDis_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_highm_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_medm_toggled                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_lowm_toggled                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_modify_clicked                      (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview2_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_show_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_refresh_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);
