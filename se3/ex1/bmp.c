#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "bmp.h"

int main(int argc, char *argv[]) {
    if ((argc != 2 && argc != 3) || strlen(argv[1]) < 5 ||
        strcmp(argv[1] + (strlen(argv[1]) - 4), ".bmp") != 0) {
        fprintf(stderr, "use: %s {filename}.bmp [offset]\n", argv[0]);
        return 1;
    }

    int offset = 0;
    if(argc == 3) {
        offset = atoi(argv[2]);
        if (offset < -255 || offset > 255) {
            fprintf(stderr, "invalid offset value '%i'", offset);
            return 2;
        }
    }

    int fd = open(argv[1], O_RDWR);

    struct stat buf;
    fstat(fd, &buf);
    off_t size = buf.st_size;

    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    BITMAPFILEHEADER *bmfh = (BITMAPFILEHEADER *) ptr;

    char *bfType = ((char *) &bmfh->bfType);
//    bfType[2] = '\0';

    printf("bfType: %s (Should be '%s')\nbfSize: %u\nbfOffBits: %u\n", bfType, (char *) &BMP_MAGIC, bmfh->bfSize,
           bmfh->bfOffBits);

    BITMAPINFOHEADER *bmih = (BITMAPINFOHEADER *) (ptr + sizeof(BITMAPFILEHEADER));
    printf("biWidth: %u\nbiHeight: %u\nbiBitCount: %u\nbiCompression:%u\n", bmih->biWidth, bmih->biHeight,
           bmih->biBitCount, bmih->biCompression);

    if (offset != 0 && bmih->biCompression == 0 && bmih->biBitCount == 24 && (bmih->biWidth % 4) == 0 ) {
        int pixelCount = bmih->biWidth * bmih->biHeight;
        for (int i = 0; i < pixelCount; i++) {
            RGBTRIPLE *rgb = (RGBTRIPLE *) (ptr + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
                                            (sizeof(RGBTRIPLE) * i));
            //printf("From: R:%u G:%u B:%u\n", rgb->rgbtRed, rgb->rgbtGreen, rgb->rgbtBlue);
            rgb->rgbtRed = (rgb->rgbtRed + offset) > 255 ? (rgb->rgbtRed + offset) - 256 :
                           (rgb->rgbtRed + offset) < 0 ? (rgb->rgbtRed + offset) + 256 :
                           (rgb->rgbtRed + offset);
            rgb->rgbtGreen = (rgb->rgbtGreen + offset) > 255 ? (rgb->rgbtGreen + offset) - 256 :
                             (rgb->rgbtGreen + offset) < 0 ? (rgb->rgbtGreen + offset) + 256 :
                             (rgb->rgbtGreen + offset);
            rgb->rgbtBlue = (rgb->rgbtBlue + offset) > 255 ? (rgb->rgbtBlue + offset) - 256 :
                            (rgb->rgbtBlue + offset) < 0 ? (rgb->rgbtBlue + offset) + 256 :
                            (rgb->rgbtBlue + offset);
            //printf("To:   R:%u G:%u B:%u\n", rgb->rgbtRed, rgb->rgbtGreen, rgb->rgbtBlue);
        }
    }

    return 0;
}
