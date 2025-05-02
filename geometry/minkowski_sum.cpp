vector<point> minkowskiSum(vector<point> A, vector<point> B){
	int na = (int)A.size(), nb = (int)B.size();
	if(A.empty() || B.empty()) return {};

	rotate(A.begin(), min_element(A.begin(), A.end()), A.end());
	rotate(B.begin(), min_element(B.begin(), B.end()), B.end());

	int pa = 0, pb = 0;
	vector<point> M;

	while(pa < na && pb < nb){
		M.push_back(A[pa] + B[pb]);
		ld x = (A[(pa + 1) % na] - A[pa]).cross(B[(pb + 1) % nb] - B[pb]);
		if(leq(x, 0)) pb++;
		if(geq(x, 0)) pa++;
	}

	while(pa < na) M.push_back(A[pa++] + B[0]);
	while(pb < nb) M.push_back(B[pb++] + A[0]);

	return M;
}
