#pragma once


#include <allheaders.h>
#include <baseapi.h>
#include <iostream>
#include <memory>
#include <stdio.h>


#define DLL_EXPORT __declspec(dllexport)

extern "C" {
	DLL_EXPORT tesseract::TessBaseAPI* base_api_create();
	DLL_EXPORT void api_end(tesseract::TessBaseAPI* tess);
	DLL_EXPORT void api_init(tesseract::TessBaseAPI* tess, const char* lang);
	DLL_EXPORT void api_setup(tesseract::TessBaseAPI* tess);	

	DLL_EXPORT int set_img_path(tesseract::TessBaseAPI* tess, const char* path);
	DLL_EXPORT int set_img_array(tesseract::TessBaseAPI* tess, l_uint8* im_array, int size, int page);

	DLL_EXPORT int get_text(tesseract::TessBaseAPI* tess, char* output, int iter, int length);
	DLL_EXPORT int get_text_length(tesseract::TessBaseAPI* tess, int incl_null);

	DLL_EXPORT void tess_clear(tesseract::TessBaseAPI* tess);
	DLL_EXPORT void get_init_lang(tesseract::TessBaseAPI* tess, char* output);	
}

// Internal functions
int rec_img(tesseract::TessBaseAPI* tess, PIX* pixs);
void c_str_cpy(char* destination, const char* source, const int length);


