bool pointInLine(const point & a, const point & v, const point & p){
	//line a+tv, point p
	return eq((p - a).cross(v), 0);
}
