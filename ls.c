#include "standardHeaders.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


void handleLflag(char *fileName, char*path, char * newHome)
{
    
    struct stat sb;    
      //type
    lstat(path, &sb);
    if ((sb.st_mode & S_IFMT) == S_IFBLK)
        printf("b");
    else if ((sb.st_mode & S_IFMT) == S_IFLNK)
        printf("l");
    else if ((sb.st_mode & S_IFMT) == S_IFCHR)
        printf("c");
    else if ((sb.st_mode & S_IFMT) == S_IFDIR)
        printf("d");
    else if ((sb.st_mode & S_IFMT) == S_IFIFO)
        printf("f");
    else if ((sb.st_mode & S_IFMT) == S_IFREG)
        printf("-");
    else if ((sb.st_mode & S_IFMT) == S_IFSOCK)
        printf("s");
    //sbmissions
    printf("%c", (sb.st_mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (sb.st_mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (sb.st_mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (sb.st_mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (sb.st_mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (sb.st_mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (sb.st_mode & S_IROTH) ? 'r' : '-');
    printf("%c", (sb.st_mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (sb.st_mode & S_IXOTH) ? 'x' : '-');
    printf(" %4ld ", sb.st_nlink);


    struct group *grp;
    struct passwd *pwd;

    grp = getgrgid(sb.st_gid);
    pwd = getpwuid(sb.st_uid);
    // uname and grp
    printf("%10s ", pwd->pw_name);
    printf("%10s ", grp->gr_name);


    // size
    printf("%10ld ", sb.st_size);
    

    // last access time
    struct tm *t;
    char T[1111];
    time_t cur_time;
    char buf[1111];

    
    t = localtime(&sb.st_mtime);
    strftime(T, sizeof(T), "%b %e %Y %H:%M", t);
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
        //printf("  lflag: %d: aflag: %d\n",lflag,aflag);
        //printf("%s:\n",folders[i]);
        DIR *D = opendir(folders[i]);
        if(D==NULL){perror(" "); return;}

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



