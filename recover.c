/**
 * recover.c
 *
 * Recovers JPEGs from an image.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "jpg.h"

int main(int argc, char* argv[])
{
    // hardcode filename
    char* file = "card.raw";
    
    // open the file
    FILE* raw = fopen(file, "r");
    if (raw == NULL)
    {
        printf("Could not open file %s.\n", file);
        return 1;
    }
    
    // define a cluster in which to store the 512 bytes cluster to read
    CLUSTER cluster;
    
    int lines_read;
    
    // keep track of images found for filenames
    int imgs_found = 0;
    
    // reserve memory for file name
    char* file_name = malloc(8);
    
    // keep track of image found on disk, so remaining space can be skipped
    bool img_found = false;
    
    // define img file to create jpegs
    FILE* img = NULL;
    
    do
    {
        // check if end of file is reached
        lines_read = fread(&cluster, sizeof(CLUSTER), 1, raw);
        
        // check for startsequence of jpeg
        if (cluster.firstByte == 0xff && cluster.secondByte == 0xd8
        && cluster.thirdByte == 0xff && (cluster.fourthByte == 0xe0 
        || cluster.fourthByte == 0xe1))
        {
            // create new filename
            sprintf(file_name, "%03d.jpg", imgs_found);
            // increase counter of images found
            imgs_found++;
            
            if (img_found)
            {
                // close previous image
                fclose(img);
            }
            // image is found
            img_found = true;
            
            img = fopen(file_name, "w");
            if (img == NULL)
            {
                printf("Could not open file %s.\n", file_name);
            }
            
            // write cluster to file
            fwrite(&cluster, sizeof(CLUSTER), 1, img);
        }
        else
        {
            // write data in cluster to image found
            if (img_found && lines_read == 1)
            {
                // write cluster to file
                fwrite(&cluster, sizeof(CLUSTER), 1, img);
            }
        }
    }
    while (lines_read == 1);
    
    // close all files and free memory    
    fclose(img);
    free(file_name);
    fclose(raw);
    
    return 0;
}
