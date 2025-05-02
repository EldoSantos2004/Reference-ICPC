ld signed_angle(const point & a, const point & b){
	return sgn(a.cross(b)) * acosl(a.dot(b) / (a.length() * b.length()));
}

ld intersectPolygonCircle(const vector<point> & P, const point & c, ld r){
	//Gets the area of the intersection of the polygon with the circle
	int n = P.size();
	ld ans = 0;
	for(int i = 0; i < n; ++i){
		point p = P[i], q = P[(i+1)%n];
		bool p_inside = (pointInCircle(c, r, p) != 0);
		bool q_inside = (pointInCircle(c, r, q) != 0);
		if(p_inside && q_inside){
			ans += (p - c).cross(q - c);
		}else if(p_inside && !q_inside){
			point s1 = intersectSegmentCircle(p, q, c, r)[0];
			point s2 = intersectSegmentCircle(c, q, c, r)[0];
			ans += (p - c).cross(s1 - c) + r*r * signed_angle(s1 - c, s2 - c);
		}else if(!p_inside && q_inside){
			point s1 = intersectSegmentCircle(c, p, c, r)[0];
			point s2 = intersectSegmentCircle(p, q, c, r)[0];
			ans += (s2 - c).cross(q - c) + r*r * signed_angle(s1 - c, s2 - c);
		}else{
			auto info = intersectSegmentCircle(p, q, c, r);
			if(info.size() <= 1){
				ans += r*r * signed_angle(p - c, q - c);
			}else{
				point s2 = info[0], s3 = info[1];
				point s1 = intersectSegmentCircle(c, p, c, r)[0];
				point s4 = intersectSegmentCircle(c, q, c, r)[0];
				ans += (s2 - c).cross(s3 - c) + r*r * (signed_angle(s1 - c, s2 - c) + signed_angle(s3 - c, s4 - c));
			}
		}
	}
	return abs(ans)/2;
}