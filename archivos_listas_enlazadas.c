#include <stdio.h>
#include <stdlib.h>
#define EXIT 3
#define MAX_NAME 30
#define LOAD 1
#define SHOW 2

typedef struct video_cards{
    char Name[MAX_NAME];
    int Cuda_Cores;
    float Freq;
    int Vram;
    struct video_cards *next;
}video_cards_t;

video_cards_t *nvda_cards = NULL;


void print_card(video_cards_t card){
    printf("Name: %s\n", card.Name);
    printf("Cuda_Cores: %d\n", card.Cuda_Cores);
    printf("Max_Frequency in MHz: %f\n", card.Freq);
    printf("Vram: %d\n", card.Vram);

    printf("************************\n");
}


void show_list(){
    video_cards_t *list = nvda_cards;

    while(list != NULL){
        print_card(*list);
        list = list->next;
    }
}


void save_card(video_cards_t *card){
    FILE *f;
    f = fopen("List.txt", "a+");

    fprintf(f, "Name: %s", card->Name);
    fprintf(f, "\nCuda Cores: %d", card->Cuda_Cores);
    fprintf(f, "\nMax_Frequency: %f", card->Freq);
    fprintf(f, "\nVram: %d\n\n********************************\n", card->Vram);
    fclose(f);
}


void get_data(video_cards_t *card){
    printf("Enter card's name:\n");
    scanf("%s", card->Name);

    printf("Enter cuda cores:\n");
    scanf("%i", &(card->Cuda_Cores));

    printf("Enter frequency:\n");
    scanf("%f", &(card->Freq));
    
    printf("Enter Vram:\n");
    scanf("%i", &(card->Vram));
}


void load_card(){
    video_cards_t *card_aux;
    card_aux = malloc(sizeof(video_cards_t));

    if(card_aux==NULL){
        printf("Out of memory\n");
    }
    else{
        get_data(card_aux);
        save_card(card_aux);
        card_aux->next=nvda_cards;
        nvda_cards=card_aux;
    }
}


void free_memory(){
    video_cards_t *aux = NULL;

    while(nvda_cards!=NULL){
        aux = nvda_cards;
        nvda_cards = nvda_cards->next;
        free(aux);
    }
}


void main(){
    int option;
    do{
        printf("1_Load a new graphics card\n");
        printf("2_Show all graphic cards\n");
        printf("3_Exit\n");

        scanf("%d",&option);
        if(option == LOAD){
            load_card();
        }
        if(option == SHOW)show_list();

    }while(option != EXIT);
    free_memory();
}
