/* qui inclut tous les transferts et conversions de couleurs */
/* jj 2005 base sur Foley, Van Dam, Feiner, Hugues           */

#include "ima.h"

#define UNDEFINED -1.0

void range (float a, float b, float c, float *x, float *y, float *z) {
  if (a > b) {
	if (b > c) {
	  *x = a;
	  *y = b;
	  *z = c;
	}
	else {
	  *z = b;
	  if (a > c) {
		*x = a;
		*y = c;
	  }
	  else {
		*x = c;
		*y = a;
	  }
	}
  }
  else {
	if (a > c) {
	  *x = b;
	  *y = a;
	  *z = c;
	}
	else {
	  *z = a;
	  if (b > c) {
		*x = b;
		*y = c;
	  }
	  else {
		*x = c;
		*y = b;
	  }
	}
  }
}
	  
void floattoint3(float r, float g, float b, int *rr, int *gg, int *bb) {
  *rr = (int) (0.5 + r * 255.0);
  *gg = (int) (0.5 + g * 255.0);
  *bb = (int) (0.5 + b * 255.0);
}
void inttofloat3(int r, int g, int b, float *rr, float *gg, float *bb) {
  *rr = ( r / 255.0);
  *gg = ( g / 255.0);
  *bb = ( b / 255.0);
}


void rgbtohls(float r, float g, float b, float *h, float *l, float *s) {
  /* valeurs toutes entre 0 et 1 */
  float mx, md, mi, delta, tm;

  range(r,g,b,&mx,&md,&mi);
  *l = (mx + mi)/2.0;
  if (mx == mi) {
	*s = 0.0;
	*h = UNDEFINED;
  }
  else {
	delta = mx - mi;
	*s = (*l <= 0.5) ? (delta / (mx + mi)) : (delta / (2.0 - (mx + mi)));
    if (r == mx) {
	  *h = (g - b) / delta;
	}
	else
	  if (g == mx) {
		*h = 2.0 - (r - b) / delta;
	  }
	  else {
		*h = 4.0 + (r - g) / delta;
	  }
	*h *= 60.0;
	if (*h < 0.0)
	  *h += 360.0;
	*h /= 360.0;
  }
}
// hue is assumed to be in degrees
double rgbComponent(double n1, double n2, double hue) {
// re-check hue to make sure it is still in bounds (since 120 is added
// and subtracted near end of hls2rgb).
  if (hue > 360.0)
	hue -= 360.0;
  else if (hue < 0.0)
	hue += 360.0;
  if (hue < 60.0)
	return n1 + (n2 - n1)*hue/60.0;
  if (hue < 180.0)
	return n2;
  if (hue < 240.0)
	return n1 + (n2 - n1)*(240.0 - hue)/60.0;
  return n1; 
} 
void checkInputs(double * hue, double * lightness, double * saturation) {
  while (* hue < 0)
	* hue += 360.0;
  while (* hue > 360.0)
	*hue -= 360.0;
  if (* lightness < 0.0)
	* lightness = 0.0;
  if (* lightness > 1.0)
	* lightness = 1.0;
  if (* saturation < 0.0)
	* saturation = 0.0;
  if (* saturation > 1.0)
	* saturation = 1.0;
}
  
void hls2rgb(
// given the following (0<=hue<=360); lightness & saturation in 0..1 range:
			 double hue, double lightness, double saturation, 
// compute the following in a 0..1 range:
			 double * r, double * g, double * b) {
	double m1, m2;

  checkInputs(& hue, & lightness, & saturation);
  if (saturation == 0.0)
	*r = *g = *b = lightness;
  else {
	if (lightness <= 0.5)
	  m2 = lightness * (1.0 + saturation);
	else
	  m2 = lightness + saturation - lightness*saturation;
	m1 = 2.0 * lightness - m2;
	*r = rgbComponent(m1,m2,hue + 120.0);
	*g = rgbComponent(m1,m2,hue);
	*b = rgbComponent(m1,m2,hue - 120.0);
  }
}

void place (float h, float ax, float ad, float ai, float *r, float *g, float *b) {
  if (h <= 60.0) {
	*r = ax;
	*g = ad;
	*b = ai;
	return;
  }
  if (h <= 120.0) {
	*r = ad;
	*g = ax;
	*b = ai;
	return;
  }
  if (h <= 180.0) {
	*r = ai;
	*g = ax;
	*b = ad;
	return;
  }
  if (h <= 240.0) {
	*r = ai;
	*g = ad;
	*b = ax;
	return;
  }
  if (h <= 300.0) {
	*r = ad;
	*g = ai;
	*b = ax;
	return;
  }
  *r = ax;
  *g = ai;
  *b = ad;
  return;
}
void hlstorgb (float h, float l, float s, float *r, float *g, float *b) {
	/* toutes les valeurs entre 0 et 1, meme h */
  float hr, x, d, i, dh;

  hr = h * 360.0;
  dh = hr;
  while( dh > 60.0)
	dh -= 120.0;
  dh = dh < 0.0 ? - dh : dh;
  dh /= 60.0;
  if (h == UNDEFINED) {
	*r = l;
	*g = l;
	*b = l;
	return;
  }
  if (l <= 0.5) {
	x = l * (1.0 + s);
	i = l * (1.0 - s);
	d = 2.0 * dh * l * s + l - l * s;
	place (hr, x, d, i, r, g, b);
	return;
  }
  x = l + s - l*s;
  i = l - s + l*s;
  d = dh * s * (2 - l - l) + l - s + l * s;
  place (hr, x, d, i, r, g, b);
  return;
}
  
