#include <stdio.h>

#define SIZE 4

typedef struct
{
    char name[20];
    char species[20];
    int length;
    int weight;
    char naturalHabitat[20];
}Animal;

void fill_struct_array(Animal[]);
void length_info(Animal[],int*,int*,double*);
void filter_mammals(Animal[],Animal[]);
void change_weight(Animal*);
void print_animals(Animal[]);
void fill(Animal*,char*,char*,int,int,char*);
int getInt(const char*);
void strCpy(char*,char*);
int strCmp(char*,char*);

int main(void)
{
    Animal animal[SIZE];
    Animal filtered_animals[SIZE];
    int min=0,max=0;
    double average=0.;

    fill_struct_array(animal);
    length_info(animal,&max,&min,&average);
    filter_mammals(animal,filtered_animals);
    print_animals(animal);
    change_weight(&animal[0]);

    printf("Min : %d Max : %d Ave : %.2lf\n",min,max,average);
    print_animals(animal);
    print_animals(filtered_animals);
    return 0;
}

void fill_struct_array(Animal table[])
{
    fill(&table[0],"Lion","Mammals",200,130,"Savannah");
    fill(&table[1],"Dolphin","Mammals",300,180,"Oceans");
    fill(&table[2],"Shark","Fish",450,250,"Oceans");
    fill(&table[3],"Wolf","Mammals",160,60,"Forest");
}

void fill(Animal* animal, char* name, char* species, int length, int weight, char* naturalHabitat)
{
    strCpy(animal->name,name);
    strCpy(animal->species,species);
    strCpy(animal->naturalHabitat,naturalHabitat);
    animal->length = length;
    animal->weight = weight;
}

void length_info(Animal table[], int* max, int* min, double* average)
{
    *max = *min = table[0].length;

    for(int i=0 ; i < SIZE ; ++i)
    {
        if(table[i].length > *max)
            *max = table[i].length;
        if(table[i].length < *min)
            *min = table[i].length;

        *average += table[i].length;
    }

    *average /= SIZE;
}

void filter_mammals(Animal table[], Animal filtered_animals[])
{
    int index=0;

    for(int i=0 ; i < SIZE ; ++i)
        if(strCmp(table[i].species,"Mammals") == 0 && table[i].weight > 100 && strCmp(table[i].naturalHabitat,"Oceans") != 0)
            filtered_animals[index++] = table[i];
    
    for(int i = index ; i < SIZE ; ++i)
        filtered_animals[i].length = -1;
}

void change_weight(Animal* animal_to_change)
{
    int weight=0;

    printf("Current weight : %d\n",animal_to_change->weight);

    weight = getInt("Weight : ");
    animal_to_change->weight = weight;
}

void print_animals(Animal table[])
{
    for(int i=0 ; i < SIZE ; ++i)
        if(table[i].length != -1)
            printf("Name : %s\nSpecies : %s\nLenght(cm) : %d\nWeight(kg) : %d\nNatural Habitat : %s\n",table[i].name,table[i].species,table[i].length,table[i].weight,table[i].naturalHabitat);
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}

void strCpy(char* s1, char* s2)
{
    while(*s1++ = *s2++);
}

int strCmp(char* s1, char* s2)
{
    while(*s1 && *s2 && *s1 == *s2)
        ++s1,++s2;
    return *s1 - *s2;
}