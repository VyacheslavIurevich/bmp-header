#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    die("There must be one command line argument\n")
  }

  FILE *picture = fopen(argv[1], "r");
  struct BITMAPFILEHEADER file_header;
  struct BITMAPINFOHEADER info_header;
  size_t file_header_size = sizeof(file_header);
  size_t info_header_size = sizeof(info_header);
  size_t pixels_offset;

  if (picture == NULL) {
    die("Picture reading error\n")
  }

  if (fread(&file_header, file_header_size, 1, picture) != 1) {
    die("File header reading error\n")
  }

  if (file_header.type != BMP_TYPE) {
    die("Not a BMP file passed in command line argument\n")
  }

  if (file_header.reversed1 != 0) {
    die("File header's reserved1 field must be equal to 0\n")
  }

  if (file_header.reversed2 != 0) {
    die("File header's reserved2 field must be equal to 0\n")
  }

  pixels_offset = file_header.offbits - file_header_size;
  info_header_size =
      pixels_offset > info_header_size ? info_header_size : pixels_offset;

  if (fread(&info_header, info_header_size, 1, picture) != 1) {
    die("Info header reading error\n")
  }

  if (info_header.planes != 1) {
    die("Info header's planes field must be equal to 1\n")
  }

  if (info_header.size != BMP3_INFO_HEADER_SIZE &&
      info_header.size != BMP4_INFO_HEADER_SIZE &&
      info_header.size != BMP5_INFO_HEADER_SIZE) {
    die("Incorrect info header size, must be 40, 108 or 124\n")
  }

  printf("Size: %u\n", file_header.size);
  printf("BMP Info header size: %u\n", info_header.size);
  printf("Width: %d\n", info_header.width);
  printf("Height: %d\n", info_header.height);
  printf("Planes: %u\n", info_header.planes);
  printf("Bits/pixel: %u\n", info_header.bit_count);
  printf("Compression: %u\n", info_header.compression);
  printf("Image size: %u\n", info_header.size_image);
  printf("Pixels/meter: %dx%d\n", info_header.x_pels_per_meter,
         info_header.y_pels_per_meter);
  printf("Colors number: %u\n", info_header.clr_used);
  printf("Important colors: %u\n", info_header.clr_important);

  if (info_header.size == BMP3_INFO_HEADER_SIZE) {
    close();
  }

  printf("Red mask: %x\n", info_header.red_mask);
  printf("Green mask: %x\n", info_header.green_mask);
  printf("Blue mask: %x\n", info_header.blue_mask);
  printf("Alpha mask: %x\n", info_header.alpha_mask);
  printf("Color space type: %x\n", info_header.cs_type);

  if (info_header.cs_type == 0) {
    printf("CIEXYZ Red: %x %x %x\n", info_header.end_points.red.x,
           info_header.end_points.red.y, info_header.end_points.red.z);
    printf("CIEXYZ Green: %x %x %x\n", info_header.end_points.green.x,
           info_header.end_points.green.y, info_header.end_points.green.z);
    printf("CIEXYZ Blue: %x %x %x\n", info_header.end_points.blue.x,
           info_header.end_points.blue.y, info_header.end_points.blue.z);
    printf("Gamma: %x %x %x\n", info_header.gamma_red, info_header.gamma_green,
           info_header.gamma_blue);
  }

  if (info_header.size == BMP4_INFO_HEADER_SIZE) {
    close()
  }

  if (info_header.reserved != 0) {
    die("In 5th version info header's field reserved must be equal to 0\n")
  }

  printf("Intent: %u\n", info_header.intent);
  printf("Profile data: %u\n", info_header.profile_data);
  printf("Profile size: %u\n", info_header.profile_size);

  close()
}
