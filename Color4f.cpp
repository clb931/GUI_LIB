#include "Color4f.h"

Color4f::Color4f(float r, float g, float b, float a)
{
	std::wcout << L"Color4f::Color4f()" << std::endl;

	m_r = min(1.0f, r);
	m_g = min(1.0f, g);
	m_b = min(1.0f, b);
	m_a = min(1.0f, a);
}

Color4f::Color4f(unsigned int c)
{
	std::wcout << L"Color4f::Color4f()" << std::endl;

	m_a = ((c >> 24) & 0xFF) / 255.0f;
	m_r = ((c >> 16) & 0xFF) / 255.0f;
	m_g = ((c >> 8) & 0xFF) / 255.0f;
	m_b = ((c >> 0) & 0xFF) / 255.0f;
}

Color4f::~Color4f()
{
	std::wcout << L"Color4f::~Color4f()" << std::endl;
}

Color32 Color4f::ToColor32() const
{
	return Color32(
		((unsigned int)(m_a * 255.0f) << 24) |
		((unsigned int)(m_r * 255.0f) << 16) |
		((unsigned int)(m_g * 255.0f) << 8) |
		((unsigned int)(m_b * 255.0f) << 0));
}

Color4f Color4f::operator+=(const Color4f &top)
{
	m_r += top.m_r;
	m_g += top.m_g;
	m_b += top.m_b;
	m_a += top.m_a;
	return *this;
}

Color4f Color4f::operator-(const Color4f &top) const
{
	return Color4f(m_r - top.m_r, m_g - top.m_g, m_b - top.m_b, m_a - top.m_a);
}

Color4f Color4f::operator*(const Color4f &top) const
{
	return Color4f(m_r * top.m_r, m_g * top.m_g, m_b * top.m_b, m_a * top.m_a);
}

Color4f Color4f::operator/(const Color4f &top) const
{
	if (top.m_r == 0.0f && top.m_g == 0.0f && top.m_b == 0.0f)
		return Color4f();

	Color4f c(m_r / top.m_r, m_g / top.m_g, m_b / top.m_b, m_a / top.m_a);
	return c;
}

Color4f Color4f::operator*(float f) const
{
	return Color4f(m_r * f, m_g * f, m_b * f, m_a * f);
}

Color4f Color4f::operator/(float f) const
{
	return Color4f(m_r / f, m_g / f, m_b / f, m_a / f);
}

Color4f Color4f::operator~()
{
	return Color4f(1.0f - m_r, 1.0f - m_g, 1.0f - m_b, 1.0f - m_a);
}

Color4f operator+(Color4f bottom, const Color4f &top)
{
	return bottom += top;
}

char *GetBlendModeName(BlendMode blend_mode)
{
	char *result;

	switch (blend_mode) {
	default:
	case BLEND_NORMAL:
		result = "BLEND_NORMAL";
		break;
	case BLEND_ADD:
		result = "BLEND_ADD";
		break;
	case BLEND_SUBTRACT:
		result = "BLEND_SUBTRACT";
		break;
	case BLEND_MULTIPLY:
		result = "BLEND_MULTIPLY";
		break;
	case BLEND_DIVIDE:
		result = "BLEND_DIVIDE";
		break;
	case BLEND_SCREEN:
		result = "BLEND_SCREEN";
		break;
	case BLEND_OVERLAY:
		result = "BLEND_OVERLAY";
		break;
	case BLEND_COLOR_DOGE:
		result = "BLEND_COLOR_DOGE";
		break;
	case BLEND_COLOR_BURN:
		result = "BLEND_COLOR_BURN";
		break;
	case BLEND_DIFFERENCE:
		result = "BLEND_DIFFERENCE";
		break;
	case BLEND_DARKEN:
		result = "BLEND_DARKEN";
		break;
	case BLEND_LIGHTEN:
		result = "BLEND_LIGHTEN";
		break;
	}

	return result;
}

Color4f Blend(Color4f bottom, Color4f top, BlendMode blend_mode)
{
	Color4f result;

	switch (blend_mode) {
	default:
	case BLEND_NORMAL:
		result = BlendNormal(bottom, top);
		break;
	case BLEND_ADD:
		result = BlendAdd(bottom, top);
		break;
	case BLEND_SUBTRACT:
		result = BlendSubtract(bottom, top);
		break;
	case BLEND_MULTIPLY:
		result = BlendMultiply(bottom, top);
		break;
	case BLEND_DIVIDE:
		result = BlendDivide(bottom, top);
		break;
	case BLEND_SCREEN:
		result = BlendScreen(bottom, top);
		break;
	case BLEND_OVERLAY:
		result = BlendOverlay(bottom, top);
		break;
	case BLEND_COLOR_DOGE:
		result = BlendDodge(bottom, top);
		break;
	case BLEND_COLOR_BURN:
		result = BlendBurn(bottom, top);
		break;
	case BLEND_DIFFERENCE:
		result = BlendDifference(bottom, top);
		break;
	case BLEND_DARKEN:
		result = BlendDarken(bottom, top);
		break;
	case BLEND_LIGHTEN:
		result = BlendLighten(bottom, top);
		break;
	}

	return result;
}

Color4f BlendNormal(Color4f bottom, Color4f top)
{
	return top;
}

Color4f BlendAdd(Color4f bottom, Color4f top)
{
	return bottom + top;
}

Color4f BlendSubtract(Color4f bottom, Color4f top)
{
	return bottom - top;
}

Color4f BlendMultiply(Color4f bottom, Color4f top)
{
	return bottom * top;
}

Color4f BlendDivide(Color4f bottom, Color4f top)
{
	return bottom / top;
}

Color4f BlendScreen(Color4f bottom, Color4f top)
{
	return ~(~bottom * ~top);
}

