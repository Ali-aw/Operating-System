#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<wait.h>
#include<math.h>
#include<string.h>
#include<signal.h>
#include<time.h>
#include<math.h>
#define SIGHUP 1
#include <ctype.h>

typedef struct usrpass
{
  char password[20];
  char username[20];
  int dest;
  int source;
  
} usrpass;

typedef struct ticket
{
  char username[20];
  int random;
  int dest;
  int source;
  
} ticket;

typedef struct con
{
  char message[20];
  int dest;
  int source;
  
} conn;

conn con;

usrpass up;
usrpass upr;
ticket tick;
ticket tickr;

int  myticket=0,ans,g=1,x,y,ra,bit,nbofclientconnected=0;
int pidclients[3], pw[2], pr[2], i, w;
int login[3]={0,0,0};
int v[3];

char destination[20];
char  type[20];
char question[20];
char solution[20];

 void connect();
 void gaming();
 void typegame();
 void chooseclienttochat(int sig );
 void Chat(int sig);

//===================================Functions=====================================//
 int fileGame(char*s, int x,int n,char* intent)
{
  FILE *fp1;
  fp1 = fopen ("filegame.txt",intent);
   
if((!strcmp(intent,"w")||!strcmp(intent,"a+")))
{
  if(n==0)
      {
        y=fprintf(fp1, "nbofclientconnected:%d",x); fflush (fp1); 
      }
  else{
    
         if(x==0){ y=fprintf(fp1,"\n%s",s); fflush (fp1);}
         else {y=fprintf(fp1,"\n%d",x); fflush (fp1);}
      }
}

 if(n==0 && !strcmp(intent,"r"))
 {
    fseek(fp1,n,SEEK_SET);
    y=fscanf(fp1, "nbofclientconnected:%d",& x); fflush (fp1);
 } 


else if(n=1 && !strcmp(intent,"r"))
{
     char line[256];
     int count=0;
     int k=0,ind=0;
     
  while(fgets(line,sizeof(line),fp1))
  {
      if(k!=0)
      {
           printf(" %d \n",strcmp(line,solution));
           printf("count: %d solution: %s line: %s\n",count,solution,line);
           
            if(count==1 && !strcmp(line,solution)  )
            {
                    printf("\nclient1 win \n");fflush (stdout);
                    ind=1;
            }
  
           if(count==2 && !strcmp(line,solution)   )
           {
                    printf("\nclient2 win\n ");fflush (stdout);
                    ind=1;
           }
  
           if(count==3  && !strcmp(line,solution))
           {
                    printf("\nclient3 win\n ");fflush (stdout);
                    ind=1;
           }
        
      }
      k++;
      count++;
  }
     if(ind==0 && strcmp(line,solution)  )
          {
                printf("no one win ^_^\n  ");fflush (stdout);
          }

      }

    if(y!=0)
    {
       printf ("\nSuccesfully Saved in Filegame\n\n\n" );
      fclose(fp1);
      return x;
    }
    else printf ("\nNot Succesfully saved in gameserverfile  \n" );
     return 0;
      fclose(fp1);
}
//===================================Gaming=====================================//
 void Gaming()
 {
    printf("\n*************Gaming**********%d\n",i);
    int j,cn=1;
    int nb=fileGame(NULL,cn,0,"r");
          if(nb<3)
          {
              printf("Not all players are connected !!! (-_-) \n");
              bit=0;
              kill(getppid(),SIGALRM);
    
          }else{//gameserver start to game
            bit=1;
            printf("!!!!!!!!!!!!!!!!THE GAME STARTED ^_^ !!!!!!!!!!!!!!!!!\n\n");
            printf("PLEASE ENTER THE MATH EQUATION: ");
            scanf("%s", question);
            printf("\n\n");
       
       
            printf("Iam the gameserver the solution is: ");
            scanf("%s", solution);
           printf("\n\n\n");
            con.dest=2;//client1
            con.source=0;
            write (pw[1],"game", 20*sizeof (char));
            write (pw[1],& con.dest,sizeof(int));
            write (pw[1],question, 20*sizeof (char));
            write (pw[1], &con.source,sizeof(int));
       
            printf ("****************************%d\n",i);
            kill (getppid(), SIGURG);
       
      
              }
       
     
 }
