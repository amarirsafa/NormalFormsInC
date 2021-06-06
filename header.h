
#ifndef Header_FUNCTION
#define Header_FUNCTION
typedef struct
{
    char Left_part[10];
    char Right_part[10];
}FD;

//-------------------------Filling in functions------------------------------
void Fill_In_Relation(int Nombre_att,char *Relation); //this function will fill the table of Realtion with attributs
void Fill_In_FD(int Numbre_FD,FD *Functional_Dep);//this function will fill table of structes with FD

//------------------------- Afichage Functions-------------------------------
void affichage_Relation(int Number_Att,char *Relation);//This function will out put ur Realtion
void affichage_DF(FD *Functional_Dep,int Numbre_FD);//This function will out put FD

//-------------------------Comparing functions-------------------------------
char *COMPARE(char* string01,char* string02,int Number_Att);//This function will return the characters two strings have in commen
int COMPARE01(char Attribut,char *string02);//This fucntion will search for an attribut in a string
int COMPARE_Two_Strings(char* searching_In,char* searching_For);//This function will search for a string in other string
int Search_String_In_Array(char** Store_Keys,char* TEMP,int Number_FD);//this will compare two strings even if the order of chars is different
int Search_String_In_Array01(char** Store_Keys,char* TEMP,int Number_FD);
int COMPARE_Two_Strings01(char* searching01_In,char* searching02_For);//This function compares two strings they have to be the exact same the order of attributs doesnt matter
char* Concatenate_Two_Strings(char *string01,char *string02);//This function will add a string to an already existed string basicly concatenate
int Search_Char_In_Array(char *array,char attribut); //this function will search for att in array

//--------------------------Searching functions------------------------------
char* Search_Non_Definded_attributs01(int Number_FD,FD *Functional_Dep,char *Relation,int Number_Att);//this function serves to find which attributs arent definded by any other ones
void In_Case_Part_Of_Key_Is_Null(int Number_FD,FD *Functional_Dep,char *TEMP01,int Number_Att,char *Relation,char **Store_Keys,int *Number_Keys,char* Part_Of_Key,int *Min);//this one will serve to find the keys when Part_Of_key is null
char* Take_From_FD(char* Part_Of_Key,int Number_Att,FD Functional_Dep,char* Relation);//this fucntion concatenate part of the key with thr left part of any functional dep
void CLEAN(int Number_Att,char* Relation,char* Part_Of_Key);//this function is made to clean strings from any attributs which dont exist in R

//-------------------------Calcule Fermeture---------------------------------
void Calcule_Fermeture(int Number_FD,FD *Functional_Dep,char* Fermeture,char* Relation,char* TEMP,char** Store_Keys,int *Number_Keys);//this will come as the second one in case the first key didnt work
void Calcule_Fermeture02(int Number_FD,FD *Functional_Dep,char* Fermeture,char* Relation,char* TEMP,char* Part_Of_Key,int Number_Att,char** Store_Keys,int *Number_Keys);//this is the first function that will calculate the key!
void But_First(char* Part_Of_Key,char* TEMP01,int Number_FD,FD *Functional_Dep,int Number_Att,char* Relation,char* TEMP, char* Fermeture,char** Store_Keys,int *Value,int *Number_Keys);//This one will check if the Part of key is the key first before moving to any other FD
void Correct_Key(int *Number_Keys,char **Store_Keys);//This will make sure all keys are minimal (exp BC AB, BDC, BDE)
//-------------------------Decomposition--------------------------------------
int Find_DF_Violation_2NF(int Number_FD,char **Store_Keys,FD *Functional_Dep,FD *Functional_Dep2,int *Number_Of_DF_2FN,int Number_Keys,int Min);
void Decompose_To_2ndNF(int Number_FD,int Number_Of_DF_2FN,FD *Functional_Dep2,FD *Functional_Dep,char **Store_Keys,int Number_Keys,char **Relations_After_Decomp);
void To_3rd_NF(int Number_FD,FD *Functional_Dep,char **Relations_After_Decomp);
#endif // Header_FUNCTION
