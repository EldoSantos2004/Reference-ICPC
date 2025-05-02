ld perimeter(vector<point> & P){
	int n = P.size();
	ld ans = 0;
	for(int i = 0; i < n; i++){
		ans += (P[i] - P[(i + 1) % n]).length();
	}
	return ans;
}

ld area(vector<point> & P){
	int n = P.size();
	ld ans = 0;
	for(int i = 0; i < n; i++){
		ans += P[i].cross(P[(i + 1) % n]);
	}
	return abs(ans / 2);
}