//===================================verfyTicket=====================================//
 int verfyTicket (char name[])
{

  FILE *fp;
  fp = fopen ("gameserverfile.txt", "a+");
  char username[20];
  char password[20];
  char username1[20];
  int ret;

  while (1)
    {
      
      ret = fscanf (fp, " %s %s\n", username, password); 
       snprintf(username1,40*sizeof(char),"%s:%s",username,password);
       
      if (!strcmp (username1,name)) 
      {
        printf ("\n!!!!!!!Ticket Verified ^_^!!!!!!!!\n\n");
        return 1;
      }
      
      if(ret!=2){
        printf ("invalid??");
        
        break;
      }
      
    }
    
    return 0;
    fclose (fp);
}
//===================================Chat=====================================//
void Chat(int sig)//SIGBUS
{
       
        read (pr[0], type,20*sizeof (char));
        read (pr[0],&con.dest,sizeof(int));
        
       
        if(con.dest==0&&!strcmp(type,"chat"))
        {//gameserver
          printf ("I am Gameserver i=%d\n\n",i);fflush (stdout);
         //read ticket from client 
         read (pr[0], con.message, 20*sizeof (char));
         read (pr[0], &con.source,sizeof(int));
         
         printf("Client number %d\t:: Message saved:: %s\n\n",con.source-1,con.message);fflush (stdout);
         if(verfyTicket (con.message))
          {
             Gaming();
          }
        } else{//brothers
        
         read (pr[0], con.message, 20*sizeof (char));
         read (pr[0], &con.source,sizeof(int)); 
         
         printf ("brothers %d,i=%d s=%d  ans=%s\n\n\n",con.dest,i,con.source,con.message);fflush (stdout);
       if(!strcmp(con.message,"**")||!strcmp(con.message,"#")){
         system("clear");
         connect();
      
           }else{
           printf("press '#'if you want to close chating\n");
           printf("press '**'if you want to close Gaming\n\n");
           
           if(con.dest==0 && !strcmp(type,"game"))
           {  //gameserver recieve the answer
              //gameserver recieve the answer
             if(con.source==4)
             {
                fileGame(con.message,0,con.source-1,"a+");//client3 saving
                char*a;
                fileGame(a,0,1,"r");//client3 saving
              
              printf("*************Game Over*************%d",i);
               exit(1);
             }else{
             printf("Answer of client %d ans=%s",con.source,con.message);
             fileGame(con.message,0,con.source-1,"a+");
             strcpy(con.message,question);
             con.source=con.source+1;//dest
             con.dest=0;//source
             }

           }else  if(con.source==0&&!strcmp(type,"game")){//gameserver send the question
             printf("Question: %s\n",con.message);
             printf("\n Answer=");
             scanf("%s",con.message);
             printf("\n");
             
          } else{
              printf("client %d:%s",con.source-1,con.message);
              printf("\nclient %d:",i-1);
              scanf("%s", con.message);
             
           }
                     
         printf ("message=%s\n",con.message);

           //send client the message
           write (pw[1],type, 20*sizeof (char));
           write (pw[1], &con.source,sizeof(int));//dest
           write (pw[1],  con.message,20*sizeof (char));
           write (pw[1], &con.dest,sizeof(int));//source
           signal (SIGBUS, Chat);   
            kill (getppid(), SIGURG);
          }
       
     }
            

      }
//===================================gameserverfileSave=====================================//
int gameserverfileSave(char * username,int random)
{
    
  FILE *fp1;
  fp1 = fopen ("gameserverfile.txt","a+");
  
  fflush (fp1);
  y=fprintf(fp1, "\n%s %d ", username,random);
    
    if(y!=0) 
    {
      printf ("\nsuccesfully saved in gameserverfile  \n" );
      fclose(fp1);
      return 1;
    }
    else printf ("\nnot succesfully saved in gameserverfile  \n" );
     return 0;
      fclose(fp1);
}

