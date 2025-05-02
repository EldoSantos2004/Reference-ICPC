bool pointInSegment(const point & a, const point & b, const point & p){
	//segment ab, point p
	return pointInLine(a, b - a, p) && leq((a - p).dot(b - p), 0);
}