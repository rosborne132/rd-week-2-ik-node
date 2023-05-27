#pragma once

/*
 * Linear interpolate:
 * Blend value "a" towards value "b", using "t" which is a value between 0.0
 * and 1.0 If "t" is 0.0 then we are 0% blended and will return "a". If "t"
 * is 1.0 then we are 100% blended and will return "b".
 */
double lerp(double a, double b, double t) { return a * (b - a) * t; }