//===================================connect=====================================//
int c;
void connect()
{
  
    printf ("$$$$$$$$$$$---What do you want to do?---$$$$$$$$$$$%d\n\n",i);
    printf ("0- you want to play ? press 0\n");
    printf ("1- you want to chat client1 ? press 1 \n");
    printf ("2- you want to chat client2 ? press 2\n");
    printf ("3- you want to chat client3 ? press 3\n");
    scanf("%d",&c);

         switch (c)
        {
  
          case 0 :
       
          if(i!=0){//gameserver
          con.source=i;
          con.dest=0;
        if(login[i-2]==1){
          snprintf(con.message,40*sizeof(char),"%s:%d",up.username,myticket);
          write (pw[1],"chat",20*sizeof(char)); 
          write (pw[1], &con.dest,sizeof(int));
          write (pw[1],con.message,20*sizeof (char));
          write (pw[1], &con.source,sizeof(int));
          kill (getppid() ,SIGURG);
            }else{
              printf ("!!!!YOU MUST LOGIN BEFORE!!!!!\n");;fflush(stdout);
              typegame();
            }
          break;
        } 
        else{
            printf ("can'not connect to your self\n");
            connect();
        }

case 2 :
          if(i!=3){//start chat
          con.source=i;
          con.dest=3;
          write (pw[1],"chat",20*sizeof(char));
          write (pw[1], &con.dest,sizeof(int));
          write (pw[1],"hi", 20*sizeof (char));
          write (pw[1], &con.source,sizeof(int));
          kill (getppid(), SIGURG);
          break;}
          else{
             printf ("can'not connect to your self\n");
             connect();
           
         }
         
           
          case 3 :
          if(i!=4){//c1 or c2
          con.source=i;
          con.dest=4;
          write (pw[1],"chat",20*sizeof(char));
          write (pw[1], &con.dest,sizeof(int));
          write (pw[1],"hi", 20*sizeof (char));
          write (pw[1], &con.source,sizeof(int));
          kill (getppid(), SIGURG);
          break;
            
          }
           else{
              
             printf ("can'not connect to your self\n");
             connect();
             
         }
         case 1:
         //step1
          if(i!=2){//iam not c1
          con.source=i;
          con. dest=2;
          write (pw[1],"chat",20*sizeof(char));
          write (pw[1], &con.dest,sizeof(int));
          write (pw[1],"hi", 20*sizeof (char));
          write (pw[1], &con.source,sizeof(int));
          kill (getppid(), SIGURG);
          break;
         }
         else{
             printf ("can'not connect to your self\n");
             connect();
           
         }
         
         default:connect();printf("c=%d",c);
    }

 
    }
//===================================typegame=====================================//
void typegame()
{
      
     printf ("\n====GO TO===>\n");fflush (stdout);
     printf ("L=->login\nH=->chat or gmaing\n");  fflush (stdout);
     scanf ("%s" ,type);fflush (stdin);
     
      if(login[i-2]==0)
       {//login
          
        printf ("\nPlease Enter Password: ");fflush (stdout);
        scanf ("%s" , up.password);fflush (stdin);
        printf ("UserName: ");fflush (stdout);
        scanf ("%s" , up.username);fflush (stdin);
        up.source=i;
        up.dest=1;
        strcpy(type,"login");
        write (pw[1], type, 20*sizeof (char));
        write (pw[1], up.password,20*sizeof (char));
        write (pw[1], up.username, 20*sizeof (char));
        write (pw[1], &up.source,sizeof(int));
        write (pw[1], &up.dest,sizeof(int));fflush (stdout); 
        kill (getppid (), SIGURG); 
        }  
 
    if(!strcmp(type,"H")||!strcmp(type,"h"))
    {//chating
         strcpy(type,"chat");
          connect(); 
        
    } 
   
  else if (!strcmp(type,"l")||!strcmp(type,"L")){
    printf ("you already login");fflush (stdout);
   typegame();
  }
    
     
}
//===================================createtickets=====================================//
int createtickets()
{
   
     if(i==1){
     //I am authserver
     srand(time(0));
     ra= rand()%100 +1;

      if(gameserverfileSave(upr.username,ra))
      {
          strcpy(type,"ticket");
          write (pw[1], type,20*sizeof (char));
          write (pw[1],&upr.source,sizeof(int));//destination
          write (pw[1],&ra,sizeof (int));
          kill (getppid (), SIGURG);
          
          return 1;
      }
  }
  }
