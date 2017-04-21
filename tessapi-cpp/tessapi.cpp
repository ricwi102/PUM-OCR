// tessapi.cpp : Defines the entry point for the console application.
//


#include "tessapi.h"
#include "math.h""



tesseract::TessBaseAPI* base_api_create() {
	return new tesseract::TessBaseAPI();
}

void api_end(tesseract::TessBaseAPI* tess) {
	tess->End();
}

void api_init(tesseract::TessBaseAPI* tess, const char* lang = "eng") {
	tess->Init("./tessdata", "eng");
}

void api_setup(tesseract::TessBaseAPI* tess) {
	tess->SetPageSegMode(tesseract::PageSegMode::PSM_AUTO);
	tess->SetVariable("save_best_choices", "T");
}

int set_img_path(tesseract::TessBaseAPI* tess, const char* path) {
	PIX* pixs = pixRead(path);
	return rec_img(tess, pixs);	
}

int set_img_array(tesseract::TessBaseAPI* tess, l_uint8* im_array, int size, int page = 0 ) {
	PIX* pixs = pixReadMemTiff(im_array, size, page);
	return rec_img(tess, pixs);
}

int rec_img(tesseract::TessBaseAPI* tess, PIX* pixs) {
	if (!pixs) { return 1; }

	tess->SetImage(pixs);
	pixDestroy(&pixs);

	return tess->Recognize(0);
}
/**
 * Returns text by writing to a given buffer. Since the buffer can be smaller
 * than the real text contained, this function can be called multiple times with
 * with increased offsets.
 * Returns 0 if there 
 * output: Output buffer
 * offset: Offset in bufferlengths
 * length: Length of the buffer
 */
int get_text(tesseract::TessBaseAPI* tess, char* output, const int offset, const int length) {
	
	const char* text = tess->GetUTF8Text();	

	int text_length = strlen(text) + 1; //Includes null char at the end
	int offset_i = offset * length;
	int diff = text_length - offset_i;	

	if (diff <= 0) { return 0; }

	int r_value = (diff > length);
	if (r_value) {	
		diff = length;	
	}
	c_str_cpy(output, (text + offset_i), diff);
	
	delete[] text;
	return r_value;	
}

int get_text_length(tesseract::TessBaseAPI* tess, int incl_null = 1) {
	const char* text = tess->GetUTF8Text();
	int length = strlen(text);
	delete[] text;
	return length + incl_null;
}

void c_str_cpy(char* destination, const char* source, const int length) {
	for (int i = 0; i < length; ++i) {
		*(destination + i) = *(source + i);
	}
}

void tess_clear(tesseract::TessBaseAPI* tess) {
	tess->Clear();
}

void get_init_lang(tesseract::TessBaseAPI* tess, char* output) {
	strcpy(output, tess->GetInitLanguagesAsString());
}

/* 
int main(int argc, char *argv[])
{

	std::cout << "program started\n\n";

	tesseract::TessBaseAPI* tess = base_api_create();
	api_init(tess);
	api_setup(tess);
	set_pic_path(tess, argv[1]);

	char text[10];
	int i = 0;
	char real_text[300];
	while (get_text(tess, text, i, 10, 0)) {
		for (int j = 0; j < 10; ++j) {
			real_text[i * 10 + j] = text[j];
		}
		i++;
	}
	
	std::cout << real_text;

	tess_clear(tess);
	delete[] tess;

	return 0;
}*/

