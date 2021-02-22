#include <iostream>
#include <string>
//-----------------------------------------------------------------------------------------//
//  Automatically writes if/else if/else code blocks for a VGA pixel generator             //
//   that displays 16 equal color and gray scale lines                                     //
//                                                                                         //
//  Variables                                                                              //
//    vert_var          (string) - tracks vertical line num, 11 bits                       //
//    vert_f_param      (string) - parameter for vertical front porch, 11bits              //
//    switch_var        (string) - variable name to switch between color/gray scale, 1 bit //
//    vert_active_lines (int)    - number of active video vertical lines                   //
//                                                                                         //
//  Written by Alakh P. on 2/21/21                                                         //
//-----------------------------------------------------------------------------------------//

//TODO - add argument inputs
//run program into output file. i.e.
//  "./main > code.txt"
int main(int argc, char** argv) {
  char* vert_var;
  char* vert_f_param;
  char* switch_var;
  int   vert_active_lines;
  //assumed 11 bit vert vars/params, 1 bit switch param
  vert_var          = "vert_lines";
  vert_f_param      = "VERT_FPORCH";
  switch_var        = "switch";
  vert_active_lines = 720;
  

  int colorscale [16][3] = {{0xB2,0x00,0x00}, {0xFF,0x7F,0x7F},{0xFF,0x9F,0x7F},{0xFF,0xCF,0x7F},{0xEF,0xFF,0x7F},{0xAF,0xFF,0x7F},{0x7F,0xFF,0x7F},{0x7F,0xFF,0xB2},{0x7F,0xE9,0xFF},{0x7F,0xB0,0xFF},{0x7F,0x88,0xFF},{0xAE,0x7F,0xFF},{0x41,0x00,0xB2},{0xE5,0x7F,0xFF},{0xFF,0x7F,0xD0},{0xFF,0x7F,0x94}};
  //only need one color since all same in grayscale
  int grayscale [16]  = {0xFF, 0xF0,0xE1,0xD2,0xC3,0xB4,0xA5,0x96,0x87,0x78,0x69,0x5A,0x4B,0x3C,0x2D,/*0x1E,0x0F,*/0x00};

  printf("if(~reset_n) begin\n  VGA_R = 8'hFF;\n  VGA_G = 8'hFF;\n  VGA_B = 8'hFF;\n" );
  for(int i = 0; i < 16; i++){
    printf("end else if(%s > %s + 11'd%d && %s < %s + 11'd%d) begin\n",vert_var,vert_f_param,i*45,vert_var,vert_f_param,(i+1)*45);
    printf("  if(%s) begin\n    VGA_R = 8'h%x;\n    VGA_G = 8'h%x;\n    VGA_B = 8'h%x;\n  end else begin\n    VGA_R = 8'h%x;\n    VGA_G = 8'h%x;\n    VGA_B = 8'h%x;\n  end\n",switch_var,grayscale[i],grayscale[i],grayscale[i],colorscale[i][1],colorscale[i][2],colorscale[i][3]);
  }
  printf("end else begin\n  VGA_R = 8'h00;\n  VGA_G = 8'h00;\n  VGA_B = 8'h00;\nend");
}
