vector<point> intersectLineCircle(const point & a, const point & v, const point & c, ld r){
	//line a+tv, circle with center c and radius r
	ld h2 = r*r - v.cross(c - a) * v.cross(c - a) / v.norm();
	point p = a + v * v.dot(c - a) / v.norm();
	if(eq(h2, 0)) return {p}; //line tangent to circle
	else if(le(h2, 0)) return {}; //no intersection
	else{
		point u = v.unit() * sqrt(h2);
		return {p - u, p + u}; //two points of intersection (chord)
	}
}