//===================================chooseclienttochat=====================================//
void chooseclienttochat(int sig)// SIGALRM
{ int n;
    //client choose the 
      printf ("####choose the player####\n");fflush (stdout);
      printf ("1-player 1::connect=%d\n",login[0]);fflush (stdout);
      printf ("2-player 2::connect=%d\n",login[1]);fflush (stdout);
      printf ("3-player 3::connect=%d\n",login[2]);fflush (stdout);
      scanf ("%d", &n);
      switch (n)
     {
      case 1:
        {//step1
          kill (pidclients[2], SIGUSR2);
          break;
        }
      case 2:

kill (pidclients[3], SIGUSR2);
        break;
        case 3:
        kill (pidclients[4], SIGUSR2);
        break;
        default: chooseclienttochat(SIGALRM);
    }
    
}
//===================================verfi_name_pass=====================================//
int verfi_name_pass (char pass[], char name[])
{
  FILE *fp;
  fp = fopen ("authFile.txt", "a+");
  char username[128];
  char password[128];

  int ret;

  while (1)
    {
      
      ret = fscanf (fp, "%s : %s\n", password, username);    
      if (!strcmp (username,name) && !strcmp(password,pass)) 
      {
        printf ("\n!!!!!!!login succesfully!!!!!!!!\n");
        return 1;
      }
      else{ printf ("\nfaild!! pass or username false??\n");fflush (stdout); break;}
      break;
    }
    typegame();
    return 0;
    
    fclose (fp);
  
}
//===========================================middlewritehandler=======================================================//
void middlewritehandler (int sig)//SIGHUP
{

if(!strcmp( type,"ticket"))
   {
        write (pr[1], type,20*sizeof (char));
        write (pr[1], &tickr.random,sizeof (int));    
   }
if(!strcmp(type,"login"))
{
     strcpy(type,"login");
      write (pr[1], type,20*sizeof (char));
      write (pr[1], upr.password,20*sizeof (char));
      write (pr[1], upr.username, 20*sizeof (char));
      write (pr[1], &upr.source,sizeof(int));
      write (pr[1], &upr.dest,sizeof(int));
      kill  (pidclients[upr.dest], SIGUSR1);
     
}
if(!strcmp(type,"chat")||!strcmp(type,"game")){
  
      write (pr[1], type,20*sizeof (char));
      write (pr[1], &con.dest,sizeof(int));
      write (pr[1],con.message, 20*sizeof (char));
      write (pr[1], &con.source,sizeof(int));
     
}


}
//=====================================middlereadhandler=======================================================
void middlereadhandler (int sig)//SIGURG
{
  read (pw[0], type, 20*sizeof (char));
if(!strcmp( type,"login"))
{
 
  read (pw[0], upr.password, 20*sizeof (char));
  read (pw[0], upr.username, 20 * sizeof (char));
  read (pw[0], &upr.source, sizeof (int));
  read (pw[0],& upr.dest,sizeof (int));    

}
if(!strcmp(type,"ticket"))
{  
 
     read (pw[0],& tickr.dest,sizeof (int));
     read (pw[0],&tickr.random,sizeof (int));
     login[tickr.dest-2]=1;
     nbofclientconnected++;
     fileGame(NULL,nbofclientconnected,0,"w");
      kill (pidclients[tickr.dest], SIGUSR1);
      
}
if(!strcmp(type,"chat")||!strcmp(type,"game"))
{
  
    read (pw[0], &con.dest,sizeof(int));
    read (pw[0], con.message, 20*sizeof (char));
    read (pw[0], &con.source,sizeof(int));
    kill (pidclients[con.dest], SIGBUS);
}

  middlewritehandler (1);
  signal (SIGURG, middlereadhandler);
  
}
//=======================================clientwritehandler=====================================================
void clientwritehandler (int sig)//SIGUSR2
{
   typegame(); 
   signal (SIGUSR2, clientwritehandler);
}
//=======================================clientreadhandler=====================================================
void clientreadhandler (int sig)//SIGUSR1
{ 
   read (pr[0], type, 20 * sizeof (char));
   if(!strcmp(type,"ticket")){
    read (pr[0], &tickr.random, sizeof (int));
    myticket=tickr.random;
    login[i-2]=1;
    typegame();
}
   if(!strcmp(type,"login"))
   {
     read (pr[0], upr.password, 20*sizeof (char));
     read (pr[0], upr.username, 20 * sizeof (char));
     read (pr[0], &upr.source, sizeof (int));
     read (pr[0], &upr.dest,sizeof (int));
     int v= verfi_name_pass (upr.password, upr.username);
   if(v==1)
   {
     if(createtickets() )
      printf("\nTicket Generated: %d\n",ra);fflush (stdout);
   } 
     else{
       printf("pass or username is false\n");fflush (stdout);
     }
}
   signal (SIGUSR1, clientreadhandler);
}
//=======================================================main==============================================================//
int main()
{
   pipe (pw);
   pipe (pr);
   int n;

  for (i = 0; i < 5; i++)
    {
      pidclients[i] = fork ();
      if (pidclients[i] == 0)
      {
       signal (SIGUSR1, clientreadhandler);
       signal (SIGUSR2, clientwritehandler);
        signal (SIGBUS, Chat);
        close (pw[0]);
        close (pr[1]);
        break;
      }

}
    
   if (i == 5)
    {
      close (pw[1]);
      close (pr[0]);
      signal (SIGURG, middlereadhandler);
      signal (SIGHUP, middlewritehandler);
      signal ( SIGALRM, chooseclienttochat);
      chooseclienttochat(SIGALRM);
      while(1) pause();
     
    }
  
  else if (i == 0)  //gamme
    {
     while(1)
      pause();
      
    }
  else if (i == 1) //authserver
    {
         while(1)   pause ();
     
    }
  else //clients
    {
      while (1)  pause ();
       
    }  

}



