/*******************************************************************************
*      Fichier            : Build_c++_Builder_Version.h                        *
*      Programmeur        : ZAAGANE Mohammed                                   *
*      Email              : zagmoh2005@yahoo.fr                                *
*      site web           : http://zaagane-mohammed.ifrance.com                *
*      Date source        : mardi 05 février 2008                              *
*      Version source     : 1.16.02.2008                                       *
*      Langage            : C++ Builder                                        *
*      Type licence       : libre.                                             *
*      Modification       : dimenche 17 février 2008                           *
*******************************************************************************/

#include <stdio.h>// pour FILE,fopen,fread,...
#include <string.h>//pour strcpy,strcat
#include <stdlib.h>//pour itoa,_splitpath
#define MAX_OCTET  16*1024 // 16 koctet la taille du buffer de lecture/ecriture

/*-----------------------------------------------------------------------------*
*      Fonction : bool Is_ZMSB_File(FILE *ZMSB_File_Pointer)                   *
*      Déscription : cette fonction permet de vérifier si le fichier pointé par*
*      le pointeur "ZMSB_File_Pointer" est de type "ZMSB" ou non.              *
*      Paramètres :- FILE *ZMSB_File_Pointer:pointeur vers le fichier à tester *
*      Valeurs retournées :* true : le fichier est de type "ZMSB"              *
*                          * false: le fichier n'est pas de type "ZMSB"        *
*-----------------------------------------------------------------------------*/
bool Is_ZMSB_File(FILE *ZMSB_File_Pointer)
{
       char signature[10]=""; //ZMSBFILE 

       fread(signature,8,1,ZMSB_File_Pointer);//lecture de 8 premiers octets et les mettre dans
                                              //la variable signature.
       if(strcmp(signature,"ZMSBFILE")==0) // comparaison des octets lu avec la signature
       { //si les premiers 8 octets = "ZMSBFILE" (la signature)
               return true;// alors le fichier est de type "ZMSB"
       }
       else // sinon
       {
               return false;// alors il n'est pas de type "ZMSB"
       }
}
//-----------------------------------------------------------------------------*

/*------------------------------------------------------------------------------------------------------*
* Fonction : int Extract_Informations(FILE *ZMSB_File_Pointer,char File_Name[260],char Part_Name_Src[1])*
* Déscription : cette fonction permet d'extraire les informations (nom de fichier et le nombre de       *
*              partitions et une information pour définir les noms de partitions)                       *
* Paramètres : - FILE *ZMSB_File_Pointer: pointeur vers le fichier d'informations ".zmsb"               *
*              - char *File_Name : variable où le nom du fichier source sera stocké.                    *
*              - char Part_Name_Src[1] :* si = 1 les noms de partitions sont les memes que le fichiers  *
*               décomposés par la procedure (File_Split).                                               *
*                                       * si = 0 les noms de partitions sont des nombres (0,1,2,3,...)  *
* Valeurs retournées :  le nombre de partitions                                                         *
*------------------------------------------------------------------------------------------------------*/
int Extract_Informations(FILE *ZMSB_File_Pointer,char File_Name[260],char Part_Name_Src[1])
{
       char informations[512]="";
       int ZMSB_File_Size;// la taille du fichier d'informations


       //Obtenir la taille du fichier d'informations.
       fseek (ZMSB_File_Pointer, 0 , SEEK_END);//mettre le pointeur vers la fin du fichier
       ZMSB_File_Size = ftell (ZMSB_File_Pointer);// lire la position courante(dans ce cas 'la fin du fichier')
       rewind (ZMSB_File_Pointer);// remettre le pointeur vers l'emplacement précédent
       //fin : Obtenir la taille du fichier d'informations.

       fread(informations,ZMSB_File_Size,1,ZMSB_File_Pointer);//lecture d'informations

       // Extraction des informations
       char temp[260]="";// variable temporaire pour le nom de fichier
       char temp2[10]="";// variable temporaire pour le nombre de partitions

       bool After=false;
       bool After_2=false;
       int index=0;

       for(int i=9;i<ZMSB_File_Size;i++)
       {
             if(!After)// avant le premier '#'
             {
                     if(informations[i]!='#')
                     {
                             temp[i-9]=informations[i];
                     }
                     else
                     {
                             After=true;
                     }
             }
             else
             {
                     if(!After_2) // avant le deuxieme '#'
                     {
                            if(informations[i]!='#')
                            {
                                  temp2[index]=informations[i];
                                  index++;
                            }
                            else
                            {
                                  After_2=true;
                            }
                     }
                     else
                     {
                            Part_Name_Src[0]=informations[i];
                     }
                     /*if(informations[i]!='#')
                     {
                            temp2[index]=informations[i];
                            index++;
                     } */
             }
       }
       //Part_Name_Src[0]=informations[ZMSB_File_Size-1];
       // fin : Extraction des informations

       strcpy(File_Name,temp);
       return atoi(temp2);// le nombre de partitions.
}
//-----------------------------------------------------------------------------*