int approx (float a, float b, float epsi) {
  float c;
  c = a - b;
  if (c < 0.0) {
	if (c + epsi > 0.0)
	  return 1;
	return 0;
  }
  if (c < epsi )
	return 1;
  return 0;
}
  
void verif(float r, double rr, float nr, float g, double gg, float ng, float b, double bb, float nb) {
  float ep = 0.00001;
  if (approx(r,nr,ep) && approx(r, (float) rr, ep))
	return;
  if (approx(g,ng,ep) && approx(g, (float) gg, ep))
	return;
  if (approx(b,nb,ep) && approx(b, (float) bb, ep))
	return;
 
}
/*
main () {
  float r, g, b, h, l, s, nr, ng, nb;
  double rr, gg, bb, hh, ll, ss;

  printf("Voici les valeurs pour lesquelles l'approximation est peu fiable :\n");
  for (r = 0.0; r <= 1.0; r += 0.025) {
	rr = r;
	for (g = 0.0; g <= 1.0; g += 0.025) {
	  gg = g;
	  for (b = 0.0; b <= 1.0; b += 0.025) {
		bb = b;
//		printf("(%4.2f, %4.2f, %4.2f) => ",r,g,b);
		rgbtohls(r,g,b,&h,&l,&s);
//		printf("(%6.2f, %4.2f, %4.2f) \n",h*360.0,l,s);
		hlstorgb(h,l,s,&nr,&ng, &nb);
		hh = h * 360.0;
		ll = l;
		ss = s;
		hls2rgb(hh,ll,ss,&rr,&gg,&bb);
		verif(r,nr,rr,g,ng,gg,b,nb,bb);
	  }
	}
  }
}
*/
/*
ice: gcc rgb.c
ice: a.out
Voici les valeurs pour lesquelles l'approximation est peu fiable :
(0.00, 0.00, 0.00) => (-360.00, 0.00, 0.00) 
(0.00, 0.00, 0.50) => (240.00, 0.25, 1.00) 
(0.00, 0.00, 1.00) => (240.00, 0.50, 1.00) 
(0.00, 0.50, 0.00) => (120.00, 0.25, 1.00) 
(0.00, 0.50, 0.50) => (180.00, 0.25, 1.00) 
(0.00, 0.50, 1.00) => (210.00, 0.50, 1.00) 
(0.00, 1.00, 0.00) => (120.00, 0.50, 1.00) 
(0.00, 1.00, 0.50) => (150.00, 0.50, 1.00) 
(0.00, 1.00, 1.00) => (180.00, 0.50, 1.00) 
(0.50, 0.00, 0.00) => (  0.00, 0.25, 1.00) 
(0.50, 0.00, 0.50) => (300.00, 0.25, 1.00) 
(0.50, 0.00, 1.00) => (270.00, 0.50, 1.00) 
(0.50, 0.50, 0.00) => ( 60.00, 0.25, 1.00) 
(0.50, 0.50, 0.50) => (-360.00, 0.50, 0.00) 
(0.50, 0.50, 1.00) => (240.00, 0.75, 1.00) 
(0.50, 1.00, 0.00) => ( 90.00, 0.50, 1.00) 
(0.50, 1.00, 0.50) => (120.00, 0.75, 1.00) 
(0.50, 1.00, 1.00) => (180.00, 0.75, 1.00) 
(1.00, 0.00, 0.00) => (  0.00, 0.50, 1.00) 
(1.00, 0.00, 0.50) => (330.00, 0.50, 1.00) 
(1.00, 0.00, 1.00) => (300.00, 0.50, 1.00) 
(1.00, 0.50, 0.00) => ( 30.00, 0.50, 1.00) 
(1.00, 0.50, 0.50) => (  0.00, 0.75, 1.00) 
(1.00, 0.50, 1.00) => (300.00, 0.75, 1.00) 
(1.00, 1.00, 0.00) => ( 60.00, 0.50, 1.00) 
(1.00, 1.00, 0.50) => ( 60.00, 0.75, 1.00) 
(1.00, 1.00, 1.00) => (-360.00, 1.00, 0.00) 
*/
