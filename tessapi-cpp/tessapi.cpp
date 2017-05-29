// tessapi.cpp : Defines the entry point for the console application.
//


#include "tessapi.h"
#include "math.h"



tesseract::TessBaseAPI* base_api_create() {
	return new tesseract::TessBaseAPI();
}

void api_end(tesseract::TessBaseAPI* tess) {
	tess->End();
}

void api_init(tesseract::TessBaseAPI* tess, const char* lang) {
	tess->Init("./tessdata", lang);
}


/**
 * Should be used before initalizaton
 * Settings == 1 disables dictionaries
 */
void api_setup(tesseract::TessBaseAPI* tess, int settings) {
	tess->SetPageSegMode(tesseract::PageSegMode::PSM_AUTO);
	tess->SetVariable("save_best_choices", "T");
	if (settings == 1) {
		tess->SetVariable("load_system_dawg", "0");
		tess->SetVariable("load_freq_dawg", "0");
	}
}

// Set image by path
int set_img_path(tesseract::TessBaseAPI* tess, const char* path) {
	PIX* pixs = pixRead(path);
	return rec_img(tess, pixs);	
}

// Set image by array. Only Tiff format supported on Windows
int set_img_array(tesseract::TessBaseAPI* tess, l_uint8* im_array, int size, int page = 0 ) {
	PIX* pixs = pixReadMemTiff(im_array, size, page);
	return rec_img(tess, pixs);
}

// Recognizes text from image and saves it to an internal buffer
int rec_img(tesseract::TessBaseAPI* tess, PIX* pixs) {
	if (!pixs) { return 1; }

	Pix* pixb = binarization_otsu(pixs);

	pixWrite("pic_binary.tif", pixb, IFF_TIFF);

	tess->SetImage(pixb);
	pixDestroy(&pixs);
	pixDestroy(&pixb);

	return tess->Recognize(0);
}

/**
 * Returns text by writing to a given buffer. Since the buffer can be smaller
 * than the real text contained, this function can be called multiple times with
 * with increased offset.
 * Returns 0 if end of text reachee
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

// Gets length of internaly stored text
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


#define SCOREFRACT 0.1
#define X_RES 100
#define Y_RES 100
#define SMOOTHING 2
// Binarizaion by the otsu method. First turns image to grayscale
Pix* binarization_otsu(Pix* pixs) {
	if (!pixs) {
		return nullptr;
	}

	Pix* pixg = pixConvertRGBToGray(pixs, 0, 0, 0);

	Pix* temp;
	Pix* r_pix;
	l_int32 thresh = pixOtsuAdaptiveThreshold(pixg, X_RES, Y_RES, SMOOTHING, SMOOTHING, SCOREFRACT, &temp, &r_pix);

	pixDestroy(&pixg);
	pixDestroy(&temp);
	
	return r_pix;
}


/*
int main(int argc, char *argv[]){
	return 0;
}*/