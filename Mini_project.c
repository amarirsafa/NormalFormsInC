#include "header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Fill_In_Relation(int Number_Att,char *Relation)//this relation is used to fill in the Relation
{
    int i,c;
    //fseek(stdin,0,SEEK_END);
    for(i=0; i<Number_Att; i++)
    {
        c=i+1;
        fseek(stdin,0,SEEK_END);
        printf("Give me attribut number %d : ",c);
        Relation[i]=getchar();
    }
}
//---------------------------------------------------------------------------------------------------------------
void Fill_In_FD(int Number_FD,FD *Functional_Dep)//this function is used to get the functional dependencies from the user
{
    int i;
    for(i=0; i<Number_FD; i++)
    {
        printf("Give me attributs of the left part for the FD number %d : ",i+1);
        scanf("%s", Functional_Dep[i].Left_part);
        printf("---->");
        scanf("%s", Functional_Dep[i].Right_part);
    }
}
//-----------------------------------------------------------------------------------------------------------------
void affichage_Relation(int Number_Att,char *Relation)
{
    int i;
    printf("\nYour relation : R(");
    for(i=0; i<(Number_Att-1);i++)
    {
        printf("%c,",Relation[i]);
    }
    printf("%c)\n\n",Relation[i]);
}
//-----------------------------------------------------------------------------------------------------------------
void affichage_DF(FD *Functional_Dep,int Number_FD)
{
    int i;
    printf("-----Your functional dependecies are:--\n\n");
    for(i=0; i<Number_FD; i++)
    {
        printf("\t %s ---> %s\n", Functional_Dep[i].Left_part,Functional_Dep[i].Right_part);
    }
}
//--------------------------------------------------------------------------------------------------------------------------
char *COMPARE(char* string01,char* string02,int Number_Att)//this function will compare two strings looking for a char in commen to return it via the table TAB
{
    int i,j;
    char *TAB=(char*)calloc((Number_Att+1),sizeof(char));//this table is needed to store the results of comparing the two strings
    TAB[Number_Att+1]='\0';
    for (i=0; i<strlen(string02); i++)
    {
        for(j=0; j<strlen(string01); j++)
        {
            if(string01[j]==string02[i])
                TAB[j]=string01[j];
        }
    }
    return TAB;
}
//-----------------------------------------------------------------------------------------------------------------
int COMPARE01(char Attribut,char *string02)//this function is used to search for an attribut in a string if found it will retun 1 and pass to the next char in the string
{
    int i;
    for (i=0; i<strlen(string02); i++)
    {
        if(Attribut==string02[i])
        {
            return 1;
        }
    }
    return 0;
}
//----------------------------------------------------------------------------------------------------------------
int COMPARE_Two_Strings(char* searching01_In,char* searching02_For)//this function will search for a string "searching_For" in the string "searching_In"
{
    int i,counter=0;
    for (i=0; i<strlen(searching02_For); i++)
    {
        if(COMPARE01(searching02_For[i],searching01_In))
            counter++;
    }
    if(counter==strlen(searching02_For))
        return 1;
    return 0;
}
//----------------------------------------------------------------------------------------------------------------
int COMPARE_Two_Strings01(char* searching01_In,char* searching02_For)
{
    int i,counter=0;
    if(strlen(searching01_In) == strlen(searching02_For))
    {
        for (i=0; i<strlen(searching02_For); i++)
        {
            if(COMPARE01(searching02_For[i],searching01_In))
                counter++;
        }
        if(counter==strlen(searching02_For))
            return 1;
    }
    return 0;
}
//----------------------------------------------------------------------------------------------------------------
int Search_String_In_Array(char** Store_Keys,char* TEMP,int Number_FD)
{
    int i;
    for(i=0; i<Number_FD; i++)
    {
        if(COMPARE_Two_Strings(Store_Keys[i],TEMP))
        {
            return 1;
            break;
        }
    }
    return 0;
}
//------------------------------------------------------------------------------------------------------------------
int Search_String_In_Array01(char** Store_Keys,char* TEMP,int Number_FD)
{
    int i;
    for(i=0; i<Number_FD; i++)
    {
        if(COMPARE_Two_Strings01(Store_Keys[i],TEMP))
        {
            return 1;
            break;
        }
    }
    return 0;
}
//----------------------------------------------------------------------------------------------------------------
int Search_Char_In_Array(char *array,char attribut)
{
    int i;
    for(i=0;i<strlen(array);i++)
    {
        if(array[i]==attribut)
        {
            return 1;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------
char* Search_Non_Definded_attributs01(int Number_FD,FD *Functional_Dep,char *Relation,int Number_Att)//this function serves to find all the attributs which arent determened by any other attributs
{
    int i,j,counter=0,counter01=0;
    char* Temp=(char*)calloc(100,sizeof(char));
    Temp[Number_Att+1]='\0';
    char* Temp01=(char*)calloc(100,sizeof(char));
    Temp01[Number_Att+1]='\0';
    for(j=0; j<Number_FD; j++)
    {
        for(i=0; i<Number_Att; i++)
        {
            if(COMPARE01(Relation[i],Functional_Dep[j].Right_part))
            {
                Temp[counter]=Relation[i];
                counter++;
            }
        }
    }

    for(i=0; i<Number_Att; i++)
    {
        if(!COMPARE01(Relation[i],Temp))
        {
            if(!COMPARE01(Relation[i],Temp01))
            {
                Temp01[counter01]=Relation[i];
                counter01++;
            }
        }
    }
    return Temp01;
}
//-------------------------------------------------------------------------------------------------------------------
void CLEAN(int Number_Att,char* Relation,char* Part_Of_Key)
{
    int i;
    for(i=0; i<Number_Att; i++)
    {
        if(COMPARE01(Part_Of_Key[i],Relation)==0)
        {
            Part_Of_Key[i]='\0';
        }
    }
}

char* Take_From_FD(char* Part_Of_Key,int Number_Att,FD Functional_Dep,char* Relation)
{
    int i,k,counter=strlen(Part_Of_Key);
    char* Rest_Of_Key=(char*)calloc(100,sizeof(char));
    Rest_Of_Key[Number_Att+1]='\0';
    for(i=0; i<strlen(Part_Of_Key); i++)
    {
        Rest_Of_Key[i]=Part_Of_Key[i];
    }
    for(k=0; k<Number_Att; k++)
    {
        if(!COMPARE01(Functional_Dep.Left_part[k],Rest_Of_Key))
        {
            Rest_Of_Key[counter]=Functional_Dep.Left_part[k];
            counter++;
        }
    }
    for(i=0; i<Number_Att; i++)
    {
        if(COMPARE01(Rest_Of_Key[i],Relation)==0)
        {
            Rest_Of_Key[i]='\0';
        }
    }
    return Rest_Of_Key;
}
//-------------------------------------------------------------------------------------------------------
char* Concatenate_Two_Strings(char *string01,char *string02)
{
    int j,Counter01=strlen(string01);
    for(j=0; j<strlen(string02); j++)
    {
        if(!COMPARE01(string02[j],string01))
        {
            //printf("the attribut which doesnt exist in the first string is: %c\n",string02[j]);
            string01[Counter01]=string02[j];
            Counter01++;
        }
    }
    return string01;
}
//-------------------------------------------------------------------------------------------------------
void Calcule_Fermeture(int Number_FD,FD *Functional_Dep,char* Fermeture,char* Relation,char* TEMP,char** Store_Keys,int *Number_Keys)
{
    int i,j;
    do
    {
        for(i=0; i<Number_FD; i++)
        {
            if(COMPARE_Two_Strings(Fermeture,Functional_Dep[i].Left_part))
            {
                Concatenate_Two_Strings(Fermeture,Functional_Dep[i].Right_part);
            }
            if(strlen(Relation)!=strlen(Fermeture))
            {
                continue;
            }
            else
            {
                for(j=0; j<strlen(TEMP); j++)
                {
                    if (!Search_String_In_Array(Store_Keys,TEMP,Number_FD))
                    {
                        Store_Keys[*Number_Keys][j]=TEMP[j];
                    }
                }
                *Number_Keys=*Number_Keys+1;
            }
            break;
        }

    }
    while(strlen(Relation)!=strlen(Fermeture));
}
//----------------------------------------------------------------------------------------------------------
void Calcule_Fermeture02(int Number_FD,FD *Functional_Dep,char* Fermeture,char* Relation,char* TEMP,char* Part_Of_Key,int Number_Att,char** Store_Keys,int *Number_Keys)
{
    int j;
    for(j=0; j<Number_FD; j++)
    {
        Fermeture=Take_From_FD(Part_Of_Key,Number_Att,Functional_Dep[j],Relation);
        TEMP=Take_From_FD(Part_Of_Key,Number_Att,Functional_Dep[j],Relation);
        Calcule_Fermeture(Number_FD,Functional_Dep,Fermeture,Relation,TEMP,Store_Keys,Number_Keys);
    }
}
//----------------------------------------------------------------------------------------------------------------
void In_Case_Part_Of_Key_Is_Null(int Number_FD,FD *Functional_Dep,char *TEMP01,int Number_Att,char *Relation,char **Store_Keys,int *Number_Keys,char* Part_Of_Key,int *Min)
{
    int i,j,k,s;
    for(i=0; i<Number_FD; i++)
    {
        for(k=0; k<strlen(Functional_Dep[i].Left_part); k++)
        {
            TEMP01[k]=Functional_Dep[i].Left_part[k];
        }
        printf("\n-------%s",TEMP01);
        Concatenate_Two_Strings(TEMP01,Functional_Dep[i].Right_part);
        for(s=0; s<Number_FD; s++)
        {
            for(j=0; j<Number_FD;j++)
            {
                if(COMPARE_Two_Strings(TEMP01,Functional_Dep[j].Left_part))
                {
                    Concatenate_Two_Strings(TEMP01,Functional_Dep[j].Right_part);
                }
            }
        }
        if(strlen(TEMP01)==strlen(Relation))
        {
            printf("\n2-------%s",TEMP01);
            Store_Keys[*Number_Keys]=Functional_Dep[i].Left_part;
            *Number_Keys=*Number_Keys+1;
        }

        for(k=0; k<Number_Att; k++)
        {
            TEMP01[k]='\0';
        }
    }
    printf("\n _____All keys are: ");
    for(k=0; k<*Number_Keys; k++)
    {
        printf("{%s}",Store_Keys[k]);
    }

}
//----------------------------------------------------------------------------------------------
void But_First(char* Part_Of_Key,char* TEMP01,int Number_FD,FD *Functional_Dep,int Number_Att,char* Relation,char* TEMP,char* Fermeture,char** Store_Keys,int *Value,int *Number_Keys)
{
    int i,j;
    for(i=0; i<strlen(Part_Of_Key); i++)
    {
        TEMP01[i]=Part_Of_Key[i];//the TMP01 is used to store the atributs which arent in the right part of any functional D so we can work with it to calculate fermeture for it
    }
    CLEAN(Number_Att,Relation,Part_Of_Key);
    for(j=0; j<Number_FD; j++)
    {
        for(i=0; i<Number_FD; i++)
        {
            if(COMPARE_Two_Strings(TEMP01,Functional_Dep[i].Left_part))
            {
                Concatenate_Two_Strings(TEMP01,Functional_Dep[i].Right_part);
            }
        }
    }
    if(strlen(Relation)==strlen(TEMP01))
    {
        *Value=*Value+1;
        *Number_Keys=*Number_Keys+1;
        for(i=0; i<strlen(Part_Of_Key); i++)
        {
            Store_Keys[0][i]=Part_Of_Key[i];
        }
    }
    else
    {
        //printf("\n\n---------- %s isnt enough to be a key. \n",Part_Of_Key);
        Calcule_Fermeture02(Number_FD,Functional_Dep,Fermeture,Relation,TEMP,Part_Of_Key,Number_Att,Store_Keys,Number_Keys);
    }
}
//----------------------------------------------------------------------------------------------------------------
//int Find_DF_Violation_2NF(int Number_FD,char **Store_Keys,FD *Functional_Dep,FD *Functional_Dep2,int *Number_Of_DF_2FN,int Number_Keys,int Min)
//{
//    int i,s,j,l,COUNTER=0;//counter will be used to count how many FDs which ae violent to the 2NF
//    char** Store_Left_Parts=(char**)calloc(100,sizeof(char));
//    for(i=0; i<20; i++)
//    {
//        Store_Left_Parts[i]=(char*)calloc(100,sizeof(char));
//    }
//    for(i=0; i<Number_FD; i++)
//    {
//        for(j=0; j<strlen(Functional_Dep[i].Left_part); j++)
//        {
//            Store_Left_Parts[i][j]=Functional_Dep[i].Left_part[j];
//        }
//    }
//    for(j=0; j<Number_Keys; j++)
//    {
//        for(i=0; i<Number_FD; i++)
//        {
//            if(!Search_String_In_Array01(Store_Keys,Functional_Dep[i].Left_part,Number_FD))
//            {
//                //!Search_String_In_Array01(Store_Left_Parts,Store_Keys[j],Number_FD)
//                if(COMPARE_Two_Strings(Store_Keys[j],Functional_Dep[i].Left_part) && strlen(Functional_Dep[i].Left_part) != strlen(Store_Keys[j]) && strlen(Functional_Dep[i].Left_part) != 0 )
//                {
//                    for(s=0; s<strlen(Functional_Dep[i].Left_part); s++)
//                    {
//                        Functional_Dep2[COUNTER].Left_part[s]=Functional_Dep[i].Left_part[s];
//                    }
//                    for(l=0; l<strlen(Functional_Dep[i].Right_part); l++)
//                    {
//                        Functional_Dep2[COUNTER].Right_part[l]=Functional_Dep[i].Right_part[l];
//                    }
//                    COUNTER++;
//                    *Number_Of_DF_2FN=*Number_Of_DF_2FN+1;
//                }
//            }
//        }
//    }
//    if(Functional_Dep2[0].Left_part[0] == '\0')
//    {
//        printf("\n ____This relation is in the SECOND Normal Form.____");
//        return 1;
//    }
//    else
//    {
//        printf("\n\n ____This relation is in the FIRST Normal Form.____");
////        printf("\n\n ____These are the FDs that violate the second Normal Form: ");
////        for(i=0; i<COUNTER; i++)
////        {
////            printf("\n      %s -----> %s",Functional_Dep2[i].Left_part,Functional_Dep2[i].Right_part);
////        }
//        return 0;
//    }
//}
//--------------------------------------------------------------------------------------------------------------
void Correct_Key(int *Number_Keys,char **Store_Keys)
{
    int i,j,s;
    for(i=0; i<*Number_Keys; i++)
    {
        int counts=0;
        for(j=0; j<*Number_Keys; j++)
        {
            if(COMPARE_Two_Strings(Store_Keys[i],Store_Keys[j]) && strlen(Store_Keys[i]) != strlen(Store_Keys[j]) && strlen(Store_Keys[i]) != '\0' && strlen(Store_Keys[j]) !='\0')
            {
                counts++;
            }
        }
        if(counts == 1)
        {
            for(s=0; s<strlen(Store_Keys[i]); s++)
            {
                Store_Keys[i][s]=Store_Keys[i+1][s];
            }
            *Number_Keys=*Number_Keys-1;
        }
        if(Store_Keys[i][0] == '\0')
        {
            *Number_Keys=*Number_Keys-1;
        }
    }
}
//---------------------------------------------------------------------------------------------
//void Decompose_To_2ndNF(int Number_FD,int Number_Of_DF_2FN,FD *Functional_Dep2,FD *Functional_Dep,char **Store_Keys,int Number_Keys,char **Relations_After_Decomp)
//{
//    int i,j,s,x,y;
//    for(j=0;j<Number_FD;j++)
//    {
//        if(Search_String_In_Array01(Store_Keys,Functional_Dep[j].Left_part,Number_Keys))
//        {
//            for(x=0;x<strlen(Functional_Dep[j].Right_part);x++)
//            {
//                for(i=0;i<Number_Of_DF_2FN;i++)
//                {
//                    for(s=0;s<(strlen(Functional_Dep2[i].Right_part)+1);s++)
//                    {
//                        if(Functional_Dep2[i].Right_part[s] == Functional_Dep[j].Right_part[x] && Functional_Dep2[i].Right_part[s] != '\0')
//                           {
//                               //printf("\n%c - %c",Functional_Dep[j].Right_part[x],Functional_Dep[j].Right_part[x+1]);
//                               Functional_Dep[j].Right_part[x] = Functional_Dep[j].Right_part[x+1];
//                           }
//                    }
//                }
//            }
//        }
//    }
////    for(i=0;i<Number_FD;i++)
////    {
////        printf("\n%s--->%s",Functional_Dep[i].Left_part,Functional_Dep[i].Right_part);
////    }
//        int COUNTS=0,COUNTS02=0,count,COUNTS03;
//        //COUNTS is used to count how many relations we will have by the end of decomposition
//        //COUNTS02 each time a FD that violate the second normal form will be deleted COUNTS02 will increase by 1
//        //count it's used to count the attributs inside the relation so as to store them in
//
//        count=0;
//        if(Number_FD == Number_Of_DF_2FN && Number_Keys == 1)
//        {
//            for(s=0; s<strlen(Store_Keys[0]); s++)
//            {
//                Relations_After_Decomp[COUNTS][count]=Store_Keys[0][s];
//                count++;
//            }
//            COUNTS++;
//        }
//        for(i=0; i<Number_Keys; i++)
//        {
//            count=0;
//            for(j=0; j<Number_FD; j++)
//            {
//                if(COMPARE_Two_Strings01(Store_Keys[i],Functional_Dep[j].Left_part) && Functional_Dep[j].Left_part[0] != '\0')
//                {
//                    //printf("\n0TEST or TEST: %s--->%s",Functional_Dep[j].Left_part,Functional_Dep[j].Right_part);
//                    for(s=0; s<strlen(Functional_Dep[j].Left_part); s++)
//                    {
//                        if(!COMPARE01(Functional_Dep[j].Left_part[s],Relations_After_Decomp[COUNTS]))
//                        {
//                            Relations_After_Decomp[COUNTS][count] = Functional_Dep[j].Left_part[s];
//                            count++;
//                        }
//                    }
//                    for(s=0; s<strlen(Functional_Dep[j].Right_part); s++)
//                    {
//                        if(!COMPARE01(Functional_Dep[j].Right_part[s],Relations_After_Decomp[COUNTS]))
//                        {
//                            Relations_After_Decomp[COUNTS][count] = Functional_Dep[j].Right_part[s];
//                            count++;
//                        }
//                    }
//                    //printf("\n0Test relation: %s the value of counts: %d",Relations_After_Decomp[COUNTS],COUNTS);
//                    for(y=0; y<Number_FD; y++)
//                    {
//                        if(COMPARE_Two_Strings01(Functional_Dep[y].Left_part,Functional_Dep[j].Left_part) && !COMPARE_Two_Strings01(Functional_Dep[y].Right_part,Functional_Dep[j].Right_part))
//                        {
//                            for(s=0; s<strlen(Functional_Dep[y].Left_part); s++)
//                            {
//                                if(!COMPARE01(Functional_Dep[y].Left_part[s],Relations_After_Decomp[COUNTS]))
//                                {
//                                    Relations_After_Decomp[COUNTS][count] = Functional_Dep[y].Left_part[s];
//                                    count++;
//                                }
//                            }
//                            for(s=0; s<strlen(Functional_Dep[y].Right_part); s++)
//                            {
//                                if(!COMPARE01(Functional_Dep[y].Right_part[s],Relations_After_Decomp[COUNTS]))
//                                {
//                                    Relations_After_Decomp[COUNTS][count] = Functional_Dep[y].Right_part[s];
//                                    count++;
//                                }
//                            }
//                            for(s=0; s<strlen(Functional_Dep[y].Left_part); s++)
//                            {
//                                Functional_Dep[y].Left_part[s] = '\0';
//                            }
//                            for(s=0; s<strlen(Functional_Dep[y].Right_part); s++)
//                            {
//                                Functional_Dep[y].Right_part[s] = '\0';
//                            }
//                        }
//                    }
//                    for(y=0; y<Number_FD; y++)
//                    {
//                        if(COMPARE_Two_Strings01(Functional_Dep[j].Right_part,Functional_Dep[y].Left_part) && Functional_Dep[y].Right_part[0] != '\0')
//                        {
//                            for(s=0; s<strlen(Functional_Dep[y].Left_part); s++)
//                            {
//                                if(!COMPARE01(Functional_Dep[y].Left_part[s],Relations_After_Decomp[COUNTS]))
//                                {
//                                    Relations_After_Decomp[COUNTS][count] = Functional_Dep[y].Left_part[s];
//                                    count++;
//                                }
//                            }
//                            for(s=0; s<strlen(Functional_Dep[y].Right_part); s++)
//                            {
//                                if(!COMPARE01(Functional_Dep[y].Right_part[s],Relations_After_Decomp[COUNTS]))
//                                {
//                                    Relations_After_Decomp[COUNTS][count] = Functional_Dep[y].Right_part[s];
//                                    count++;
//                                }
//                            }
//                            for(s=0; s<strlen(Functional_Dep[y].Left_part); s++)
//                            {
//                                Functional_Dep[y].Left_part[s] = '\0';
//                            }
//                            for(s=0; s<strlen(Functional_Dep[y].Right_part); s++)
//                            {
//                                Functional_Dep[y].Right_part[s] = '\0';
//                            }
//                        }
//                        COUNTS03++;
//                    }
//                    //printf("\nTest relation: %s value of counts: %d",Relations_After_Decomp[COUNTS],COUNTS);
//                    for(s=0; s<strlen(Functional_Dep[j].Left_part); s++)
//                    {
//                        Functional_Dep[j].Left_part[s] = '\0';
//                    }
//                    for(s=0; s<strlen(Functional_Dep[j].Right_part); s++)
//                    {
//                        Functional_Dep[j].Right_part[s] = '\0';
//                    }
//                    if(Relations_After_Decomp[COUNTS][0] != 0)
//                    {
//                        COUNTS++;
//                    }
//                    COUNTS03++;
//                }
//            }
//        }
//
//        for(i=0; i<Number_Of_DF_2FN; i++)
//        {
//            count=0;
//            for(j=0; j<Number_FD; j++)
//            {
//                if(COMPARE_Two_Strings(Functional_Dep2[i].Right_part,Functional_Dep[j].Left_part) && Functional_Dep[j].Left_part[0] != '\0')
//                {
//                    //printf("\n%s-->%s",Functional_Dep2[i].Left_part,Functional_Dep2[i].Right_part);
//                    //printf("\n%s-->%s",Functional_Dep[j].Left_part,Functional_Dep[j].Right_part);
//                    for(s=0; s<strlen(Functional_Dep2[i].Left_part); s++)
//                    {
//                        if(!COMPARE01(Functional_Dep2[i].Left_part[s],Relations_After_Decomp[COUNTS]))
//                        {
//                            Relations_After_Decomp[COUNTS][count]=Functional_Dep2[i].Left_part[s];
//                            count++;
//                        }
//                    }
//                    for(s=0; s<strlen(Functional_Dep2[i].Right_part); s++)
//                    {
//                        if(!COMPARE01(Functional_Dep2[i].Right_part[s],Relations_After_Decomp[COUNTS]))
//                        {
//                            Relations_After_Decomp[COUNTS][count]=Functional_Dep2[i].Right_part[s];
//                            count++;
//                        }
//                    }
//                    for(s=0; s<strlen(Functional_Dep[j].Right_part); s++)
//                    {
//                        if(!COMPARE01(Functional_Dep[j].Right_part[s],Relations_After_Decomp[COUNTS]))
//                        {
//                            Relations_After_Decomp[COUNTS][count]=Functional_Dep[j].Right_part[s];
//                            count++;
//                        }
//                    }
//                    for(s=0; s<strlen(Functional_Dep[j].Left_part); s++)
//                    {
//                        if(!COMPARE01(Functional_Dep[j].Left_part[s],Relations_After_Decomp[COUNTS]))
//                        {
//                            Relations_After_Decomp[COUNTS][count]=Functional_Dep[j].Left_part[s];
//                            count++;
//                        }
//                    }
//                    for(s=0; s<strlen(Functional_Dep[j].Left_part); s++)
//                    {
//                        Functional_Dep[j].Left_part[s] = '\0';
//                    }
//                    for(s=0; s<strlen(Functional_Dep[j].Right_part); s++)
//                    {
//                        Functional_Dep[j].Right_part[s] = '\0';
//                    }
//                    COUNTS02++;
//                    for(y=0; y<Number_FD; y++)
//                    {
//                        if(COMPARE_Two_Strings01(Functional_Dep2[i].Left_part,Functional_Dep[y].Left_part) && !COMPARE_Two_Strings01(Functional_Dep2[i].Right_part,Functional_Dep[y].Right_part))
//                        {
//                            for(s=0; s<strlen(Functional_Dep[y].Right_part); s++)
//                            {
//                                if(!COMPARE01(Functional_Dep[y].Right_part[s],Relations_After_Decomp[COUNTS]))
//                                {
//                                    Relations_After_Decomp[COUNTS][count]=Functional_Dep[y].Right_part[s];
//                                    count++;
//                                }
//                            }
//                            for(s=0; s<strlen(Functional_Dep[y].Left_part); s++)
//                            {
//                                if(!COMPARE01(Functional_Dep[y].Left_part[s],Relations_After_Decomp[COUNTS]))
//                                {
//                                    Relations_After_Decomp[COUNTS][count]=Functional_Dep[y].Left_part[s];
//                                    count++;
//                                }
//                            }
//                            for(s=0; s<strlen(Functional_Dep[y].Left_part); s++)
//                            {
//                                Functional_Dep[y].Left_part[s] = '\0';
//                            }
//                            for(s=0; s<strlen(Functional_Dep[y].Right_part); s++)
//                            {
//                                Functional_Dep[y].Right_part[s] = '\0';
//                            }
//                            COUNTS02++;
//                        }
//                    }
//                    //printf("\nTesting the relation: %s value of Count: %d",Relations_After_Decomp[COUNTS],COUNTS);
//                    if(Relations_After_Decomp[COUNTS][0] != '\0')
//                    {
//                        COUNTS++;
//                    }
//                    for(y=0; y<Number_FD; y++)
//                    {
//                        if(COMPARE_Two_Strings01(Functional_Dep[y].Left_part,Functional_Dep2[i].Left_part) && COMPARE_Two_Strings01(Functional_Dep[y].Right_part,Functional_Dep2[i].Right_part))
//                        {
//                            for(s=0; s<strlen(Functional_Dep[y].Left_part); s++)
//                            {
//                                Functional_Dep[y].Left_part[s] = '\0';
//                            }
//                            for(s=0; s<strlen(Functional_Dep[y].Right_part); s++)
//                            {
//                                Functional_Dep[y].Right_part[s] = '\0';
//                            }
//                            COUNTS02++;
//                        }
//                    }
//                    for(s=0; s<strlen(Functional_Dep2[i].Left_part); s++)
//                    {
//                        Functional_Dep2[i].Left_part[s] = '\0';
//                    }
//                    for(s=0; s<strlen(Functional_Dep2[i].Right_part); s++)
//                    {
//                        Functional_Dep2[i].Right_part[s] = '\0';
//                    }
//                }
//            }
//            count=0;
//            for(j=0; j<Number_FD; j++)
//            {
//                if(!COMPARE_Two_Strings(Functional_Dep2[i].Right_part,Functional_Dep[j].Left_part) && Functional_Dep[j].Left_part[0] != '\0' && Functional_Dep2[i].Left_part[0] != '\0')
//                {
//                    for(s=0; s<strlen(Functional_Dep2[i].Left_part); s++)
//                    {
//                        if(!COMPARE01(Functional_Dep2[i].Left_part[s],Relations_After_Decomp[COUNTS]))
//                        {
//                            Relations_After_Decomp[COUNTS][count] = Functional_Dep2[i].Left_part[s];
//                            count++;
//                        }
//                    }
//                    for(s=0; s<strlen(Functional_Dep2[i].Right_part); s++)
//                    {
//                        if(!COMPARE01(Functional_Dep2[i].Right_part[s],Relations_After_Decomp[COUNTS]))
//                        {
//                            Relations_After_Decomp[COUNTS][count] = Functional_Dep2[i].Right_part[s];
//                            count++;
//                        }
//                    }
//                    for(s=0; s<strlen(Functional_Dep2[i].Left_part); s++)
//                    {
//                        Functional_Dep2[i].Left_part[s] = '\0';
//                    }
//                    for(s=0; s<strlen(Functional_Dep2[i].Right_part); s++)
//                    {
//                        Functional_Dep2[i].Right_part[s] = '\0';
//                    }
//                    //printf("\nTesting the relation: %s value of Count: %d",Relations_After_Decomp[COUNTS],COUNTS);
//                    if(Relations_After_Decomp[COUNTS][0] != '\0' )
//                    {
//                        COUNTS++;
//                    }
//                }
//            }
//        }
//        //printf("\n value of COUNTS02: %d",COUNTS02);
//        //printf("\nThis is the rest: ");
//        for(i=0; i<Number_FD; i++)
//        {
//            count =0;
//            if(Functional_Dep[i].Left_part[0] != '\0')
//            {
//                //printf("\n %s---%s",Functional_Dep[i].Left_part,Functional_Dep[i].Right_part);
//                for(s=0;s<strlen(Functional_Dep[i].Left_part);s++)
//                {
//                    if(!COMPARE01(Functional_Dep[i].Left_part[s],Relations_After_Decomp[COUNTS]))
//                    {
//                        Relations_After_Decomp[COUNTS][count]=Functional_Dep[i].Left_part[s];
//                        count++;
//                    }
//                }
//                for(s=0;s<strlen(Functional_Dep[i].Right_part);s++)
//                {
//                    if(!COMPARE01(Functional_Dep[i].Right_part[s],Relations_After_Decomp[COUNTS]))
//                    {
//                        Relations_After_Decomp[COUNTS][count]=Functional_Dep[i].Right_part[s];
//                        count++;
//                    }
//                }
//                for(s=0;s<strlen(Functional_Dep[i].Left_part);s++)
//                {
//                    Functional_Dep[i].Left_part[s] = '\0';
//                }
//                for(s=0;s<strlen(Functional_Dep[i].Right_part);s++)
//                {
//                    Functional_Dep[i].Right_part[s] = '\0';
//                }
//                //printf("\nTest Relation2 %s nd COUNTS: %d",Relations_After_Decomp[COUNTS],COUNTS);
//                COUNTS++;
//            }
//        }
//
//
//        int K=0;
//        for(j=0;j<Number_FD;j++)
//        {
//            for(i=0;i<COUNTS;i++)
//            {
//                if(i>=1)
//                {
//                    if(COMPARE_Two_Strings01(Relations_After_Decomp[j],Relations_After_Decomp[i]) && i!=j)
//                    {
//                        for(s=0;s<strlen(Relations_After_Decomp[j]);s++)
//                        {
//                            Relations_After_Decomp[j][s] = '\0';
//                        }
//                    }
//                }
//            }
//        }
//        printf("\n\n ____Decomposition: ");
//        for(i=0;i<COUNTS;i++)
//        {
//            if(Relations_After_Decomp[i][0] != '\0')
//            {
//                printf("\n\tR%d(%s)",K,Relations_After_Decomp[i]);
//                K++;
//            }
//        }
//}
//-------------------------------------------------------------------------------------------------------------------------------
//void To_3rd_NF(int Number_FD,FD *Functional_Dep,char **Relations_After_Decomp)
//{
//    int COUNTS=0,i,s,y;
//        for(i=0;i<Number_FD; i++)
//        {
//            int count=0;
//            for(s=0; s<strlen(Functional_Dep[i].Left_part);s++)
//            {
//                if(!COMPARE01(Functional_Dep[i].Left_part[s],Relations_After_Decomp[COUNTS]))
//                {
//                    Relations_After_Decomp[COUNTS][count]=Functional_Dep[i].Left_part[s];
//                    count++;
//                }
//            }
//            for(s=0; s<strlen(Functional_Dep[i].Right_part);s++)
//            {
//                if(!COMPARE01(Functional_Dep[i].Right_part[s],Relations_After_Decomp[COUNTS]))
//                {
//                    Relations_After_Decomp[COUNTS][count]=Functional_Dep[i].Right_part[s];
//                    count++;
//                }
//            }
//            for(s=0; s<strlen(Functional_Dep[i].Left_part);s++)
//            {
//                Functional_Dep[i].Left_part[s] = '\0';
//            }
//            for(s=0; s<strlen(Functional_Dep[i].Right_part);s++)
//            {
//                Functional_Dep[i].Left_part[s] = '\0';
//            }
//            COUNTS++;
//        }
//        printf("\n ____Decomposition: ");
//        for(y=0;y<COUNTS;y++)
//        {
//            printf("\n\tR%d(%s)",y,Relations_After_Decomp[y]);
//        }
//
//}