/*-----------------------------------------------------------------------------*
*   Fonction : int Build(char *ZMSB_File_Name)                                 *
*      Déscription : cette fonction permet de recomposer les partitions        *
*      d'un fichier décomposé par la procedure "Split_File".                   *
*   Paramètres :- char *ZMSB_File_Name: le chemin complet du fichier           *
*                   d'informations ".ZMSB"                                     *
*                  le fichier qui contient(le noms du fichier et le nombre des *
*                  partions et l'information qui défini les noms de partitions)*
*   Valeurs retournées:* 0 : ecomposition réussit.                             *
*                      * 1 : impossible d'ouvrir le fichier ".zmsb"            *
*                      * 2 : le fichier sélectionné n'est pas de type".zmsb"   *
*                      * 3 : impossible de fermer le fichier ".zmsb"           *
*                      * 4 : impossible de créer le fichier déstination        *
*                      * 5 : impossible d'ouvrir un fichier source(partition)  *
*                      * 6 : impossible de fermer un fichier source (partition)*
*-----------------------------------------------------------------------------*/
int Build(char *ZMSB_File_Name)
{
         FILE *ZMSB_File_Pointer;// pointeur vers le fichiers d'iformations ".zmsb".
         FILE *Des_Pointer;// pointeur vers le fichier déstination.
         FILE *Part_Pointer;//pointeur vers les partitions.
         char Des_File_Name[260]="";// le nom du fichier déstination.
         int Nbr_Part=0;// le nombre de partition.
         char Current_Dir[260]="";// le repertoire courant
         // variables utilisés pour décomposé un chemin
         char drive[3]=""; // lecteur (c:,d:,...)
         char _dir[260]="";// repertoire
         char file[256]="";// fichier
         char ext[256]=""; // l'extancien
         //--------------------------------------------

         // obtenir le repertoire courant.
         getcwd(Current_Dir,260);// mettre le chemin du repertoire courant dans la variable Current_Dir.
         //fin : obtenir le repertoire courant.

         _splitpath(ZMSB_File_Name,drive,_dir,file,ext);//décomposition du nom du fichier d'informations.
         /*pour extraire le chemin du repertoire qui comporte les partitions et le fichier d'informations*/

         char Parts_Dir[260]="";
         strcpy(Parts_Dir,drive);
         strcat(Parts_Dir,_dir);
         chdir(Parts_Dir);

         // ouverture du fichier d'informations ".zmsb"
         if((ZMSB_File_Pointer=fopen(ZMSB_File_Name,"r"))==NULL)
         {
                  return 1;// impossible d'ouvrir le fichier d'informations.
         }
         // fin : ouverture du fichier d'informations

         // vérification du type du fichier
         if(Is_ZMSB_File(ZMSB_File_Pointer)==false)
         {
                  return 2;// fichier n'est pas de type ".zmsb".
         }
         // fin : vérification du type du fichier

         char Part_Name_Src[5]="";// voir la fonction "Extract_Informations".

         //Extraction des informations
         Nbr_Part=Extract_Informations(ZMSB_File_Pointer,Des_File_Name,Part_Name_Src);


         if(fclose(ZMSB_File_Pointer)!=0)// fermeture du fichier d'informatrions
         {
                  return 3;//impossible de fermer le fichier d'informatrions
         }

         // recomposition

         //--création du fichier déstination
         if((Des_Pointer=fopen(Des_File_Name,"w+b"))==NULL)
         {
                  return 4;// impossible de créer le fichier déstination
         }
         //-- fin : création du fichier déstination

         // obtenir le nom de partitions
         _splitpath(Des_File_Name,drive,_dir,file,ext);//décomposition du nom du fichier Destination.

         char Part_Name[256]="";
         char temp[256]="";
         char temp2[15]="";

         if(strcmp(Part_Name_Src,"1")==0)
         {
                  strcpy(temp,file);
                  strcat(temp,"_");
         }
         // fin : obtenir le nom de partitions.

         int Part_Size;// la taille de chaque partition.
         char buf[MAX_OCTET]; // buffer de lecture/écriture.
         int Remain_Octet;
         int Nbr_Octet_To_Read_Write;

         //---------------------------------------------------------------------
         // obtenir la taille du fichier
         long File_Size;
         // la taille de la premiere partition----------------------------------
         strcpy(Part_Name,temp);
         strcat(Part_Name,"0");
         Part_Pointer=fopen(Part_Name,"rb");
         fseek (Part_Pointer, 0 , SEEK_END);//mettre le pointeur vers la fin du fichier
         int Part_0_Size = ftell (Part_Pointer);// lire la position courante(dans ce cas 'la fin du fichier')
         rewind(Part_Pointer);// remettre le pointeur vers l'emplacement précédent
         fclose(Part_Pointer);
         //---------------------------------------------------------------------
         if(Nbr_Part-1!=0)// s'il ya plusse q'une partition
         {
                  // la taille de la derniere partition-------------------------
                  strcpy(Part_Name,temp);
                  itoa(Nbr_Part-1,temp2,10);
                  strcat(Part_Name,temp2);
                  Part_Pointer=fopen(Part_Name,"rb");
                  fseek (Part_Pointer, 0 , SEEK_END);//mettre le pointeur vers la fin du fichier
                  int Part_n_Size = ftell (Part_Pointer);// lire la position courante(dans ce cas 'la fin du fichier')
                  rewind(Part_Pointer);// remettre le pointeur vers l'emplacement précédent
                  fclose(Part_Pointer);
                  //------------------------------------------------------------

                  if(Part_0_Size==Part_n_Size)// si la taille de la dernire partition = la taille de la premiere partition
                  {
                          File_Size=Part_0_Size*Nbr_Part;
                  }
                  else
                  {
                          File_Size=(Part_0_Size*(Nbr_Part-1))+Part_n_Size;
                  }

         }
         else// une seule partition
         {
                  File_Size=Part_0_Size;
         }

         Status_Form->ProgressBar1->Max=File_Size;
         //------------------------------------------------------------

         for(int i=0;i<Nbr_Part;i++)// pour toutes les partitions
         {
                  //-- ouverture de partitions (fichiers sources)
                  strcpy(Part_Name,temp);

                  strcpy(temp2,"");// vider 'temp2'
                  itoa(i,temp2,10);// convertir l'entier 'i' en string

                  strcat(Part_Name,temp2);

                  if((Part_Pointer=fopen(Part_Name,"rb"))==NULL)// si l'opération échoué
                  {
                          fclose(Des_Pointer);// fermer le fichier déstinataire avant de quitter
                          return 5;//impossible d'ouverir un fichier source(partition)
                  }
                  //-- fin : ouverture de partitions (fichiers sources)

                  //Obtenir la taille de la partition courante.
                  fseek (Part_Pointer, 0 , SEEK_END);//mettre le pointeur vers la fin du fichier
                  Part_Size = ftell (Part_Pointer);// lire la position courante(dans ce cas 'la fin du fichier')
                  rewind (Part_Pointer);// remettre le pointeur vers l'emplacement précédent
                  //fin : Obtenir la taille de la partition courante.

                  Remain_Octet = Part_Size;// premeirement le nombre d'octet reste = la taille de prtition

                  while(Remain_Octet>0)//tant que le copiage pas terminé
                  {
                         strcpy(buf,"");// vider le buffer

                         Nbr_Octet_To_Read_Write=Min(MAX_OCTET,Remain_Octet);

                         /*long Current_Position=ftell(Part_Pointer);// obtenir la position courant dans le fichier source
                         long Remain_Octet_In_Src_File=Part_Size-Current_Position;

                         if(Remain_Octet_In_Src_File < Nbr_Octet_To_Read_Write)// si le nombre d'octet reste dans le fichier source < la taille du parttion
                         {                                  // ce probleme arriver dans la derniere partition ou si la taille de partition choisi est > la taille de fichier
                                  Nbr_Octet_To_Read_Write=Remain_Octet_In_Src_File;
                         }*/

                         if(fread(buf,Nbr_Octet_To_Read_Write,1,Part_Pointer)>0)// lecture
                         {
                                fwrite(buf,Nbr_Octet_To_Read_Write,1,Des_Pointer);// écriture
                                Remain_Octet -= Nbr_Octet_To_Read_Write;
                         }
                         else// la fin du fichier 'EOF'
                         {
                                Remain_Octet = 0; //force l'arret
                         }
                         Status_Form->ProgressBar1->Position+=Nbr_Octet_To_Read_Write;
                         Application->ProcessMessages();
                  }

                  if(fclose(Part_Pointer)!=0)
                  {
                         fclose(Des_Pointer);// fermer le fichier déstinataire avant de quitter
                         return 6;// impossible de fermer un fichier source (partition).
                  }
         }

         if(fclose(Des_Pointer))
         {
                  return 7;// impossible de fermer le fichier déstination.
         }
         // fin : recomposition

         chdir(Current_Dir);//retourner au repertoire précédent

         return 0;// Recomposition réussit.
}

