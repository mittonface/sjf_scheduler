//
//  main.c
//  SF_sched
//
//  Created by Brent Mitton on 2/27/2014.
//  Copyright (c) 2014 Brent Mitton. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// structure to contain each process.
struct Process{
    int pid;
    int arrival;
    int *cpu_bursts;
    int *io_bursts;
};

int main(int argc, const char * argv[])
{
    FILE *fp;
    fp = fopen("/Users/brentmitton/Desktop/SF_sched/SF_sched/processes", "r");
    int num_lines = 1;
    int char_counts[500]; // max 500 lines

    // is this how c is supposed to be written or am I mentally deficient?
    
    // figure out how many lines are in the file
    if (fp != NULL){
        char cur_char;
        
        cur_char = fgetc(fp);
        while (cur_char != EOF){
            char_counts[num_lines - 1]++;
            if (cur_char == '\r'){
                num_lines++;
            }
            cur_char = fgetc(fp);
        }
        
        rewind(fp); // internal pointer back to the beginning of the file

        
        // num_lines now has the number of lines in the file
        // I can allocated an array for each line
        char *lines[num_lines];
        
        for (int i=0; i<num_lines; i++){
            lines[i] = malloc(sizeof(char) * char_counts[i]);
        }
        
        
        // now I have an array called lines. Each element should have room for the number
        // of characters in the string. Now I just need to load the characters into the
        // appropriate elements
        int line_num = 0;
        int char_num = 0;

        cur_char = fgetc(fp);
        while (cur_char != EOF){
            if (cur_char == '\r'){
                line_num++;
                char_num = 0;
                cur_char = fgetc(fp);
            }else{
                lines[line_num][char_num] = cur_char;
                char_num++;
                cur_char = fgetc(fp);
            }
        }
        
        // that was sufficiently painful. Now I have each of the lines stored in a different element

    
        struct Process process[num_lines]; // load the lines from that line array into this process array
    
        // So before I get here, I need to create an array of lines from the file,
        // there's no easy way to do this apparently, so I'm going to do it the hard
        // way.
            
        for (int ln=0; ln< num_lines; ln++){
            char *line = lines[ln];
            
            // count the number of spaces that occur in the line
            int space_count = 0;
            char *pch=strchr(line,' ');

            while (pch!=NULL) {
                space_count++;
                pch=strchr(pch+1,' ');
            }
            
            // now that I know there are x spaces, I'm going to malloc some appropriately
            // sized arrays
            int* full = malloc(space_count * sizeof(int));
            
            // populate full with the entirety of the line, we'll have an array
            // that has all of the different parts of the string as different elements
            // then we can split that up to CPU and I/O bursts
            char* token;
            int i = 0;
            token = strtok(line, " ");
            while (token != NULL){
                full[i] = atoi(token);
                i++;
                token = strtok(NULL, " ");
            }
            
            // now I want to malloc the array for cpu bursts and i/o bursts
            // the number of cpu bursts will be ((space_count-2)/2) + 1
            // and the number of io bursts will be (space_count-2)/2)
            process[ln].cpu_bursts = malloc((((space_count-2)/2) + 1) * sizeof(int));
            process[ln].io_bursts = malloc((((space_count-2)/2) ) * sizeof(int));
            
            // now we can figure out all the different values for this process
            int pid = full[0];
            int arrival = full[1];


            // populate burst arrays
            int cpu_n = 0;
            int io_n = 0;
            for (int j=2; j < space_count; j++){
                printf("--%d--\n", full[j]);
                if (j % 2 == 0){
                    // even numbers go in cpu burst
                    process[ln].cpu_bursts[cpu_n] = full[j];
                    cpu_n++;
                }else{
                    // odd numbers go in io burst
                    process[ln].io_bursts[io_n] = full[j];
                    //printf("this is io #%d %d\n", io_n, io[io_n]);
                    io_n++;
                    
                }
            }
            
            printf("%d \n", process[ln].io_bursts[0]);
            printf("%d \n", process[ln].io_bursts[1]);
            printf("%d \n", process[ln].io_bursts[2]);
            printf("%d \n", process[ln].io_bursts[3]);
            
            
            printf("%d \n", process[ln].cpu_bursts[0]);
            printf("%d \n", process[ln].cpu_bursts[1]);
            printf("%d \n", process[ln].cpu_bursts[2]);
            printf("%d \n", process[ln].cpu_bursts[3]);
            printf("%d \n", process[ln].cpu_bursts[4]);

            process[ln].pid = full[0];
            process[ln].arrival = full[1];
        } // end of line looping
        
    }
}







