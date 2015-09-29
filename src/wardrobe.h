#ifndef WARDROBE_H_INCLUDED
#define WARDROBE_H_INCLUDED

//clothes
typedef struct{
    int id;
    char* name;

} Clothe;

void initData();
void deleteData();
void addData();

void loadData();
void parseRFIDString();
void displayData(Clothe);

size_t findIndexById(int);

Clothe findClotheById(int);

#endif // WARDROBE_H_INCLUDED
