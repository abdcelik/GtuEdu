#include <stdio.h>

#define ROW 8
#define COLUMN 14

typedef struct
{
    char content;
}pixel;

void fill_canvas(pixel[][COLUMN]);
void show_canvas(pixel[][COLUMN]);
void find_shape(pixel[][COLUMN],char*);
int strLen(const char*);

int main(void)
{
    pixel canvas[ROW][COLUMN];

    fill_canvas(canvas);
    show_canvas(canvas);
    find_shape(canvas,"-");

    return 0;
}

void fill_canvas(pixel canvas[][COLUMN])
{
    pixel temp[ROW][COLUMN] = {
        {{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'}},
        {{'.'},{'s'},{'s'},{'s'},{'s'},{'s'},{'s'},{'s'},{'s'},{'s'},{'s'},{'s'},{'s'},{'.'}},
        {{'.'},{'|'},{' '},{'-'},{'-'},{'-'},{' '},{' '},{'-'},{'-'},{'-'},{' '},{'|'},{'.'}},
        {{'.'},{'|'},{' '},{'('},{'-'},{')'},{' '},{' '},{'('},{'-'},{')'},{' '},{'|'},{'.'}},
        {{'.'},{'|'},{' '},{' '},{' '},{' '},{'/'},{'_'},{' '},{' '},{' '},{' '},{'|'},{'.'}},
        {{'.'},{'|'},{' '},{' '},{' '},{'_'},{'_'},{'_'},{'_'},{' '},{' '},{' '},{'|'},{'.'}},
        {{'.'},{'|'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'|'},{'.'}},
        {{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'},{'.'}}
    };

    for(int i=0 ; i < ROW ; ++i)
        for(int j=0 ; j < COLUMN ; ++j)
            canvas[i][j] = temp[i][j];
}

void show_canvas(pixel canvas[][COLUMN])
{
    for(int i=0 ; i < ROW ; ++i)
    {
        for(int j=0 ; j < COLUMN ; ++j)
            printf("%c",canvas[i][j].content);
        printf("\n");
    }
}

void find_shape(pixel canvas[][COLUMN], char* shape)
{
    int len = strLen(shape);
    int index=0;

    if(len == 0)
        return;

    for(int i=0 ; i < ROW ; ++i)
        for(int j=0 ; j < COLUMN ; ++j)
        {
            for(index=0 ; j < COLUMN && shape[index] == canvas[i][j].content && index < len; ++index,++j);
            
            if(index == len)
                printf("Row : %d Column : %d\n",i+1,j+1-len);
        }
}

int strLen(const char* str)
{
    int len=0;

    while(str[len])
        ++len;

    return len;
}