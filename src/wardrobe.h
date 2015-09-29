#ifndef WARDROBE_H_INCLUDED
#define WARDROBE_H_INCLUDED

//clothes
typedef struct{
    int id;
    char* name;

} clothe;

void initData();
void deleteData();
void addData();

void loadData();
void parseRFIDString();
void displayData();

size_t findIndexById(int);

clothe findClotheById(int);

#endif // WARDROBE_H_INCLUDED
