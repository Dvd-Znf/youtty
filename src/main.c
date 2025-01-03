#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>

#include "version.h"

char target[255],data[12],home[256],video_method_target[255],save_video_target[256];
bool    change_key=false,
        kitten=false, 
        video_method=false,
        no_key=false,
        no_audio=false,
        save_video=false;

FILE *ptrf;

static char helpstr[] = "\n"
		    	"Usage: youtty [OPTION] TARGET\n"
		    	"\n"
		    	"Download video from target and they play it via vlc\n"
		    	"\n"
		    	"Posible command options:\n"
		    	"		        -h | --help       : Display this message\n"
	                "		        -k | --kitty      : Preview thumbnail if you have kitty\n"
	                "		        -v | --version    : Print version and exit\n"
	                "		        -V | --vout       : Specify a valid vlc output method\n"
	                "		        -n | --no-key     : Use the ytsearch integreated in yt-dlp instead\n"
	                "		        -N | --no-audio   : Completly disable audio output\n"
	                "		        -s | --save       : Save the downloaded video instead of discarding it\n"
	                "		        -c | --change-key : Change the current API key\n"
		    	"\n"
		    	"Examples:\n"
		    	"	youtty -c                   Change the current API key\n"
		    	"	youtty 'Bad Apple'          Download and watch Bad Apple!!\n"
	                "	youtty -V aa 'Bad Apple'    Download and watch Bad Apple!! in ascii art\n"
		    	"\n";

int main(int argc, char *argv[]){
    if(argc==1){
        printf("\e[91mErr\e[0m: expected some additional argument\n\e[33mHint\e[0m: You could use -h or --help to see a list\n");
        return(1);
    }

    for(int i=1;i<argc;i++){
        if(!strcmp(argv[i],"-h") || !strcmp(argv[i],"--help")){
            printf("%s",helpstr); 
            return 0;
        } else if(!strcmp(argv[i],"-v") || !strcmp(argv[i],"--version")) {
            printf("youtty version: ");
            puts(RELEASE_VERSION);
            return 0;
        } else if(!strcmp(argv[i],"-c") || !strcmp(argv[i],"--change-key")) {
            change_key=true;
        } else if(!strcmp(argv[i],"-k") || !strcmp(argv[i],"--kitty")) {
            kitten=true;
        } else if(!strcmp(argv[i],"-V") || !strcmp(argv[i],"--vout")) {
            video_method=true;
            if(i+1<argc){
                strcpy(video_method_target,argv[i+1]);
            } else {
                printf("\e[91mErr\e[0m: expected some additional argument\n\e[33mHint\e[0m: Please specify a valid vlc output module\n)");
                return 1;
            }
        } else if(!strcmp(argv[i],"-n") || !strcmp(argv[i],"--no-key")) {
            no_key=true;
        } else if(!strcmp(argv[i],"-N") || !strcmp(argv[i],"--no-audio")) {
            no_audio=true;
        } else if(!strcmp(argv[i],"-s") || !strcmp(argv[i],"--save")) {
            save_video=true;
            if(i+1<argc){
                strcpy(save_video_target,argv[i+1]);
            } else {
                printf("\e[91mErr\e[0m: expected some additional argument\n\e[33mHint\e[0m: Please specify a valid path for save video\n");
                return 1;
            }
        } else {
            strcpy(target,argv[i]);
        }
    }
    
    if(change_key){
        char resp[256],py_key[512]="api_key=\"";

        printf("Please enter a valid YouTube data API key:\n");
        fgets(resp,sizeof(resp),stdin);
        resp[strcspn(resp, "\n")] = 0;

        strcat(py_key,resp);
        strcat(py_key,"\"");

        FILE *key_name_file;
        strcpy(home, getenv("HOME"));
        key_name_file=fopen(strcat(home,"/.local/share/youtty/key_name.py"),"w");
        if(key_name_file==NULL){
            printf("\e[91mErr\e[0m: Couldn't allocate file pointer!\n\e[33mHint\e[0m: Have you ran the install.sh script?");
        }
        fprintf(key_name_file,"%s", py_key);
        fclose(key_name_file);

        return 0;
    }

    if(kitten){
        FILE *kitten_ptr;
        strcpy(home, getenv("HOME"));
        kitten_ptr=fopen(strcat(home,"/.cache/youtty/data/kitten"),"w"); //Maybe there's a way to create the file if it doesn't exist?
        if(kitten_ptr==NULL){                                            //It would also need to create parent folders
            printf("\e[91mErr\e[0m: Couldn't allocate file pointer!\n\e[33mHint\e[0m: Have you ran the install.sh script?");
        }
        fprintf(kitten_ptr,"1");
        fclose(kitten_ptr);
    }

    if(no_key){
        printf("Warning: --no-key flag detected!\nUsing yt-dlp ytsearch instead, this may lead to bad things happening\nBe ready to CTR+C\n");
        system("sleep 1");

        char youtube_dl_caller[255] = "yt-dlp --format mp4 -o ~/.cache/youtty/data/content ytsearch:";
        char tmp_data[255] = "'";
        strcat(tmp_data,target);
        strcat(tmp_data,"'");
        strcat(youtube_dl_caller,tmp_data);

        system(youtube_dl_caller);
    } else {
        char python_caller[255] = "python ~/.local/share/youtty/api-caller.py ";
        strcpy(home, getenv("HOME"));

        strcat(python_caller,"'");
        strcat(python_caller,target);
        strcat(python_caller,"'");

        system(python_caller);

        ptrf=fopen(strcat(home,"/.cache/youtty/data/history"),"r");

        if(ptrf==NULL){
            printf("\e[91mErr\e[0m: Couldn't allocate file pointer!\n\e[33mHint\e[0m: Maybe API query failled?\n");
            exit(1);
        }  
        fseek(ptrf,0,SEEK_END);
        if(ftell(ptrf)==0){
            printf("\e[91mErr\e[0m: API Caller failed!\n\e[33mHint\e[0m: Maybe you didn't select a video?\n");
            fclose(ptrf);
            exit(1);
        }
        fseek(ptrf,0,SEEK_SET);
        fgets(data,12,ptrf);
        fclose(ptrf);

        printf("Recived data from API\nUsing youtube-dl to temporarly download content\n");

        char youtube_dl_caller[255] = "yt-dlp --format mp4 -o ~/.cache/youtty/data/content https://www.youtube.com/watch?v=";
        strcat(youtube_dl_caller,data);
        system(youtube_dl_caller);

    }

    
    printf("yt-dlp finished doing it's thing!\n");

    strcpy(home, getenv("HOME"));
    if(access(strcat(home,"/.cache/youtty/data/content"),F_OK)){
        printf("\e[91mErr\e[0m: Downloaded video dosen't exist!\n\e[33mHint\e[0m: Maybe yt-dlp failled?\n");
        exit(1);
    }

    if(save_video){
        char cp_call[256] = "cp ~/.cache/youtty/data/content ";
        strcat(cp_call, save_video_target);

        system("cp_call");
    }

    printf("Everything looks good!\nUsing cvlc to view content...\n");

    char output_method[255]="cvlc ";
    if(video_method){
        strcat(output_method,"-V ");
        strcat(output_method,video_method_target);
    }
    if(no_audio){
        strcat(output_method," --no-audio");
    }
    strcat(output_method," ~/.cache/youtty/data/content");
    system(output_method);
    system("rm ~/.cache/youtty/data/content");    



    printf("If you found any issues please post them on github\nThanks for using my program \e[91m<3\e[0m\n");

    return 0;
}
