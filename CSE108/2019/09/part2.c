#include <stdio.h>

struct CN
{
    int real;
    int imaginary;
};

struct CN add_complex(struct CN,struct CN);
struct CN sub_complex(struct CN,struct CN);
struct CN getComplexNumber(const char*);

int main(void)
{
    struct CN complex1 = getComplexNumber("Enter 1st complex number : ");
    struct CN complex2 = getComplexNumber("Enter 2st complex number : ");
    struct CN complex;

    complex = add_complex(complex1,complex2);
    printf("Addition : %d%+di\n",complex.real,complex.imaginary);

    complex = sub_complex(complex1,complex2);
    printf("Substraction : %d%+di\n",complex.real,complex.imaginary);

    return 0;
}

struct CN add_complex(struct CN a, struct CN b)
{
    struct CN var = {a.real + b.real , a.imaginary + b.imaginary};
    return var;
}

struct CN sub_complex(struct CN a, struct CN b)
{
    struct CN var = {a.real - b.real , a.imaginary - b.imaginary};
    return var;   
}

struct CN getComplexNumber(const char* text)
{
    struct CN var;

    printf("%s",text);
    scanf("%d%d",&var.real,&var.imaginary);

    return var;
}