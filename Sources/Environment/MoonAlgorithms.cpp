#include <Engine/Headers/EsenthelEngine.h>

inline void createMoonMask() {
	ImagePtr originalImage = UID(751191074, 1273901359, 2472514488, 2970955246); // Images/Moon/triron
	auto height = originalImage()->h();
	auto width = originalImage()->w();
	auto depth = originalImage()->d();
	originalImage = NULL;

	Image image(width, height, depth, IMAGE_R8G8B8A8, IMAGE_2D);

	image.lock();
	for (auto x = 0; x < width; ++x) {
		Vec4 pixelColour(1.0 - x * 1.0 / width, 1.0 - x * 1.0 / width, 1.0 - x * 1.0 / width, 1);
		for (auto y = 0; y < height; ++y) {
			auto value = -Pow(1.0 / Sqrt(width) * (y - width / 2), 2) + x;
			// circle point formula (x - a)^2 + (y - b)^2 = r^2, (x, y) - point coordinates; (a, b) - center coordinates
			if ((value - width / 2) * (value - width / 2) + (y - height / 2) * (y - height / 2) <= width / 2 * width / 2) {
				image.colorF(value, y, pixelColour);
			} else {
				image.colorF(value, y, Vec4(0, 0, 0, 0));
			}


		}
	}
	image.unlock();

	image.ExportPNG("result.png");
}