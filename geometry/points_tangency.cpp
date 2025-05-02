pair<point, point> pointsOfTangency(const point & c, ld r, const point & p){
	//point p (outside the circle), circle with center c and radius r
	point v = (p - c).unit() * r;
	ld d2 = (p - c).norm(), d = sqrt(d2);
	point v1 = v * (r / d), v2 = v.perp() * (sqrt(d2 - r*r) / d);
	return {c + v1 - v2, c + v1 + v2};
}