#include <Engine/Headers/EsenthelEngine.h>

// get y-coordinate of ellipse with specified "a"-value and "b"-value = 1
// width2 is width / 2, where width is width of original image
inline float getY(float x, float a, float width2) {
	auto temp = Pow(width2, 2) - Pow(x, 2);
	float y;
	// wrapped with if-else, cause Esenthel Engine's Sqrt method return UNDEF, upon Sqrt(0)
	if (temp == 0) {
		y = 0;
	} else {
		y = Sqrt(temp / Pow(a, 2));
	}
	// floor desired value, cause we're working with pixels positions
	return Floor(y);
}

// width2 is width / 2, where width is width of original image
// get gradient luminance of pixel on position (?, y)
// assuming 0 (black) luminance at y = width
//          0.5 (grey) luminance at y = width / 2
//			1 (white) luminance at y = 0
inline float getLuminance(float y, int width2) {
	return 0.5 * (y + width2) / width2;
}

// L0 - luminance of pixel on position (0, y) for current ellipse "a"-value
// width2 is width / 2, where width is width of original image
inline float getColourIntencity(float x, float y, float L0, float width2) {
	// limunance of pixel on position (x, y); typical gradient luminance
	auto L1 = getLuminance(y, width2);
	//
	// transponates pixels interval to luminance interval
	// i.e.: let x = -width/2 and ellipse "a"-value = 1
	//		 so calculated "y" will be = 0
	//		 and L1 = 0.5 (pixel with (-width/2, 0) coordinates are in middle of picture and it's grey)
	//		 and L0 = 1
	//
	// this line of code try to transpont
	// -width/2            0
	// |-------------------|
	//
	// to
	//
	// 0.5                 1
	// |-------------------|	
	//
	auto temp = Abs(x) * Tan((L0 - L1) / width2);
	// also add center limunance, for correctness
	return temp + L0;
}

// sets pixel to image if it's inside circle with radius width2
// width2 is width / 2, where width is width of original image
void setPixelIfInsideCircle(Image& image, float width2, float x2, float y, float colorIntencity) {
	auto colour = Vec4(colorIntencity, colorIntencity, colorIntencity, 1);
	if ((x2 - width2) * (x2 - width2) + (y - width2) * (y - width2) <= width2 * width2) {
		image.colorF(x2, y, colour);
	}
}

// create black-&-white moon mask, based on moon's image size
//
// this code create series of ellipses (changing "a"-value, "b"-value = 1), flattening them by y-axis,
// increasing it's eccenricity values, begining from circle
// (see https://upload.wikimedia.org/wikipedia/commons/5/54/Ellipse_and_hyperbola.gif)
// so it looks like ellipse inside ellise, inside ellipse and so on
// mathematicaly it looks like
// x^2/a^2 + y^2 = r^2/a^2
// if a = 1, result is circle (eccentricity = 0)
// if a > 1, result is ellipse (eccentricity = sqrt(1 - 1/a))
// if a -> INF, result is line (eccentricity = INF)
// 
// On each calculated ellise, also each pixel's luminance calculated (see upper functions descriptions)
// 
// NOTE: cause straight line eccentricity value equal INFINITY
// you can't achieve complete image with all pixels filled, anyway you will
// get some transparent pixels in center (which can be easilly manually replaced, using some image editor, even MS Paint)
inline void createMoonMask() {
	ImagePtr originalImage = UID(751191074, 1273901359, 2472514488, 2970955246); // Images/Moon/triron
	auto height = originalImage()->h();
	auto width = originalImage()->w();
	auto depth = originalImage()->d();
	originalImage = NULL;

	Image image(width, height, depth, IMAGE_R8G8B8A8, IMAGE_2D);

	float width2 = width / 2;
	float STEP = 1.0 / width2;	
	float previousValue = width;
	// pixel "y"-value for x = 0, for specific ellipse "a"-value
	float y0;
	// luminance in "y0" position
	float L0;
	// luminance in "-y0" position
	float nL0;

	image.lock();
	for (auto a = 1.0; a < width2; a += STEP) {
		y0 = width2 / a;
		L0 = getLuminance(y0, width2);		
		nL0 = getLuminance(-y0, width2);
		for (auto x = -width2; x < width2; ++x) {			
			auto x2 = x + width2;

			// process down hemisphere
			auto y = getY(x, a, width2);			
			auto colorIntencity = getColourIntencity(x, y, L0, width2);			
			y += width2;			
			setPixelIfInsideCircle(image, width2, x2, y, colorIntencity);

			// process upper hemisphere
			y = getY(x, a, width2);
			y *= -1;
			colorIntencity = getColourIntencity(x, y, nL0, width2);

			y += width2;
			setPixelIfInsideCircle(image, width2, x2, y, colorIntencity);			
		}

		// transponated "y"-position according image center
		auto temp = y0 + width2;
		// this code manage to perform one ellipse per "y"-position pixel (increasing performance)
		// it tries to achieve correct step of computation, de/increasing it
		// if ellipses draws too spradly or too closely
		if (Floor(previousValue) - Floor(temp) < 1.0) {
			// more step value you set here - less glitches you will receive, more time it will consume
			STEP += 20;// 1.0 / width2; 
		} else if (Floor(previousValue) - Floor(temp) > 1.0) {
			a = a - STEP;
			// more step value you set here - less glitches you will receive, more time it will consume
			STEP -= 20; // 1.0 / width2;
		} else {
			previousValue = temp;
		}
	}
	image.unlock();

	image.ExportPNG("result.png");
}