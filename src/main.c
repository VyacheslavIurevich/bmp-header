#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

#pragma pack(push, 1)

struct CIEXYZ {
    uint32_t ciexyz_x;
    uint32_t ciexyz_y;
    uint32_t ciexyz_z;
};

struct BITMAPFILEHEADER {
    uint16_t type;
    uint32_t size;
    uint16_t reversed1;
    uint16_t reversed2;
    uint32_t offbits;
};

struct BITMAPINFOHEADER {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t size_image;
    int32_t x_pels_per_meter;
    int32_t y_pels_per_meter;
    uint32_t clr_used;
    uint32_t clr_important;
    // next fields are only used in versions 4-5
    uint32_t red_mask;
    uint32_t green_mask;
    uint32_t blue_mask;
    uint32_t alpha_mask;
    uint32_t cs_type;
    struct CIEXYZTRIPLE {
        struct CIEXYZ ciexyz_red;
        struct CIEXYZ ciexyz_green;
        struct CIEXYZ ciexyz_blue;
    } end_points;
    uint32_t gamma_red;
    uint32_t gamma_green;
    uint32_t gamma_blue;
    // next fields are only used in version 5
    uint32_t intent;
    uint32_t profile_data;
    uint32_t profile_size;
    uint32_t reserved;
};

#pragma pack(pop)

int main(int argc, char *argv[]) {
    FILE* picture = fopen(argv[1], "r");
    struct BITMAPFILEHEADER file_header;
    struct BITMAPINFOHEADER info_header;
    size_t file_header_size = sizeof(file_header);
    size_t info_header_size = sizeof(info_header);
    size_t file_header_success;
    size_t info_header_success;
    size_t pixels_offset;
    
    if (picture == NULL) {
        fprintf(stderr, "File parsing error\n");
        exit(-1);
    }

    file_header_success = fread(&file_header, file_header_size, 1, picture);
    pixels_offset = file_header.offbits - file_header_size;
    info_header_size = pixels_offset > info_header_size ? info_header_size : pixels_offset;
    info_header_success = fread(&info_header, info_header_size, 1, picture);

    fclose(picture);
    return 0;
}
