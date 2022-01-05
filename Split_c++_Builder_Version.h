/*******************************************************************************
*      Fichier            : Split_c++_Builder_Version.h                        *
*      Programmeur        : ZAAGANE Mohammed                                   *
*      Email              : zagmoh2005@yahoo.fr                                *
*      site web           : http://zaagane-mohammed.ifrance.com                *
*      Date source        : mardi 05 février 2008                              *
*      Version source     : 1.16.02.2008                                       *
*      Langage            : C++ Builder                                        *
*      Type licence       : libre.                                             *
*      Modification       : dimenche 17 février 2008                           *
*******************************************************************************/

/*-----------------------------------------------------------------------------*
*                            Entete                                           */

#include <stdio.h>// pour FILE,fopen,fread,...
#include <math.h>// pour ceil
#include <dir.h>// pour mkdir,chdir
#include <string.h>//pour strcpy,strcat
#include <stdlib.h>//pour itoa,_splitpath
#include "Status_Unit.h";

#define MAX_OCTET  16*1024 // 16 koctet// la taille du buffer de lecture/ecriture


/*----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*
*     Fonction :    int Min(int value1, int value2)                            *
*     Déscription: cette fonction retourne la valeur min entre les deux valeurs*
*                  entiers value1,value2.                                      *
*-----------------------------------------------------------------------------*/
int Min(int value1, int value2)
{
         return ( (value1 < value2) ? value1 : value2);
}
//-----------------------------------------------------------------------------*

/*-----------------------------------------------------------------------------*
*                   char *My_Int_To_Str(int Integer_Number)                    *
*-----------------------------------------------------------------------------*/
/*char *My_Int_To_Str(int Integer_Number)
{
         char str[]="";
         itoa(Integer_Number,str,10);
         return str;

}*/
//-----------------------------------------------------------------------------*

