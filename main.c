#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>


char target[255],data[12];
bool kitten=false;
FILE *ptrf;

static char helpstr[] = "\n"
		    	"Usage: youtty <option> <target>\n"
		    	"\n"
		    	"Download video from target and they play it via vlc\n"
		    	"\n"
		    	"Posible command options:\n"
		    	"		        -h | --help : Display this message\n"
		    	"\n"
		    	"Examples:\n"
		    	"	youtty 'Bad Apple'	Download and watch Bad Apple!!\n"
		    	"\n";

int main(int argc, char *argv[]){
    if(argc==1){
        printf("Err: expected some additional argument\n(You could use -h or --help to see a list)\n");
        return(1);
    }

    for(int i=1;i<argc;i++){
        if(!strcmp(argv[i],"-h") || !strcmp(argv[i],"--help")){
            printf("%s",helpstr); 
            return 0;
        } else {
            strcpy(target,argv[i]);
        }
    }
    
    char python_caller[255] = "python ~/.youtty/api-caller.py ",home[255];
    strcpy(home, getenv("HOME"));

    strcat(python_caller,"'");
    strcat(python_caller,target);
    strcat(python_caller,"'");

    system(python_caller);

    printf("Recived data from API\nUsing youtube-dl to temporarly download content\n");

    ptrf=fopen(strcat(home,"/.youtty/data/history"),"r");
    if(ptrf==NULL){
        printf("Err: Couldn't allocate file pointer!\n(Maybe API query failled?)\n");
        exit(1);
    }   
    fgets(data,12,ptrf);
    fclose(ptrf);

    char youtube_dl_caller[255] = "youtube-dl --format mp4 -o ~/.youtty/data/content https://www.youtube.com/watch?v=";
    strcat(youtube_dl_caller,data);
    system(youtube_dl_caller);

    printf("Youtube-dl finished doing it's thing!\n");

    strcpy(home, getenv("HOME"));
    if(access(strcat(home,"/.youtty/data/content"),F_OK)!=0){
        printf("Err: Downloaded video dosen't exist!\n(Maybe youtube-dl failled?)\n");
        exit(1);
    }

    printf("Everything looks good!\nUsing cvlc to view content...\n");
    system("cvlc ~/.youtty/data/content");

    printf("If you found any issues please post them on github\nThanks for using my program <3\n");

    return 0;
}
