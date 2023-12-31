#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE* fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        printf("Unable to open file!\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER head;             // the 1st 44 bytes of a .wav file
                                // Reading 1st chunk of WAV header: (contains file format)
    for (int i = 0; i < 4; i++) // reads "RIFF"
    {
        fread(&head.chunkID[i], sizeof(char), 1, fptr);
    }
    fread(&head.chunkSize, sizeof(DWORD), 1, fptr);
    for (int i = 0; i < 4; i++) // reads "WAVE"
    {
        fread(&head.format[i], 1, 1, fptr);
    }

    // Reading 2nd chunk of WAV header: (contains info about the channels & sample: speed,etc.)
    for (int i = 0; i < 4; i++) // reads "fmt "
    {
        fread(&head.subchunk1ID[i], 1, 1, fptr);
    }
    fread(&head.subchunk1Size, sizeof(DWORD), 1, fptr);
    fread(&head.audioFormat, sizeof(WORD), 1, fptr);
    fread(&head.numChannels, sizeof(WORD), 1, fptr);
    fread(&head.sampleRate, sizeof(DWORD), 1, fptr);
    fread(&head.byteRate, sizeof(DWORD), 1, fptr);
    fread(&head.blockAlign, sizeof(WORD), 1, fptr);
    fread(&head.bitsPerSample, sizeof(WORD), 1, fptr);

    // Reading 3rd chunk of WAV header: (contains the audio data)
    for (int i = 0; i < 4; i++)
    {
        fread(&head.subchunk2ID[i], sizeof(BYTE), 1, fptr);
    }
    fread(&head.subchunk2Size, sizeof(DWORD), 1, fptr);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(head) == 0)
    {
        printf("Input file must be a .wav file!\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE* ofptr = fopen(argv[2], "w");
    if (ofptr == NULL)
    {
        printf("Unable to create a new file!\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    // Writing 1st chunk of WAV header: (contains file format)
    for (int i = 0; i < 4; i++) // writes "RIFF"
    {
        fwrite(&head.chunkID[i], sizeof(char), 1, ofptr);
    }
    fwrite(&head.chunkSize, sizeof(DWORD), 1, ofptr);
    for (int i = 0; i < 4; i++) // writes "WAVE"
    {
        fwrite(&head.format[i], 1, 1, ofptr);
    }

    // Writing 2nd chunk of WAV header: (contains info about the channels & sample: speed,etc.)
    for (int i = 0; i < 4; i++) // writes "fmt "
    {
        fwrite(&head.subchunk1ID[i], 1, 1, ofptr);
    }
    fwrite(&head.subchunk1Size, sizeof(DWORD), 1, ofptr);
    fwrite(&head.audioFormat, sizeof(WORD), 1, ofptr);
    fwrite(&head.numChannels, sizeof(WORD), 1, ofptr);
    fwrite(&head.sampleRate, sizeof(DWORD), 1, ofptr);
    fwrite(&head.byteRate, sizeof(DWORD), 1, ofptr);
    fwrite(&head.blockAlign, sizeof(WORD), 1, ofptr);
    fwrite(&head.bitsPerSample, sizeof(WORD), 1, ofptr);

    // Writing 3rd chunk of WAV header: (contains the audio data)
    for (int i = 0; i < 4; i++)
    {
        fwrite(&head.subchunk2ID[i], sizeof(BYTE), 1, ofptr);
    }
    fwrite(&head.subchunk2Size, sizeof(DWORD), 1, ofptr);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(head);

    // Write reversed audio to file
    // TODO #8
    // Check for correctness by writing the same audio

    // Reversing the blocks:
    BYTE* block = (BYTE*) malloc(block_size);
    fseek(fptr, -(block_size), SEEK_END);
    while (ftell(fptr) != 44 - (block_size)) // to determine EOF
    {
        for (int i = 0; i < block_size; i++)
        {
            fread(block + i, 1, 1, fptr);
            fwrite(block + i, 1, 1, ofptr);
        }
        fseek(fptr, -2 * (block_size), SEEK_CUR);
    }

    // closing the files:
    free(block);
    fclose(fptr);
    fclose(ofptr);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if ((header.format[0] == 'W') && (header.format[1] == 'A') && (header.format[2] == 'V') && (header.format[3] == 'E'))
        return 1;
    else
        return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int block_size = 0;
    block_size = (header.numChannels) * ((header.bitsPerSample) / 8);
    return block_size;
}