/*--------------------------------------------------------------------------------*
*Fonction:                                                                        *
*Split_File(char *File_Name,long Part_Size,bool Part_Name_Src,bool Creat_Bat_File)*
*     Pramètres: - char *File_Name:le chemin complet du fichier à décomposer      *
*                - int Part_Size :la taille(en octet) de chaque partition         *
*                - bool Part_Name_Src: pour indiquer si les partition prend       *
*                 le meme nom que le fichier source (pour eviter des problèmes)   *
*                 dans le fichier ".bat"                                          *
*                - bool Creat_Bat_File:si egale true un fichier de commande       *
*                 ".bat" sera créer,il permet de concatiner les partitions        *
*                 en utilisant la commande dos 'copy'.                            *
*     valeurs retournées : * 0 :la fonction réussit                               *
*                          * 1 :impossible d'ouvrir le fichier sources            *
*                          * 2 :impossible de créer un fichier déstination        *
*                          * 3 :impossible de fermer un fichier déstination       *
*                          * 4 :impossible de fermer le fichier source            *
*                          * 5 :impossible de créer le fichier ".zmsb"            *
*                          * 6 :impossible de fermer le fichier ".zmsb"           *
*                          * 7 :impossible de créer le fichier ".bat"             *
*                          * 8 :impossible de fermer le fichier ".bat"            *
*--------------------------------------------------------------------------------*/
int Split_File(char *File_Name,long Part_Size,bool Part_Name_Src,bool Creat_Bat_File)
{
         int Nbr_Parts;// le nombre des partitions
         double File_Size;// la taille du fichier source (à décomposer)
         FILE *Src_Pointer;//pointeur vers le fichier source (à décomposer)
         FILE *Des_Pointer;// pointeur vers le fichier destination (les partitions)
         char Part_Name[256]="";// le nom des partitions
         int Nbr_Octet_To_Read_Write;// le nombre des octets à lire/écrir
         char buf[MAX_OCTET]="";// le buffer de lecture/écriture
         char Current_Dir[260]="";// le repertoire courant

         // obtenir le repertoire courant.
         getcwd(Current_Dir,260);// mettre le chemin du repertoire courant dans la variable Current_Dir
         //fin : obtenir le repertoire courant.

         // ouverture du fichier source en mode binaire et en lecture seule
         if((Src_Pointer=fopen(File_Name,"rb"))==NULL)// si l'opération échoué
         {
                 return 1;//impossible d'ouvrir le fichier sources
         }
         //fin : ouverture du fichier source en mode binaire et en lecture seule


         //Obtenir la taille du fichier source.
         fseek (Src_Pointer, 0 , SEEK_END);//mettre le pointeur vers la fin du fichier
         File_Size = ftell (Src_Pointer);// lire la position courante(dans ce cas 'la fin du fichier')
         rewind (Src_Pointer);// remettre le pointeur vers l'emplacement précédent
         Nbr_Parts=ceil(File_Size/Part_Size);// ceil pour obtenir le petit nombre entier grand (en cas le resultat de la division est réel)
         //fin : Obtenir la taille du fichier source.

         //création d'un répertoire comporte les partitions
         char dir[260]="";
         strcpy(dir,File_Name);
         strcat(dir,"_Parts");
         mkdir(dir); // créer le repertoire
         chdir(dir); // changer le repertoire courant
         //fin : création d'un répertoire comporte les partitions

         //création de fichiers déstinations (partitions)
         //--décomposition de chemin du fichier source.
         char drive[3]=""; // lecteur (c:,d:,...)
         char _dir[260]="";// repertoire
         char file[256]="";// fichier
         char ext[256]=""; // l'extancien

         _splitpath(File_Name,drive,_dir,file,ext);
         //--fin : décomposition de chemin du fichier source.

         char temp[512]="";
         if(Part_Name_Src)// si l'utilisateur choisir que le nom de la partition et le meme que cel du fichier source.
         {                // exemple(si nom du fichier : file.ext ---> noms partitions : file_0, file_1,...
                 strcpy(temp,file);
                 strcat(temp,"_");
         }

         //--création du fichier ".bat"(un fichier de commande DOS).
         /* ce fichier permet de concatner les partitions, en utilisant la
         commande dos "copy"*/
         char commande[512]="";// la commande utilisé dans le fichier ".bat"  elle est de la forme :
                             // copy /b part_1+part_2+part_3+...+part_n /b part.ext
         char Bat_File_Name[256]="";// le nom du fichier ".bat"
         FILE *Bat_File_Pointer;// pointeur vers le fichier ".bat"

         if(Creat_Bat_File)// si l'utilisateur choisir la création du fichier ".bat"
         {
                  strcpy(Bat_File_Name,file);
                  strcat(Bat_File_Name,".bat");

                  if((Bat_File_Pointer=fopen(Bat_File_Name,"w+b"))==NULL)
                  {
                          fclose(Src_Pointer);//fermeture du fichier source avant de quitter
                          return 7;// impossible de créer le fichier ".bat"
                  }
                  strcpy(commande,"copy /b ");
                  fwrite(commande,strlen(commande),1,Bat_File_Pointer);// ecriture de la partie "copy /b"
         }
         //--fin création du fichier ".bat"

         //----------------------
         Status_Form->ProgressBar1->Max=File_Size;
         //----------------------

         char temp2[15]="";
         for(int i=0;i<Nbr_Parts;i++)//pour toutes les partitions
         {
                 strcpy(Part_Name,temp);

                 strcpy(temp2,"");
                 itoa(i,temp2,10);// convertir l'entier 'i' en string
                 strcat(Part_Name,temp2);

                 if(Creat_Bat_File)//si l'utilisateur choisir la création du fichier ".bat"
                 {
                         if(i!=Nbr_Parts-1)//si pas la derniere partition on ajoute "+"
                         {
                                 strcpy(commande,Part_Name);
                                 strcat(commande," + ");
                                 // ecriture du nom de chaque partition suivé de la signe '+' dans le fichier ".bat".
                                 fwrite(commande,strlen(commande),1,Bat_File_Pointer);
                         }
                         else// la derniere partition
                         {
                                 // ecriture du nom de la derniere partition dans le fichier ".bat".
                                 fwrite(Part_Name,strlen(Part_Name),1,Bat_File_Pointer);
                         }
                 }

                 if((Des_Pointer=fopen(Part_Name,"w+b"))==NULL)//création de fichiers déstinations en mode binaire et en lecture/écriture
                 {                                             //en cas où le fichier existe déja il sera ecrasé
                         fclose(Src_Pointer);
                         return 2;//impossible de créer un fichier déstination
                 }


                 int Remain_Octet = Part_Size;// premeirement le nombre d'octet reste = la taille de prtition
                 while(Remain_Octet>0)//tant que le copiage pas terminé
                 {
                        strcpy(buf,"");// vider le buffer

                        Nbr_Octet_To_Read_Write=Min(MAX_OCTET,Remain_Octet);

                        long Current_Position=ftell(Src_Pointer);// obtenir la position courant dans le fichier source
                        long Remain_Octet_In_Src_File=File_Size-Current_Position;
                        if(Remain_Octet_In_Src_File < Nbr_Octet_To_Read_Write)// si le nombre d'octet reste dans le fichier source < la taille du parttion
                        {                                  // ce probleme arriver dans la derniere partition ou si la taille de partition choisi est > la taille de fichier
                                 Nbr_Octet_To_Read_Write=Remain_Octet_In_Src_File;
                        }


                        if(fread(buf,Nbr_Octet_To_Read_Write,1,Src_Pointer)>0)// si la lecture réussi
                        {
                               fwrite(buf,Nbr_Octet_To_Read_Write,1,Des_Pointer);// écriture
                               Remain_Octet -= Nbr_Octet_To_Read_Write;
                        }
                        else// la fin du fichier 'EOF'
                        {
                               Remain_Octet = 0; //force l'arret
                        }
                        //-----------
                        Status_Form->ProgressBar1->Position+=Nbr_Octet_To_Read_Write;
                        Application->ProcessMessages();
                        //-----------
                  }

                  if(fclose(Des_Pointer)!=0)// fermeture d'un fichier déstination
                  {
                        return 3;//impossible de fermer un fichier déstination
                  }
         }
         //fin : création de fichiers déstinations (partitions)

         //finition du fichier ".bat"
         if(Creat_Bat_File)//si l'utilisateur choisir la création du fichier ".bat"
         {
                  strcpy(commande," /b ");
                  strcat(commande,file);
                  strcat(commande,ext);
                  fwrite(commande,strlen(commande),1,Bat_File_Pointer); // écriture de la partie ( /b file.ext) dans le fichier ".bat"

                  if(fclose(Bat_File_Pointer)!=0)// fermeture du fichier ".bat"
                  {
                        return 8;//impossible de fermer le fichier ".bat" 
                  }
         }
         //fin : finition du fichier '.bat'

         if(fclose(Src_Pointer)!=0)//fermeture du ficheir source
         {
                  return 4;//impossible de fermer le fichier source
         }

         // création du fichier ".zmsb".
         /* ce fichier contient les informations (le nom du fichier source et le nombre de partitions et une information
          pour connaitre les noms de partitions ) qui sont utilisés par la procedure de recomposition "Build".*/

         char Zmsb_File_Name[256]="";// le nom du fichier ".zmsb"
         FILE *Zmsb_File_Pointer;// un pointeur vers le fichier ".zmsb"
         char informations[512]="";
         strcpy(Zmsb_File_Name,file);
         strcat(Zmsb_File_Name,".zmsb");

         if((Zmsb_File_Pointer=fopen(Zmsb_File_Name,"w+b"))==NULL)
         {
                  return 5;//impossible de créer le fichier ".zmsb"
         }

         strcpy(informations,"ZMSBFILE&");// une signature pour marquer le fichier
         strcat(informations,file);// ajouter le nom du fichier source a l'information
         strcat(informations,ext);// ajouter l'extancien a l'information
         strcat(informations,"#");// ajouter le caractere '#' comme un séparateur.

         char temp3[15]="";
         itoa(Nbr_Parts,temp3,10);// convertir le nombre de partition a une string.
         strcat(informations,temp3);//ajouter le nombre de partition a l'information
         strcat(informations,"#");//ajouter le caractere '#' comme un séparateur.

         if(Part_Name_Src)
         {
                strcat(informations,"1");// les noms de partitions sont les memes que le nom du fichier source
         }
         else
         {
                strcat(informations,"0");// les noms des partitions sont des nombres (0,1,2,3,...)
         }

         fwrite(informations,strlen(informations),1,Zmsb_File_Pointer);// ecriture de l'information dans le fichier ".zmsb"

         if(fclose(Zmsb_File_Pointer)!=0)// fermeture du fichier ".zmsb"
         {
                  return 6;//impossible de fermer le fichier ".zmsb" 
         }
         //fin : création du fichier ".zmsb"

         chdir(Current_Dir);//retourner au répertoire précédent

         return 0;// décomposition réussit
}
