vector<vector<point>> tangents(const point & c1, ld r1, const point & c2, ld r2, bool inner){
	//returns a vector of segments or a single point
	if(inner) r2 = -r2;
	point d = c2 - c1;
	ld dr = r1 - r2, d2 = d.norm(), h2 = d2 - dr*dr;
	if(eq(d2, 0) || le(h2, 0)) return {};
	point v = d*dr/d2;
	if(eq(h2, 0)) return {{c1 + v*r1}};
	else{
		point u = d.perp()*sqrt(h2)/d2;
		return {{c1 + (v - u)*r1, c2 + (v - u)*r2}, {c1 + (v + u)*r1, c2 + (v + u)*r2}};
	}
}