#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>


char target[255],data[12],home[256];
bool kitten=false;
FILE *ptrf;

static char helpstr[] = "\n"
		    	"Usage: youtty <option> <target>\n"
		    	"\n"
		    	"Download video from target and they play it via vlc\n"
		    	"\n"
		    	"Posible command options:\n"
		    	"		        -h | --help  : Display this message\n"
                "		        -k | --kitty : Preview thumbnail if you have kitty\n"
		    	"\n"
		    	"Examples:\n"
		    	"	youtty 'Bad Apple'	Download and watch Bad Apple!!\n"
		    	"\n";

int main(int argc, char *argv[]){
    if(argc==1){
        printf("\e[91mErr\e[0m: expected some additional argument\n(You could use -h or --help to see a list)\n");
        return(1);
    }

    for(int i=1;i<argc;i++){
        if(!strcmp(argv[i],"-h") || !strcmp(argv[i],"--help")){
            printf("%s",helpstr); 
            return 0;
        } else if(!strcmp(argv[i],"-k") || !strcmp(argv[i],"--kitty")) {
            kitten=true;
        } else {
            strcpy(target,argv[i]);
        }
    }
    
    if(kitten==true){
        FILE *kitten_ptr;
        strcpy(home, getenv("HOME"));
        kitten_ptr=fopen(strcat(home,"/.youtty/data/kitten"),"w");
        if(kitten_ptr==NULL){
            printf("\e[91mErr\e[0m: Couldn't allocate file pointer!\n(Have you ran the install.sh script?)");
        }
        fprintf(kitten_ptr,"1");
        fclose(kitten_ptr);
    }

    char python_caller[255] = "python ~/.youtty/api-caller.py ";
    strcpy(home, getenv("HOME"));

    strcat(python_caller,"'");
    strcat(python_caller,target);
    strcat(python_caller,"'");

    system(python_caller);

    ptrf=fopen(strcat(home,"/.youtty/data/history"),"r");

    if(ptrf==NULL){
        printf("\e[91mErr\e[0m: Couldn't allocate file pointer!\n(Maybe API query failled?)\n");
        exit(1);
    }  
    fseek(ptrf,0,SEEK_END);
    if(ftell(ptrf)==0){
        printf("\e[91mErr\e[0m: API Caller failed!\n(Maybe you didn't select a video?)\n");
        fclose(ptrf);
        exit(1);
    }
    fseek(ptrf,0,SEEK_SET);
    fgets(data,12,ptrf);
    fclose(ptrf);

    printf("Recived data from API\nUsing youtube-dl to temporarly download content\n");

    char youtube_dl_caller[255] = "yt-dlp --format mp4 -o ~/.youtty/data/content https://www.youtube.com/watch?v=";
    strcat(youtube_dl_caller,data);
    system(youtube_dl_caller);

    printf("yt-dlp finished doing it's thing!\n");

    strcpy(home, getenv("HOME"));
    if(access(strcat(home,"/.youtty/data/content"),F_OK)!=0){
        printf("\e[91mErr\e[0m: Downloaded video dosen't exist!\n(Maybe yt-dlp failled?)\n");
        exit(1);
    }

    printf("Everything looks good!\nUsing cvlc to view content...\n");
    system("cvlc ~/.youtty/data/content");
    system("rm ~/.youtty/data/content");

    
    printf("If you found any issues please post them on github\nThanks for using my program \e[91m<3\e[0m\n");

    return 0;
}
