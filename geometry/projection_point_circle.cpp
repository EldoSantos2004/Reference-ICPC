point projectionPointCircle(const point & c, ld r, const point & p){
	//point p (outside the circle), circle with center c and radius r
	return c + (p - c).unit() * r;
}