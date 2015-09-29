#include "wardrobe.h"

clothe clothesDataBase*;
size_t clothesDataBaseSize;
void initData()
{
    clotheDataBase = (clothe*)malloc(sizeof(clothe)*100);
    clothesDataBaseSize = 0;
}
void deleteData()
{
    free(clotheDataBase);
}
void addData()
{

}


void loadData();
void parseRFIDString();
void displayData();

clothe findClotheById(int id);
{
    size_t buf = findIndexById(id);
    if(buf == -1)
        return NULL;
    else
        return clothesDataBaseSize[buf];
}

size_t findIndexById(int id);
{
    size_t left = 0,right = clothesDataBaseSize-1;
    while(left != right)
    {
        middle = (left+right)/2;
        if(clothesDataBase[middle].id == id)
        {
            return middle;
        }
        else if(clothesDataBase[middle].id > id)
        {
            right = middle;
        }
        else
        {
            left = middle;
        }
    }
    return -1;
}
