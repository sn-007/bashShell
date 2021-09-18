#include "standardHeaders.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


void handleLflag(char *fileName, char*path, char * newHome)
{
    
    struct stat sb;    
    if(lstat(path, &sb) < 0)
    {
        perror(" ");
    }
    

    switch (sb.st_mode & S_IFMT) {
    case S_IFBLK :  printf("b");break;
    case S_IFREG :  printf("-");break;
    case S_IFDIR :  printf("d");break;
    case S_IFCHR :  printf("c");break;
    case S_IFIFO :  printf("f");break;
    case S_IFSOCK:  printf("s");break;
    case S_IFLNK :  printf("l");break;
    default:        printf("x");break;
    }
    
    
    if(sb.st_mode & S_IRUSR) printf("r"); else printf("-");
    if(sb.st_mode & S_IWUSR) printf("w"); else printf("-");
    if(sb.st_mode & S_IXUSR) printf("x"); else printf("-");
    if(sb.st_mode & S_IRGRP) printf("r"); else printf("-");
    if(sb.st_mode & S_IWGRP) printf("w"); else printf("-");
    if(sb.st_mode & S_IXGRP) printf("x"); else printf("-");
    if(sb.st_mode & S_IROTH) printf("r"); else printf("-");
    if(sb.st_mode & S_IWOTH) printf("w"); else printf("-");
    if(sb.st_mode & S_IXOTH) printf("x"); else printf("-");

    //hardlinks
    printf(" %4ld ", sb.st_nlink);


    // uid gid
    struct group *grp; struct passwd *pwd;

    grp = getgrgid(sb.st_gid); 
    pwd = getpwuid(sb.st_uid);
    printf("%10s %10s ", pwd->pw_name,grp->gr_name);


    //size
    printf("%10ld ", sb.st_size);
    

    //time
    struct tm *t;
    char T[1111],buf[1111]; memset(T, '\0', 1111); memset(buf, '\0', 1111);
    time_t cur_time;
    
    t = localtime(&sb.st_mtime);
    strftime(T, sizeof(T), "   %b  %e  %Y  %H:%M ", t);
    printf("%s ", T);

    // read symlink
    int cnt =0;
   
    if ((sb.st_mode & S_IFMT) == S_IFLNK)
    {
        if ((cnt = readlink(path, buf, sizeof(buf))) != -1)
        {
            buf[cnt] = '\0';
            printf("%s -> %s\n", fileName, buf);
        }
    }
    else
        printf("%s\n", fileName);

    
    return;

};


void processLs(char **folders, int folderCount, int lflag, int aflag,  char* newHome)
{
    if(folderCount==0) {folders[folderCount++]=".";}
    for(int i =0;i < folderCount;i++)
    {
        
        DIR *D = opendir(folders[i]);
        if(D==NULL){perror(folders[i]); return;}

        printf("%s:\n",folders[i]);

        struct dirent *d = readdir(D);
        char fileName[1000];

        while(d!=NULL)
        {
            fileName[0]='\0';
            sprintf(fileName,"%s", d->d_name);
            

            if(fileName[0]=='.' && aflag !=1)
            {
                d =readdir(D);continue;
            }
            

            else if (lflag == 1)
            {
                
                
                int tempLength = strlen(folders[i]);
                
                if(folders[i][tempLength-1] == '/')
                {
                    folders[i][tempLength-1] = '\0';
                }
                
                char *path = malloc (1000*sizeof(char));
                sprintf(path, "%s/%s", folders[i],fileName);
                
                handleLflag(fileName,path,newHome);
                free(path);
                d =readdir(D);continue;

            }

            else
            {
                printf("%s\n", d->d_name);
                d = readdir(D);
            }
            
        }
        printf("\n");
    }
    return;

 
}



