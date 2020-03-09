#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true}bool;

typedef struct
{
    int* arr;
    int capacity;
    int used;
}Dyn_arr;

Dyn_arr* init(Dyn_arr*);
bool insert(Dyn_arr*,int,int);
bool delete(Dyn_arr*,int);
void printDynArr(Dyn_arr*);
void freeDynArr(Dyn_arr*);
int getInt(const char*);

int main(void)
{
    Dyn_arr *arr = init(arr);
    int var=0,var2=0;
    bool exit = false;

    while(!exit)
    {
        var = getInt("User Input Value : ");

        if(var >= 0)
        {
            var2 = getInt("User Insertion Index : ");
            insert(arr,var2,var);
        }
        else if(var == -1)
        {
            var2 = getInt("User Input Index : ");
            delete(arr,var2);
        }
        else
            exit = true;

        printDynArr(arr);
    }

    freeDynArr(arr);

    return 0;
}

Dyn_arr* init(Dyn_arr* arr)
{
    if(arr == NULL)
        arr = (Dyn_arr*)calloc(1,sizeof(Dyn_arr));

    arr->capacity = 5;
    arr->used = 0;
    
    if(arr->arr != NULL)
        free(arr->arr);

    arr->arr = (int*)calloc(arr->capacity,sizeof(int));
}

bool insert(Dyn_arr* arr, int insertion_index, int input_value)
{
    if(arr == NULL)
        return false;
    if(insertion_index < 0 || insertion_index > arr->used)
        return false;
    
    if(arr->used ==  arr->capacity)
    {
        arr->capacity += 5;

        int* temp = (int*)calloc(arr->capacity,sizeof(int));

        for(int i=0 ; i < arr->used ; ++i)
            temp[i] = arr->arr[i];
        
        free(arr->arr);
        arr->arr = temp;
    }

    for(int i = arr->used-1 ; i >= insertion_index ; --i)
        arr->arr[i+1] = arr->arr[i];

    arr->arr[insertion_index] = input_value;
    arr->used++;

    return true;
}

bool delete(Dyn_arr* arr, int deletion_index)
{
    if(arr == NULL)
        return false;
    if(deletion_index < 0 || deletion_index >= arr->used)
        return false;
    
    for(int i = deletion_index + 1 ; i < arr->used ; ++i)
        arr->arr[i-1] = arr->arr[i];
    
    arr->used--;
    arr->arr[arr->used] = 0;

    return true;
}

void printDynArr(Dyn_arr* arr)
{
    if(arr == NULL)
        return;

    printf("Used : %d\nCapacity : %d\n",arr->used,arr->capacity);

    for(int i=0 ; i < arr->used ; ++i)
        printf("%d ",arr->arr[i]);
    printf("\n");
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}

void freeDynArr(Dyn_arr* arr)
{
    if(arr != NULL)
    {
        if(arr->arr != NULL)
            free(arr->arr);
        free(arr);
    }
}