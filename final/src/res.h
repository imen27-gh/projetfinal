#ifndef RES_H_INCLUDED
#define RES_H_INCLUDED
#include "parkingmanagment.h"
typedef struct {
    int dayb;
    int monthb;
    int yearb;
}date; 
typedef struct {
    char u_id[50];  
    char p_id[50];   
    char res_id[50];    
    char ph_num[50];
    date entry_date ;         
    int duration ;
    int security;
    int option;    
       
} book;
typedef enum {
    U_ID,
    RES_ID,
    P_ID,
    PH_NUM,
    OTHER
} champ_type; 

void delete_entryb(const char *filename, const char *res_delete, const char *park_delete);
void search_res2(GtkWidget *treeview, const char *filename, const char *res_search, const char *park_search) ;
void show_res(GtkWidget *res);
void dis_park(GtkWidget *treeview, Parking parkings[], int nombre_parkings);

int add_res(const char *filename, book b);
int modify_res(const char *filename, const char *res_id, book nouv);
int Deleteb(const char *filename, const char *res_id);
book searchb(const char *filename, const char *res_id, const char *p_id);
int controle_saisieb(const char *data, champ_type type);
int validate_booking_details(const char *user_id, const char *res_id, const char *p_id, const char *ph_num);
void charger_parkings(Parking parkings[], int *nombre_parkings);
int get_selected_parking_id(GtkWidget *treeview);
void replace_last_parking_id_in_file(const char *filename, const char *new_p_id);

#endif 
