ld distancePointCircle(const point & c, ld r, const point & p){
	//point p, circle with center c and radius r
	return max((ld)0, (p - c).length() - r);
}