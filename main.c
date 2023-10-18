#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>


char target[255],data[12],home[256],video_method_target[255],save_video_target[256];
bool    kitten=false, 
        video_method=false,
        no_key=false,
        save_video=false;

FILE *ptrf;

static char helpstr[] = "\n"
		    	"Usage: youtty [OPTION] TARGET\n"
		    	"\n"
		    	"Download video from target and they play it via vlc\n"
		    	"\n"
		    	"Posible command options:\n"
		    	"		        -h | --help    : Display this message\n"
                "		        -k | --kitty   : Preview thumbnail if you have kitty\n"
                "		        -v | --version : Print version and exit\n"
                "		        -V | --vout    : Specify a valid vlc output method\n"
                "		        -n | --no-key  : Use the ytsearch integreated in yt-dlp instead\n"
                "		        -s | --save    : Save the downloaded video instead of discarding it\n"
		    	"\n"
		    	"Examples:\n"
		    	"	youtty 'Bad Apple'      	Download and watch Bad Apple!!\n"
                "	youtty -V aa 'Bad Apple'	Download and watch Bad Apple!! in ascii art\n"
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
        } else if(!strcmp(argv[i],"-v") || !strcmp(argv[i],"--version")) {
            printf("youtty version: v0.3.1\n"); 
            return 0;
        } else if(!strcmp(argv[i],"-k") || !strcmp(argv[i],"--kitty")) {
            kitten=true;
        } else if(!strcmp(argv[i],"-V") || !strcmp(argv[i],"--vout")) {
            video_method=true;
            if(i+1<argc){
                strcpy(video_method_target,argv[i+1]);
            } else {
                printf("\e[91mErr\e[0m: expected some additional argument\n(Please specify a valid vlc output module\n)");
                return 1;
            }
        } else if(!strcmp(argv[i],"-n") || !strcmp(argv[i],"--no-key")) {
            no_key=true;
        } else if(!strcmp(argv[i],"-s") || !strcmp(argv[i],"--save")) {
            save_video=true;
            if(i+1<argc){
                strcpy(save_video_target,argv[i+1]);
            } else {
                printf("\e[91mErr\e[0m: expected some additional argument\n(Please specify a valid path for save video)\n");
                return 1;
            }
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

    if(no_key==true){
        printf("Warning: --no-key flag detected!\nUsing yt-dlp ytsearch instead, this may lead to bad things happening\nBe ready to CTR+C\n");
        system("sleep 1");

        char youtube_dl_caller[255] = "yt-dlp --format mp4 -o ~/.youtty/data/content ytsearch:";
        char tmp_data[255] = "'";
        strcat(tmp_data,target);
        strcat(tmp_data,"'");
        strcat(youtube_dl_caller,tmp_data);
        //printf(youtube_dl_caller);
        system(youtube_dl_caller);
    } else {
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

    }

    
    printf("yt-dlp finished doing it's thing!\n");

    strcpy(home, getenv("HOME"));
    if(access(strcat(home,"/.youtty/data/content"),F_OK)!=0){
        printf("\e[91mErr\e[0m: Downloaded video dosen't exist!\n(Maybe yt-dlp failled?)\n");
        exit(1);
    }

    if(save_video){
        char cp_call[256] = "cp ~/.youtty/data/content ";
        strcat(cp_call, save_video_target);

        system("cp_call");
    }

    printf("Everything looks good!\nUsing cvlc to view content...\n");

    if(video_method==false){
        system("cvlc ~/.youtty/data/content");
        system("rm ~/.youtty/data/content");
    } else {
        char output_method[255]="cvlc -V ";
        strcat(output_method,video_method_target);
        strcat(output_method," ~/.youtty/data/content");
        system(output_method);
        system("rm ~/.youtty/data/content");
    }
    



    printf("If you found any issues please post them on github\nThanks for using my program \e[91m<3\e[0m\n");

    return 0;
}
