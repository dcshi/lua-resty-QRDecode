#include <iostream>
#include <fstream>
#include <string>
#include <Magick++.h>
#include "MagickBitmapSource.h"
#include <zxing/common/Counted.h>
#include <zxing/Binarizer.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/Result.h>
#include <zxing/ReaderException.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/common/HybridBinarizer.h>
#include <exception>
#include <zxing/Exception.h>
#include <zxing/common/IllegalArgumentException.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/DecodeHints.h>

#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/multi/qrcode/QRCodeMultiReader.h>
#include <zxing/multi/ByQuadrantReader.h>
#include <zxing/multi/MultipleBarcodeReader.h>
#include <zxing/multi/GenericMultipleBarcodeReader.h>

#ifndef __cplusplus
#define __cplusplus
#endif
#include "QRDecode.h"

using namespace Magick;
using namespace std;
using namespace zxing;
using namespace zxing::multi;
using namespace zxing::qrcode;

static bool tryHarder = false;

Ref<Result> decode(Ref<BinaryBitmap> image, DecodeHints hints) {
	Ref<Reader> reader(new MultiFormatReader);
	return reader->decode(image, hints);
}

int decode_image(Image& image, bool hybrid, string& cell_result) {

	int res = 0;
	cell_result = "";

	Ref<BitMatrix> matrix(NULL);
	Ref<Binarizer> binarizer(NULL);
	const char* result_format = "";

	try {
		Ref<MagickBitmapSource> source(new MagickBitmapSource(image));

		if (hybrid) {
			binarizer = new HybridBinarizer(source);
		} else {
			binarizer = new GlobalHistogramBinarizer(source);
		}

		DecodeHints hints(DecodeHints::DEFAULT_HINT);
		hints.setTryHarder(tryHarder);
		Ref<BinaryBitmap> binary(new BinaryBitmap(binarizer));
		Ref<Result> result(decode(binary, hints));
		cell_result = result->getText()->getText();
		result_format = barcodeFormatNames[result->getBarcodeFormat()];
	} 
	catch (ReaderException e) {
		cell_result = "zxing::ReaderException: " + string(e.what());
		res = -2;
	} 
	catch (zxing::IllegalArgumentException& e) {
		cell_result = "zxing::IllegalArgumentException: " + string(e.what());
		res = -3;
	} 
	catch (zxing::Exception& e) {
		cell_result = "zxing::Exception: " + string(e.what());
		res = -4;
	} 
	catch (std::exception& e) {
		cell_result = "std::exception: " + string(e.what());
		res = -5;
	}

	return res;
}

int image_hybrid(Image& image, string& result) {
	return decode_image(image, true, result);
}

int image_global(Image& image, string& result) {
	return decode_image(image, false, result);
}

int QRDecode(const char *file, char *data, int maxlen)
{
	string result;
	Image image;

    try {
      image.read(file);
    } 
	catch (...) {
      cerr << "Unable to open image, ignoring" << endl;
	  return -1;
    }

	int res;
	
	res = image_hybrid(image, result);
	if (res == 0 && maxlen > result.size()) 
		goto done;

	res = image_global(image, result);
	if (res < 0 || maxlen <= result.size())
		return -1;

done:
	memcpy(data, result.c_str(), result.size());
	
	return 0;
}
