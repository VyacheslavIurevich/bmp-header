#pragma once
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BMP_TYPE 0x4D42 // = BM
#define BMP3_INFO_HEADER_SIZE 40
#define BMP4_INFO_HEADER_SIZE 108
#define BMP5_INFO_HEADER_SIZE 124

#pragma pack(push, 1)

struct CIEXYZ {
  uint32_t x;
  uint32_t y;
  uint32_t z;
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
    struct CIEXYZ red;
    struct CIEXYZ green;
    struct CIEXYZ blue;
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

static FILE *open_file(int argc, char *argv[]);

static struct BITMAPFILEHEADER read_file_header(FILE *picture);

static struct BITMAPINFOHEADER read_info_header(FILE *picture,
                                                size_t pixels_offset);

static void print_header_version_3(struct BITMAPFILEHEADER *file_header,
                                   struct BITMAPINFOHEADER *info_header);

static void print_header_version_4(struct BITMAPFILEHEADER *file_header,
                                   struct BITMAPINFOHEADER *info_header);

static void print_header_version_5(struct BITMAPFILEHEADER *file_header,
                                   struct BITMAPINFOHEADER *info_header);

static void print_header(struct BITMAPFILEHEADER *file_header,
                         struct BITMAPINFOHEADER *info_header);