Color4f BlendOverlay(Color4f bottom, Color4f top)
{
	Color4f c1 = (bottom * top) * 2.0f;
	Color4f c2 = ~((~bottom * ~top) * 2.0f);
	return Color4f(bottom.m_r < 0.5f ? c1.m_r : c2.m_r,
		bottom.m_g < 0.5f ? c1.m_g : c2.m_g,
		bottom.m_b < 0.5f ? c1.m_b : c2.m_b,
		bottom.m_a < 0.5f ? c1.m_a : c2.m_a);
}

Color4f BlendDodge(Color4f bottom, Color4f top)
{
	return bottom / ~top;
}

Color4f BlendBurn(Color4f bottom, Color4f top)
{
	return ~((~bottom) / top);
}

Color4f BlendDifference(Color4f bottom, Color4f top)
{
	Color4f c;
	c.m_r = bottom.m_r < top.m_r ? top.m_r - bottom.m_r : bottom.m_r - top.m_r;
	c.m_g = bottom.m_g < top.m_g ? top.m_g - bottom.m_g : bottom.m_g - top.m_g;
	c.m_b = bottom.m_b < top.m_b ? top.m_b - bottom.m_b : bottom.m_b - top.m_b;
	c.m_a = bottom.m_a < top.m_a ? top.m_a - bottom.m_a : bottom.m_a - top.m_a;
	return c;
}

Color4f BlendDarken(Color4f bottom, Color4f top)
{
	return Color4f(min(bottom.m_r, top.m_r), min(bottom.m_g, top.m_g), min(bottom.m_b, top.m_b), min(bottom.m_a, top.m_a));
}

Color4f BlendLighten(Color4f bottom, Color4f top)
{
	return Color4f(max(bottom.m_r, top.m_r), max(bottom.m_g, top.m_g), max(bottom.m_b, top.m_b), max(bottom.m_a, top.m_a));
}


struct hsv
{
	float h;
	float s;
	float v;
};

hsv rgb2hsv(Color4f in)
{
	hsv out;
	float min, max, delta;

	min = in.m_r < in.m_g ? in.m_r : in.m_g;
	min = min < in.m_b ? min : in.m_b;

	max = in.m_r > in.m_g ? in.m_r : in.m_g;
	max = min > in.m_b ? min : in.m_b;

	out.v = max;
	delta = max - min;
	if (max > 0.0) {
		out.s = (delta / max);
	}
	else {
		out.s = 0.0;
		out.h = NAN;
		return out;
	}
	if (in.m_r >= max)
		out.h = (in.m_g - in.m_b) / delta;
	else if (in.m_g >= max)
		out.h = 2.0f + (in.m_b - in.m_r) / delta;
	else
		out.h = 4.0f + (in.m_r - in.m_g) / delta;

	out.h *= 60.0f;

	if (out.h < 0.0)
		out.h += 360.0f;

	return out;
}

Color4f hsv2rgb(hsv in)
{
	Color4f out;
	float hh, p, q, t, ff;
	int i;

	if (in.s <= 0.0f) {
		out.m_r = in.v;
		out.m_g = in.v;
		out.m_b = in.v;
		return out;
	}

	hh = in.h;
	if (hh >= 360.0f) hh = 0.0f;
	hh /= 60.0f;
	i = (long)hh;
	ff = hh - i;
	p = in.v * (1.0f - in.s);
	q = in.v * (1.0f - (in.s * ff));
	t = in.v * (1.0f - (in.s * (1.0f - ff)));

	switch (i) {
	case 0:
		out.m_r = in.v;
		out.m_g = t;
		out.m_b = p;
		break;
	case 1:
		out.m_r = q;
		out.m_g = in.v;
		out.m_b = p;
		break;
	case 2:
		out.m_r = p;
		out.m_g = in.v;
		out.m_b = t;
		break;

	case 3:
		out.m_r = p;
		out.m_g = q;
		out.m_b = in.v;
		break;
	case 4:
		out.m_r = t;
		out.m_g = p;
		out.m_b = in.v;
		break;
	case 5:
	default:
		out.m_r = in.v;
		out.m_g = p;
		out.m_b = q;
		break;
	}
	return out;
}

Color4f LerpColor(Color4f min_color, Color4f max_color, float step)
{
	//hsv ca = rgb2hsv(min_color);
	//hsv cb = rgb2hsv(max_color);
	//hsv result;

	//result.h = ca.h * (1 - step) + cb.h * step;
	//result.s = ca.s * (1 - step) + cb.s * step;
	//result.v = ca.v * (1 - step) + cb.v * step;

	//return hsv2rgb(result);

	return lerp(min_color, max_color, step);
}

const Color4f Color4f::RED = Color4f(1.0f, 0.0f, 0.0f, 0.1f);
const Color4f Color4f::GREEN = Color4f(0.0f, 1.0f, 0.0f, 0.1f);
const Color4f Color4f::BLUE = Color4f(0.0f, 0.0f, 1.0f, 0.1f);
const Color4f Color4f::BLACK = Color4f(0.0f, 0.0f, 0.0f, 0.1f);
const Color4f Color4f::CYAN = Color4f(0.0f, 1.0f, 1.0f, 0.1f);
const Color4f Color4f::MAGENTA = Color4f(1.0f, 0.0f, 1.0f, 0.1f);
const Color4f Color4f::YELLOW = Color4f(1.0f, 1.0f, 0.0f, 0.1f);
const Color4f Color4f::WHITE = Color4f(1.0f, 1.0f, 1.0f, 0.1f);
const Color4f Color4f::DARK_GRAY = Color4f(0.2f, 0.2f, 0.2f, 0.1f);
const Color4f Color4f::LIGHT_GRAY = Color4f(0.8f, 0.8f, 0.8f, 0.1f);