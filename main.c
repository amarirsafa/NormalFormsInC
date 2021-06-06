#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define X 30

int main()
{
    //-------------Testing functions area-------
//    char string01[10],string02[10];
//    printf("give me strings: ");
//    fseek(stdin,0,SEEK_END);
//    scanf("%s",string01);
//    fseek(stdin,0,SEEK_END);
//    scanf("%s",string02);
//    int d=COMPARE_Two_Strings02(string01,string02);
//    printf("%d",d);
//    system("pause");
    //-----------------------------------------
    int Number_Att,Number_FD,i,j,s,y,Value=0,Number_Keys=0,Min=0,Second_NF,Number_Of_DF_2FN=0,Number_FD3=0;
    //---------------Realtion-----------//
    printf("Would you please give me number of atributs: ");
    scanf("%d",&Number_Att);
    char *Relation=(char*)calloc(X,sizeof(char));
    Fill_In_Relation(Number_Att,Relation);

    //------------les dep-fontionel------------//
    printf("How many functional dependencies do you have?:\n");
    scanf("%d",&Number_FD);
    FD *Functional_Dep = (FD*) calloc( Number_FD,sizeof(FD) );
    FD *Functional_Dep3 = (FD*) calloc( Number_FD,sizeof(FD) );
    printf("would you please give me Functional dependencies: \n");
    Fill_In_FD(Number_FD,Functional_Dep);

    //----------------affichage DF--------------//
    system("cls");
    affichage_Relation(Number_Att,Relation);
    affichage_DF(Functional_Dep,Number_FD);

    //----------------Allocation--------------------------------------------------------------------------------------//
    char *Part_Of_Key=(char*)malloc((Number_Att+1)*sizeof(char));
    Part_Of_Key[Number_Att+1]='\0';
    char* Fermeture=(char*)calloc(X,sizeof(char));
    char* TEMP = (char*)calloc(X,sizeof(char));
    char* TEMP01=(char*)calloc(X,sizeof(char));
    char* Relation_Rest =(char*)calloc(X,sizeof(char));
    char** Store_Keys=(char**)calloc(100,sizeof(char));
    for(i=0; i<20; i++)
    {
        Store_Keys[i]=(char*)calloc(100,sizeof(char));
    }
    char** Relations_After_Decomp=(char**)calloc(100,sizeof(char));
    for(i=0; i<20; i++)
    {
        Relations_After_Decomp[i]=(char*)calloc(100,sizeof(char));
    }
    //__________________________________________END of allocation------------------------------------------
    Part_Of_Key=Search_Non_Definded_attributs01(Number_FD,Functional_Dep,Relation,Number_Att);
    if (Part_Of_Key[0] == '\0')
    {
        In_Case_Part_Of_Key_Is_Null(Number_FD,Functional_Dep,TEMP01,Number_Att,Relation,Store_Keys,&Number_Keys,Part_Of_Key,&Min);

    }
    else
    {
        Part_Of_Key=Search_Non_Definded_attributs01(Number_FD,Functional_Dep,Relation,Number_Att);
        But_First(Part_Of_Key,TEMP01,Number_FD,Functional_Dep,Number_Att,Relation,TEMP,Fermeture,Store_Keys,&Value,&Number_Keys);
        Correct_Key(&Number_Keys,Store_Keys);
        printf(" ____Keys Are: ");
        for(i=0; i<Number_Keys; i++)
        {
            printf("{%s}",Store_Keys[i]);
        }
    }

    printf("\nThese are the FDs which violate BCNF:");
    for(i=0;i<Number_FD;i++)
    {
        int H=0;
        for(j=0;j<Number_Keys;j++)
        {
            if(COMPARE_Two_Strings01(Functional_Dep[i].Left_part,Store_Keys[j]))
            {
                H++;
            }
        }
        if(!H )
        {
            printf("\n\t(%d)%s ---> %s",Number_FD3,Functional_Dep[i].Left_part,Functional_Dep[i].Right_part);
            //printf("\n%d  %d ",WTVR,Woa);
            for(s=0;s<strlen(Functional_Dep[i].Left_part);s++)
            {
                Functional_Dep3[Number_FD3].Left_part[s] = Functional_Dep[i].Left_part[s];
            }
            for(s=0;s<strlen(Functional_Dep[i].Right_part);s++)
            {
                Functional_Dep3[Number_FD3].Right_part[s] = Functional_Dep[i].Right_part[s];
            }
            Number_FD3++;
        }
    }
    Concatenate_Two_Strings(Relation_Rest,Relation);
    int size=strlen(Relation_Rest),k;
    for(i=0;i<Number_FD3;i++)
    {
        int WTVR = strlen(Functional_Dep3[i].Left_part)+strlen(Functional_Dep3[i].Right_part);
        int Whoa = strlen(Functional_Dep3[i].Left_part);
        for(s=0;s<Whoa;s++)
        {
            Relations_After_Decomp[i][s]=Functional_Dep3[i].Left_part[s];
        }
        Concatenate_Two_Strings(Relations_After_Decomp[i],Functional_Dep3[i].Right_part);
        printf("\nThe relation: %s",Relations_After_Decomp[i]);
        if(COMPARE_Two_Strings(Relation_Rest,Functional_Dep3[i].Left_part))
        {
            //printf("\nOkay bitch");
            for(s=0;s<strlen(Relation_Rest);s++)
            {
                for(y=0;y<strlen(Functional_Dep3[i].Right_part);y++)
                {
                    if(Relation_Rest[s]==Functional_Dep3[i].Right_part[y])
                    {
                            Relation_Rest[s]=Relation_Rest[s+1];
                    }
                }
            }
        }
        for (s = 0; s < size; s++)
        {
          for (j = s + 1; j < size;)
          {
             if (Relation_Rest[j] == Relation_Rest[s])
             {
                for (k = j; k < size; k++)
                {
                   Relation_Rest[k] = Relation_Rest[k + 1];
                }
                size--;
             }else
                j++;
          }
        }
        printf("\nThe rest is: %s",Relation_Rest);
        if(!COMPARE_Two_Strings(Relation_Rest,Functional_Dep3[i].Left_part) )
        {

        }
    }

    free(Relations_After_Decomp);
    free(Store_Keys);
    free(TEMP01);
    free(TEMP);
    free(Fermeture);
    free(Part_Of_Key);
    free(Functional_Dep3);
    free(Functional_Dep);
    free(Relation);
    return 0;
}
