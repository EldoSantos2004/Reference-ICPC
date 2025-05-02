pair<point, ld> getCircle(const point & m, const point & n, const point & p){
	//find circle that passes through points p, q, r
	point c = intersectLines((n + m) / 2, (n - m).perp(), (p + n) / 2, (p - n).perp());
	ld r = (c - m).length();
	return {c, r};
}